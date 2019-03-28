#ifndef TRAVELPACK_H_INCLUDED
#define TRAVELPACK_H_INCLUDED


#include <iostream>
#include <string>
#include <vector>
#include "convenient.h"
#include "date.h"
#include "globaldefs.h"

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
    template<class ForwardIterator>
    static std::ostream& print(ForwardIterator first, ForwardIterator last, std::string f, std::ostream& os = std::cout);
};

/***/
std::istream& operator>>(std::istream& is, TravelPack& t);

/***/
std::ostream& operator<<(std::ostream& os, const TravelPack& t);

#endif
