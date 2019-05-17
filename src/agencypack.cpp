#include "agency.h"

#include "globaldefs.h"
#include <algorithm>
#include <fstream>

bool Agency::loadPacks(const string& fpath){
    ifstream is(fpath, ios_base::in);
    if(!is) throw ios_base::failure("could not open travelpacks file");
    vtravel.clear();
    TravelPack t; string b;
    getline(is, b); lasttravel = stoi(b);
    while(is){
        is >> t;
        if(!is) throw ios_base::failure("could not read travelpack");
        vtravel[t.GetID()] = t;
        getline(is, b);
    }
    return true;
}

void Agency::tpack() const{
    header("Travel packs table");
    TravelPack::Print(vtravel.cbegin(), vtravel.cend(), "table", cos); cos << endl;
}

pair<ID, bool> Agency::seePack() const{
    TravelPack::Print(vtravel.begin(), vtravel.end(), "table", cos) << endl;
    ID id;
    while(true){
        if(!vin("ID of travel pack to see: ", id, cis, cos)) return make_pair(0, false);
        if(vtravel.find(id) != vtravel.end()) break;
        else cos << "Error: ID not attributed to any travel pack" << endl;
    }
    cos << endl;
    auto it = vtravel.find(id);
    TravelPack::Print(it, next(it), "screenfull", cos);
    cos << endl;
    return make_pair(id, true);
}

void Agency::spack()const{
    header("See pack");
    seePack();
}

void Agency::ppack(){
    header("Add travel pack");
    TravelPack t;
    if(t.UserPack(lasttravel+1, cis, cos)){
        ++lasttravel;
        vtravel[t.GetID()] = t;
        cos << "Travel pack added" << endl;
        InfoChanged = true;
    }
}

void Agency::cpack(){
    header("Change travel pack");
    auto p = seePack();
    if(!p.second) return;
    auto id = p.first;
    string b;
    int j;{
        while(true){
            if(!vin("# of property to change: ", j, cis, cos)) return;
            if(0 <= j && j < 8)      break;
            else cos << "Error: # outside valid input range [0,7]" << endl;
        }
    }
    cos << endl;
    auto& it = vtravel[id];

    if(it.UserPackprop((unsigned)j, cis, cos)){


        cos << endl << "Property changed" << endl;
        InfoChanged = true;
    }
}

void Agency::mpack(){
    header("Delete travel pack");
    auto p = seePack();
    if(!p.second) return;
    auto id = p.first;
    if(!confirm("Confirm you want to delete travel pack with ID "+to_string(id)+" [y/n]: ", cis, cos)) return;

    vtravel.erase(id);
    cos << "Travel pack deleted" << endl;
    InfoChanged = true;
}

void Agency::fpack() const{
    header("Find (search) packs");
    cos << "If you do not want to use a search field, fill with an invalid input (like '-' or press 'Enter')" << endl;
    set<string> splaces;{
        string b;
        if(!vin("Destinations (separated by ',' if more than one): ", b, cis, cos)) return;
        if(b != "-"){
            vector<string> v = split(b, ',');
            splaces.insert(v.begin(), v.end());
        }
    }
    Date first, last;{
        string b;

        if(!vin("Begin date (yyyy/mm/dd): ", b, cis, cos)) return;
        try{
            first = Date(b);
        }catch(const invalid_argument& e){
            first = Date::GetBegin();
        }


        if(!vin("End date (yyyy/mm/dd): ", b, cis, cos)) return;
        try{
            last = Date(b);
        }catch(const invalid_argument& e){
            last = Date::GetEnd();
        }
    }
    map<ID, TravelPack> m;
    for(const auto& p:vtravel){
        const auto& t = p.second;
        bool b = (first <= t.GetBegin() && t.GetEnd() <= last);
        for(const auto& s:splaces)
            if(find(t.GetVPlaces().begin(), t.GetVPlaces().end(), s) == t.GetVPlaces().end())
                b = false;
        if(b) m.insert(p);
    }
    cos << endl;
    TravelPack::Print(m.cbegin(), m.cend(), "table", cos); cos << endl;
}
