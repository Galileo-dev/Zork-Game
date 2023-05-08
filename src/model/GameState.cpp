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
    character = Character("Player", "This is you");
    createRooms();
    createItems();
}

string GameState::getReaction()
{
    return this->reaction;
}

void GameState::addReaction(string reaction)
{
    this->reaction += reaction + "\n";
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

void GameState::createRooms()
{
    // Todo: read from file
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i;

    a = new Room("a");
    b = new Room("b");
    c = new Room("c");
    d = new Room("d");
    e = new Room("e");
    f = new Room("f");
    g = new Room("g");
    h = new Room("h");
    i = new Room("i");

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
    // items["zork_slayer"] = Item("zork_slayer", "a sword buitl from the bones of a zork", 10, 400, true, false);
    // // a shield
    // items["zork_shield"] = Item("zork_shield", "a shield made from the skin of a zork", 20, 500, true, false);
    // // a key
    // items["zork_key"] = Item("zork_key", "a key made from the teeth of a zork", 30, 100, true, false);

    // create items
    // Room *a = this->rooms["a"];
    // add the sword to room a
    // a->addItem(&items["zork_slayer"]);
    // add the shield to room a

    // Room *b = &this->rooms["b"];
    // b->addItem(new Item("xx", 3, 33));
    // b->addItem(new Item("yy", 4, 44));
}

void GameState::go(Direction direction)
{
    // check if the room in the given direction is not null
    if (currentRoom->getRoom(direction) != NULL)
    {
        // set the current room to the room in the given direction
        currentRoom = currentRoom->getRoom(direction);
    }
    else
    {
        cout << "there is no room in that direction" << endl;
    }
}

Room *GameState::getCurentRoom()
{
    return this->currentRoom;
}

void GameState::createCharacter(string name, string description)
{
    this->character = Character(name, description);
}