#include "client.h"

#include "vin.h"

void Client::setPacks(Client& c, std::string s){
    c.vtravel_ = makePacks(s);
}

std::vector<ID> Client::makePacks(std::string s){
    std::vector<ID> ret;
    std::vector<std::string> v = split(s, ';');
    for(auto i:v) ret.push_back(std::stoi(i));
    return ret;
}

std::string Client::getPacks() const{
    std::string ret = join(vtravel_.begin(), vtravel_.end(), std::to_string, " ; ");
    return ret;
}

bool Client::userClient(std::istream& is, std::ostream& os){
    if(!vin("Nome: "                                 ,                   name_   ) ||
       !vin("NIF: "                                  ,                   nif_    ) ||
       !vin("Número de elementos da família: "       ,                   numFam_ ) ||
       !vin("Morada: "                               , Address::set    , address_) ||
       !vin("Pacotes comprados (separados por ';'): ", Client::setPacks, *this   ))
        return false;
    return true;
}

bool Client::userClientprop(int propn, std::istream& is, std::ostream& os){
    switch(propn){
        case 0: os << "Nome: "                           << name_      << std::endl; if(!vin("Novo nome: "                          ,                   name_   )) return false; break;
        case 1: os << "NIF: "                            << nif_       << std::endl; if(!vin("Novo NIF: "                           ,                   nif_    )) return false; break;
        case 2: os << "Número de elementos da família: " << numFam_    << std::endl; if(!vin("Novo número de elementos da família: ",                   numFam_ )) return false; break;
        case 3: os << "Morada: "                         << address_   << std::endl; if(!vin("Nova morada: "                        , Address::set    , address_)) return false; break;
        case 4: os << "Compras de pacotes devem ser processadas através da operação [sell]" << std::endl; return false; break;
        default: throw std::invalid_argument("trying to access client property that does not exist");
    }
    return true;
}

template<class ForwardIterator>
std::ostream& Client::print(ForwardIterator first, ForwardIterator last, std::string f, std::ostream& os){
    if(f == "table"){
        os << setwidth("#"     ,     4) << "   "
           << setwidth("Nome"  ,    42) << " \t"
           << setwidth("NIF"   ,     9) << "   "
           << setwidth("NumFam",     6) << " "
           << setwidth("Morada",    60) << " \t"
           << std::endl;
        os << std::string(140, '-') << std::endl;
        unsigned i = 0;
        for(auto it = first; it != last; ++it, ++i){
            const auto& c = *it;
            os << setwidth(std::to_string(i)                ,  4) << "   ";
            os << setwidth(c.name()                         , 42) << " \t";
            os << setwidth(c.nif()                          ,  9) << "   ";
            os << setwidth(std::to_string(c.numFamily())    ,  6) << " ";
            os << setwidth(std::string(c.address())         , 60) << " \t";
            os << std::endl;
        }
    }else if(f == "screenfull"){
        if(last != first){
            const auto& c = *first;
            os << "#"                                                << std::endl;
            os << "0      Nome:                            " << c.name_    << std::endl;
            os << "1      NIF:                             " << c.nif_     << std::endl;
            os << "2      Número de elementos da família:  " << c.numFam_  << std::endl;
            os << "3      Morada:                          " << c.address_ << std::endl;
            os << "4      Pacotes comprados:               ";
            if(!c.vtravel_.empty()){
                os << c.vtravel_[0];
                for(unsigned i = 1; i < c.vtravel_.size(); ++i)
                    os << " ; " << c.vtravel_[i];
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
    std::stringstream dummy;
    if(!vin("",                   c.name_   , is, dummy) ||
       !vin("",                   c.nif_    , is, dummy) ||
       !vin("",                   c.numFam_ , is, dummy) ||
       !vin("", Address::set    , c.address_, is, dummy) ||
       !vin("", Client::setPacks, c         , is, dummy))
       throw std::invalid_argument("could not read client file");
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
