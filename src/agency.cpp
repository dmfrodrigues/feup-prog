#include "agency.h"

#include <fstream>
#include "vin.h"

Agency::Agency(){
    std::ifstream is;
    while(true){
        agencypath = "agency.txt";
        is.clear();
        is.open(agencypath, std::ifstream::in);
        if(is.is_open()) break;
        std::cout << "Ficheiro da agência não foi aberto";
    }
    is >> *this;
    //loadClients();
    //loadPacks();
}


std::istream& operator>>(std::istream& is, Agency& a){
    std::stringstream dummy;
    vin("", a.name, is, dummy);
    vin("", a.nif , is, dummy);
    
    return is;
}
