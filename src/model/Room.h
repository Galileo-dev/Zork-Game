#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "Item.h"
#include "Enum.h"

using namespace std;
using std::vector;

class IRoom
{
public:
	// all rooms exits
	virtual void Room(string description) = 0;
	virtual string const shortDescription() = 0;
	virtual string longDescription() = 0;
	virtual ~IRoom() {}

private:
	string description;
};

class ExitRoom
{
public:
	void setExits(IRoom *north, IRoom *east, IRoom *south, IRoom *west);
	IRoom *getRoom(Direction direction);
	string exitString();

private:
	map<Direction, IRoom *> exits;
};

class ItemRoom : public IRoom, public ExitRoom

{
public:
	int numberOfItems();
	void addItem(Item *inItem);
	void removeItem(Item *inItem);
	string displayItem();
	int isItemInRoom(string inString);

private:
	vector<Item *> itemsInRoom;
};

#endif
