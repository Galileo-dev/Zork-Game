
#define CHARACTER_H_
#include "GameState.h"

#include <string>
using namespace std;
#include <vector>
using std::vector;

class Character
{
private:
	string description;
	vector<string> itemsInCharacter;

public:
	void addItems(string Item);

public:
	Character(string description);
	string shortDescription();
	string longDescription();
};
