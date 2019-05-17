#pragma once
#ifndef VAT_H_INCLUDED
#define VAT_H_INCLUDED

#include <iostream>

using namespace std;

/**
* Represents VAT, providing some encapsulation
*/
class VAT: public string{
private:
    static const size_t VATsize = 9; ///size of VAT in Portugal
public:
    /**
    Constructs VAT with a valid number of zeroes
    @exceptsafe no-throw
    */
    VAT() noexcept: string(VATsize, '0'){}

    /**
    Constructs VAT from a string of *VATsize* digits
    @param  s   string with *VATsize* digits
    @throws     invalid_argument   when s does not have size equal to *VATsize*,
        when at least one of the characters is not a digit,
        or when it is not a valid VAT (modulus)
    */
    VAT(string s);

    VAT& operator=(const VAT& a){ string::operator=(a); return *this;}
};

#endif
