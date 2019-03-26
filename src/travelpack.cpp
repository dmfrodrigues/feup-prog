#include "travelpack.h"

#include "vin.h"

std::istream& operator>>(std::istream& is, TravelPack& t){
    std::stringstream dummy;
    ID id;
    if(!vin("",                        id        , is, dummy) ||
       !vin("", TravelPack::setPlaces, t         , is, dummy) ||
       !vin("", Date::set            , t.begin_  , is, dummy) ||
       !vin("", Date::set            , t.end_    , is, dummy) ||
       !vin("",                        t.price_  , is, dummy) ||
       !vin("",                        t.numMax_ , is, dummy) ||
       !vin("",                        t.numSold_, is, dummy))
       throw std::invalid_argument("could not read client file");
    t.id_ = abs(id);
    t.avail_ = (id >= 0);
    return is;
}

std::ostream& operator<<(std::ostream& os, const TravelPack& t){
    os << t.id()*(t.avail()?1:-1) << std::endl;
    os << t.getPlaces()           << std::endl;
    os << t.begin()               << std::endl;
    os << t.end()                 << std::endl;
    os << t.price()               << std::endl;
    os << t.numMax()              << std::endl;
    os << t.numSold()             << std::flush;
    return os;
}

bool TravelPack::userPack(unsigned lasttravel, std::istream&, std::ostream& os){
    id_ = lasttravel;
    avail_ = true;
    if(!vin("Destino (principal - secundários separados por ','): ", TravelPack::setPlaces, *this  ) ||
       !vin("Data de início (yyyy/mm/dd): "                        , Date::set            , begin_ ) ||
       !vin("Data de fim (yyyy/mm/dd): "                           , Date::set            , end_   ) ||
       !vin("Preço por pessoa: "                                   ,                        price_ ) ||
       !vin("Número máximo de pessoas: "                           ,                        numMax_))
        return false;
    numSold_ = 0;
    return true;
}

void TravelPack::setPlaces(TravelPack& t, std::string s){
    t.vplaces_ = makePlaces(s);
}

std::string TravelPack::getPlaces() const{
    std::string ret = vplaces_[0];
    if(vplaces_.size() > 1)
        ret += " - " + join(vplaces_.begin()+1, vplaces_.end(), ", ");
    return ret;
}

std::vector<std::string> TravelPack::makePlaces(std::string s){
    std::vector<std::string> ret;
    std::vector<std::string> v = split(s, '-');
    if(v.size() < 1) throw std::invalid_argument("could not find at least one place");
    ret.push_back(v[0]);
    if(v.size() == 2){
        v = split(v[1], ',');
        ret.insert(ret.end(), v.begin(), v.end());
    }
    return ret;
}
