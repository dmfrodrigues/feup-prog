#pragma once
#ifndef ADDRESS_H_INCLUDED
#define ADDRESS_H_INCLUDED

#include <ostream>

using namespace std;

/**
* Stores fields of an address: street, door number, floor, postal code and city
*/
class Address{
private:
    string      street_;
    unsigned    door_;
    string      floor_;
    string      postalCode_;
    string      location_;
public:
    /**
    Constructs 'Address' object with all fields empty
    */
    Address() noexcept{}

    /**
    Constructs 'Address' object from slash-separated fields in a string
    @param  s   string with 5 slash-separated fields of the address
    @throws     invalid_argument   s does not have the required 5 fields
    */
    Address(string s);

    /**
    Changes content of 'Address' object by one from an object created from a string
    @param  a   'Address' object to be changed
    @param  s   string with 5 slash-separated fields of the address
    @throws     invalid_argument   s does not have the required 5 fields,
        since it calls Address::Address(string)
    */
    static void Set(Address& a, string s){ a = Address(s); }

    /**
    'Get' functions of class 'Address'
    @return const reference to corresponding member variable
    @exceptsafe no-throw
    */
    inline const string&    GetStreet    ()const noexcept{ return street_    ; }
    inline const unsigned&  GetDoor      ()const noexcept{ return door_      ; }
    inline const string&    GetFloor     ()const noexcept{ return floor_     ; }
    inline const string&    GetPostalCode()const noexcept{ return postalCode_; }
    inline const string&    GetLocation  ()const noexcept{ return location_  ; }

    /**
    Get string version of 'Address', with custom format (implemented with sprintf)
    Does not fail or throw exceptions for default fmt
    @param  fmt C string containing a format string
    @return     result of the write
    @throws     runtime_error  when sprintf fails
    */
    string str(const char* fmt = "%s / %u / %s / %s / %s") const;

    /**
    Some relational operators. Implemented by conversion to string and comparison
    with string relational operators
    @return     result of the relational operator
    @exceptsafe no-throw (default Address::str(const char*) fmt does not throw)
    */
    inline bool operator== (const Address& a) const noexcept{ return (str() == a.str()); }
    inline bool operator!= (const Address& a) const noexcept{ return !(*this == a);      }
    inline bool operator<  (const Address& a) const noexcept{ return (str() <  a.str()); }

    /**
    Inserts the content of an 'Address' object into a ostream, using Address::str
    Destined to be used to write to files
    @param  os  output stream where 'Address' is inserted
    @param  a   'Addres' object with the content to insert
    @return     the same as parameter os
    @throws     when os throws
    */
    friend ostream& operator<<(ostream& os, const Address& a);
};

#endif
