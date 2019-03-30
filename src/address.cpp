#include "address.h"

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

std::string Address::str(const char* fmt) const{
    char b[512];
    if(sprintf(b, fmt, street_.c_str(), door_.c_str(), floor_.c_str(), postalCode_.c_str(), city_.c_str()) < 0)
        throw std::runtime_error("sprintf failed");
    return std::string(b);
}

Address::operator std::string()const{
    return (this->str());
}

std::ostream& operator<<(std::ostream& os, const Address& a){
    return (os << a.str());
}
