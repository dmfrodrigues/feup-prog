#include "agency.h"

#include <fstream>
#include <stdexcept>
#include "vin.h"

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

std::pair<unsigned, bool> Agency::seeClient() const{
    Client::print(vclient.begin(), vclient.end(), "table") << std::endl;
    int i;
    while(true){
        if(!vin("# do cliente a visualizar: ", i)) return std::make_pair(0, false);
        if(0 <= i && i < (int)vclient.size())      break;
        else std::cout << "Número fora do intervalo permitido [0," << vclient.size()-1 << "]" << std::endl;
    }
    std::cout << std::endl;
    auto it = vclient.begin(); std::advance(it, i);
    Client::print(it, std::next(it), "screenfull");
    return std::make_pair(i, true);
}

void Agency::addClient(){
    Client c;
    if(c.userClient()){
        vclient.insert(c);
        std::cout << "Cliente adicionado" << std::endl;
    }
}
