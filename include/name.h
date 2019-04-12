#pragma once
#ifndef NAME_H_INCLUDED
#define NAME_H_INCLUDED

#include <string>
#include <vector>
#include "convenient.h"
#include "vin.h"

struct Name: public std::string{
public:
    Name() noexcept{}
    Name(const std::string& s);
};

/**
Specialization of vin for obj of type Name
 */
template<> inline bool vin(const char *q, Name& obj, std::istream& is, std::ostream& os){
    std::string b;
    while(true){
        if(!vin(q, b, is, os)) return false;
        try{
            obj = Name(b);
            return true;
        }catch(const std::invalid_argument& e){
            os << "Error: " << e.what() << std::endl;
        }
    }
}

#endif
