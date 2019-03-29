#include "travelpack.h"

#include <map>
#include "vin.h"

std::string TravelPack::getPlaces() const{
    std::string ret = vplaces_[0];
    if(vplaces_.size() > 1)
        ret += " - " + join(vplaces_.begin()+1, vplaces_.end(), ", ");
    return ret;
}

void TravelPack::setPlaces(TravelPack& t, std::string s){
    t.vplaces_ = makePlaces(s);
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

bool TravelPack::userPack(ID lasttravel, std::istream&, std::ostream& os){
    id_ = lasttravel;
    avail_ = true;
    if(!vin("Destination (main - secondary separated by ','): ", TravelPack::setPlaces, *this  ) ||
       !vin("Begin date (yyyy/mm/dd): "                        , Date::set            , begin_ ) ||
       !vin("End date   (yyyy/mm/dd): "                        , Date::set            , end_   ) ||
       !vin("Price per person: "                               ,                        price_ ) ||
       !vin("Max number of people: "                           ,                        numMax_))
        return false;
    numSold_ = 0;
    return true;
}

bool TravelPack::userPackprop(int propn, std::istream& is, std::ostream& os){
    std::string b;
    switch(propn){
        case 0: os << "Travel pack ID can not be changed" << std::endl; return false; break;
        case 1: os << "Availability: "                    << (avail_?"yes":"no") << std::endl;
            while(true){
                if(!vin("New availability value [yes/no]: ", b)) return false;
                if(b == "yes" || b == "no") break;
                else os << "Error: only [y] (yes) or [n] (no) are valid possiblities" << std::endl;
            }
            avail_ = (b == "yes");
            break;
        case 2: os << "Destination: "          << getPlaces() << std::endl; if(!vin("New destination: "         , TravelPack::setPlaces, *this  )) return false; break;
        case 3: os << "Begin date: "           << begin_      << std::endl; if(!vin("New begin date: "          , Date::set            , begin_ )) return false; break;
        case 4: os << "End date: "             << end_        << std::endl; if(!vin("New end date: "            , Date::set            , end_   )) return false; break;
        case 5: os << "Price per person: "     << price_      << std::endl; if(!vin("New price per person: "    ,                        price_ )) return false; break;
        case 6: os << "Max number of people: " << numMax_     << std::endl; if(!vin("New max number of people: ",                        numMax_)) return false; break;
        case 7: os << "Travel pack sells should be handled by operation [sell]" << std::endl; return false; break;
        default: throw std::invalid_argument("trying to access travelpack property that does not exist");
    }
    return true;
}

template<class ForwardIterator>
std::ostream& TravelPack::print(ForwardIterator first, ForwardIterator last, std::string f, std::ostream& os){
    if(f == "table"){
        os << setwidth("ID"         ,  4) << "   "
           << setwidth("Avail"      ,  5) << "\t"
           << setwidth("Destination", 53) << " \t"
           << setwidth("Begin"      , 12) << " "
           << setwidth("End"        , 12) << " "
           << setwidth("Price"      ,  5) << " "
           << setwidth("MaxPeople"  ,  9) << " "
           << setwidth("Sold"       ,  4) << " "
           << std::endl;
        os << std::string(118, '-') << std::endl;;
        for(auto it = first; it != last; ++it){
            const auto& t = it->second;
            os << setwidth(std::to_string(t.id     ()),  4) << "   ";
            os << setwidth((t.avail()? "yes" : "no")  ,  5) << "\t";
            os << setwidth(t.getPlaces()              , 53) << " \t";
            os << setwidth(std::string(t.begin())     , 12) << " ";
            os << setwidth(std::string(t.end())       , 12) << " ";
            os << setwidth(std::to_string(t.price  ()),  5) << " ";
            os << setwidth(std::to_string(t.numMax ()),  9) << " ";
            os << setwidth(std::to_string(t.numSold()),  4) << " ";
            os << std::endl;
        }
    }else if(f == "screenfull"){
        if(last != first){
            const auto& t = first->second;
            os << "#"                                                      << std::endl;
            os << "0      ID:                   " << t.id_                 << std::endl;
            os << "1      Availability:         " << (t.avail_?"yes":"no") << std::endl;
            os << "2      Destination:          " << t.getPlaces()         << std::endl;
            os << "3      Begin date:           " << t.begin_              << std::endl;
            os << "4      End date:             " << t.end_                << std::endl;
            os << "5      Price per person:     " << t.price_              << std::endl;
            os << "6      Max number of people: " << t.numMax_             << std::endl;
            os << "7      Sold:                 " << t.numSold_            << std::endl;
        }
    } return os;
}
template std::ostream& TravelPack::print(std::map<ID, TravelPack>::const_iterator first, std::map<ID, TravelPack>::const_iterator last, std::string f, std::ostream& os);

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
