#include "Game.h"
#include "GameCLI.h"
#include <iostream>
#include <string>

using namespace std;

// void GameCLI::setup(GameModel *gameModel)
// {
// 	this->gameState = gameModel;
// }
GameCLI::GameCLI()
{
}

void GameCLI::start()
{
	cout << "start" << endl;

	bool isFinished = false;
	while (!isFinished)
	{
		cout << ">";

		// wait for input
		string input;
		getline(cin, input);

		// clear console
		system("clear");
	}
}

void GameCLI::update(const GameModel *gameModel)
{
}

/**
 *  Main play routine.  Loops until end of play.
 */
// void GameCLI::start()
// {
// 	cout << "start" << endl;
// 	cout << "info for help" << endl;
// 	cout << endl;
// 	cout << this->gameState->getCurentRoom()->longDescription() << endl;

// 	bool finished = false;
// while (!finished)
// {
// 	cout << ">";

// 	// temp string
// 	string input;
// 	getline(cin, input);

// 	// create command object
// 	// CommandManager command = CommandManager::fromString(input);

// 	// validate command
// 	if (!command.validate())
// 	{
// 		cout << "invalid input" << endl;
// 		continue;
// 	}
// }
// cout << endl;
// cout << "goodbye ;)" << endl;
// }

// void GameCLI::printWelcome()
// {
// 	cout << "start" << endl;
// 	cout << "info for help" << endl;
// 	cout << endl;

// 	Room *currentRoom = gameState->getCurentRoom();
// 	cout << currentRoom->longDescription() << endl;
// }

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the Game game, true is returned, otherwise false is
 * returned.
 */
// bool GameCLI::processCommand(CommandManager command)
// {
// 	if (command.isUnknown())
// 	{
// 		cout << "invalid input" << endl;
// 		return false;
// 	}

// 	string commandWord = command.getCommandWord();
// 	if (commandWord.compare("info") == 0)
// 		printHelp();

// 	else if (commandWord.compare("map") == 0)
// 	{
// 		cout << "[h] --- [f] --- [g]" << endl;
// 		cout << "         |         " << endl;
// 		cout << "         |         " << endl;
// 		cout << "[c] --- [a] --- [b]" << endl;
// 		cout << "         |         " << endl;
// 		cout << "         |         " << endl;
// 		cout << "[i] --- [d] --- [e]" << endl;
// 	}

// 	else if (commandWord.compare("go") == 0)
// 		// go(command);

// 		else if (commandWord.compare("take") == 0)
// 		{
// 			if (!command.hasSecondWord())
// 			{
// 				cout << "incomplete input" << endl;
// 			}
// 			else if (command.hasSecondWord())
// 			{
// 				// cout << "you're trying to take " + command.getSecondWord() << endl;
// 				// int location = currentRoom->isItemInRoom(command.getSecondWord());
// 				if (location < 0)
// 					cout << "item is not in room" << endl;
// 				else
// 					cout << "item is in room" << endl;
// 				cout << "index number " << +location << endl;
// 				cout << endl;
// 				cout << currentRoom->longDescription() << endl;
// 			}
// 		}

// 	else if (commandWord.compare("put") == 0)
// 	{
// 	}
// 	/*
// 	{
// 	if (!command.hasSecondWord()) {
// 		cout << "incomplete input"<< endl;
// 		}
// 		else
// 			if (command.hasSecondWord()) {
// 			cout << "you're adding " + command.getSecondWord() << endl;
// 			itemsInRoom.push_Back;
// 		}
// 	}
// */
// 	else if (commandWord.compare("quit") == 0)
// 	{
// 		if (command.hasSecondWord())
// 			cout << "overdefined input" << endl;
// 		else
// 			return true; /**signal to quit*/
// 	}
// return false;
// }
// /** COMMANDS **/
// void GameCLI::printHelp()
// {
// 	cout << "valid inputs are; " << endl;
// 	// parser.showCommands();
// }