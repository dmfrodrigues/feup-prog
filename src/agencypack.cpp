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

void Agency::addPack(){
    TravelPack t;
    if(t.userPack(lasttravel+1)){
        ++lasttravel;
        vtravel[t.id()] = t;
        std::cout << "Pacote turístico adicionado" << std::endl;
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


void Agency::changePack(){
    auto p = seePack();
    if(!p.second) return;
    int id = p.first;
    std::string b; std::cout << std::endl;
    int j;{
        while(true){
            if(!vin("# da propriedade a alterar: ", j)) return;
            if(0 <= j && j < 8)      break;
            else std::cout << "Número fora do intervalo permitido [0,7]" << std::endl;
        }
    }
    auto& it = vtravel[id];
    if(it.userPackprop(j)){
        std::cout << "Propriedade alterada" << std::endl;
    }
}


void Agency::deletePack(){
    auto p = seePack();
    if(!p.second) return;
    int id = p.first;
    std::string b; std::cout << std::endl;
    while(true){
        if(!vin("Confirme que pretende eliminar o pacote com ID "+std::to_string(id)+" [y/n]: ", b)) return;
        b = lower_case(b);
        if(b == "y" || b == "n") break;
        std::cout << "Apenas [y] (sim) ou [n] (não) são possibilidades válidas" << std::endl;
    }
    if(b == "y"){
        vtravel.erase(id);
        std::cout << "Pacote turístico eliminado" << std::endl;
    }
}
