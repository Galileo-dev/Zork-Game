#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
using namespace std;

class Item
{
private:
	string identifier;
	string displayName;
	string description;
	string longDescription;
	float weight;
	float value;
	// TODO: add stats
	bool isWeapon;
	bool isQuestItem;

public:
	Item() {}
	Item(string identifier, string displayName, string description, int weight, float value, bool isWeapon, bool isQuestItem);
	string getDisplayName();
	string getShortDescription();
	string getLongDescription();
	float getWeight();
	void setWeight(float weight);
	void setValue(float value);
	float getValue();
	bool getIsWeapon();
	void setIsWeapon(bool weaponCheck);
};

#endif /*ITEM_H_*/
