#include "agency.h"

#include "globaldefs.h"
#include <fstream>


bool Agency::loadClients(const string& fpath){
    ifstream is(fpath, ios_base::in);

    if(!is) throw ios_base::failure("could not open clients file");
    vclient.clear();
    Client c; string b;

    while(is){
        is >> c;
        if(!is) throw ios_base::failure("could not read client");
        vclient.insert(c);
        if(is.eof()) break;
        getline(is, b);
    }
    return true;
}

void Agency::tclient() const{
    header("Clients table");
    Client::Print(vclient.cbegin(), vclient.cend(), "table", cos); cos << endl;
}

pair<unsigned, bool> Agency::seeClient() const{
    Client::Print(vclient.begin(), vclient.end(), "table", cos) << endl;
    int i;
    while(true){
        if(!vin("# of client to see: ", i, cis, cos)) return make_pair(0, false);
        if(0 <= i && i < (int)vclient.size())      break;
        else cos << "Error: # outside valid input range [0," << vclient.size()-1 << "]" << endl;
    }
    cos << endl;
    auto it = vclient.begin(); advance(it, i);
    Client::Print(it, next(it), "screenfull", cos);
    cos << endl;
    return make_pair(i, true);
}

void Agency::sclient() const{
    header("See client");
    seeClient();
}

void Agency::pclient(){
    header("Add client");
    Client c;
    if(c.UserClient(cis, cos)){

        vclient.insert(c);
        cos << "Client added" << endl;
        InfoChanged = true;
    }
}

void Agency::cclient(){
    header("Change client");
    auto p = seeClient();
    if(!p.second) return;
    auto i = p.first;
    string b;
    int j;{
        while(true){
            if(!vin("# of property to change: ", j, cis, cos)) return;
            if(0 <= j && j < 6)      break;
            else cos << "Error: # outside valid input range [0,4]" << endl;
        }
    }
    cos << endl;
    auto it = vclient.begin(); advance(it, i);
    auto c = *it;
    if(c.UserClientprop((unsigned)j, cis, cos)){
        vclient.erase(it);
        vclient.insert(c);
        cos << endl << "Property changed" << endl;
        InfoChanged = true;
    }
}

void Agency::mclient(){
    header("Delete client");
    auto p = seeClient();
    if(!p.second) return;
    auto i = p.first;
    if(!confirm("Confirm you want to delete client #"+to_string(i)+" [y/n]: ", cis, cos)) return;
    auto it = vclient.begin(); advance(it, i);
    vclient.erase(it);
    cos << "Client deleted" << endl;
    InfoChanged = true;
}
