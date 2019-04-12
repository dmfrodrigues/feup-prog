#include "helpers.h"

#include <algorithm>
#include <set>
#include <stdexcept>

std::string trim(std::string s) noexcept{
    auto ret = s;
    size_t i;
    i = ret.find_first_not_of(' '); ret = (i != s.npos ? ret.substr(i) : "");
    i = ret.find_last_not_of (' '); if(i != s.npos) ret = ret.substr(0, i+1);
    return ret;
}

std::vector<std::string> split(std::string s, char delim) noexcept{
    std::vector<std::string> ret;
    while(true){
        auto i = s.find(delim); if(i == s.npos) break;
        auto t = trim(s.substr(0,i));
        if(t != "") ret.push_back(t);
        s = s.substr(i+1);
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
    if(sz < 3) throw std::invalid_argument("size less than 3");
    if(s.size() < sz) s = s + std::string(sz-s.size(), ' ');
    if(s.size() > sz) s = s.substr(0,sz-3) + "...";
    return s;
}

std::string rjust(std::string s, size_t sz){
    if(sz < 3) throw std::invalid_argument("size less than 3");
    if(s.size() < sz) s = std::string(sz-s.size(), ' ') + s;
    if(s.size() > sz)s = s.substr(0,sz-3) + "...";
    return s;
}

std::string lower_case(std::string s) noexcept{
    std::transform(s.begin(), s.end(), s.begin(), tolower);
    return s;
}
