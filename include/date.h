#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <iostream>

struct Date{
friend std::ostream& operator<<(std::ostream& os, const Date& d);
private:
    int y_, m_, d_;
public:
    Date(){}
    /***/
    Date(std::string s);
    /***/
    bool checkValid() const;
    /***/
    static void set(Date& d, std::string s);

    /***/
    operator std::string() const;
    /***/
    static Date begin(){ return Date("0001/01/01"); }
    static Date end  (){ return Date("9999/12/31"); }
    /***/
    bool operator< (const Date& d) const{
        if     (this->y_ != d.y_) return (this->y_ < d.y_);
        else if(this->m_ != d.m_) return (this->m_ < d.m_);
        else                      return (this->d_ < d.d_);
    }
    bool operator==(const Date& d) const{
        return (this->y_ == d.y_ && this->m_ == d.m_ && this->d_ == d.d_);
    }
    bool operator<=(const Date& d) const{ return (*this < d || *this == d); }

    static bool isLeap(int y);
};

/***/
std::ostream& operator<<(std::ostream& os, const Date& d);

#endif
