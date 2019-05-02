#pragma once
#ifndef NIF_H_INCLUDED
#define NIF_H_INCLUDED

#include <iostream>

/**
* Represents NIF (numero de identificacao fiscal), providing some encapsulation
*/
class NIF: public std::string{
private:
    static const size_t NIFsize = 9; ///size of NIF in Portugal
public:
    /**
    Constructs NIF with a valid number of zeroes
    @exceptsafe no-throw
    */
    NIF() noexcept: std::string(NIFsize, '0'){}

    /**
    Constructs NIF from a string of *NIFsize* digits
    @param  s   string with *NIFsize* digits
    @throws     std::invalid_argument   when s does not have size equal to *NIFsize*,
        when at least one of the characters is not a digit,
        or when it is not a valid NIF (modulus)
    */
    NIF(std::string s);
};

#endif
