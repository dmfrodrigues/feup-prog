#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <iostream>

struct Date{
friend std::ostream& operator<<(std::ostream& os, const Date& d);
private:
    int y, m, d;
public:
    Date(){}
    /***/
    Date(std::string s);
    /***/
    bool checkValid() const;
    /***/
    static void set(Date* dptr, std::string s);

    /***/
    operator std::string() const;
    /***/
    static Date begin(){ return Date("0001/01/01"); }
    static Date end  (){ return Date("9999/12/31"); }
    /***/
    bool operator< (const Date& d) const{
        if     (this->y != d.y) return (this->y < d.y);
        else if(this->m != d.m) return (this->m < d.m);
        else                    return (this->d < d.d);
    }
    bool operator==(const Date& d) const{
        return (this->y == d.y && this->m == d.m && this->d == d.d);
    }
    bool operator<=(const Date& d) const{ return (*this < d || *this == d); }
};

/***/
//std::ostream& operator<<(std::ostream& os, const Date& d);

#endif
