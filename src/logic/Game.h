#ifndef Game_H_
#define Game_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include <iostream>
#include <string>
using namespace std;

class Game {
private:
	Parser parser;
	Room *currentRoom;
	void createRooms();
	void printWelcome();
	bool processCommand(Command command);
	void printHelp();
	void goRoom(Command command);
    void createItems();
    void displayItems();

public:
	Game();
	void play();
	string go(string direction);
};

#endif /*Game_H_*/
