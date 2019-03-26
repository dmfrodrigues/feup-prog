#include "agency.h"

#include <fstream>
#include <stdexcept>

void Agency::loadClients(std::string fpath){
    std::ifstream is(fpath);
    if(!is.is_open()) throw std::invalid_argument("could not open client file");
    vclient.clear();
    Client c; std::string b;
    while(is){
        is >> c;
        vclient.insert(c);
        getline(is, b);
    }
}
