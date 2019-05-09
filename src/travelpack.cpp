#include "travelpack.h"

#include <map>
#include "vin.h"

void TravelPack::setPlaces(TravelPack& t, string s){
    t.vplaces_ = makePlaces(s);
}

string TravelPack::getPlaces() const noexcept{
    auto ret = vplaces_[0];
    if(vplaces_.size() > 1)
        ret += " - " + join(vplaces_.begin()+1, vplaces_.end(), ", ");
    return ret;
}

vector<string> TravelPack::makePlaces(string s){
    vector<string> ret;
    auto v = split(s, '-');
    if(v.size() < 1) throw invalid_argument("could not find at least one place");
    ret.push_back(v[0]);
    if(v.size() == 2){
        v = split(v[1], ',');
        ret.insert(ret.end(), v.begin(), v.end());
    }
    return ret;
}

bool TravelPack::userPack(ID lasttravel, istream& is, ostream& os){
    id_ = lasttravel;
    avail_ = true;
    if(!vin("Destination (main - secondary separated by ','): ", TravelPack::setPlaces, *this  , is, os) ||
       !vin("Begin date (yyyy/mm/dd): "                        , Date::set            , begin_ , is, os)) return false;
    while(true){
       if(!vin("End date   (yyyy/mm/dd): "                     , Date::set            , end_   , is, os)) return false;
       if(end_ >= begin_) break;
       os << "Error: end date happens before begin date" << endl;
    }
    auto i = price_;
    while(true){
        if(!vin("Price per person: ", i, is, os)) return false;
        if(0 <= i) break;
        else       os << "Price per person out of valid range >=0" << endl;
    }
    price_ = i;
    auto j = numMax_;
    while(true){
        if(!vin("Max number of people: ", i, is, os)) return false;
        if(1 <= i) break;
        else       os << "Max number of people out of valid range >=1" << endl;
    }
    numMax_ = j;
    numSold_ = 0;
    return true;
}

bool TravelPack::userPackprop(unsigned propn, istream& is, ostream& os){
    string b;
    auto i = price_;
    auto j = numMax_;
    switch(propn){
        case 0: os << "Travel pack ID can not be changed" << endl; return false; break;
        case 1: os << "Availability: "                    << (avail_?"yes":"no") << endl;
            while(true){
                if(!vin("New availability value [y/n]: ", b, is, os)) return false;
                if(b == "y" || b == "n") break;
                os << "Error: only [y] (yes) or [n] (no) are valid possiblities" << endl;
            }
            avail_ = (b == "y");
            break;
        case 2: os << "Destination: "          << getPlaces() << endl; if(!vin("New destination: "         , TravelPack::setPlaces, *this  , is, os)) return false; break;
        case 3: os << "Begin date: "           << begin_      << endl;
            while(true){
                if(!vin("New begin date: "            , Date::set            , begin_ , is, os)) return false;
                if(end_ <= begin_) break;
                os << "Error: begin date happens after end date" << endl;
            }
            break;
        case 4: os << "End date: "             << end_        << endl;
            while(true){
                if(!vin("New end date: "            , Date::set            , end_   , is, os)) return false;
                if(end_ <= begin_) break;
                os << "Error: end date happens before begin date" << endl;
            }
            break;
        case 5: os << "Price per person: "     << price_      << endl;
            while(true){
                if(!vin("New price per person: ", i, is, os)) return false;
                if(0 <= i) break;
                else       os << "Price per person out of valid range >=0" << endl;
            }
            price_ = i;
            break;
        case 6: os << "Max number of people: " << numMax_     << endl;
            while(true){
                if(!vin("New max number of people: ", i, is, os)) return false;
                if(1 <= i) break;
                else       os << "Max number of people out of valid range >=1" << endl;
            }
            numMax_ = j;
            break;
        case 7: os << "Travel pack sells should be handled by operation [sell]" << endl; return false; break;
        default: throw invalid_argument("trying to access travelpack property that does not exist");
    }
    return true;
}

