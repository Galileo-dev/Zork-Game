#ifndef GameCLI_H_
#define GameCLI_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include <iostream>
#include <string>
using namespace std;

class GameCLI
{
private:
	CommandManager commandManager;
	void printWelcome();
	void printItems();
	void printHelp();
	bool processCommand(CommandManager command);
	GameState *gameState;

public:
	GameCLI();
	void start();
	void setup();
	string go(string direction);
};

#endif /*GameCLI_H_*/
