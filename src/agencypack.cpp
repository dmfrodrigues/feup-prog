#include "agency.h"

#include <fstream>
#include <stdexcept>
#include "vin.h"

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

std::pair<unsigned, bool> Agency::seePack() const{
    TravelPack::print(vtravel.begin(), vtravel.end(), "table") << std::endl;
    int id;
    while(true){
        if(!vin("ID do pacote turístico a visualizar: ", id)) return std::make_pair(0, false);
        if(vtravel.find(id) != vtravel.end()) break;
        else std::cout << "ID não atribuído a nenhum pacote turístico" << std::endl;
    }
    std::cout << std::endl;
    auto it = vtravel.find(id);
    TravelPack::print(it, std::next(it), "screenfull");
    return std::make_pair(id, true);
}

void Agency::addPack(){
    TravelPack t;
    if(t.userPack(lasttravel+1)){
        ++lasttravel;
        vtravel[t.id()] = t;
        std::cout << "Pacote turístico adicionado" << std::endl;
    }
}
