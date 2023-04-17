#ifndef GameState_H_
#define GameState_H_

#include "Command.h"
#include "Parser.h"
#include "item.h"
#include "Room.h"
#include <iostream>
#include <string>
using namespace std;

// This the game and state of the game
class GameState
{
private:
    int currentRoomIndex;
    vector<Item> items;
    vector<Room> rooms;

public:
    GameState();
    void go(Direction direction);
    void setup();
    void createRooms();
    void createItems();
    Room getCurentRoom();
    vector<Item> *getAvailableItems();
};

#endif /*GameState_H_*/
