#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <vector>
#include "Item.h"

using namespace std;

class Character
{
private:
		string description;
	vector<Item *> inventory;

public:
	Character() {}
	string getInventoryDescription();
	void addInventory(Item *Item);
	void removeInventory(Item *Item);
	vector<Item *> getInventory();
	Character(string name, string description);
	string getDescription();

	friend class GameModel;
	string name;
};

#endif /*CHARACTER_H_*/
