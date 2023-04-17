#include "Command.h"
#include "Room.h"
#include <iostream>

/**
 * Create a command object. First and second word must be supplied, but
 * either one (or both) can be null. The command word should be null to
 * indicate that this was a command that is not recognised by this game.
 * objectives
 * - prove that the command is valid
 * - give suggestions
 * - give usage
 */
CommandManager::CommandManager()
{
	// COMMANDS:
	// go <direction>
	// take <item>
	// put <item>
	// quit
	// help
	this->currentCommand = {};
	this->validCommands = {"go", "take", "put", "quit", "help"};
}

void CommandManager::setCommand(string command)
{
	this->currentCommand = split(command, ' ');
}

/**
 * Return true if the command has a second word.
 */

void CommandManager::giveUsage()
{
	string commandWord = currentCommand[0];

	cout << "usage: ";
	if (commandWord.compare("go") == 0)
	{
		cout << "go <direction>" << endl;
	}
	else if (commandWord.compare("take") == 0)
	{
		cout << "take <item>" << endl;
	}
	else if (commandWord.compare("put") == 0)
	{
		cout << "put <item>" << endl;
	}
}

/**
 * Print out suggestions for the command.
 */
void CommandManager::giveSuggestions(Room *currentRoom)
{
	string commandWord = currentCommand[0];

	if (commandWord.compare("go") == 0)
	{
		cout << "direction: ";
		cout << currentRoom->exitString() << endl;
	}
	else if (commandWord.compare("take") == 0)
	{
		cout << "item: ";
		currentRoom->displayItem();
		cout << endl;
	}
}

/**
 * Return true if the command was not understood.
 */
bool validate()
{
}