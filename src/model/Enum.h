#ifndef ENUM_H
#define ENUM_H

#include <unordered_map>
#include <string>

enum class Action
{
    StartGame,      // start a new game with given difficulty and player name (params: difficulty, player_name)
    CommandEntered, // parse a command and update game state accordingly  (params: input)
    PickupItem,     // pick up an item (params: item_name)
    DropItem,       // drop an item (params: item_name)
    Go,             // go to a room (params: room_name)
    UseItem,        // use an item (params: item_name)
    Attack,         // attack an enemy (params: enemy_name)
    Quit,           // quit the game (params: none)
    Help,           // print help message (params: none)
    InvalidCommand, // invalid command (params: command)
    Look,           // look around the room (params: none)
    ShowInventory,  // show inventory (params: none)
    SolveRiddle     // solve a riddle (params: riddle_answer)

};

enum Direction
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

enum Difficulty
{
    EASY,
    NORMAL,
    HARD,
    CURSED
};

inline Difficulty stringToDifficulty(const std::string &str)
{
    if (str == "easy")
    {
        return Difficulty::EASY;
    }
    else if (str == "medium")
    {
        return Difficulty::NORMAL;
    }
    else if (str == "hard")
    {
        return Difficulty::HARD;
    }
    else
    {
        // handle invalid input
        return Difficulty::EASY;
    }
}

#endif // ENUM_H