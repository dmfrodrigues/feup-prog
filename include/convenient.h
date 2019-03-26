#ifndef STRMANIP_H_INCLUDED
#define STRMANIP_H_INCLUDED

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

/**
Trims a string (removes leading and trailing spaces).
@param  s   string to be trimmed
@return     trimmed version of s
*/
std::string trim(const std::string& s);

/**
Parses a string with a certain delimiter, saving each of the delimited strings
in a vector of strings. All the returned strings are trimmed.
@param  s       string to be parsed
@param  delim   delimiter to parse the string
@return         vector of strings of s delimited by delim
*/
std::vector<std::string> parse(std::string s, char delim);

/***/
#include <iostream>
template<typename T> T str_to(std::string s){
    std::stringstream ss(s);
    T ret; ss >> ret; return ret;
}

/***/
std::string setwidth(std::string s, int sz);

/***/
std::string lower_case(std::string s);

#endif
