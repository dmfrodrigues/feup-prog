#include "agency.h"

#include <fstream>
#include "vin.h"

Agency::Agency(){
    std::ifstream is;
    while(true){
        //std::cout << "Ficheiro da agência: "; std::cin >> agencypath;
        agencypath = "agency.txt";
        is.clear();
        is.open(agencypath, std::ifstream::in);
        if(is.is_open()) break;
        std::cout << "Ficheiro da agência não foi aberto\n";
    }
    is >> *this;
}

void operator>>(std::istream& is, Agency& a){
    std::stringstream dummy;
    if(!vin("",                a.name      , is, dummy) ||
       !vin("",                a.nif       , is, dummy) ||
       !vin("",                a.url       , is, dummy) ||
       !vin("", &Address::set, &a.address  , is, dummy) ||
       !vin("",                a.clientpath, is, dummy) ||
       !vin("",                a.travelpath, is, dummy))
        throw std::invalid_argument("failed to find one of the required fields in agency file");
    a.loadClients(a.clientpath);
    std::cout << "L30" << std::endl;
    a.loadPacks  (a.travelpath);
    std::cout << "L32" << std::endl;

}

void Agency::run(){
    Client::print(vclient.begin(), vclient.end(), "table") << std::endl << std::endl;
}
