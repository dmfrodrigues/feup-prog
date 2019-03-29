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

std::string Client::getPacks() const{
    std::string ret = join(vtravel_.cbegin(), vtravel_.cend(), std::to_string, " ; ");
    return ret;
}

bool Client::userClient(std::istream& is, std::ostream& os){
    if(!vin("Name: "                           ,                   name_   ) ||
       !vin("NIF: "                            ,                   nif_    ) ||
       !vin("Household members:  "             ,                   numFam_ ) ||
       !vin("Address: "                        , Address::set    , address_) ||
       !vin("Bought packs (separated by ';'): ", Client::setPacks, *this   ))
        return false;
    return true;
}

bool Client::userClientprop(int propn, std::istream& is, std::ostream& os){
    switch(propn){
        case 0: os << "Name: "           << name_      << std::endl; if(!vin("New name: "          ,                   name_   )) return false; break;
        case 1: os << "NIF: "            << nif_       << std::endl; if(!vin("New NIF: "           ,                   nif_    )) return false; break;
        case 2: os << "Household size: " << numFam_    << std::endl; if(!vin("New household size: ",                   numFam_ )) return false; break;
        case 3: os << "Address: "        << address_   << std::endl; if(!vin("New address: "       , Address::set    , address_)) return false; break;
        case 4: os << "Travel pack sells should be handled by operation [sell]" << std::endl; return false; break;
        default: throw std::invalid_argument("trying to access client property that does not exist");
    }
    return true;
}

template<class ForwardIterator>
std::ostream& Client::print(ForwardIterator first, ForwardIterator last, std::string f, std::ostream& os){
    if(f == "table"){
        os << setwidth("#"         ,  4) << "   "
           << setwidth("Name"      , 48) << " \t"
           << setwidth("NIF"       ,  9) << "   "
           << setwidth("#Household", 10) << " "
           << setwidth("Address"   , 60) << " \t"
           << std::endl;
        os << std::string(150, '-') << std::endl;
        unsigned i = 0;
        for(auto it = first; it != last; ++it, ++i){
            const auto& c = *it;
            os << setwidth(std::to_string(i)                ,  4) << "   ";
            os << setwidth(c.name()                         , 48) << " \t";
            os << setwidth(c.nif()                          ,  9) << "   ";
            os << setwidth(std::to_string(c.numFamily())    , 10) << " ";
            os << setwidth(std::string(c.address())         , 60) << " \t";
            os << std::endl;
        }
    }else if(f == "screenfull"){
        if(last != first){
            const auto& c = *first;
            os << "#"                                     << std::endl;
            os << "0      Name:           " << c.name_    << std::endl;
            os << "1      NIF:            " << c.nif_     << std::endl;
            os << "2      Household size: " << c.numFam_  << std::endl;
            os << "3      Address:        " << c.address_ << std::endl;
            os << "4      Bought packs:   ";
            if(!c.vtravel_.empty()){
                auto it = c.vtravel_.begin();
                os << *(it++);
                for(; it != c.vtravel_.end(); ++it)
                    os << " ; " << *it;
            }os << std::endl;
        }
    } return os;
}
template std::ostream& Client::print(std::multiset<Client>::const_iterator first, std::multiset<Client>::const_iterator last, std::string f, std::ostream& os);

bool Client::operator<(const Client& c) const{
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
