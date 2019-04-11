#pragma once
#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <iostream>

/**
* Represents a date, providing some checks and utilities
*/
struct Date{
friend std::ostream& operator<<(std::ostream& os, const Date& d);
private:
    int y_, m_, d_; ///year, month, day
public:
    /**
    Constructs Date without arguments (defaults to begin())
    @exceptsafe no-throw (default value is valid)
    */
    Date() noexcept{ *this = begin(); }

    /**
    Constructs Date from a string with 3 fields separated by '/'
    @param  s   string with Date content, in format 'yyyy/mm/dd'
    @throws     std::invalid_argument   when s does not have 3 slash-separated fields,
        or when the date is not valid
    */
    Date(std::string s);

    /**
    Changes content of 'Date' object by one from an object created from a string
    @param  d   'Date' object to be changed
    @param  s   string with 3 slash-separated fields of the date
    @throws     std::invalid_argument   s does not have 3 slash-separated fields,
        or the date is not valid [same as Date::Date(std::string)]
    */
    static void set(Date& d, std::string s);

    /**
    Converts date to slash-separated string of format yyyy/mm/dd
    @return     string with slash-separated fields of a date
    @exceptsafe no-throw
    */
    operator std::string() const noexcept;

    /**
    Static functions returning important date values, namely the earliest and latest valid dates
    @return     Jan 1st, 1AD; Dec 31st, 9999AD
    @exceptsafe no-throw
    */
    static Date begin() noexcept{ return Date("0001/01/01"); }
    static Date end  () noexcept{ return Date("9999/12/31"); }

    /**
    Relational operators for dates, employing string conversion (since strings
    can be compared, this is the easiest way to compare dates)
    @param  d   right-hand size of the operation
    @return     result of the corresponding relational operation
    @exceptsafe no-throw
    */
    bool operator<  (const Date& d) const noexcept{ return (std::string(*this) <  std::string(d)); }
    bool operator== (const Date& d) const noexcept{ return !(*this < d || d < *this);              }
    bool operator<= (const Date& d) const noexcept{ return (*this < d || *this == d);              }
    bool operator>  (const Date& d) const noexcept{ return !(*this <= d);                          }
    bool operator>= (const Date& d) const noexcept{ return !(*this < d);                           }

    /**
    Checks if a certain year is a leap year
    @param  y   year
    @return     true if y is a leap year, false otherwise
    @exceptsafe no-throw
    */
    static bool isLeap(int y) noexcept;

    /**
    Checks if *this is a valid date
    A date is valid if it refers to a day after or equal to Jan 1, 1 AD
    and to a day before or equal to Dec 31st, 9999 AD
    */
    bool checkValid() const;
};

/**
Inserts the content of a Date object into a std::ostream, using Date::operator std::string()
@param  os  output stream where Date is inserted
@param  d   Date object with the content to insert
@return     the same as parameter os
@throws     std::ios_base::failure  inherent to 'os'
*/
std::ostream& operator<<(std::ostream& os, const Date& d);

#endif
