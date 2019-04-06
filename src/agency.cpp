#include "agency.h"

#include <fstream>
#include "vin.h"

Agency::Agency(std::istream& is, std::ostream& os) noexcept :cis(is),cos(os){
    std::ifstream ifs;
    while(true){
        std::string fullpath;
        //os << "Agency file: "; getline(is, fullpath);
        fullpath = "input/agency.txt"; //#DEV
        size_t n = fullpath.find_last_of('/');
        if(n != fullpath.npos){
            inputpath  = fullpath.substr(0,n+1);
            agencypath = fullpath.substr(n+1, fullpath.npos);
        }else{
            inputpath  = "";
            agencypath = fullpath;
        }

        ifs.clear();
        ifs.open(inputpath + agencypath, std::ifstream::in);
        ifs >> *this;
        if(ifs) break;
        else std::cout << "Error: failed to read agency file" << std::endl;
    }
}

void Agency::run(){
    this->print() << std::endl;
    this->printHelp();
    std::string b;
    while(true){
        std::cout << std::endl;
        std::cout << "Operation$ "; getline(std::cin, b); b = trim(b);
        std::cout << std::endl;

        if     (b == "tclient")     Client::print(vclient.cbegin(), vclient.cend(), "table");
        else if(b == "tpack"  ) TravelPack::print(vtravel.cbegin(), vtravel.cend(), "table");
        else if(b == "sclient") seeClient();    else if(b == "spack") seePack();
        else if(b == "+client") addClient();    else if(b == "+pack") addPack();
        else if(b == "#client") changeClient(); else if(b == "#pack") changePack(); //#DEV
        else if(b == "-client") deleteClient(); else if(b == "-pack") deletePack();
        else if(b == "sell"   ) sell();         else if(b == "fpack") findPack();
        else if(b == "sold"   ) seeSold();
        else if(b == "help"   ) printHelp();
        else if(b == "save"   ) save();         else if(b == "exit" ) return;
        else std::cout << "Invalid operation" << std::endl;
    }
}

std::ostream& Agency::print(std::ostream& os) const{
    const long unsigned n = std::max(size_t(0), size_t(74-name.size()))/2;
    os << std::string(2*n+name.size(), '#')                  << std::endl;
    os << std::string(n, ' ') << name << std::string(n, ' ') << std::endl;
    os << std::string(2*n+name.size(), '#')                  << std::endl;
    os                                                       << std::endl;
    os << "NIF: " << nif                                     << std::endl;
    os << address                                            << std::endl;
    os << url                                                << std::endl;
    return os;
}

std::ostream& Agency::printHelp(std::ostream& os) const{
    os << "Client management:                       Travel pack management:          \n"
          "=================================        =================================\n"
          "Add client              [+client]        Add pack                  [+pack]\n"
          "Change client           [#client]        Change pack               [#pack]\n"
          "Delete client           [-client]        Delete pack               [-pack]\n"
          "Sell pack to client        [sell]                                         \n"
          "                                                                          \n"
          "Information visualization:               Other operations:                \n"
          "=================================        =================================\n"
          "Clients table           [tclient]        Command list (help)        [help]\n"
          "See client              [sclient]        Save                       [save]\n"
          "Packs table               [tpack]        Exit                       [exit]\n"
          "See pack                  [spack]                                         \n"
          "Find (search) packs       [fpack]                                         \n"
          "See packs sold to clients  [sold]                                         \n";
    return os << std::flush;
}

std::ostream& Agency::save(std::ostream& os) const{
    try{
        //Save agency
        std::ofstream of_agency(inputpath + agencypath);
        if(!of_agency.is_open()) throw std::ios_base::failure("failed to open agency file for write");
        of_agency << *this;
        of_agency.close();
        //Save clients
        std::ofstream of_client(inputpath + clientpath);
        if(!of_client.is_open()) throw std::ios_base::failure("failed to open client file for write");
        if(vclient.size() >= 1){
            auto it = vclient.begin();
            of_client << *(it++) << std::endl;
            for(; it != vclient.end(); ++it){
                of_client << "::::::::::" << std::endl;
                of_client << *it << std::endl;
            }
        }
        of_client.close();
        //Save travel packs
        std::ofstream of_pack(inputpath + travelpath);
        if(!of_pack.is_open()) throw std::ios_base::failure("failed to open travelpack file for write");
        of_pack << lasttravel << std::endl;
        if(vtravel.size() >= 1){
            auto it = vtravel.begin();
            of_pack << (it++)->second << std::endl;
            for(; it != vtravel.end(); ++it){
                of_pack << "::::::::::" << std::endl;
                of_pack << it->second << std::endl;
            }
        }
        return (os << "Files saved" << std::endl);
    }catch(...){
        return (os << "Error: could not save files");
    }
}

void Agency::seeSold() const{
    Client::print(vclient.begin(), vclient.end(), "table") << std::endl;
    std::string b; int i;
    while(true){
        if(!vin("# of client to see (if all clients, fill with '-'): ", b)) return;
        b = trim(b); if(b == "-") break;
        i = std::stoi(b);
        if(0 <= i && i < (int)vclient.size()) break;
        else std::cout << "Error: # outside valid input range [0," << vclient.size()-1 << "]" << std::endl;
    }
    std::cout << std::endl;
    std::map<ID, TravelPack> m;
    if(b == "-"){
        std::cout << "Travel packs bought by at least one client:" << std::endl;
        for(const auto& it:vclient)
            for(const auto& id:it.vtravel())
                if(vtravel.find(id) != vtravel.end())
                    m[id] = vtravel.at(id);
    }else{
        std::cout << "Travel packs bought by client #" << i << ": " << std::endl;
        auto it = vclient.begin(); std::advance(it, i);
        for(const auto& id:it->vtravel())
            if(vtravel.find(id) != vtravel.end())
                m[id] = vtravel.at(id);
    }
    TravelPack::print(m.cbegin(), m.cend(), "sold");
}

void Agency::sell(){
    auto p = seeClient(); unsigned i  = p.first; if(!p.second) return;
    auto q = seePack  (); ID       id = q.first; if(!q.second) return;
    auto it = vclient.begin(); std::advance(it, i);
    std::cout << std::endl;
    if(it->vtravel().find(id) != it->vtravel().end()){
        std::cout << "Client #" << i <<" has already bought travel pack with ID " << id << std::endl;
        return;
    }
    if(!vtravel[id].sellable()){
        std::cout << "Travel pack can no longer be sold (not available or sold out)" << std::endl;
        return;
    }
    if(!confirm("Confirm you want to sell the pack with ID "+std::to_string(id)+" to client #"+std::to_string(i),cis,cos)) return;
    Client c = *it;
    vtravel[id].sell();
    c.sell(id);
    vclient.erase(it);
    vclient.insert(c);
}

std::istream& operator>>(std::istream& is, Agency& a){
    vin(              a.name      , is);
    vin(              a.nif       , is);
    vin(              a.url       , is);
    vin(Address::set, a.address   , is);
    vin(              a.clientpath, is);
    vin(              a.travelpath, is);
    if(!a.loadClients(a.inputpath + a.clientpath) ||
       !a.loadPacks  (a.inputpath + a.travelpath)){
        is.setstate(std::ios::badbit);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Agency& a){
    os << a.name       << std::endl;
    os << a.nif        << std::endl;
    os << a.url        << std::endl;
    os << a.address    << std::endl;
    os << a.clientpath << std::endl;
    os << a.travelpath;
    return os;
}
