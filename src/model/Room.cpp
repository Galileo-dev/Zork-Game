#include "Room.h"
#include <algorithm>
Room::Room(string description)
{
    this->description = description;
}

std::string toString(Direction direction)
{
    switch (direction)
    {
    case Direction::NORTH:
        return "north";
        break;
    case Direction::EAST:
        return "east";
        break;
    case Direction::SOUTH:
        return "south";
        break;
    case Direction::WEST:
        return "west";
        break;
    }
    return "invalid_direction: this should never happen";
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west)
{
    if (north != NULL)
        exits[NORTH] = north;
    if (east != NULL)
        exits[EAST] = east;
    if (south != NULL)
        exits[SOUTH] = south;
    if (west != NULL)
        exits[WEST] = west;
}

string const Room::shortDescription()
{
    return description;
}

string Room::longDescription()
{
    string str = "";
    str += ("You are in room " + this->shortDescription()) + ".\n";
    str += ("Items in room: ") + displayItem() + "\n";
    str += ("Exits: ") + exitString() + "\n";
    return str;
}
string Room::exitString()
{
    string returnString = "";
    for (map<Direction, Room *>::iterator i = exits.begin(); i != exits.end(); i++)
        // Loop through map

        returnString += " " + toString(i->first); // access the "first" element of the pair (direction as a string)
    return returnString;
}

Room *Room::getRoom(Direction direction)
{
    map<Direction, Room *>::iterator next = exits.find(direction);
    if (next == exits.end())
        return NULL;
    return next->second;
}
void Room::addItem(Item *inItem)
{
    itemsInRoom.push_back(inItem);
}

void Room::removeItem(Item *inItem)
{
    // print the address of the item
    cout << "Address of item: " << inItem << endl;
    // print the address of the item in the vector
    cout << "Address of item in vector: " << itemsInRoom[0] << endl;
    auto it = std::find(itemsInRoom.begin(), itemsInRoom.end(), inItem);
    if (it != itemsInRoom.end())
    {
        itemsInRoom.erase(it);
    }
    else
    {
        cout << "Item not found in room" << endl;
    }
}

string Room::displayItem()
{
    string tempString = "";
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1)
    {
        tempString = "None";
    }
    else if (itemsInRoom.size() > 0)
    {
        int x = (0);
        for (int n = sizeItems; n > 0; n--)
        {
            tempString = tempString + itemsInRoom[x]->getShortDescription() + "  ";
            x++;
        }
    }
    return tempString;
}

int Room::numberOfItems()
{
    return itemsInRoom.size();
}

int Room::isItemInRoom(string inString)
{
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1)
    {
        return false;
    }
    else if (itemsInRoom.size() > 0)
    {
        int x = (0);
        for (int n = sizeItems; n > 0; n--)
        {
            // compare inString with short description
            int tempFlag = inString.compare(itemsInRoom[x]->getShortDescription());
            if (tempFlag == 0)
            {
                itemsInRoom.erase(itemsInRoom.begin() + x);
                return x;
            }
            x++;
        }
    }
    return -1;
}
