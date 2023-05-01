// ============================================================================
// Entity Component System (ECS) implementation
// Based on https://austinmorlan.com/posts/entity_component_system/
// Author:  F. Barrett
// ============================================================================
#include <cstdint>
#include <bitset>
#include <queue>
#include <assert.h>
#include <set>

// entity types
using Entity = std::uint32_t;

const Entity MAX_ENTITIES = 5000; // Maximum number of entities

// component types

using ComponentType = std::uint8_t;

const ComponentType MAX_COMPONENTS = 32; // Maximum number of components per entity

// use a bit to represent each component type
using Signature = std::bitset<MAX_COMPONENTS>; // Create a bitset with a size of MAX_COMPONENTS

// Entity Manager
// Manages all entities, component types, and component data
class EntityManager
{
private:
    std::queue<Entity> mAvailableEntities{}; // Queue of available entities

    std::array<Signature, MAX_ENTITIES> mSignatures{}; // Array of signatures where each index represents an entity and the bitset represents all components associated with that entity

    uint32_t mLivingEntityCount{}; // Number of living entities - used to keep limits on how many exist
public:
    EntityManager()
    {
        // Initialize the queue
        for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
        {
            mAvailableEntities.push(entity);
        }
    }

    // Create a new entity
    Entity CreateEntity()
    {
        assert(mLivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

        // Take an ID from the front of the queue
        Entity id = mAvailableEntities.front();
        mAvailableEntities.pop();
        ++mLivingEntityCount;
        return id;
    }

    void DestroyEntity(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        // Invalidate the destroyed entity's signature
        mSignatures[entity].reset();

        // Put the destroyed ID at the back of the queue so it can be reused
        mAvailableEntities.push(entity);
        --mLivingEntityCount;
    }

    void SetSignature(Entity entity, Signature signature)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        // Set the signature for this entity
        mSignatures[entity] = signature;
    }
};

class IComponentArray
{

public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(Entity entity) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray
{
private:
    // The packed array of components (of generic type T),
    // set to a specified maximum amount, matching the maximum number
    // of entities allowed to exist simultaneously, so that each entity
    // has a unique spot.
    std::array<T, MAX_ENTITIES> mComponentArray;

    // Map from an entity ID to an array index.
    // Entity -> Index
    std::unordered_map<Entity, size_t> mEntityToIndexMap;

    // Map from an array index to an entity ID.
    // Index -> Entity
    std::unordered_map<size_t, Entity> mIndexToEntityMap;

    // Total size of valid entries in the array.
    size_t mSize;

public:
    void InsertData(Entity entity, T component)
    {

        assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

        // Put new entry at end and update the map
        size_t newIndex = mSize;
        mEntityToIndexMap[entity] = newIndex;
        mIndexToEntityMap[newIndex] = entity;
        mComponentArray[newIndex] = component;
        mSize++;
    }

    void RemoveData(Entity entity)
    {
        // check that the entity exists
        assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Trying to remove an Entity that does'nt exist!");

        // find the location in the entity to index map
        size_t indexOfOldEntity = mEntityToIndexMap[entity];

        // copy the component at the end of the array to the location of the component being removed
        mComponentArray[indexOfOldEntity] = mComponentArray[mSize - 1];

        // take the last element and move it to this location
        Entity LastIndexEntity = mIndexToEntityMap[mSize - 1];

        // update the mapping
        mEntityToIndexMap[LastIndexEntity] = indexOfOldEntity;
        mIndexToEntityMap[indexOfOldEntity] = LastIndexEntity;

        // delete the last element in the array
        mEntityToIndexMap.erase(entity);
        mIndexToEntityMap.erase(indexOfOldEntity);

        // recover size
        mSize--;
    }

    T &GetData(Entity entity)
    {
        // check if the component is in the array
        assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Trying to get a non-existant component");

        // return a reference to the entity component
        return mComponentArray[mEntityToIndexMap[entity]];
    }

    void EntityDestroyed(Entity entity) override
    {
        if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end())
        {
            // dispose of the entity data
            RemoveData(entity);
        }
    }
};

class ComponentManager
{
private:
    // map from string pointer to component type
    std::unordered_map<const char *, ComponentType> mComponentTypes{};

    // map from string pointer to component array
    // we are going to use a shared pointer as component array should'nt be copied
    std::unordered_map<const char *, std::shared_ptr<IComponentArray>> mComponentArrays{};

    // the component type to be assigned to the next registered component
    ComponentType mNextComponentType{};

    // Function to give us a staticly casted pointer to the ComponentArray.
    template <typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray()
    {
        const char *typeName = typeid(T).name();

        assert(mComponentArrays.find(typeName) != mComponentArrays.end() && "Component not registered before use");

        return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
    }

public:
    template <typename T>
    void RegisterComponent()
    {
        const char *typeName = typeid(T).name();
        // check if type name is already in the registered components
        assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component cannot be registered more then once");

        // register
        mComponentTypes.insert({typeName, mNextComponentType});
        // make a shared pointer to for ComponentArray storing this type
        mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
        // increment so next component type is different
        mNextComponentType++;
    }

    template <typename T>
    ComponentType GetComponentType()
    {
        const char *typeName = typeid(T).name();

        // check it exists first
        assert(mComponentTypes.find(typeName) != mComponentTypes.end());

        // return this components type
        return mComponentTypes[typeName];
    }

    template <typename T>
    void AddComponent(Entity entity, T component)
    {
        // Add a component to an entity
        GetComponentArray<T>()->InsertData(entity, component);
    }

    template <typename T>
    void RemoveComponent(Entity entity)
    {
        GetComponentArray<T>()->RemoveData(entity);
    }

    template <typename T>
    T &GetComponent(Entity entity)
    {
        return GetComponentArray<T>()->GetData(entity);
    }

    void EntityDestroyed(Entity entity)
    {
        // notify each component an entity an entity has been destroyed
        for (auto const &pair : mComponentArrays)
        {
            auto const &component = pair.second;

            component->EntityDestroyed(entity);
        }
    }
};

// A system is any functionality that iterates upon a list of entities with a certain signature of components.
class System
{
public:
    std::set<Entity> mEntities;
};
