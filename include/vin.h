#pragma once
#ifndef VIN_H_INCLUDED
#define VIN_H_INCLUDED

#include "helpers.h"
#include <sstream>

using namespace std;

/**
Checks if provided string compares equal to "cancel"
@param  s   string to compare
@return     boolean value corresponding to the result of the comparison
@exceptsafe no-throw
*/
inline bool isCancel(string s) noexcept{ return (s == "cancel"); }

/**
Recieves verified input from the user. Queries the user until a valid input is provided.
Saves provided input to obj.
Exceptions thrown by operator>>(istream&,T&) are handled.
Exceptions thrown by is, os are not handled
@param  q   query text
@param  obj object to be changed
@param  is  input stream
@param  os  output stream
@return     boolean value, true if input succeeded, false if cancelled
@throws     when is, os throw
*/
template<class T> inline bool vin(const char *q, T& obj, istream& is, ostream& os){
    string b; stringstream ss; ss.exceptions(stringstream::failbit | stringstream::badbit);
    while(true){
        os << q; getline(is, b); b = trim(b);
        if(isCancel(b)){ os << "Operation cancelled" << endl; return false; }
        ss.clear(); ss.str(b);
        try{
            ss >> obj;
            return true;
        }catch(const ios_base::failure& e){
            os << "Error: input failed" << endl;
        }catch(const exception& e){
            os << "Error: " << e.what() << endl;
        }
    }
}

/**
Specialization for obj of type string
*/
template<> inline bool vin(const char *q, string& obj, istream& is, ostream& os){
    string b;
    os << q; getline(is, b); b = trim(b);
    if(isCancel(b)){ os << "Operation cancelled" << endl; return false; }
    obj = b;
    return true;
}

/**
Recieves verified input from the user. Queries the user until a valid input is provided.
Processes input through function fptr and saves the result in obj
Exceptions thrown by f(T&,string) are handled.
Exceptions thrown by is, os are not handled
@param  q   query text
@param  f   function that alters obj based on an input string
@param  obj object to be changed
@param  is  input stream
@param  os  output stream
@return     boolean value, true if input succeeded, false if cancelled
@throws     when os::operator<<() throws
*/
template<class T> inline bool vin(const char *q, void f(T&, string), T& obj, istream& is, ostream& os){
    string b;
    while(true){
        os << q; getline(is, b); b = trim(b);
        if(isCancel(b)){ os << "Operation cancelled" << endl; return false; }
        try{
            f(obj, b);
            return true;
        }catch(const ios_base::failure& e){
            os << "Error: input failed" << endl;
        }catch(const exception& e){
            os << "Error: " << e.what() << endl;
        }
    }
}

/**
Recieves input to obj, only tries once
@param  obj object to be changed
@param  is  input stream
@throws     ios_base::failure  from operator>>(istream&,T&)
*/
template<class T> inline void vin(T& obj, istream& is){
    string b; stringstream ss;
    ss.exceptions(stringstream::failbit | stringstream::badbit);
    getline(is, b); b = trim(b);
    try{
        ss.clear(); ss.str(b);
        ss >> obj;
    }catch(...){
        is.setstate(ios::badbit);
    }
}

/**
Specialization for string
*/
template<> inline void vin(string& obj, istream& is){
    string b;
    getline(is, b); b = trim(b);
    obj = b;
}

/**
Recieves input. Provides input to f, which alters obj
All exceptions are unhandled
@param  f   function that alters obj based on an input string
@param  obj object to be changed
@param  is  input stream
@throws     ios_base::failure  inherent to 'is'
@throws     ios_base::failure  converts all exceptions to failure
*/
template<class T> inline void vin(void fptr(T&, string), T& obj, istream& is){
    string b;
    getline(is, b); b = trim(b);
    try{
        fptr(obj, b);
    }catch(...){
        is.setstate(ios::badbit);
    }
}

#endif
