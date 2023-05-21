#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <vector>
#include "Item.h"

using namespace std;

class Character
{

public:
	Character() {}
	Character(string name, string description);

	// inventory system
	string getInventoryDescription();
	void addInventory(Item *Item);
	vector<Item *> getInventory();
	void removeInventory(Item *Item);
	string getDescription();

	// told you I have friends
	friend class GameModel;

private:
	string description;
	vector<Item *> inventory;
	string name;
};

#endif /*CHARACTER_H_*/
