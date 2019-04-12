#pragma once
#ifndef STRMANIP_H_INCLUDED
#define STRMANIP_H_INCLUDED

#include <string>
#include <vector>

/**
Trims a string, removing leading and trailing spaces
@param  s   string to be trimmed
@return     trimmed version of s
@exceptsafe	no-throw
*/
std::string trim(std::string s) noexcept;

/**
Splits a string into a vector of words delimited by character delim
All elements of the returned vector are trimmed
@param  s       string to be split
@param  delim   delimiter
@return         vector of strings of s delimited by delim
@exceptsafe     no-throw
*/
std::vector<std::string> split(std::string s, char delim) noexcept;

/**
Joins elements stored in [first, last) with delim, creating a string with elements
pointed by the iterators and delimited by delim
@param  first input iterator to the initial position of the sequence
@param  last  input iterator to the past-the-end position of the sequence
@param  delim delimiter
@return       delim-separated list of elements in [first, last)
@throws       all exceptions thrown by iterators
*/
template<class ForwardIterator>
std::string join(ForwardIterator first, ForwardIterator last, std::string delim);

/**
Same as join(ForwardIterator, ForwardIterator, std::string), but uses a function
to convert the elements pointed by the iterators to string
@param  first input iterator to the initial position of the sequence
@param  last  input iterator to the past-the-end position of the sequence
@param  fptr  function to convert elements pointed by iterators to strings
@return       delim-separated list of elements in [first, last)
@throws       all exceptions thrown by iterators and fptr
*/
template<class ForwardIterator, class T = long long>
std::string join(ForwardIterator first, ForwardIterator last, std::string fptr(T), std::string delim);

/**
Left-justifies text by adding spaces to the end of the string
Truncates string if its size is greater than sz
@param  s   string to left-justify
@param  sz  size of the returned string
@return     string padded with spaces at the end
@throws std::invalid_argument   thrown if sz is not at least 3
*/
std::string ljust(std::string s, size_t sz);

/**
Right-justifies text by adding spaces to the end of the string
Truncates string if its size is greater than sz
@param  s   string to right-justify
@param  sz  size of the returned string
@return     string padded with spaces at the beginning
@throws std::invalid_argument   thrown if sz is not at least 3
*/
std::string rjust(std::string s, size_t sz);

/**
Convert characters in string to their lowercase equivalent
@param  s   string to convert to lower lowercase
@return     lowercase version of s
@exceptsafe no-throw
*/
std::string lower_case(std::string s) noexcept;

#endif
