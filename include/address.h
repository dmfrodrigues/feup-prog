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
    Constructs Address object from slash-separated fields in a string
    @param  s   string with slash-separated fields of the address
    */
    Address(std::string s);

    static void set(Address& a, std::string s);

    /***/
    const std::string& street    ()const{ return street_    ; }
    const std::string& door      ()const{ return door_      ; }
    const std::string& floor     ()const{ return floor_     ; }
    const std::string& postalCode()const{ return postalCode_; }
    const std::string& city      ()const{ return city_      ; }

    /***/
    std::string str(std::string s = "%s / %s / %s / %s / %s") const;

    /***/
    bool operator==(const Address& a) const;
    bool operator!=(const Address& a) const;
    bool operator< (const Address& a) const;

    /***/
    bool isFloor()const;

};

/**
Allows to print the content of the object
@param  os  output stream to which the object's content should be printed
@return     the same output stream
*/
std::ostream& operator<<(std::ostream& os, const Address& a);

#endif
