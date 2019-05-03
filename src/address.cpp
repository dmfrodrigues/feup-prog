#include "address.h"

#include "helpers.h"

Address::Address(string s){
    auto v = split(s, '/');
    if(v.size() != 5) throw invalid_argument("address does not have 5 fields");
    street_     = v[0];
    int n = stoi(v[1]);
    if(n < 0) throw invalid_argument("door number is not an unsigned integer");
    door_ = unsigned(n);
    floor_      = v[2];
    postalCode_ = v[3];
    location_   = v[4];
}

string Address::str(const char* fmt) const{
    char b[512];
    if(sprintf(b, fmt, street_.c_str(), door_, floor_.c_str(), postalCode_.c_str(), location_.c_str()) < 0)
        throw runtime_error("sprintf failed");
    return string(b);
}

ostream& operator<<(ostream& os, const Address& a){
    return (os << a.str());
}
