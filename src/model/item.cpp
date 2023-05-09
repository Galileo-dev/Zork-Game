#include "item.h"

Item::Item(string _identifier, string _displayName, string _description, int _weight, float _value, bool _isWeapon, bool _isQuestItem)
{
    description = _description;
    weight = _weight;
    value = _value;
    displayName = _displayName;
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

string Item::getShortDescription()
{
    return description;
}

string Item::getLongDescription()
{
    return " item(s), " + description + ".\n";
}
