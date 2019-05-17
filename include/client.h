#pragma once
#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include "address.h"
#include "name.h"
#include "vat.h"
#include "travelpack.h"
#include <set>

using namespace std;

/**
 * Stores client data, provides some helpers
 */
class Client{
private:
    Name name_;         ///name of client
    VAT vat_;           ///numero de identificacao fiscal
    unsigned numFam_;   ///number of household members
    Address address_;   ///address
    set<ID> vtravel_;   ///set of bought packs
    Price   totalPurchased_; ///

    /**
     * Changes content of vtravel_ by parsing the contents of a string
     * @param c 'Client' object of which vtravel_ will be changed
     * @param s string with several semicolon-separated IDs
     * @throws   invalid_argument no conversion could be performed (from Client::makePacks)
     * @throws   out_of_range value read is out of int range (from Client::makePacks)
     */
    static void SetPacks(Client& c, string s);

    /**
     * Returns string containing delim-separated elements of vtravel_
     * @param  delim delimiter
     * @return       string with delim-separated elements of vtravel_
     * @exceptsafe   no-throw (may throw bad_alloc from string constructor, but
     *      if that failed then it is not even worth to keep trying)
     */
    string GetPacks(const string& delim = " ; ") const noexcept;

public:
    /**
     * From a semicolon-separated list of integers, returns their values in a set
     * @param  s semicolon-separated list of integers
     * @return   set containing all integers in s
     * @throws   invalid_argument no conversion could be performed (from stoi)
     * @throws   out_of_range value read is out of int range (from stoi)
     */
    static set<ID> MakePacks(string s);

    /**
     * Queries user about properties of new client object
     * @param  is input stream
     * @param  os output stream
     * @return    true if new client was created successfully, false if cancelled
     * @throws    when vin throws
     */
    bool UserClient(istream& is, ostream& os) noexcept;

    /**
     * Change one property of Client
     * @param  propn index of property (check src code to see which index corresponds to which property)
     * @param  is    input stream
     * @param  os    output stream
     * @return       true if property was changed successfully, false if cancelled
     * @throws       when 'is', 'os' throw
     * @throws       when vin throws
     * @throws  out_of_range when propn is not in the valid range
     */
    bool UserClientprop(unsigned propn, istream& is, ostream& os);

    /**
     * 'Get' functions
     * @return const reference to corresponding member variable
     * @exceptsafe  no-throw
     */
    const Name&     GetName          ()const noexcept{ return name_   ;        }
    const VAT&      GetVAT           ()const noexcept{ return vat_    ;        }
    const unsigned& GetNumFamily     ()const noexcept{ return numFam_ ;        }
    const Address&  GetAddress       ()const noexcept{ return address_;        }
    const set<ID>&  GetVTravel       ()const noexcept{ return vtravel_;        }
    const Price&    GetTotalPurchased()const noexcept{ return totalPurchased_; }

    /**
     * Sell pack with certain ID to the client
     * @param id ID of the travel pack
     * @exceptsafe  no-throw
     */
    void Sell(ID id) noexcept{ vtravel_.insert(id); }

    /**
     * Print clients to screen
     * options:
     *      "table":        print in table
     *      "screenfull":   print all properties of *first
     * @param  first input iterator to first element
     * @param  last  input iterator to past-the-end element
     * @param  f     options
     * @param  os    output stream
     * @return       the same output stream
     * @throws       if os throws
     */
    template<class ForwardIterator>
    static ostream& Print(ForwardIterator first, ForwardIterator last, string f, ostream& os);

    /**
     * Compare clients (meant for comparator in set)
     * @param obj right-hand side of the comparison
     * @return    true if *this is smaller than obj, false otherwise
     * @exceptsafe no-throw
     */
    bool operator<(const Client& obj) const noexcept;

    /**
     * Extracts content to fill 'Client' object
     * Destined to be used to read from files
     * @param is input stream where Client will be read from
     * @param c  receiver of the extracted information
     * @return   the same parameter as is
     * @throws   when vin(), is throw
     */
    friend istream& operator>>(istream& is, Client& c);

    /**
     * Inserts the content of a 'Client' object into a ostream
     * Destined to be used to write to files
     * @param os output stream
     * @param c  'Client' object with the content to insert
     * @return   the same as parameter os
     * @throws   when os throws
     */
    friend ostream& operator<<(ostream& os, const Client& c);
};

#endif
