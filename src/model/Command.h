#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <vector>
#include "Room.h"
#include "CommandUtils.h"

using namespace std;

class CommandManager
{
private:
	std::vector<string> currentCommand;
	std::vector<string> validCommands;

public:
	void setCommand(string command);
	CommandManager();
	std::vector<string> arguments;
	string getCommandWord();
	bool isUnknown();
	bool hasSecondWord();
	void giveSuggestions(Room *currentRoom);
	void giveUsage();
	bool validate();
};

#endif /*COMMAND_H_*/
