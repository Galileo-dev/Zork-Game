#include "Character.h"

Character::Character(string, string)
{
  this->name = name;
  this->description = description;
}

// Todo(): find a way to delete the item after adding to inventory
void Character::addInventory(Item &item)
{
  inventory.push_back(item);
}

vector<Item> Character::getInventory()
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
