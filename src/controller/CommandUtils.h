#include <string>
#include <vector>
#include <sstream>

/**
 * Split a string into a vector of strings.
 * @param str The string to split.
 * @param delimiter The delimiter to split the string on.
 * @return A vector of strings.
 *
 */
std::vector<std::string> split(std::string str, char delimiter)
{
    std::vector<std::string> internal;
    std::stringstream ss(str); // Turn the string into a stream.
    std::string tok;

    while (getline(ss, tok, delimiter))
    {
        internal.push_back(tok);
    }

    return internal;
}