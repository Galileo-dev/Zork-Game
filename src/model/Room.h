#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
#include "Direction.h"

using namespace std;
using std::vector;

class Room
{

private:
	string description;
	map<Direction, Room *> exits;
	vector<Item> itemsInRoom;

public:
	int numberOfItems();
	Room(string description);
	void setExits(Room *north, Room *east, Room *south, Room *west);
	string const shortDescription();
	string longDescription();
	Room *getRoom(Direction direction);
	void addItem(Item *inItem);
	string displayItem();
	int isItemInRoom(string inString);
	string exitString();
	void removeItemFromRoom(int location);
};

#endif
