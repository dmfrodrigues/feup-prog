#include "globaldefs.h"

#include <stdexcept>
#include "convenient.h"
#include "vin.h"

NIF::NIF(std::string s){
    s = trim(s);
    if(s.size() != NIFsize) throw std::invalid_argument("NIF has wrong size");
    for(const auto& c:s) if(!isdigit(c)) throw std::invalid_argument("NIF has nonnumeric character");
    s_ = s;
}

std::ostream& operator<<(std::ostream& os, const NIF& obj){
    return (os << std::string(obj));
}

std::istream& operator>>(std::istream& is, NIF& obj){
    std::string s; is >> s;
    obj = NIF(s);
    return is;
}


bool confirm(std::string q, std::istream& is, std::ostream& os){
    std::string b;
    while(true){
        if(!vin(q, b, is, os)) return false;
        b = lower_case(b);
        if(b == "y" || b == "n") break;
        os << "Error: only [y] (yes) or [n] (no) are valid possiblities" << std::endl;
    }
    return (b == "y");
}
