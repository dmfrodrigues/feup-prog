#include "agency.h"

#include "globaldefs.h"
#include <fstream>

const std::string Agency::opstr = "Operation$ ";

Agency::Agency(std::istream& is, std::ostream& os) noexcept :cis(is),cos(os){
    std::ifstream ifs;
    while(true){
        std::string fullpath;
        ///ENTRY_POINT #DEV
        //os << "Agency file: "; getline(is, fullpath);
        fullpath = "input/agency.txt"; //#DEV
        if(loadAgency(fullpath)) break;
    }
    os << std::endl;
}


bool Agency::loadAgency(const std::string& fpath) noexcept{
    size_t n = fpath.find_last_of('/');
    if(n != fpath.npos){
        inputpath  = fpath.substr(0,n+1);
        agencypath = fpath.substr(n+1, fpath.npos);
    }else{
        inputpath  = "";
        agencypath = fpath;
    }
    std::ifstream is(fpath);
    if(!is){
        cos << "Error: could not open agency file " << fpath << std::endl;
        return false;
    }
    vin(              name      , is);
    vin(              nif       , is);
    vin(              url       , is);
    vin(Address::set, address   , is);
    vin(              clientpath, is);
    vin(              travelpath, is);
    if(!is){
        cos << "Error: could not read from agency file " << fpath << std::endl;
        return false;
    }
    return (loadClients(inputpath + clientpath) &&
            loadPacks  (inputpath + travelpath));
}


void Agency::run(){
    std::string b;
    while(true){
        CLEAR();
        this->print(); cos << std::endl;
        this->printHelp();
        cos << std::endl;
        cos << opstr; getline(cis, b); b = trim(b);
        cos << std::endl;

        if     (b == "tclient") tclient();
        else if(b == "tpack"  ) tpack();
        else if(b == "sclient") sclient(); else if(b == "spack") spack();
        else if(b == "+client") pclient(); else if(b == "+pack") ppack();
        else if(b == "#client") cclient(); else if(b == "#pack") cpack();
        else if(b == "-client") mclient(); else if(b == "-pack") mpack();
        else if(b == "sell"   ) sell();    else if(b == "fpack") fpack();
        else if(b == "sold"   ) sold();
        else if(b == "save"   ) save();    else if(b == "exit" ) return;
        else continue;
        wait(cis,cos);
    }
}

bool Agency::print() const{
    try{
        const long unsigned n = std::max(size_t(0), size_t(WIDTH-name.size()))/2;
        cos << std::string(2*n+name.size(), '#')                  << std::endl;
        cos << std::string(n, ' ') << name << std::string(n, ' ') << std::endl;
        cos << std::string(2*n+name.size(), '#')                  << std::endl;
        cos                                                       << std::endl;
        cos << "NIF: " << nif                                     << std::endl;
        cos << address                                            << std::endl;
        cos << url                                                << std::endl;
        return bool(cos);
    }catch(...){
        return false;
    }
}

bool Agency::printHelp() const{
    try{
        cos << "Client management:                       Travel pack management:          \n"
               "=================================        =================================\n"
               "Add client              [+client]        Add pack                  [+pack]\n"
               "Change client           [#client]        Change pack               [#pack]\n"
               "Delete client           [-client]        Delete pack               [-pack]\n"
               "Sell pack to client        [sell]                                         \n"
               "                                                                          \n"
               "Information visualization:               Other operations:                \n"
               "=================================        =================================\n"
               "Clients table           [tclient]        Save                       [save]\n"
               "See client              [sclient]        Exit                       [exit]\n"
               "Packs table               [tpack]                                         \n"
               "See pack                  [spack]                                         \n"
               "Find (search) packs       [fpack]                                         \n"
               "See packs sold to clients  [sold]                                         \n";
        cos << std::flush;
        return bool(cos);
    }catch(...){
        return false;
    }
}

