#include "agency.h"

#include <fstream>
#include <stdexcept>
#include "vin.h"

void Agency::loadPacks(const std::string& fpath){
    std::ifstream is(fpath);
    if(!is.is_open()) throw std::invalid_argument("could not open packs file");
    vtravel.clear();
    TravelPack t; std::string b;
    getline(is, b); lasttravel = std::stoi(b);
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

std::pair<ID, bool> Agency::seePack() const{
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
    ID id = p.first;
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

void Agency::findPack(){
    std::cout << "Se não pretender utilizar um campo de pesquisa, preencher com '-'" << std::endl;
    std::set<std::string> splaces;{
        std::string b;
        if(!vin("Destinos (separados por ',' se for mais que um): ", b)) return;
        if(b != "-"){
            std::vector<std::string> v = split(b, ',');
            splaces.insert(v.begin(), v.end());
        }
    }
    Date first, last;{
        std::string b;
        while(true){
            std::cout << "Data de início (yyyy/mm/dd): ";
            getline(std::cin, b);
            if(b == "-"){
                first = Date::begin();
                break;
            }else{
                try{
                    first = Date(b);
                    break;
                }catch(const std::invalid_argument& e){
                    std::cout << "Error: " << e.what() << std::endl;
                }
            }
        }
        while(true){
            std::cout << "Data de fim (yyyy/mm/dd): ";
             getline(std::cin, b);
            if(b == "-"){
                last = Date::end();
                break;
            }else{
                try{
                    last = Date(b);
                    break;
                }catch(const std::invalid_argument& e){
                    std::cout << "Error: " << e.what() << std::endl;
                }
            }
        }
    }
    std::map<ID, TravelPack> m;
    for(const auto& p:vtravel){
        const auto& t = p.second;
        bool b = (first <= t.begin() && t.end() <= last);
        for(const auto& s:splaces)
            if(std::find(t.vplaces().begin(), t.vplaces().end(), s) == t.vplaces().end())
                b = false;
        if(b) m.insert(p);
    }
    std::cout << std::endl;
    TravelPack::print(m.begin(), m.end(), "table");
}
