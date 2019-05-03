#include "address.h"

#include "helpers.h"

Address::Address(std::string s){
    auto v = split(s, '/');
    if(v.size() != 5) throw std::invalid_argument("address does not have 5 fields");
    street_     = v[0];
    door_       = stoul(v[1]);
    floor_      = v[2];
    postalCode_ = v[3];
    location_   = v[4];
}

std::string Address::str(const char* fmt) const{
    char b[512];
    if(sprintf(b, fmt, street_.c_str(), door_, floor_.c_str(), postalCode_.c_str(), location_.c_str()) < 0)
        throw std::runtime_error("sprintf failed");
    return std::string(b);
}

std::ostream& operator<<(std::ostream& os, const Address& a){
    return (os << a.str());
}
