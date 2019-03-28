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
template std::string join(std::vector<int>::const_iterator first, std::vector<int>::const_iterator last, std::string fptr(long long), std::string delim);

std::string setwidth(std::string s, size_t sz){
    if(s.size() < sz)
        s += std::string(sz-s.size(), ' ');
    if(s.size() > sz){
        s.erase(s.end()-3, s.end()); s += "...";
    }
    return s;
}

std::string lower_case(std::string s){
    std::transform(s.begin(), s.end(), s.begin(), tolower);
    return s;
}
