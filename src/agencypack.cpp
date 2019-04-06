#include "agency.h"

#include <fstream>
#include <stdexcept>
#include "vin.h"

bool Agency::loadPacks(const std::string& fpath){
    std::ifstream is(fpath, std::ios_base::in);
    if(!is.is_open()) throw std::ios_base::failure("failed to open travelpacks file for read");
    vtravel.clear();
    TravelPack t; std::string b;
    getline(is, b); lasttravel = std::stoi(b);
    while(is){
        is >> t;
        if(!is) return false;
        vtravel[t.id()] = t;
        getline(is, b);
    }
    return true;
}

void Agency::addPack(){
    TravelPack t;
    if(t.userPack(lasttravel+1)){
        ++lasttravel;
        vtravel[t.id()] = t;
        std::cout << "Travel pack added" << std::endl;
    }
}

std::pair<ID, bool> Agency::seePack() const{
    TravelPack::print(vtravel.begin(), vtravel.end(), "table") << std::endl;
    int id;
    while(true){
        if(!vin(id, "ID of travel pack to see: ")) return std::make_pair(0, false);
        if(vtravel.find(id) != vtravel.end()) break;
        else std::cout << "Error: ID not attributed to any travel pack" << std::endl;
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
            if(!vin(j,"# of property to change: ")) return;
            if(0 <= j && j < 8)      break;
            else std::cout << "Error: # outside valid input range [0,7]" << std::endl;
        }
    }
    auto& it = vtravel[id];
    if(it.userPackprop(j)){
        std::cout << "Property changed" << std::endl;
    }
}

void Agency::deletePack(){
    auto p = seePack();
    if(!p.second) return;
    ID id = p.first;
    std::cout << std::endl;
    if(!confirm("Confirm you want to delete travel pack with ID "+std::to_string(id)+" [y/n]: ", cis, cos)) return;
    vtravel.erase(id);
    std::cout << "Travel pack deleted" << std::endl;
}

void Agency::findPack() const{
    std::cout << "If you do not want to use a search field, fill with '-'" << std::endl;
    std::set<std::string> splaces;{
        std::string b;
        if(!vin(b, "Destinations (separated by ',' if more than one): ")) return;
        if(b != "-"){
            std::vector<std::string> v = split(b, ',');
            splaces.insert(v.begin(), v.end());
        }
    }
    Date first, last;{
        std::string b;
        while(true){
            std::cout << "Begin date (yyyy/mm/dd): ";
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
            std::cout << "End date (yyyy/mm/dd): ";
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
    TravelPack::print(m.cbegin(), m.cend(), "table");
}
