#include "Item.h"
#include <iomanip>
#include "Utils.h"

Item::Item(string _identifier, string _displayName, string _description, int _weight, float _value, bool _isWeapon, bool _isQuestItem)
{
    identifier = _identifier;
    displayName = _displayName;
    description = _description;
    weight = _weight;
    value = _value;
    isWeapon = _isWeapon;
    isQuestItem = _isQuestItem;

    /**weaponCheck(isWeapon);*/
}

// void Item::setWeight(int inWeightGrams)
// {
// if (inWeightGrams > 9999 || inWeightGrams < 0)
//     cout << "weight invalid, must be 0<weight<9999";
// else
// but what if an item has  negative gravity???
// what if we are very strong and can carry 10000 grams?
//         weightGrams = WeightGrams;
// }

string Item::getIdentifier()
{
    return identifier;
}

void Item::setValue(float inValue)
{
    if (inValue > 9999 || inValue < 0)
        cout << "value invalid, must be 0<value<9999";
    else
        value = inValue;
}

/**void Item::setWeaponCheck(int isWeapon)
{
    if(isWeapon > 0 || isWeapon < 0)
        cout << "Item not a weapon" ;
    else
        cout << "Item is a weapon" ;
}*/

string Item::getDisplayName()
{
    return displayName;
}

string Item::getDescription()
{
    return description;
}

string Item::getShortDescription()
{
    return displayName + "(" + identifier + ")";
}

string Item::getLongDescription()
{
    return displayName +
           "(" + identifier + "):\n         description: " + description + "\n         weight: " + floatToString(weight) + "kg" + "\n         price: " + floatToString(value) + "zs"; // Use std::to_string() instead of to_string()
}
