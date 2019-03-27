#ifndef ADDRESS_H_INCLUDED
#define ADDRESS_H_INCLUDED

#include <string>

struct Address{
friend std::ostream& operator<<(std::ostream& os, const Address& a);
private:
    std::string street_;
    std::string door_;
    std::string floor_;
    std::string postalCode_;
    std::string city_;
public:
    Address(){}
    /**
    Constructs 'Address' object from slash-separated fields in a string
    @param  s   string with slash-separated fields of the address
    */
    Address(std::string s);

    static void set(Address& a, std::string s);

    /***/
    inline const std::string& street    ()const{ return street_    ; }
    inline const std::string& door      ()const{ return door_      ; }
    inline const std::string& floor     ()const{ return floor_     ; }
    inline const std::string& postalCode()const{ return postalCode_; }
    inline const std::string& city      ()const{ return city_      ; }

    /***/
    std::string str(std::string s = "%s / %s / %s / %s / %s") const;

    /***/
    inline bool operator==(const Address& a) const{ return (str() == a.str()); }
    inline bool operator!=(const Address& a) const{ return !(*this == a);      }
    inline bool operator< (const Address& a) const{ return (str() <  a.str()); }
};

/**
Print the content of an 'Address' object, without field names.
Destined to be used to write to files
@param  os  output stream to which the object's content should be printed
@param  a   object whose content should be printed to os
@return     the same output stream
*/
std::ostream& operator<<(std::ostream& os, const Address& a);

#endif
