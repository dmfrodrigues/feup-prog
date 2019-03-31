#include "nif.h"

#include <stdexcept>
#include "convenient.h"

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
