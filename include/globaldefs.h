#pragma once
#ifndef GLOBALDEFS_H_INCLUDED
#define GLOBALDEFS_H_INCLUDED

#include <iostream>

typedef int Price;
typedef std::string Name;

bool confirm(std::string q, std::istream& is = std::cin, std::ostream& os = std::cout);

#endif
