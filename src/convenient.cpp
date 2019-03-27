#include "convenient.h"

std::string trim(std::string s){
    s = s.substr(s.find_first_not_of(' '));
    return s.substr(0, s.find_last_not_of(' ')+1);
}

std::vector<std::string> split(std::string s, char delim){
    std::vector<std::string> ret;
    size_t i;
    while(true){
        i = s.find(delim); if(i == s.npos) break;
        ret.push_back(trim(s.substr(0, i)));
        s = s.substr(i+1, s.npos);
    }
    ret.push_back(trim(s));
    return ret;
}

std::string setwidth(std::string s, size_t sz){
    if(s.size() < sz)
        s += std::string(sz-s.size(), ' ');
    if(s.size() > sz){
        s.erase(s.end()-3, s.end()); s += "...";
    }
    return s;
}

std::string lower_case(std::string s){
    for(auto& c:s) c = tolower(c);
    return s;
}
