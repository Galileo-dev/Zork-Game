#ifndef GameState_H_
#define GameState_H_

#include "Item.h"
#include "Room.h"
#include "Character.h"
#include <iostream>
#include <string>
using namespace std;

// This the game and state of the game
class GameState
{
private:
    Character *character = nullptr;
    Room *currentRoom;
    std::map<string, Item *> items;
    std::map<string, Room *> rooms;
    string reaction;
    bool isGameStarted = false;
    Difficulty difficulty;
    // friendship makes the dream work
    friend class GameModel;

public:
    GameState();
    void setCharacter(Character *character);
    void setDifficulty(Difficulty difficulty);

    // not need as we have friends now!
    // string getReaction();
    // Character *getCharacter();
    // Room *getCurentRoom();

    void addReaction(string reaction);
    void resetReaction();
    void go(Direction direction);
    void setup();
    void createRooms();
    void createItems();
    void pickupItem(string itemName);
    void dropItem(string itemName);
    void setDifficulty();
    string getTerminalOutput(); // TODO: implement this

    vector<Item> *getAvailableItems();
};

#endif /*GameState_H_*/
