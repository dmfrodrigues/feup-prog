#include "nif.h"

#include <stdexcept>
#include "helpers.h"

NIF::NIF(std::string s){
    s = trim(s);
    //Some validity checks
    for(const auto& c:s) if(!isdigit(c)) throw std::invalid_argument("NIF has nonnumeric character");
    if(s.size() != NIFsize) throw std::invalid_argument("NIF has wrong size");
    //NIF digit check
    {
        unsigned sum = 0; for(unsigned i = 0; i < 8; ++i) sum += (9-i)*unsigned(s[i]-'0');
        sum = std::max(sum%11, 1u); sum = (11-sum)%10;
        if(unsigned(s[8]-'0') != sum) throw std::invalid_argument("NIF number is not valid");
    }

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
