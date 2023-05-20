#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "Item.h"
#include "Enum.h"
#include "Character.h"

using namespace std;
using std::vector;

class IRoom
{
public:
	// all rooms exits
	virtual void setDescription(string description) = 0;
	virtual string longDescription() = 0;
	virtual string const shortDescription() = 0;
	virtual ~IRoom() {}

private:
	string description();
};

class Room : public IRoom
{
public:
	Room(){};
	Room(string description);
	void setDescription(string description) override;
	string longDescription() override;
	string const shortDescription() override;

private:
	string description;
};

class ExitRoom
{
public:
	void setExits(IRoom *north, IRoom *east, IRoom *south, IRoom *west);
	IRoom *getRoom(Direction direction);
	string exitString();
	void lockAllExits();
	void unlockAllExits();

private:
	map<Direction, IRoom *> exits;
	map<Direction, IRoom *> lockedExits;
};

class StoryRoom
{
public:
	string getStoryEvent();
	void setStoryEvent(string storyEvent);

private:
	string storyEvent;
};

class ItemRoom : public Room, public ExitRoom, public StoryRoom
{
public:
	ItemRoom(string description);
	int numberOfItems();
	void addItem(Item *inItem);
	void removeItem(Item *inItem);
	string displayItem();
	int isItemInRoom(string inString);
	string longDescription();
	string const shortDescription();
	vector<Item *> getItems();

private:
	vector<Item *> itemsInRoom;
	string description;
};

class RiddleRoom : public ItemRoom
{
public:
	bool isSolved = false;
	RiddleRoom(string description);
	string getRiddle();
	void setRiddle(string riddle);
	void setAnswer(string answer);
	bool checkAnswer(string answer);

private:
	string riddle;
	string answer;
};
#endif
