
#define CHARACTER_H_
#include "GameState.h"

#include <string>
using namespace std;
#include <vector>
using std::vector;

class Character
{
private:
	string name;
	string description;
	vector<Item> inventory;

public:
	void addInventory(Item &Item);
	vector<Item> getInventory();
	Character(string name = "player", string description = "You are the player");
	string getDescription();
};
