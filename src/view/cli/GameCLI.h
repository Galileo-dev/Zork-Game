#ifndef GameCLI_H_
#define GameCLI_H_

#include <iostream>
#include <string>
#include "../../model/GameState.h"
using namespace std;

class GameCLI
{
private:
public:
	GameCLI();
	void start();
	void update(const GameState *gameModel);
};

#endif /*GameCLI_H_*/
