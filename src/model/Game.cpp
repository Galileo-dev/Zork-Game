#include <iostream>

#include "Game.h"
#include "Direction.h"

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
    createRooms();
    createItems();
}

GameState::setup()
{
    createRooms();
    createItems();
}

void GameState::createRooms()
{
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

    currentRoom = a; // start game at room a
}

void GameState::createItems()
{
    a->addItem(new Item("x", 1, 11));
    a->addItem(new Item("y", 2, 22));
    b->addItem(new Item("xx", 3, 33));
    b->addItem(new Item("yy", 4, 44));
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

Room GameState::getCurentRoom()
{
    return this->rooms.at(this->currentRoomIndex);
}