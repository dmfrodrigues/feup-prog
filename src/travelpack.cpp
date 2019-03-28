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
    if(!vin("Destino (principal - secundários separados por ','): ", TravelPack::setPlaces, *this  ) ||
       !vin("Data de início (yyyy/mm/dd): "                        , Date::set            , begin_ ) ||
       !vin("Data de fim (yyyy/mm/dd): "                           , Date::set            , end_   ) ||
       !vin("Preço por pessoa: "                                   ,                        price_ ) ||
       !vin("Número máximo de pessoas: "                           ,                        numMax_))
        return false;
    numSold_ = 0;
    return true;
}

bool TravelPack::userPackprop(int propn, std::istream& is, std::ostream& os){
    std::string b;
    switch(propn){
        case 0: os << "O ID de um pacote turístico não pode ser alterado" << std::endl; return false; break;
        case 1: os << "Disponibilidade: "          << (avail_?"sim":"não") << std::endl;
            while(true){
                if(!vin("Novo valor de disponibilidade [sim/não]: ", b)) return false;
                if(b == "sim" || b == "não") break;
                else os << "Apenas os valores [sim] e [não] são válidos" << std::endl;
            }
            avail_ = (b == "sim");
            break;
        case 2: os << "Destino: "                  << getPlaces() << std::endl; if(!vin("Novo destino: "         , TravelPack::setPlaces, *this  )) return false; break;
        case 3: os << "Data de início: "           << begin_      << std::endl; if(!vin("Nova data de início: "  , Date::set            , begin_ )) return false; break;
        case 4: os << "Data de fim: "              << end_        << std::endl; if(!vin("Nova data de fim: "     , Date::set            , end_   )) return false; break;
        case 5: os << "Preço por pessoa: "         << price_      << std::endl; if(!vin("Novo preço por pessoa: ",                        price_ )) return false; break;
        case 6: os << "Número máximo de pessoas: " << numMax_     << std::endl; if(!vin("Novo número máximo de pessoas: ",                numMax_)) return false; break;
        case 7: os << "Vendas de lugares devem ser processadas através da operação [sell]" << std::endl; return false; break;
        default: throw std::invalid_argument("trying to access travelpack property that does not exist");
    }
    return true;
}

template<class ForwardIterator>
std::ostream& TravelPack::print(ForwardIterator first, ForwardIterator last, std::string f, std::ostream& os){
    if(f == "table"){
        os << setwidth("ID"            ,  4) << "   "
           << setwidth("Disp"          ,  4) << "\t"
           << setwidth("Destino"       , 53) << " \t"
           << setwidth("Inicio"        , 12) << " "
           << setwidth("Fim"           , 12) << " "
           << setwidth("Preco"         ,  5) << " "
           << setwidth("MaxPessoas"    , 10) << " "
           << setwidth("Vendidos"      ,  8) << " "
           << std::endl;
        os << std::string(120, '-') << std::endl;;
        for(auto it = first; it != last; ++it){
            const auto& t = it->second;
            os << setwidth(std::to_string(t.id     ()),  4) << "   ";
            os << setwidth((t.avail()? "sim" : "não") ,  4) << "\t";
            os << setwidth(t.getPlaces()              , 53) << " \t";
            os << setwidth(std::string(t.begin())     , 12) << " ";
            os << setwidth(std::string(t.end())       , 12) << " ";
            os << setwidth(std::to_string(t.price  ()),  5) << " ";
            os << setwidth(std::to_string(t.numMax ()), 10) << " ";
            os << setwidth(std::to_string(t.numSold()),  8) << " ";
            os << std::endl;
        }
    }else if(f == "screenfull"){
        if(last != first){
            const auto& t = first->second;
            os << "#"                                                    << std::endl;
            os << "0      ID:                " << t.id_                  << std::endl;
            os << "1      Disponibilidade:   " << (t.avail_?"sim":"não") << std::endl;
            os << "2      Destino:           " << t.getPlaces()          << std::endl;
            os << "3      Data de início:    " << t.begin_               << std::endl;
            os << "4      Data de fim:       " << t.end_                 << std::endl;
            os << "5      Preço por pessoa:  " << t.price_               << std::endl;
            os << "6      Máximo de pessoas: " << t.numMax_              << std::endl;
            os << "7      Lugares vendidos:  " << t.numSold_             << std::endl;
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
