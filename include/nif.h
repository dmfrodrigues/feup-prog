#pragma once
#ifndef NIF_H_INCLUDED
#define NIF_H_INCLUDED

#include <iostream>

/**
* Represents NIF (numero de identificacao fiscal), providing some encapsulation
*/
struct NIF{
private:
    static const size_t NIFsize = 9; ///size of NIF in Portugal
    std::string s_;
public:
    /**
    Constructs NIF with a valid number of zeroes
    @exceptsafe no-throw
    */
    NIF() noexcept: s_(NIFsize, '0'){}

    /**
    Constructs NIF from a string of *NIFsize* digits
    @param  s   string with *NIFsize* digits
    @throws     std::invalid_argument   when s does not have size equal to *NIFsize*,
        when at least one of the characters is not a digit,
        or when it is not a valid NIF (modulus)
    */
    NIF(std::string s);

    /**
    Converts from NIF to std::string. Actually, only returns s_
    @return     NIF represented as a *NIFsize*-length string of digits
    @exceptsafe no-throw
    */
    operator std::string() const noexcept{ return s_; }

    /**
    Relational operators between NIF objects
    @param  obj left-hand object of the comparison
    @return     boolean value corresponding to the operation result
    @exceptsafe no-throw implemented from NIF::operator std::string()
    */
    bool operator==(const NIF& obj) const{ return (this->s_ == obj.s_); }
    bool operator!=(const NIF& obj) const{ return !(*this == obj);      }
    bool operator< (const NIF& obj) const{ return (this->s_  < obj.s_); }
};

/**
Inserts the content of a NIF object into a std::ostream, using NIF::operator std::string()
Destined to be used to write to files
@param  os  output stream where NIF is inserted
@param  obj NIF object with the content to insert
@return     the same as parameter os
@throws     std::ios_base::failure  inherent to 'os'
*/
std::ostream& operator<< (std::ostream& os, const NIF& obj);

/**
Extracts as many characters as possible and replaces obj content with the one provided
by 'is'
@param  is  input stream where NIF will be read from
@param  obj receiver of the extracted information
@return     the same as parameter is
@throws     std::invalid_argument   when extracted string does not have size equal to *NIFsize*,
    or when at least one of the characters is not a digit (same as NIF::NIF(std::string))
@throws     std::ios_base::failure inherent to 'is'
*/
std::istream& operator>>(std::istream& is,       NIF& obj);

#endif
