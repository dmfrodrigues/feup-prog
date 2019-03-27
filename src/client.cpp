#include "client.h"

#include "vin.h"

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
    std::string ret = join(vtravel_.begin(), vtravel_.end(), &std::to_string, " ; ");
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


bool Client::operator<(const Client& c) const{
    if     (name_    != c.name_   ) return (name_    < c.name_   );
    else if(nif_     != c.nif_    ) return (nif_     < c.nif_    );
    else if(numFam_  != c.numFam_ ) return (numFam_  < c.numFam_ );
    else if(address_ != c.address_) return (address_ < c.address_);
    else                            return (vtravel_ < c.vtravel_);
}
