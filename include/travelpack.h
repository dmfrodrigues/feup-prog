#ifndef TRAVELPACK_H_INCLUDED
#define TRAVELPACK_H_INCLUDED

#include <string>
#include <vector>

#include <iostream>
#include "globaldefs.h"
#include "date.h"
#include "convenient.h"

typedef int ID;

struct TravelPack{
friend std::istream& operator>>(std::istream& is,       TravelPack& t);
friend std::ostream& operator<<(std::ostream& os, const TravelPack& t);
private:
    ID id_;
    bool avail_;
    std::vector<std::string> vplaces_;
    Date begin_;
    Date end_;
    Price price_;
    int numMax_;
    int numSold_;
    /***/
    std::string getPlaces()const;
    /***/
    static void setPlaces(TravelPack& t, std::string s);
public:
    /***/
    static std::vector<std::string> makePlaces(std::string s);
    /***/
    bool userPack(ID lasttravel, std::istream& is = std::cin, std::ostream& os = std::cout);
    /***/
    bool userPackprop(int propn, std::istream& is = std::cin, std::ostream& os = std::cout);

    /***/
    const ID&                       id     ()const{ return id_     ; }
    const bool&                     avail  ()const{ return avail_  ; }
    const std::vector<std::string>& vplaces()const{ return vplaces_; }
    const Date&                     begin  ()const{ return begin_  ; }
    const Date&                     end    ()const{ return end_    ; }
    const Price&                    price  ()const{ return price_  ; }
    const int&                      numMax ()const{ return numMax_ ; }
    const int&                      numSold()const{ return numSold_; }



    /***/
    template<class InputIterator>
    static std::ostream& print(InputIterator first, InputIterator last, std::string f, std::ostream& os = std::cout){
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
};

/***/
std::istream& operator>>(std::istream& is, TravelPack& t);

/***/
std::ostream& operator<<(std::ostream& os, const TravelPack& t);

#endif
