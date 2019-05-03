#pragma once
#ifndef NIF_H_INCLUDED
#define NIF_H_INCLUDED

#include <iostream>

using namespace std;

/**
* Represents NIF (numero de identificacao fiscal), providing some encapsulation
*/
class NIF: public string{
private:
    static const size_t NIFsize = 9; ///size of NIF in Portugal
public:
    /**
    Constructs NIF with a valid number of zeroes
    @exceptsafe no-throw
    */
    NIF() noexcept: string(NIFsize, '0'){}

    /**
    Constructs NIF from a string of *NIFsize* digits
    @param  s   string with *NIFsize* digits
    @throws     invalid_argument   when s does not have size equal to *NIFsize*,
        when at least one of the characters is not a digit,
        or when it is not a valid NIF (modulus)
    */
    NIF(string s);

    NIF& operator=(const NIF& a){ string::operator=(a); return *this;}
};

#endif
