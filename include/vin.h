#pragma once
#ifndef VIN_H_INCLUDED
#define VIN_H_INCLUDED

/**
Checks if provided string compares equal to "cancel"
@param  s   string to compare
@return     boolean value corresponding to the result of the comparison
@exceptsafe no-throw
*/
inline bool isCancel(std::string s) noexcept{ return (s == "cancel"); }

/**
Recieves verified input from the user. Queries the user until a valid input is provided.
Saves provided input to obj.
Exceptions thrown by operator>>(std::istream&,T&) are handled.
Exceptions thrown by is, os are not handled
@param  q   query text
@param  obj object to be changed
@param  is  input stream
@param  os  output stream
@return     boolean value, true if input succeeded, false if cancelled
@throws     when is, os throw
*/
template<class T> inline bool vin(const char *q, T& obj, std::istream& is = std::cin, std::ostream& os = std::cout){
    std::string b; std::stringstream ss; ss.exceptions(std::stringstream::failbit | std::stringstream::badbit);
    while(true){
        os << q; getline(is, b);
        if(isCancel(b)) return false;
        ss.clear(); ss.str(b);
        try{
            ss >> obj;
            return true;
        }catch(const std::ios_base::failure& e){
            os << "Error: input failed" << std::endl;
        }catch(const std::exception& e){
            os << "Error: " << e.what() << std::endl;
        }
    }
}

/**
Specialization for obj of type string
*/
template<> inline bool vin(const char *q, std::string& obj, std::istream& is, std::ostream& os){
    std::string b;
    os << q; getline(is, b);
    if(isCancel(b)) return false;
    obj = b;
    return true;
}

/**
Recieves verified input from the user. Queries the user until a valid input is provided.
Processes input through function fptr and saves the result in obj
Exceptions thrown by f(T&,std::string) are handled.
Exceptions thrown by is, os are not handled
@param  q   query text
@param  f   function that alters obj based on an input string
@param  obj object to be changed
@param  is  input stream
@param  os  output stream
@return     boolean value, true if input succeeded, false if cancelled
@throws     when os::operator<<() throws
*/
template<class T> inline bool vin(const char *q, void f(T&, std::string), T& obj, std::istream& is = std::cin, std::ostream& os = std::cout){
    std::string b;
    while(true){
        os << q; getline(is, b);
        if(isCancel(b)) return false;
        try{
            f(obj, b);
            return true;
        }catch(const std::ios_base::failure& e){
            os << "Error: input failed" << std::endl;
        }catch(const std::exception& e){
            os << "Error: " << e.what() << std::endl;
        }
    }
}

/**
Recieves input to obj, only tries once
@param  obj object to be changed
@param  is  input stream
@throws     std::ios_base::failure  from operator>>(std::istream&,T&)
*/
template<class T> inline void vin(T& obj, std::istream& is = std::cin){
    std::string b; std::stringstream ss;
    ss.exceptions(std::stringstream::failbit | std::stringstream::badbit);
    getline(is, b);
    try{
        ss.clear(); ss.str(b);
        ss >> obj;
    }catch(...){
        is.setstate(std::ios::badbit);
    }
}

/**
Specialization for std::string
*/
template<> inline void vin(std::string& obj, std::istream& is){
    std::string b;
    getline(is, b);
    obj = b;
}

/**
Recieves input. Provides input to f, which alters obj
All exceptions are unhandled
@param  f   function that alters obj based on an input string
@param  obj object to be changed
@param  is  input stream
@throws     std::ios_base::failure  inherent to 'is'
@throws     std::ios_base::failure  converts all exceptions to failure
*/
template<class T> inline void vin(void fptr(T&, std::string), T& obj, std::istream& is = std::cin){
    std::string b;
    getline(is, b);
    try{
        fptr(obj, b);
    }catch(...){
        is.setstate(std::ios::badbit);
    }
}

#endif
