#include "address.h"

#include <stdexcept>
#include <vector>
#include "convenient.h"

Address::Address(std::string s){
    std::vector<std::string> v = split(s, '/');
    if(v.size() != 5) throw std::invalid_argument("address does not have 5 fields");
    street_     = v[0];
    door_       = v[1];
    floor_      = v[2];
    postalCode_ = v[3];
    city_       = v[4];
}

void Address::set(Address& a, std::string s){
    a = Address(s);
}

#include <iostream>
std::string Address::str(std::string s) const{
    char b[512];
    sprintf(b, s.c_str(), street_.c_str(), door_.c_str(), floor_.c_str(), postalCode_.c_str(), city_.c_str());
    return std::string(b);
}

std::ostream& operator<<(std::ostream& os, const Address& a){
    return (os << a.str());
}

bool Address::operator==(const Address& a) const{
    return (this->str() == a.str());;
}
bool Address::operator!=(const Address& a) const{
    return !(*this == a);
}
bool Address::operator< (const Address& a) const{
    return (this->str() < a.str());
}
