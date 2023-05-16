#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <vector>
#include "../model/GameState.h"
#include "../model/Enum.h"
#include "Enum.h"
#include <unordered_map>
#include <tuple>

using namespace std;

class Command
{
private:
	std::vector<string> currentCommand;
	std::vector<string> validCommands;
	string currentErrorMessage;

public:
	Command(string command);
	std::vector<string> arguments;
	string getCommandWord();
	bool isUnknown();
	bool hasSecondWord();
	void giveSuggestions(GameState *gameState);
	string getErrorMessage();
	void giveUsage();
	bool validate();

	// parse returns [Action, params]
	tuple<Action, std::unordered_map<std::string, std::string>> parse();
};

#endif /*COMMAND_H_*/
