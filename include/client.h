#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include <set>
#include "globaldefs.h"
#include "address.h"
#include "travelpack.h"
#include "convenient.h"


struct Client{
friend std::istream& operator>>(std::istream& is,       Client& c);
friend std::ostream& operator<<(std::ostream& os, const Client& c);
private:
    Name name_;
    NIF nif_;
    int numFam_;
    Address address_;
    std::vector<ID> vtravel_;
    //TOTAL DE COMPRAS EFETUADAS?

    static void setPacks(Client* cptr, std::string s);




public:

    static std::vector<ID> makePacks(std::string s);
    /***/
    bool userClient(std::istream& is = std::cin, std::ostream& os = std::cout);
    /***/
    bool userClientprop(int propn, std::istream& is = std::cin, std::ostream& os = std::cout);

    /***/
    const std::string&     name     ()const{ return name_   ; }
    const NIF&             nif      ()const{ return nif_    ; }
    const int&             numFamily()const{ return numFam_ ; }
    const Address&         address  ()const{ return address_; }
    const std::vector<ID>& vtravel  ()const{ return vtravel_; }




    /***/
    bool operator<(const Client& obj) const;
    /***/
    template<class InputIterator>
    static std::ostream& print(InputIterator first, InputIterator last, std::string f, std::ostream& os = std::cout){
        if(f == "table"){
            os << setwidth("#"     ,     4) << "   "
               << setwidth("Nome"  ,    42) << " \t"
               << setwidth("NIF"   ,     9) << "   "
               << setwidth("NumFam",     6) << " "
               << setwidth("Morada",    60) << " \t"
               << std::endl;



            os << std::string(140, '-');
            unsigned i = 0;
            for(auto it = first; it != last; ++it, ++i){
                const auto& c = *it;
                os << std::endl;
                os << setwidth(std::to_string(i)                ,  4) << "   ";
                os << setwidth(c.name()                         , 42) << " \t";
                os << setwidth(c.nif()                          ,  9) << "   ";
                os << setwidth(std::to_string(c.numFamily())    ,  6) << " ";
                os << setwidth(c.address().str()                , 60) << " \t";
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
                }
            }
        } return os;
    }
};

/***/
std::istream& operator>>(std::istream& is, Client& c);

/***/
std::ostream& operator<<(std::ostream& os, const Client& c);

#endif
