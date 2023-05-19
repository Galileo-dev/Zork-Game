#include "Utils.h"
#include <string>

using namespace std;

#include <string> // Added this line to include the string header file
string floatToString(float f)
{
    string str = to_string(f);
    str.erase(str.find_last_not_of('0') + 1, string::npos);
    str.erase(str.find_last_not_of('.') + 1, string::npos);
    return str;
}