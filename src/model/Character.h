#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <vector>
#include "Item.h"

using namespace std;

class Character
{
private:
	string name;
	string description;
	vector<Item> inventory;

public:
	Character() {}
	void addInventory(Item &Item);
	vector<Item> getInventory();
	Character(string, string);
	string getDescription();
};

#endif /*CHARACTER_H_*/
