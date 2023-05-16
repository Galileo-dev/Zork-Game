#include "Command.h"
#include "CommandUtils.h"
#include "../model/Room.h"

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
Command::Command(string command)
{
	// COMMANDS:
	// go <direction>
	// take <item>
	// put <item>
	// quit
	// help
	this->currentCommand = split(command, ' ');
	this->validCommands = {"go", "take", "put", "quit", "help"};
}

/**
 * Return true if the command has a second word.
 */

void Command::giveUsage()
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
void Command::giveSuggestions(GameState *gameState)
{
	string commandWord = currentCommand[0];

	Room *currentRoom = gameState->getCurentRoom();
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
 * Return an action based on the command.
 */
tuple<Action, std::unordered_map<std::string, std::string>> Command::parse()
{
	string commandWord = currentCommand[0];
	std::unordered_map<std::string, std::string> params;
	Action action = Action::InvalidCommand;

	if (commandWord.compare("go") == 0)
	{
		// expects a direction
		// if (currentCommand.size() < 2)
		// {
		// 	action = Action::InvalidArguments;
		// 	params["error"] = "Go where?";
		// }

		action = Action::Go;

		params["direction"] = currentCommand[1];
	}
	else if (commandWord.compare("take") == 0)
	{
		action = Action::PickupItem;
		params["item"] = currentCommand[1];
	}
	else if (commandWord.compare("put") == 0)
	{
		action = Action::PickupItem;
		params["item"] = currentCommand[1];
	}
	else if (commandWord.compare("quit") == 0)
	{
		action = Action::Quit;
	}
	else if (commandWord.compare("help") == 0)
	{
		action = Action::Help;
	}
	else if (commandWord.compare("look") == 0)
	{
		action = Action::Look;
	}

	// if (!command.validate())
	// {
	// 	// formulate error as a string
	// 	std::string error = "Invalid command: " + params["input"];
	// 	error += command.getErrorMessage();
	// 	params = {{"error", error}};
	// }

	return std::make_tuple(action, params);
}

string Command::getErrorMessage()
{
	return currentErrorMessage;
}