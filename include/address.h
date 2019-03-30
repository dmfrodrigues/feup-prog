#pragma once
#ifndef ADDRESS_H_INCLUDED
#define ADDRESS_H_INCLUDED

#include <ostream>

/**
* Stores fields of an address: street, door number, floor, postal code and city
*/
struct Address{
friend std::ostream& operator<<(std::ostream& os, const Address& a);
private:
    std::string street_;
    std::string door_;
    std::string floor_;
    std::string postalCode_;
    std::string city_;
public:
    /**
    Constructs 'Address' object with all fields empty
    */
    Address() noexcept{}

    /**
    Constructs 'Address' object from slash-separated fields in a string
    @param  s   string with 5 slash-separated fields of the address
    @throws     std::invalid_argument   s does not have the required 5 fields
    */
    Address(std::string s);

    /**
    Changes content of 'Address' object by one from an object created from a string
    @param  a   'Address' object to be changed
    @param  s   string with 5 slash-separated fields of the address
    @throws     std::invalid_argument   s does not have the required 5 fields,
        since it calls Address::Address(std::string)
    */
    static void set(Address& a, std::string s);

    /**
    'Get' functions of class 'Address'
    @return const reference to corresponding member variable
    @exceptsafe no-throw
    */
    inline const std::string& street    ()const noexcept{ return street_    ; }
    inline const std::string& door      ()const noexcept{ return door_      ; }
    inline const std::string& floor     ()const noexcept{ return floor_     ; }
    inline const std::string& postalCode()const noexcept{ return postalCode_; }
    inline const std::string& city      ()const noexcept{ return city_      ; }

    /**
    Get string version of 'Address', with custom format (implemented with sprintf)
    Does not fail or throw exceptions for default fmt
    @param  fmt C string containing a format string
    @return     result of the write
    @throws     std::runtime_error  when sprintf fails
    */
    std::string str(const char* fmt = "%s / %s / %s / %s / %s") const;

    /**
    Convert 'Address' to string through Address::str(const char*) with default format
    @return     result of the conversion
    @throws     std::runtime_error  when sprintf fails, since it is implemented with Address::str
    */
    operator std::string() const;

    /**
    Some relational operators. Implemented by conversion to string and comparison
    with std::string relational operators
    @return     result of the relational operator
    @exceptsafe no-throw (default Address::str(const char*) fmt does not throw)
    */
    inline bool operator== (const Address& a) const noexcept{ return (str() == a.str()); }
    inline bool operator!= (const Address& a) const noexcept{ return !(*this == a);      }
    inline bool operator<  (const Address& a) const noexcept{ return (str() <  a.str()); }
};

/**
Inserts the content of an 'Address' object into a std::ostream, using Address::str
Destined to be used to write to files
@param  os  output stream where 'Address' is inserted
@param  a   'Addres' object with the content to insert
@return     the same as parameter os
@exceptsafe no-throw (default Address::str(const char*) fmt does not throw)
*/
std::ostream& operator<<(std::ostream& os, const Address& a);

#endif
