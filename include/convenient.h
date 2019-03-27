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
std::string trim(std::string s);

/**
Parses a string with a certain delimiter, saving each of the delimited strings
in a vector of strings. All the returned strings are trimmed.
@param  s       string to be parsed
@param  delim   delimiter to parse the string
@return         vector of strings of s delimited by delim
*/
std::vector<std::string> split(std::string s, char delim);

/***/
template<class ForwardIterator>
std::string join(ForwardIterator first, ForwardIterator last, std::string delim){
    std::string ret;
    if(first != last){
        auto it = first;
        ret += *it;
        while(++it != last)
            ret += delim + *it;
    }
    return ret;
}

template<class ForwardIterator, class T = long long>
std::string join(ForwardIterator first, ForwardIterator last, std::string (*fptr)(T), std::string delim){
    std::string ret;
    if(first != last){
        auto it = first;
        ret += fptr(*it);
        while(++it != last)
            ret += delim + fptr(*it);
    }
    return ret;
}

/***/
std::string setwidth(std::string s, size_t sz);

/***/
std::string lower_case(std::string s);

#endif
