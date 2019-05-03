#include "globaldefs.h"

#include "vin.h"

bool confirm(string q, istream& is, ostream& os){
    string b;
    while(true){
        if(!vin(q.c_str(), b, is, os)) return false;
        b = lower_case(b);
        if(b == "y" || b == "n") break;
        os << "Error: only [y] (yes) or [n] (no) are valid possiblities" << endl;
    }
    if(b == "n"){ os << "Operation cancelled" << endl; return false; }
    else                                                    return true;
}

void wait(istream& is, ostream& os){
    string b;
    os << "(Press 'Enter' to continue)";
    getline(is, b);
}
