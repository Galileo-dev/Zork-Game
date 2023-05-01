enum Action
{
    StartGame,    // start a new game with given difficulty and player name (params: difficulty, player_name)
    ParseCommand, // parse a command and update game state accordingly  (params: input)
    PickupItem,   // pick up an item (params: item_name)
    DropItem,     // drop an item (params: item_name)
    Go,           // go to a room (params: room_name)
    UseItem,      // use an item (params: item_name)
    Attack,       // attack an enemy (params: enemy_name)
    Quit          // quit the game (params: none)
};