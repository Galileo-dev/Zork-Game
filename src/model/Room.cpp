#include "Room.h"
Room::Room(string description)
{
    this->description = description;
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
    return "room = " + description + ".\n" + displayItem() + "\nexits =" + exitString();
}

string Room::exitString()
{
    string returnString = "";
    for (map<Direction, Room *>::iterator i = exits.begin(); i != exits.end(); i++)
        // Loop through map
        returnString += " " + i->first; // access the "first" element of the pair (direction as a string)
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
    // cout <<endl;
    // cout << "Just added" + inItem->getLongDescription();
    itemsInRoom.push_back(*inItem);
}

string Room::displayItem()
{
    string tempString = "items in room = ";
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1)
    {
        tempString = "no items in room";
    }
    else if (itemsInRoom.size() > 0)
    {
        int x = (0);
        for (int n = sizeItems; n > 0; n--)
        {
            tempString = tempString + itemsInRoom[x].getShortDescription() + "  ";
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
            int tempFlag = inString.compare(itemsInRoom[x].getShortDescription());
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
