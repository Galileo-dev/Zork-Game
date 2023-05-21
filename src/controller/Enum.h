#ifndef ENUMD_H
#define ENUMD_H

enum class COMMAND_ERROR
{
    InvalidCommand,  // the entered command is not a known.
    InvalidArguments // the entered command is known but the argument is invalid.
};

enum class UI_INPUT
{
    StartGame,      // start a new game with given difficulty and player name (params: difficulty, player_name)
    CommandEntered, // parse a command that was entered into the ui and update game state accordingly  (params: input)
    PickupItem,     // pick up an item (params: item_name)
    DropItem,       // drop an item (params: item_name)
    Go,             // go in a direction (params: direction)
    UseItem,        // use an item. i.e. consume/activate (params: item_name)
    SolveRiddle,
    Attack,
    Quit,
    Help,
    Look
};

#endif // ENUM_D
