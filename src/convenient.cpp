#include "convenient.h"

#include <set>
#include "vin.h"

std::string trim(std::string s){
    size_t i;
    i = s.find_first_not_of(' '); if(i != s.npos) s = s.substr(i);
    i = s.find_last_not_of (' '); if(i != s.npos) s = s.substr(0, i+1);
    return s;
}

std::vector<std::string> split(std::string s, char delim){
    std::vector<std::string> ret;
    while(true){
        size_t i = s.find(delim); if(i == s.npos) break;
        std::string t = trim(s.substr(0,i));
        if(t != "") ret.push_back(t);
        s = s.substr(i+1, s.npos);
    }
    s = trim(s);
    if(s != "") ret.push_back(s);
    return ret;
}

template<class ForwardIterator>
std::string join(ForwardIterator first, ForwardIterator last, std::string delim){
    std::string ret;
    if(first != last){
        auto it = first;
        ret += *it;
        while(++it != last)
            ret += delim + *it;
    }
    return ret;
}
template std::string join(std::vector<std::string>::const_iterator first, std::vector<std::string>::const_iterator last, std::string delim);

template<class ForwardIterator, class T = long long>
std::string join(ForwardIterator first, ForwardIterator last, std::string fptr(T), std::string delim){
    std::string ret;
    if(first != last){
        auto it = first;
        ret += fptr(*it);
        while(++it != last)
            ret += delim + fptr(*it);
    }
    return ret;
}
template std::string join(std::set<int>::const_iterator first, std::set<int>::const_iterator last, std::string fptr(long long), std::string delim);

std::string ljust(std::string s, size_t sz){
    if(s.size() < sz) s = s + std::string(sz-s.size(), ' ');
    if(s.size() > sz){ s.erase(s.end()-3, s.end()); s += "..."; }
    return s;
}

std::string rjust(std::string s, size_t sz){
    if(s.size() < sz) s = std::string(sz-s.size(), ' ') + s;
    if(s.size() > sz){ s.erase(s.end()-3, s.end()); s += "..."; }
    return s;
}

std::string lower_case(std::string s){
    std::transform(s.begin(), s.end(), s.begin(), tolower);
    return s;
}

bool confirm(std::string q, std::istream& is, std::ostream& os){
    std::string b;
    while(true){
        if(!vin(q, b)) return false;
        b = lower_case(b);
        if(b == "y" || b == "n") break;
        std::cout << "Error: only [y] (yes) or [n] (no) are valid possiblities" << std::endl;
    }
    return (b == "y");
}
