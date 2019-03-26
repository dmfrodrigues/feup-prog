#include "agency.h"

#include <fstream>
#include <stdexcept>

void Agency::loadPacks(std::string fpath){
    std::ifstream is(fpath);
    if(!is.is_open()) throw std::invalid_argument("could not open packs file");
    vtravel.clear();
    TravelPack t; std::string b;
    while(is){
        is >> t;
        vtravel[t.id()] = t;
        getline(is, b);
    }
}
