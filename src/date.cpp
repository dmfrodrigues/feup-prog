#include "date.h"

#include "helpers.h"

Date::Date(std::string s){
    std::vector<std::string> v = split(s, '/');
    if(v.size() != 3){
        throw std::invalid_argument("date does not have 3 fields");
    }
    y_ = std::stoul(v[0]);
    m_ = std::stoul(v[1]);
    d_ = std::stoul(v[2]);
    if(!checkValid()){
        throw std::invalid_argument("date not valid");
    }
}

void Date::set(Date& d, std::string s){
    d = Date(s);
}

Date::operator std::string() const noexcept{
    char b[32];
    sprintf(b, "%04d/%02d/%02d", y_, m_, d_);
    return std::string(b);
}

unsigned days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool Date::isLeap(unsigned y) noexcept{
    if (y%4 == 0)
        if (y%100 == 0) return (y%400 == 0);
        else return true;
    else return false;
}
bool Date::checkValid()const{
    if(!(1 <= m_ && m_ <= 12)) return false;
    if(!(1 <= d_ && d_ <= days[m_]+(m_ == 2 && isLeap(y_)? 1 : 0))) return false;
    if(!(1 <= y_ && y_ <= 9999)) return false;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Date& d){
    return (os << std::string(d));
}