template<class ForwardIterator>
ostream& TravelPack::print(ForwardIterator first, ForwardIterator last, string f, ostream& os){
    if(first == last){
        return (os << "No travel packs were found" << endl);
    }
    if(f == "table"){
        os << ljust("ID"         ,  4)
           << ljust("Avail"      ,  7)
           << ljust("Destination", 50) << " \t"
           << ljust("Begin"      , 12)
           << ljust("End"        , 12)
           << rjust("Price"      ,  7)
           << rjust("MaxPeople"  , 11)
           << rjust("Sold"       ,  6)
           << endl;
        os << string(112, '=') << endl;
        for(auto it = first; it != last; ++it){
            const auto& t = it->second;
            os << ljust(to_string(t.id     ()),  4);
            os << ljust((t.avail()? "yes" : "no")  ,  7);
            os << ljust(t.getPlaces()              , 50) << " \t";
            os << ljust(string(t.begin())     , 12);
            os << ljust(string(t.end())       , 12);
            os << rjust(to_string(t.price  ()),  7);
            os << rjust(to_string(t.numMax ()), 11);
            os << rjust(to_string(t.numSold()),  6);
            os << endl;
        }
    }else if(f == "sold"){
        int revenue = 0; unsigned maxpeople = 0, sold = 0;
        os << ljust("ID"         ,  4)
           << ljust("Avail"      ,  7)
           << ljust("Destination", 50) << " \t"
           << ljust("Begin"      , 12)
           << ljust("End"        , 12)
           << rjust("Price"      ,  7)
           << rjust("MaxPeople"  , 11)
           << rjust("Sold"       ,  6)
           << rjust("Revenue"    ,  9)
           << endl;
        os << string(121, '=') << endl;;
        for(auto it = first; it != last; ++it){
            const auto& t = it->second;
            auto r = t.price()*(int)t.numSold();
            revenue += r;
            maxpeople += t.numMax();
            sold += t.numSold();
            os << ljust(to_string(t.id     ()),  4);
            os << ljust((t.avail()? "yes" : "no")  ,  7);
            os << ljust(t.getPlaces()              , 50) << " \t";
            os << ljust(string(t.begin())     , 12);
            os << ljust(string(t.end())       , 12);
            os << rjust(to_string(t.price  ()),  7);
            os << rjust(to_string(t.numMax ()), 11);
            os << rjust(to_string(t.numSold()),  6);
            os << rjust(to_string(r)          ,  9);
            os << endl;
        }
        os << string(121,'=') << endl;
        os << "TOTAL" + string(90, ' ') + rjust(to_string(maxpeople), 11)
                                             + rjust(to_string(sold), 6)
                                             + rjust(to_string(revenue), 9) << endl;
    }else if(f == "screenfull"){
        if(last != first){
            const auto& t = first->second;
            os << "#"                                                      << endl;
            os << "0   ID:                   " << t.id_                 << endl;
            os << "1   Availability:         " << (t.avail_?"yes":"no") << endl;
            os << "2   Destination:          " << t.getPlaces()         << endl;
            os << "3   Begin date:           " << t.begin_              << endl;
            os << "4   End date:             " << t.end_                << endl;
            os << "5   Price per person:     " << t.price_              << endl;
            os << "6   Max number of people: " << t.numMax_             << endl;
            os << "7   Sold:                 " << t.numSold_            << endl;
        }
    }
    return os;
}
template ostream& TravelPack::print(map<ID, TravelPack>::const_iterator first, map<ID, TravelPack>::const_iterator last, string f, ostream& os);

istream& operator>>(istream& is, TravelPack& t){
    ID id;
    vin(                       id        , is);
    vin(TravelPack::setPlaces, t         , is);
    vin(Date::set            , t.begin_  , is);
    vin(Date::set            , t.end_    , is); if(t.end_ < t.begin_) is.setstate(ios::failbit);
    vin(                       t.price_  , is);
    vin(                       t.numMax_ , is);
    vin(                       t.numSold_, is);
    if(is){
        t.id_ = abs(id);
        t.avail_ = (id >= 0);
    }
    return is;
}

ostream& operator<<(ostream& os, const TravelPack& t){
    os << t.id()*(t.avail()?1:-1) << endl;
    os << t.getPlaces()           << endl;
    os << t.begin()               << endl;
    os << t.end()                 << endl;
    os << t.price()               << endl;
    os << t.numMax()              << endl;
    os << t.numSold()             << flush;
    return os;
}
