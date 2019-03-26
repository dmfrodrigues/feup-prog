#include "address.h"

#include <stdexcept>
#include <vector>
#include "convenient.h"

Address::Address(std::string s){
    std::vector<std::string> v = parse(s, '/');
    if(v.size() != 5) throw std::invalid_argument("address does not have 5 fields");
    street_     = v[0];
    door_       = v[1];
    floor_      = v[2];
    postalCode_ = v[3];
    city_       = v[4];
}

void Address::set(Address* aptr, std::string s){
    *aptr = Address(s);
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
