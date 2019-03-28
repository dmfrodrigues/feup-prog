#ifndef GLOBALDEFS_H_INCLUDED
#define GLOBALDEFS_H_INCLUDED

#include <iostream>

typedef int Price;
typedef std::string Name;

const int NIFsize = 9;
struct NIF{
private:
    std::string s_;
public:
    NIF():s_(NIFsize, '0'){}
    NIF(std::string s);
    NIF& operator=(const std::string& s){ return (*this = NIF(s)); }
    operator std::string() const{ return s_; }
    bool operator==(const NIF& obj) const{ return (this->s_ == obj.s_); }
    bool operator!=(const NIF& obj) const{ return !(*this == obj);      }
    bool operator< (const NIF& obj) const{ return (this->s_  < obj.s_); }
};

std::ostream& operator<<(std::ostream& os, const NIF& obj);
std::istream& operator>>(std::istream& is,       NIF& obj);

bool isCancel(std::string s);

#endif
