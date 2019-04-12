#include "name.h"

Name::Name(const std::string& s): std::string(s){
    auto v = split(s, ' ');
    if(v.size() < 1) throw std::invalid_argument("name does not have at least one particle");
}
