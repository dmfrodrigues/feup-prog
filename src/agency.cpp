#include "agency.h"

#include "globaldefs.h"
#include <fstream>

const string Agency::opstr = "Operation$ ";

Agency::Agency(istream& is, ostream& os) noexcept :cis(is),cos(os){
    ifstream ifs;
    while(true){
        string fullpath;
        ///ENTRY_POINT #DEV
        os << "Agency file: "; getline(is, fullpath);
        //fullpath = "input/agency.txt"; //#DEV
        if(loadAgency(fullpath)) break;
    }
    os << endl;
}


bool Agency::loadAgency(const string& fpath) noexcept{
    auto n = fpath.find_last_of('/');
    if(n != fpath.npos){
        inputpath  = fpath.substr(0,n+1);
        agencypath = fpath.substr(n+1, fpath.npos);
    }else{
        inputpath  = "";
        agencypath = fpath;
    }
    ifstream is(fpath);
    if(!is){
        cos << "Error: could not open agency file " << fpath << endl;
        return false;
    }
    vin(              name      , is);
    vin(              nif       , is);
    vin(              url       , is);
    vin(Address::set, address   , is);
    vin(              clientpath, is);
    vin(              travelpath, is);
    if(!is){
        cos << "Error: could not read from agency file " << fpath << endl;
        return false;
    }
    return (loadClients(inputpath + clientpath) &&
            loadPacks  (inputpath + travelpath));
}


void Agency::run(){
    string b;
    #ifndef CLEAR
        this->print(); cos << endl;
        this->printHelp();
    #endif
    while(true){
        #ifdef CLEAR
            CLEAR();
            this->print(); cos << endl;
            this->printHelp();
        #endif
        cos << endl;
        cos << opstr; getline(cis, b); b = trim(b);
        cos << endl;

        if     (b == "tclient") tclient();
        else if(b == "tpack"  ) tpack();
        else if(b == "sclient") sclient(); else if(b == "spack") spack();
        else if(b == "+client") pclient(); else if(b == "+pack") ppack();
        else if(b == "#client") cclient(); else if(b == "#pack") cpack();
        else if(b == "-client") mclient(); else if(b == "-pack") mpack();
        else if(b == "sell"   ) sell();    else if(b == "fpack") fpack();
        else if(b == "sold"   ) sold();
        else if(b == "save"   ) save();    else if(b == "exit" && this->exit()) break;
        else continue;
        wait(cis,cos);
    }
}

bool Agency::print() const{
    try{
        const auto n = max(size_t(0), size_t(WIDTH-name.size()))/2;
        cos << string(2*n+name.size(), '#')                  << endl;
        cos << string(n, ' ') << name << string(n, ' ') << endl;
        cos << string(2*n+name.size(), '#')                  << endl;
        cos                                                       << endl;
        cos << "NIF: " << nif                                     << endl;
        cos << address                                            << endl;
        cos << url                                                << endl;
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
        cos << flush;
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
            ofstream of_agency; of_agency.exceptions(ios_base::badbit); of_agency.open(inputpath + agencypath);
            of_agency << name       << endl;
            of_agency << nif        << endl;
            of_agency << url        << endl;
            of_agency << address    << endl;
            of_agency << clientpath << endl;
            of_agency << travelpath << endl;
            of_agency.close();
        }
        //Save clients
        {
            ofstream of_client; of_client.exceptions(ios_base::badbit); of_client.open(inputpath + clientpath);
            if(vclient.size() >= 1){
                auto it = vclient.begin();
                of_client << *(it++) << endl;
                for(; it != vclient.end(); ++it){
                    of_client << "::::::::::" << endl;
                    of_client << *it << endl;
                }
            }
            of_client.close();
        }
        //Save travel packs
        {
            ofstream of_pack; of_pack.exceptions(ios_base::badbit); of_pack.open(inputpath + travelpath);
            of_pack << lasttravel << endl;
            if(vtravel.size() >= 1){
                auto it = vtravel.begin();
                of_pack << (it++)->second << endl;
                for(; it != vtravel.end(); ++it){
                    of_pack << "::::::::::" << endl;
                    of_pack << it->second << endl;
                }
            }
            of_pack.close();
        }

        cos << "Files saved" << endl;
        return true;
    }catch(...){
        cos << "Error: could not save files" << endl;
        return false;
    }
}

bool Agency::exit() const{
    if(InfoChanged){
        header("Exit");
        if(!confirm("There are unsaved changes. Do you wish to close without saving? [y/n]: ", cis, cos)) return false;
        return true;
    }else{
        return true;
    }
}

void Agency::sold() const{
    header("See packs sold to clients");
    Client::print(vclient.begin(), vclient.end(), "table", cos) << endl;
    string b; int i;
    while(true){
        if(!vin("# of client to see (if all clients, fill with invalid input, like '-' or press 'Enter'): ", b, cis, cos)) return;
        b = trim(b);
        try{
            i = stoi(b);
        }catch(const invalid_argument& e){
            b = "-"; break;
        }
        if(0 <= i && i < (int)vclient.size()) break;
        else cos << "Error: # outside valid input range [0," << vclient.size()-1 << "]" << endl;
    }
    cos << endl;
    map<ID, TravelPack> m;
    if(b == "-"){
        cos << "Travel packs bought by at least one client:" << endl;
        for(const auto& it:vclient)
            for(const auto& id:it.vtravel())
                if(vtravel.find(id) != vtravel.end())
                    m[id] = vtravel.at(id);
    }else{
        cos << "Travel packs bought by client #" << i << ": " << endl;
        auto it = vclient.begin(); advance(it, i);
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
    auto it = vclient.begin(); advance(it, i);
    if(it->vtravel().find(id) != it->vtravel().end()){
        cos << "Client #" << i <<" has already bought travel pack with ID " << id << endl;
        return;
    }
    if(!vtravel[id].sellable()){
        cos << "Travel pack can no longer be sold (not available or sold out)" << endl;
        return;
    }
    if(confirm("Confirm you want to sell the pack with ID "+to_string(id)+" to client #"+to_string(i) + " [y/n]: ",cis,cos)){
        Client c = *it;
        vtravel[id].sell();
        c.sell(id);
        vclient.erase(it);
        vclient.insert(c);
        cos << "Pack sold" << endl;
        InfoChanged = true;
    }
}

void Agency::header(const string& s) const{
    #ifdef CLEAR
        CLEAR(); this->print(); cos << endl;
    #endif
    cos << "==== " + s + " " + string(WIDTH-s.size()-6,'=') << endl << endl;
}
