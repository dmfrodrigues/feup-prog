#include "travelpack.h"

#include "vin.h"

std::istream& operator>>(std::istream& is, TravelPack& t){
    std::stringstream dummy;
    ID id;
    if(!vin("",                         id        , is, dummy) ||
       !vin("", &TravelPack::setPlaces, &t        , is, dummy) ||
       !vin("", &Date::set            , &t.begin_ , is, dummy) ||
       !vin("", &Date::set            , &t.end_   , is, dummy) ||
       !vin("",                         t.price_  , is, dummy) ||
       !vin("",                         t.numMax_ , is, dummy) ||
       !vin("",                         t.numSold_, is, dummy))
       throw std::invalid_argument("could not read client file");
    t.id_ = abs(id);
    t.avail_ = (id >= 0);
    return is;
}

void TravelPack::setPlaces(TravelPack* tptr, std::string s){
    tptr->vplaces_ = makePlaces(s);
}

std::string TravelPack::getPlaces() const{
    std::string ret = vplaces_[0];
    if(vplaces_.size() > 1){
        ret += " - " + vplaces_[1];
        for(unsigned i = 1; i < vplaces_.size(); ++i)
            ret += ", " + vplaces_[i];
    }
    return ret;
}

std::vector<std::string> TravelPack::makePlaces(std::string s){
    std::vector<std::string> ret;
    std::vector<std::string> v = parse(s, '-');
    if(v.size() < 1) throw std::invalid_argument("could not find at least one place");
    ret.push_back(v[0]);
    if(v.size() == 2){
        v = parse(v[1], ',');
        ret.insert(ret.end(), v.begin(), v.end());
    }
    return ret;
}
