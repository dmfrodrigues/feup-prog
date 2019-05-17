#include "client.h"

#include "vin.h"


void Client::SetPacks(Client& c, string s){
    c.vtravel_ = MakePacks(s);
}

set<ID> Client::MakePacks(string s){
    set<ID> ret;
    auto v = split(s, ';');
    for(const auto& i:v) ret.insert(stoi(i));
    return ret;
}

string Client::GetPacks(const string& delim) const noexcept{
    return join(vtravel_.cbegin(), vtravel_.cend(), to_string, delim);
}

bool Client::UserClient(istream& is, ostream& os) noexcept{
    if(!vin("Name: "                                       ,                   name_   , is, os) ||
       !vin("VAT: "                                        ,                   vat_    , is, os)) return false;
    int i;
    while(true){
        if(!vin("Household members: "                      ,                   i       , is, os)) return false;
        if(1 <= i) break;
        else       os << "Number of household members out of valid range >=1" << endl;
    }
    numFam_ = (unsigned)i;
    if(!vin("Address (street/door/floor/postalcode/city): ", Address::Set    , address_, is, os) ||
       !vin("Bought packs (separated by ';'): "            , Client::SetPacks, *this   , is, os)) return false;
    return true;
}

bool Client::UserClientprop(unsigned propn, istream& is, ostream& os){
    switch(propn){
        case 0: os << "Name: "           << name_      << endl; if(!vin("New name: "          ,                   name_   , is, os)) return false; break;
        case 1: os << "VAT: "            << vat_       << endl; if(!vin("New VAT: "           ,                   vat_    , is, os)) return false; break;
        case 2: os << "Household size: " << numFam_    << endl;
            int i;
            while(true){
                if(!vin("New household size: ", i, is, os)) return false;
                if(1 <= i) break;
                else       os << "Number of household members out of valid range >=1" << endl;
            }
            numFam_ = (unsigned)i;
            break;
        case 3: os << "Address: "        << address_   << endl; if(!vin("New address: "       , Address::Set    , address_, is, os)) return false; break;
        case 4: os << "Travel pack sells should be handled by operation 'sell' [10]" << endl; return false; break;
        case 5: os << "Travel pack sells should be handled by operation 'sell' [10]" << endl; return false; break;
        default: throw out_of_range("trying to access client property that does not exist");
    }
    return true;
}

template<class ForwardIterator>
ostream& Client::Print(ForwardIterator first, ForwardIterator last, string f, ostream& os){
    if(first == last){
        return (os << "No clients were found" << endl);
    }
    if(f == "table"){
        os << ljust("#"              ,  4)
           << ljust("Name"           , 54) << "\t"
           << ljust("VAT"            ,  9)
           << rjust("#Household"     , 12) << "  "
           << ljust("Address"        , 60) << "\t"
           << ljust("Bought packs"   , 18)
           << rjust("Total purchased", 17)
           << endl;
        os << string(187, '=') << endl;
        unsigned i = 0;
        for(auto it = first; it != last; ++it, ++i){
            const auto& c = *it;
            os << ljust(to_string(i)            ,  4);
            os << ljust(c.GetName()                     , 54) << "\t";
            os << ljust(c.GetVAT()                      ,  9);
            os << rjust(to_string(c.GetNumFamily()), 12) << "  ";
            os << ljust(c.GetAddress().str()            , 60) << "\t";
            os << ljust(c.GetPacks("; ")             , 18);
            os << rjust(to_string(c.GetTotalPurchased()), 17);
            os << endl;
        }
    }else if(f == "screenfull"){
        if(last != first){
            const auto& c = *first;
            os << "#"                                          << endl;
            os << "0   Name:            " << c.name_           << endl;
            os << "1   VAT:             " << c.vat_            << endl;
            os << "2   Household size:  " << c.numFam_         << endl;
            os << "3   Address:         " << c.address_        << endl;
            os << "4   Bought packs:    " << c.GetPacks("; ")  << endl;
            os << "5   Total purchased: " << c.totalPurchased_ << endl;
        }
    } return os;
}
template ostream& Client::Print(multiset<Client>::const_iterator first, multiset<Client>::const_iterator last, string f, ostream& os);

bool Client::operator<(const Client& c) const noexcept{
    if     (name_    != c.name_   ) return (name_    < c.name_   );
    else if(vat_     != c.vat_    ) return (vat_     < c.vat_    );
    else if(numFam_  != c.numFam_ ) return (numFam_  < c.numFam_ );
    else if(address_ != c.address_) return (address_ < c.address_);
    else                            return (vtravel_ < c.vtravel_);
}

istream& operator>>(istream& is, Client& c){
    vin(                  c.name_          , is);
    vin(                  c.vat_           , is);
    vin(                  c.numFam_        , is);
    vin(Address::Set    , c.address_       , is);
    vin(Client::SetPacks, c                , is);
    vin(                  c.totalPurchased_, is);
    return is;
}

ostream& operator<<(ostream& os, const Client& c){
    os << c.name_      << endl;
    os << c.vat_       << endl;
    os << c.numFam_    << endl;
    os << c.address_   << endl;
    os << c.GetPacks() << endl;
    os << c.totalPurchased_;
    return os;
}
