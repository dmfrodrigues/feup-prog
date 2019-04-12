#include "name.h"

Name::Name(const std::string& s): std::string(s){
    std::vector<std::string> v = split(s, ' ');
    if(v.size() < 1) throw std::invalid_argument("name does not have at least one particle");
    if(std::any_of(s.begin(), s.end(), isalpha)) throw std::invalid_argument("one of the characters is not a letter");
}