bool Agency::save() const{
    header("Save");
    try{
        //Save agency
        {
            std::ofstream of_agency; of_agency.exceptions(std::ios_base::badbit); of_agency.open(inputpath + agencypath);
            of_agency << name       << std::endl;
            of_agency << nif        << std::endl;
            of_agency << url        << std::endl;
            of_agency << address    << std::endl;
            of_agency << clientpath << std::endl;
            of_agency << travelpath << std::endl;
            of_agency.close();
        }
        //Save clients
        {
            std::ofstream of_client; of_client.exceptions(std::ios_base::badbit); of_client.open(inputpath + clientpath);
            if(vclient.size() >= 1){
                auto it = vclient.begin();
                of_client << *(it++) << std::endl;
                for(; it != vclient.end(); ++it){
                    of_client << "::::::::::" << std::endl;
                    of_client << *it << std::endl;
                }
            }
            of_client.close();
        }
        //Save travel packs
        {
            std::ofstream of_pack; of_pack.exceptions(std::ios_base::badbit); of_pack.open(inputpath + travelpath);
            of_pack << lasttravel << std::endl;
            if(vtravel.size() >= 1){
                auto it = vtravel.begin();
                of_pack << (it++)->second << std::endl;
                for(; it != vtravel.end(); ++it){
                    of_pack << "::::::::::" << std::endl;
                    of_pack << it->second << std::endl;
                }
            }
            of_pack.close();
        }

        cos << "Files saved" << std::endl;
        return true;
    }catch(...){
        cos << "Error: could not save files" << std::endl;
        return false;
    }
}

void Agency::sold() const{
    header("See packs sold to clients");
    Client::print(vclient.begin(), vclient.end(), "table", cos) << std::endl;
    std::string b; int i;
    while(true){
        if(!vin("# of client to see (if all clients, fill with '-'): ", b, cis, cos)) return;
        b = trim(b); if(b == "-") break;
        try{
            i = std::stoi(b);
        }catch(const std::invalid_argument& e){
            cos << "Error: invalid argument" << std::endl;
            continue;
        }
        if(0 <= i && i < (int)vclient.size()) break;
        else cos << "Error: # outside valid input range [0," << vclient.size()-1 << "]" << std::endl;
    }
    cos << std::endl;
    std::map<ID, TravelPack> m;
    if(b == "-"){
        cos << "Travel packs bought by at least one client:" << std::endl;
        for(const auto& it:vclient)
            for(const auto& id:it.vtravel())
                if(vtravel.find(id) != vtravel.end())
                    m[id] = vtravel.at(id);
    }else{
        cos << "Travel packs bought by client #" << i << ": " << std::endl;
        auto it = vclient.begin(); std::advance(it, i);
        for(const auto& id:it->vtravel())
            if(vtravel.find(id) != vtravel.end())
                m[id] = vtravel.at(id);
    }
    TravelPack::print(m.cbegin(), m.cend(), "sold", cos);
}

void Agency::sell(){
    header("Sell pack to client");
    auto p = seeClient(); unsigned i  = p.first; if(!p.second) return;
    auto q = seePack  (); ID       id = q.first; if(!q.second) return;
    auto it = vclient.begin(); std::advance(it, i);
    cos << std::endl;
    if(it->vtravel().find(id) != it->vtravel().end()){
        cos << "Client #" << i <<" has already bought travel pack with ID " << id << std::endl;
        return;
    }
    if(!vtravel[id].sellable()){
        cos << "Travel pack can no longer be sold (not available or sold out)" << std::endl;
        return;
    }
    if(confirm("Confirm you want to sell the pack with ID "+std::to_string(id)+" to client #"+std::to_string(i) + " [y/n]: ",cis,cos)){
        Client c = *it;
        vtravel[id].sell();
        c.sell(id);
        vclient.erase(it);
        vclient.insert(c);
        cos << "Pack sold" << std::endl;
    }
}

void Agency::header(const std::string& s) const{
    CLEAR(); this->print(); cos << std::endl;
    cos << "==== " + s + " " + std::string(WIDTH-s.size()-6,'=') << std::endl << std::endl;
}
