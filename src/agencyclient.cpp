#include "agency.h"

#include <stdexcept>

void Agency::loadClients(std::string s){
    std::ifstream is(s);
    if(!is.is_open()) throw std::invalid_argument("could not open client file");
}
