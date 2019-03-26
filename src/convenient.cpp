#include "convenient.h"

std::string trim(const std::string& s){
    return std::string(s.begin()+s.find_first_not_of(' '),
                       s.begin()+s.find_last_not_of(' ')+1);
}

std::vector<std::string> split(std::string s, char delim){
    std::vector<std::string> ret;
    size_t i;
    while(true){
        i = s.find(delim);
        if(i == s.npos) break;
        ret.push_back(trim(std::string(s.begin(), s.begin()+i)));
        s = std::string(s.begin()+i+1, s.end());
    }
    ret.push_back(trim(s));
    return ret;
}

std::string setwidth(std::string s, size_t sz){
    if(s.size() < sz)
        s += std::string(sz-s.size(), ' ');
    if(s.size() > sz)
        s = std::string(s.begin(), s.begin()+sz-3) + "...";
    return s;
}

std::string lower_case(std::string s){
    for(auto& c:s) c = tolower(c);
    return s;
}
