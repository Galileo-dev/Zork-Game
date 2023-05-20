#include <iostream>

#include "GameState.h"

using namespace std;

// #include "mainwindow.h"

// #include <QApplication>
// int main(int argc, char *argv[])
// {
// 	QApplication a(argc, argv);
// 	MainWindow w;
// 	w.show();
// 	return a.exec();
// }

GameState::GameState()
{
#ifdef DEBUG_LOG
    Character *character = new Character("Galileo", "a fierce zork hunter, travels on the back of camel named Steve moving from village to village slaying the helpless zorks and that is how he got his name, Zork Hunter.");
    this->setCharacter(character);
    this->setDifficulty(Difficulty::MEDIUM);
    this->addReaction("Welcome to the game, Galileo!");
    this->addReaction("You are " + this->character->getDescription());
    this->isGameStarted = true;

#endif

    createRooms();
    createItems();
}

void GameState::addReaction(string reaction)
{
    if (this->reaction == "")
    {
        this->reaction = reaction;
    }
    else
    {
        this->reaction += "\n" + reaction;
    }
}

void GameState::resetReaction()
{
    this->reaction = "";
}

void GameState::setup()
{
    createRooms();
    createItems();
}

void GameState::pickupItem(string itemName)
{
    character->addInventory(items[itemName]);
    ItemRoom *itemRoom = dynamic_cast<ItemRoom *>(currentRoom);
    if (itemRoom != nullptr)
    {
        itemRoom->removeItem(items[itemName]);
    }
    else
    {
        addReaction("This room does not contain any items.");
    }
}

void GameState::dropItem(string itemName)
{
    character->removeInventory(items[itemName]);

    ItemRoom *itemRoom = dynamic_cast<ItemRoom *>(currentRoom);
    if (itemRoom != nullptr)
    {
        itemRoom->addItem(items[itemName]);
    }
    else
    {
        addReaction("This room has special properties which cause any item on the ground to spontaniously combust and kill everything with 10 meters... you would'nt want that would you?");
    }
}

void GameState::createRooms()
{
    // Todo: read from file
    ItemRoom *a, *b, *c, *d, *e, *f, *g, *h, *i;

    a = new ItemRoom("a");
    b = new ItemRoom("b");
    c = new ItemRoom("c");
    d = new ItemRoom("d");
    e = new ItemRoom("e");
    f = new ItemRoom("f");
    g = new ItemRoom("g");
    h = new ItemRoom("h");
    i = new ItemRoom("i");

    //          (N, E, S, W)
    a->setExits(f, b, d, c);
    b->setExits(NULL, NULL, NULL, a);
    c->setExits(NULL, a, NULL, NULL);
    d->setExits(a, e, NULL, i);
    e->setExits(NULL, NULL, NULL, d);
    f->setExits(NULL, g, a, h);
    g->setExits(NULL, NULL, NULL, f);
    h->setExits(NULL, f, NULL, NULL);
    i->setExits(NULL, d, NULL, NULL);

    // store rooms in a map
    // could be useful for teleport or something
    this->rooms["a"] = a;
    this->rooms["b"] = b;
    this->rooms["c"] = c;
    this->rooms["d"] = d;
    this->rooms["e"] = e;
    this->rooms["f"] = f;
    this->rooms["g"] = g;
    this->rooms["h"] = h;
    this->rooms["i"] = i;

    // set current room to a
    // use a pointer
    // use this->rooms
    this->currentRoom = this->rooms["a"];
}

void GameState::createItems()
{
    // Todo: read from file

    // I want to create a master list of items
    // and then add them to the rooms

    // every item has a unique id
    // using camel case for the name

    // a sword
    items["zork_slayer"] = new Item("zork_slayer", "Zork Slayer", "a sword forged from the bones of a zork", 10, 400, true, false);
    // a shield
    items["zork_shield"] = new Item("zork_shield", "Zork Shield", "a shield crafted from the skin of a zork", 20, 500, true, false);
    // a key
    items["zork_key"] = new Item("zork_key", "Zork Key", "a key shaped from a tooth of a zork", 30, 100, true, false);

    ItemRoom *a = this->rooms["a"];
    a->addItem(items["zork_slayer"]);

    // ItemRoom *b = &this->rooms["b"];
    // b->addItem(new Item("xx", 3, 33));
    // b->addItem(new Item("yy", 4, 44));
}

void GameState::go(Direction direction)
{
    // check if the room in the given direction is not null
    // check if the current room is a ExitRoom
    ExitRoom *exitRoom = dynamic_cast<ExitRoom *>(currentRoom);
    if (exitRoom != nullptr)
    {

        if (exitRoom->getRoom(direction) != NULL)
        {
            // set the current room to the room in the given direction
            currentRoom = exitRoom->getRoom(direction);
        }
        else
        {
            cout << "there is no room in that direction" << endl;
        }
    }
}

void GameState::setCharacter(Character *character)
{
    this->character = character;
}

void GameState::setDifficulty(Difficulty difficulty)
{
    this->difficulty = difficulty;
}
