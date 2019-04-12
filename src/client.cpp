#include "client.h"

#include "vin.h"


void Client::setPacks(Client& c, std::string s){
    c.vtravel_ = makePacks(s);
}

std::set<ID> Client::makePacks(std::string s){
    std::set<ID> ret;
    std::vector<std::string> v = split(s, ';');
    for(auto i:v) ret.insert(std::stoi(i));
    return ret;
}

std::string Client::getPacks(const std::string& delim) const noexcept{
    std::string ret = join(vtravel_.cbegin(), vtravel_.cend(), std::to_string, delim);
    return ret;
}

bool Client::userClient(std::istream& is, std::ostream& os) noexcept{
    if(!vin("Name: "                                       ,                   name_   , is, os) ||
       !vin("NIF: "                                        ,                   nif_    , is, os) ||
       !vin("Household members: "                          ,                   numFam_ , is, os) ||
       !vin("Address (street/door/floor/postalcode/city): ", Address::set    , address_, is, os) ||
       !vin("Bought packs (separated by ';'): "            , Client::setPacks, *this   , is, os))
        return false;
    return true;
}

bool Client::userClientprop(int propn, std::istream& is, std::ostream& os){
    switch(propn){
        case 0: os << "Name: "           << name_      << std::endl; if(!vin("New name: "          ,                   name_   , is, os)) return false; break;
        case 1: os << "NIF: "            << nif_       << std::endl; if(!vin("New NIF: "           ,                   nif_    , is, os)) return false; break;
        case 2: os << "Household size: " << numFam_    << std::endl; if(!vin("New household size: ",                   numFam_ , is, os)) return false; break;
        case 3: os << "Address: "        << address_   << std::endl; if(!vin("New address: "       , Address::set    , address_, is, os)) return false; break;
        case 4: os << "Travel pack sells should be handled by operation [sell]" << std::endl; return false; break;
        default: throw std::out_of_range("trying to access client property that does not exist");
    }
    return true;
}

template<class ForwardIterator>
std::ostream& Client::print(ForwardIterator first, ForwardIterator last, std::string f, std::ostream& os){
    if(first == last){
        return (os << "No clients were found" << std::endl);
    }
    if(f == "table"){
        os << ljust("#"           ,  4)
           << ljust("Name"        , 54) << "\t"
           << ljust("NIF"         ,  9)
           << rjust("#Household"  , 12) << "  "
           << ljust("Address"     , 60) << "\t"
           << ljust("Bought packs", 18)
           << std::endl;
        os << std::string(170, '=') << std::endl;
        unsigned i = 0;
        for(auto it = first; it != last; ++it, ++i){
            const auto& c = *it;
            os << ljust(std::to_string(i)            ,  4);
            os << ljust(c.name()                     , 54) << "\t";
            os << ljust(c.nif()                      ,  9);
            os << rjust(std::to_string(c.numFamily()), 12) << "  ";
            os << ljust(std::string(c.address())     , 60) << "\t";
            os << ljust(c.getPacks("; ")             , 18);
            os << std::endl;
        }
    }else if(f == "screenfull"){
        if(last != first){
            const auto& c = *first;
            os << "#"                                        << std::endl;
            os << "0   Name:           " << c.name_          << std::endl;
            os << "1   NIF:            " << c.nif_           << std::endl;
            os << "2   Household size: " << c.numFam_        << std::endl;
            os << "3   Address:        " << c.address_       << std::endl;
            os << "4   Bought packs:   " << c.getPacks("; ") << std::endl;
        }
    } return os;
}
template std::ostream& Client::print(std::multiset<Client>::const_iterator first, std::multiset<Client>::const_iterator last, std::string f, std::ostream& os);

bool Client::operator<(const Client& c) const noexcept{
    if     (name_    != c.name_   ) return (name_    < c.name_   );
    else if(nif_     != c.nif_    ) return (nif_     < c.nif_    );
    else if(numFam_  != c.numFam_ ) return (numFam_  < c.numFam_ );
    else if(address_ != c.address_) return (address_ < c.address_);
    else                            return (vtravel_ < c.vtravel_);
}

std::istream& operator>>(std::istream& is, Client& c){
    vin(                  c.name_   , is);
    vin(                  c.nif_    , is);
    vin(                  c.numFam_ , is);
    vin(Address::set    , c.address_, is);
    vin(Client::setPacks, c         , is);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Client& c){
    os << c.name_      << std::endl;
    os << c.nif_       << std::endl;
    os << c.numFam_    << std::endl;
    os << c.address_   << std::endl;
    os << c.getPacks();
    return os;
}
