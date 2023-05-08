#ifndef GameState_H_
#define GameState_H_

#include "item.h"
#include "Room.h"
#include "Character.h"
#include <iostream>
#include <string>
using namespace std;

// This the game and state of the game
class GameState
{
private:
    Character character;
    Room *currentRoom;
    std::map<string, Item> items;
    std::map<string, Room *> rooms;

public:
    GameState();
    void go(Direction direction);
    void setup();
    void createRooms();
    void createItems();
    void createCharacter(string name);
    void setDifficulty();
    string getTerminalOutput(); // TODO: implement this

    Room *getCurentRoom();
    vector<Item> *getAvailableItems();
};

#endif /*GameState_H_*/
