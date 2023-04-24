#ifndef GameCLI_H_
#define GameCLI_H_

#include <iostream>
#include <string>
#include "../Utils.h"
using namespace std;

class GameCLI
{
private:
	CommandManager commandManager;
	void printWelcome();
	void printItems();
	void printHelp();
	bool processCommand(CommandManager command);
	GameModel *gameState;
	string go(string direction);

public:
	GameCLI();
	void start();
	void setup(GameModel *gameModel);
	void update(ACTION action);
};

#endif /*GameCLI_H_*/
