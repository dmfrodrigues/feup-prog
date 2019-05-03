#pragma once
#ifndef TRAVELPACK_H_INCLUDED
#define TRAVELPACK_H_INCLUDED

#include "date.h"
#include <vector>

using namespace std;

typedef int ID;
typedef int Price;

/**
 * Stores travel pack data, provides some helpers
 */
class TravelPack{
friend istream& operator>>(istream& is,       TravelPack& t);
friend ostream& operator<<(ostream& os, const TravelPack& t);
private:
    ID id_;                             ///ID of the pack
    bool avail_;                        ///availability
    vector<string> vplaces_;  ///vector of destination places
    Date begin_;                        ///begin date
    Date end_;                          ///end date
    Price price_;                       ///price per person
    unsigned numMax_;                   ///max number of people
    unsigned numSold_;                  ///number of sold tickets

    /**
     * Changes content of vplaces_ by parsing the contents of a string
     * @param t 'TravelPack' object of which vplaces_ will be changed
     * @param s string with several dash- and comma-separated destinations
     * @throws  invalid_argument    s does not have at least 1 field (same as makePlaces)
     */
    static void setPlaces(TravelPack& t, string s);

    /**
     * Returns string containing destinations from vtravel_
     * @return string with comma- and dash-separated elements of vtravel_
     * @exceptsafe  no-throw
     */
    string getPlaces() const noexcept;

public:

    /**
     * From a dash- and comma-separated list of destinations, returns the string of destinations
     * @param s dash- and comma-separated list of destinations
     * @return  vector containing all destinations in s
     * @throws  invalid_argument    s does not have at least 1 field
     */
    static vector<string> makePlaces(string s);

    /**
     * Queries user about properties of new travelpack object
     * @param  lasttravel index of last travel (so the new travelpack has a unique ID)
     * @param  is         input stream
     * @param  os         output stream
     * @return            true if the new travelpack was created successfully, false if cancelled
     * @throws            when vin throws
     */
    bool userPack(ID lasttravel, istream& is, ostream& os);

    /**
     * Change one property of TravelPack
     * @param  propn index of property (check src code to see which index corresponds to which property)
     * @param  is    input stream
     * @param  os    output stream
     * @return       true if property was changed successfully, false if cancelled
     * @throws       when is, os throw
     * @throws       when vin throws
     * @throws  out_of_range when propn is not in the valid range
     */
    bool userPackprop(unsigned propn, istream& is, ostream& os);

    /**
     * 'Get' functions
     * @return const reference to corresponding member variable
     * @exceptsafe  no-throw
     */
    const ID&                       id     ()const noexcept{ return id_     ; }
    const bool&                     avail  ()const noexcept{ return avail_  ; }
    const vector<string>& vplaces()const noexcept{ return vplaces_; }
    const Date&                     begin  ()const noexcept{ return begin_  ; }
    const Date&                     end    ()const noexcept{ return end_    ; }
    const Price&                    price  ()const noexcept{ return price_  ; }
    const unsigned&                 numMax ()const noexcept{ return numMax_ ; }
    const unsigned&                 numSold()const noexcept{ return numSold_; }

    /**
     * Checks if this travelpack can be sold
     * @return true if can be sold, false if not available or sold out
     * exceptsafe   no-throw
     */
    bool sellable() noexcept{ return (avail_ && numSold_ < numMax_); }

    /**
     * Sell this pack to someone
     * @return  true if pack was successfully bought, false if it sold out
     * @exceptsafe  no-throw
     */
    bool sell() noexcept{ if(sellable()){ ++numSold_; return true;} return false; }

    /**
     * Print travelpacks to screen
     * options:
     *      "table":        print in table
     *      "sold":         print in table, with additional revenue stats
     *      "screenfull":   print all properties of *first
     * @param  first input iterator to first element
     * @param  last  input iterator to past-the-end element
     * @param  f     options
     * @param  os    output stream
     * @return       the same output stream
     * @throws       when os throws
     */
    template<class ForwardIterator>
    static ostream& print(ForwardIterator first, ForwardIterator last, string f, ostream& os);
};

/**
 * Extracts content to fill 'TravelPack' object
 * Destined to be used to read from files
 * @param is input stream where TravelPack will be read from
 * @param t  receiver of the extracted information
 * @return   the same parameter as is
 * @throws   when vin(), is throws
 */
istream& operator>>(istream& is, TravelPack& t);

/**
 * Inserts the content of a 'TravelPack' object into a ostream
 * Destined to be used to write to files
 * @param os output stream
 * @param t  'TravelPack' object with the content to insert
 * @return   the same as parameter os
 * @throws   when os throws
 */
ostream& operator<<(ostream& os, const TravelPack& t);

#endif
