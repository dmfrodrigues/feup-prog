#include "date.h"

#include <vector>
#include "convenient.h"

Date::operator std::string() const{
    char b[32];
    sprintf(b, "%04d/%02d/%02d", y, m, d);
    return std::string(b);
}

Date::Date(std::string s){
    std::vector<std::string> v = parse(s, '/');
    if(v.size() != 3){
        throw std::invalid_argument("date does not have 3 fields");
    }
    y = str_to<int>(v[0]);
    m = str_to<int>(v[1]);
    d = str_to<int>(v[2]);
    if(!checkValid()){
        throw std::invalid_argument("date not valid");
    }
}

void Date::set(Date* dptr, std::string s){
    *dptr = Date(s);
}

int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool isLeap(int y){
    if (y%4 == 0){
        if (y%100 == 0){
            if (y%400 == 0) return true;
            else            return false;
        } else return true;
    } else return false;
}
bool Date::checkValid()const{
    if(!(1 <= m && m <= 12)) return false;
    if(!(1 <= d && d <= days[m]+(m == 2 && isLeap(y)? 1 : 0))) return false;
    if(!(0 <= y && y <= 9999)) return false;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Date& d){
    return (os << std::string(d));
}
