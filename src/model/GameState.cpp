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

void GameState::pickupItem(string itemName)
{
    character->addInventory(items[itemName]);
    ItemRoom *itemRoom = dynamic_cast<ItemRoom *>(currentRoom);
    if (itemRoom != nullptr)
    {
        itemRoom->removeItem(items[itemName]);
        addReaction("You picked up " + items[itemName]->getDisplayName() + " - " + items[itemName]->getDescription());
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
        addReaction("You drop " + items[itemName]->getDisplayName() + "... " + "why did you drop that??? it's not like there is a weight system implemented. hey you pick that back up right now!");
    }
    else
    {
        addReaction("This room has special properties which cause any item on the ground to spontaneously combust and kill everything with 10 meters... you would'nt want that would you?");
    }
}

void GameState::createRooms()
{
    // Todo: read from file
    ItemRoom *a, *b, *c;
    RiddleRoom *d, *e, *f, *g, *h, *i;

    a = new ItemRoom("a");
    b = new ItemRoom("b");
    c = new ItemRoom("c");
    d = new RiddleRoom("d");
    e = new RiddleRoom("e");
    f = new RiddleRoom("f");
    g = new RiddleRoom("g");
    h = new RiddleRoom("h");
    i = new RiddleRoom("i");

    //          (N, E, S, W)
    // main branch
    // =============== EXITS ===============
    a->setExits(b, NULL, NULL, NULL);
    b->setExits(c, NULL, a, NULL);
    c->setExits(NULL, d, b, g);

    //================ Story ===============
    string storyEvent = "";
    storyEvent += "<Dev>: Welcome to the tutorial. I will be your friend for this section of the game. you may leave at any time by pressing alt+f4. I will be sad but I will understand.\n";
    storyEvent += "<Dev>: To start you can move around the map by typing go north, go south, go east, or go west. You can also type look to see what is in the room you are in.\n";
    storyEvent += "<Dev>: if you're on the GUI you can click the buttons to move around and look at the room.\n";
    storyEvent += "<Dev>: that's all the help you get for now. good luck.\n";
    a->setStoryEvent(storyEvent);

    storyEvent.clear();
    storyEvent += "<Dev>: So you're probably wondering what this game is. you probably thought to yourself this is going to be a sick adventure game. with a fully-fledged combat system and a deep story. given you are the \"Zork Hunter\" and all. \n";
    storyEvent += "<Dev>: however I did some thinking and I decided that fighting is sick and twisted and resolves nothing. it solves nothing other than the problem of the other person being alive. \n";
    storyEvent += "<Dev>: so instead you're going to enjoy a nice relaxing riddle game. that's right. you're going to solve riddles and have fun doing it. \n";
    storyEvent += "<Dev>: that sword you picked up, the \"Zork Slayer\" is actually a trap. your difficulty was increased to Cursed because that sword is cursed \n";
    b->setStoryEvent(storyEvent);

    storyEvent.clear();
    storyEvent += "<Dev>: you're probably wondering why I'm doing this. I'm doing this because I can. I'm the developer and I can do whatever I want. \n";
    storyEvent += "<Dev>: I'll give the basic gist of the story. you're a Zork hunter but... you are not killing any zorks ever! as you are a Buddhist monk training in the  highest of Cambodia, Cardamon\n";
    storyEvent += "<Dev>: you are about to take your final test to become a Zork master. you must complete a dungeon \n";
    storyEvent += "<Dev>: that's right a dungeon. of riddles!!! \n ";
    storyEvent += "<Dev>: You must complete two branches. one of friendship and compassion (east). the other of dread and misery (west)\n";
    storyEvent += "<Dev>: You have 10 minutes to two branches starting......... now! \n";
    c->setStoryEvent(storyEvent);
    // branch 1

    // =============== EXITS ===============

    // friendship and compassion
    d->setExits(NULL, e, NULL, NULL);
    e->setExits(NULL, f, NULL, d);
    f->setExits(NULL, NULL, NULL, e);

    //================ Story ===============
    storyEvent.clear();
    storyEvent += "<Dev>: you have entered the branch of friendship and compassion. you must complete this branch in 5 minutes. starting now! \n";
    d->setStoryEvent(storyEvent);
    d->setRiddle("I'm a C++ class that can access both private and protected members of another class, who am I");
    d->setAnswer("friend");

    storyEvent.clear();
    storyEvent += "<Dev>: Turns out your a c++ programmer after all?\n";
    storyEvent += "<Dev>: These will get progressively harder!\n";
    e->setStoryEvent(storyEvent);
    e->setRiddle(R"(I'm there in laughter, through every cheer,\n
                In moments of sorrow, I'll be near.\n
                An intangible force that holds hearts tight,\n
                In this puzzle of life, I am the light.\n
                Who am I?)");

    e->setAnswer("friendship");

    storyEvent.clear();
    storyEvent += "<Dev>: so you're not so heartless after all?\n";
    storyEvent += "<Dev>: This next one will be a really tough!\n";
    f->setStoryEvent(storyEvent);
    f->setRiddle(R"(A tender touch, a caring gaze,\n
                In hearts it blooms, in countless ways.\n
                It lifts the weary, heals the soul,\n
                What is this gift that makes us whole?\n)");
    f->setAnswer("compassion");

    // dread and misery
    g->setExits(NULL, NULL, NULL, h);
    h->setExits(NULL, g, NULL, i);
    i->setExits(NULL, h, NULL, NULL);

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
    // a cake
    items["zork_cake"] = new Item("zork_cake", "Zork Cake", "a cake made from the flesh of a zork", 40, 200, true, false);
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

void GameState::solveRiddle(string answer)
{
    // check if the current room is a RiddleRoom
    RiddleRoom *riddleRoom = dynamic_cast<RiddleRoom *>(currentRoom);
    if (riddleRoom != nullptr)
    {
        // check if the answer is correct
        if (riddleRoom->checkAnswer(answer))
        {
            // set the current room to the room in the given direction
            riddleRoom->isSolved = true;
            riddleRoom->unlockAllExits();
            addReaction("RIDDLE-SYSTEM: correct answer");

            // give the player a reward
            if (currentRoom == rooms["f"])
            {
                addReaction("RIDDLE-SYSTEM: you have been given a reward for solving the riddle");
                riddleRoom->addItem(items["zork_shield"]);
                addReaction("<Dev>: you should probably pick that up, but hey don't listen to me. I'm just the developer who made the game");
            }
            else if (currentRoom == rooms["i"])
            {
                addReaction("RIDDLE-SYSTEM: you have been given a reward for solving the riddle");
                riddleRoom->addItem(items["zork_key"]);
                addReaction("<Dev>: you should probably pick that up, but hey don't listen to me. I'm just the developer who made the game");
            }
        }
        else
        {
            tries--;
            addReaction("RIDDLE-SYSTEM: wrong answer, you have " + to_string(tries) + " tries left");
            if (tries == 0)
            {
                addReaction("RIDDLE-SYSTEM: you have failed the riddle, you have been teleported to the start");
                addReaction("RIDDLE-SYSTEM: teleportation failed...");
                addReaction("<Dev>: huh the teleportation failed, what a shame. well you have 3 more tries ");
            }

            if (tries == -1)
            {
                addReaction("RIDDLE-SYSTEM: robooting teleportation system...");
            }
            if (tries == -2)
            {
                addReaction("RIDDLE-SYSTEM: teleportation system rebooted");
            }
            if (tries == -3)
            {
                addReaction("RIDDLE-SYSTEM: unauthorized tries detected, teleporting to start");
                addReaction("<Dev>: must have just been a dud");
                currentRoom = rooms["a"];
            }
        }
    }
}

void GameState::checkGameCompleted()
{

    if (character->getInventory().size() == 3)
    {
        addReaction("GAME-SYSTEM: you have completed the game");
        addReaction("GAME-SYSTEM: you have been given a reward for completing the game");
        character->addItem(items["zork_cake"]);
        addReaction("<Dev>: eww, why would anyone want to eat that?");
    }
}