#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
using namespace std;

class Item
{
private:
	string identifier;		// identifier
	string description;		// this wil be the short description used in the room
	string longDescription; // this will be the long description used when the player looks at the item
	float weight;
	float value;
	// TODO: add stats
	bool isWeapon;
	bool isQuestItem; // these cannot be dropped or stored in a chest... but have no weight
public:
	Item(string identifier, string description, int weight, float value, bool isWeapon, bool isQuestItem);
	string getShortDescription();
	string getLongDescription();
	float getWeight();
	void setWeight(float weight);
	void setValue(float value);
	float getValue();
	bool isWeapon();
	void isWeapon(bool weaponCheck);
};

#endif /*ITEM_H_*/
