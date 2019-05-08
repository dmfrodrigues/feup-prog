#include "agency.h"

#include "globaldefs.h"
#include <fstream>

const string Agency::opstr = "Operation$ ";

Agency::Agency(istream& is, ostream& os):cis(is),cos(os){
    ifstream ifs;
    string fullpath;
    ///ENTRY_POINT #DEV
    //os << "Agency file: "; getline(is, fullpath);
    fullpath = "input/agency.txt"; //#DEV
    loadAgency(fullpath);
    os << endl;
}


bool Agency::loadAgency(const string& fpath){
    auto n = fpath.find_last_of('/');
    if(n != fpath.npos){
        inputpath  = fpath.substr(0,n+1);
        agencypath = fpath.substr(n+1, fpath.npos);
    }else{
        inputpath  = "";
        agencypath = fpath;
    }
    ifstream is(fpath); is.exceptions(ifstream::failbit | ifstream::badbit);
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

void Agency::nplaces() const{
    header("Most visited places");
    /*BLA BLA BLA*/
}

void Agency::suggest() const{
    header("Travel suggestions");
    /*BLA BLA BLA*/
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
        cos << opstr; getline(cis, b);
        int n;
        try{ n = stoi(trim(b)); }catch(...){ n = -1; }

        cos << endl;

        bool mustWait = true;

        switch(n){
            case 21: pclient(); break; case 31: ppack(); break;
            case 22: cclient(); break; case 32: cpack(); break;
            case 23: mclient(); break; case 33: mpack(); break;
            case 10: sell();    break;
            case 24: tclient(); break; case 01: save(); break;
            case 25: sclient(); break; case 02: if(this->exit()) return; break;
            case 34: tpack();   break;
            case 35: spack();   break;
            case 36: fpack();   break;
            case 40: nplaces(); break;
            case 41: suggest(); break;
            case 11: sold();    break;
            default: mustWait = false; break;
        }

        if(mustWait) wait(cis,cos);

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
               "Add client                   [21]        Add pack                     [31]\n"
               "Change client                [22]        Change pack                  [32]\n"
               "Delete client                [23]        Delete pack                  [33]\n"
               "Sell pack to client          [10]                                         \n"
               "                                                                          \n"
               "Information visualization:               Other operations:                \n"
               "=================================        =================================\n"
               "Clients table                [24]        Save                         [01]\n"
               "See client                   [25]        Exit                         [02]\n"
               "Packs table                  [34]                                         \n"
               "See pack                     [35]                                         \n"
               "Find (search) packs          [36]                                         \n"
               "Get most visited places      [40]                                         \n"
               "Get travel pack suggestions  [41]                                         \n"
               "See packs sold to clients    [11]                                         \n";
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
