#pragma once
#ifndef GLOBALDEFS_H_INCLUDED
#define GLOBALDEFS_H_INCLUDED

#include <iostream>

typedef int Price;
typedef std::string Name;

/**
 * Ask the user to confirm a choice, accepting only 'y' (yes) or 'n' (no) as valid answers
 * @param  q  Query string (to be printed everytime before user input)
 * @param  is Input stream
 * @param  os Output stream
 * @return    true if user confirmed, false if user answered 'no' or cancelled
 * @throws    when is, os throw
 */
bool confirm(std::string q, std::istream& is, std::ostream& os);

/**
 * Wait for user to enter anything
 * @param is input stream
 * @param os output stream
 */
void wait(std::istream& is, std::ostream& os);

#endif
