#include "Character.h"
#include <algorithm>

Character::Character(string name, string description)
{
  this->name = name;
  this->description = description;
}

// Todo(): find a way to delete the item after adding to inventory
void Character::addInventory(Item *item)
{
  inventory.push_back(item);
}
void Character::removeInventory(Item *item)
{
  auto it = std::find(inventory.begin(), inventory.end(), item);
  if (it != inventory.end())
  {
    inventory.erase(it);
  }
  else
  {
    cout << "Item not found in inventory" << endl;
  }
}

vector<Item *> Character::getInventory()
{
  return inventory;
}

string Character::getDescription()
{
  // string ret = this->description;
  // ret += "\n Item list:\n";
  // for (vector<Item>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
  //   ret += "\t" + (*i).getLongDescription() + "\n";
  // return ret;
  return description;
}

string Character::getInventoryDescription()
{
  string description = "Inventory: \n";
  for (auto item : inventory)
  {
    description += "    " + item->getLongDescription() + "\n";
  }
  description += "\n";

  return description;
}
