#include "globaldefs.h"

#include "convenient.h"
#include "vin.h"

bool confirm(std::string q, std::istream& is, std::ostream& os){
    std::string b;
    while(true){
        if(!vin(q.c_str(), b, is, os)) return false;
        b = lower_case(b);
        if(b == "y" || b == "n") break;
        os << "Error: only [y] (yes) or [n] (no) are valid possiblities" << std::endl;
    }
    return (b == "y");
}

void wait(std::istream& is, std::ostream& os){
    std::string b;
    os << "(Press 'Enter' to continue)";
    getline(is, b);
}
