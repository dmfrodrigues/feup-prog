#include "agency.h"

#include <fstream>
#include <stdexcept>

void Agency::loadPacks(std::string fpath){
    std::ifstream is(fpath);
    if(!is.is_open()) throw std::invalid_argument("could not open packs file");
    vtravel.clear();
    TravelPack t; std::string b;
    getline(is, b); lasttravel = str_to<unsigned>(b);
    while(is){
        is >> t;
        vtravel[t.id()] = t;
        getline(is, b);
    }
}

void Agency::addPack(){
    TravelPack t;
    if(t.userPack(lasttravel+1)){
        ++lasttravel;
        vtravel[t.id()] = t;
        std::cout << "Pacote turístico adicionado" << std::endl;
    }
}
