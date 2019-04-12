#pragma once
#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include "address.h"
#include "name.h"
#include "nif.h"
#include "travelpack.h"
#include <set>

/**
 * Stores client data, provides some helpers
 */
struct Client{
friend std::istream& operator>>(std::istream& is,       Client& c);
friend std::ostream& operator<<(std::ostream& os, const Client& c);
private:
    Name name_;             ///name of client
    NIF nif_;               ///numero de identificacao fiscal
    unsigned numFam_;            ///number of household members
    Address address_;       ///address
    std::set<ID> vtravel_;  ///set of bought packs

    /**
     * Changes content of vtravel_ by parsing the contents of a string
     * @param c 'Client' object of which vtravel_ will be changed
     * @param s string with several semicolon-separated IDs
     * @throws   std::invalid_argument no conversion could be performed (from Client::makePacks)
     * @throws   std::out_of_range value read is out of int range (from Client::makePacks)
     */
    static void setPacks(Client& c, std::string s);

    /**
     * Returns string containing delim-separated elements of vtravel_
     * @param  delim delimiter
     * @return       string with delim-separated elements of vtravel_
     * @exceptsafe   no-throw (may throw bad_alloc from string constructor, but
     *      if that failed then it is not even worth to keep trying)
     */
    std::string getPacks(const std::string& delim = " ; ") const noexcept;

public:
    /**
     * From a semicolon-separated list of integers, returns their values in a std::set
     * @param  s semicolon-separated list of integers
     * @return   std::set containing all integers in s
     * @throws   std::invalid_argument no conversion could be performed (from std::stoi)
     * @throws   std::out_of_range value read is out of int range (from std::stoi)
     */
    static std::set<ID> makePacks(std::string s);

    /**
     * Queries user about properties of new client object
     * @param  is input stream
     * @param  os output stream
     * @return    true if new client was created successfully, false if cancelled
     * @throws    when vin throws
     */
    bool userClient(std::istream& is, std::ostream& os) noexcept;

    /**
     * Change one property of Client
     * @param  propn index of property (check src code to see which index corresponds to which property)
     * @param  is    input stream
     * @param  os    output stream
     * @return       true if property was changed successfully, false if cancelled
     * @throws       when 'is', 'os' throw
     * @throws       when vin throws
     * @throws  std::out_of_range when propn is not in the valid range
     */
    bool userClientprop(unsigned propn, std::istream& is, std::ostream& os);

    /**
     * 'Get' functions
     * @return const reference to corresponding member variable
     * @exceptsafe  no-throw
     */
    const Name&         name     ()const noexcept{ return name_   ; }
    const NIF&          nif      ()const noexcept{ return nif_    ; }
    const unsigned&     numFamily()const noexcept{ return numFam_ ; }
    const Address&      address  ()const noexcept{ return address_; }
    const std::set<ID>& vtravel  ()const noexcept{ return vtravel_; }

    /**
     * Sell pack with certain ID to the client
     * @param id ID of the travel pack
     * @exceptsafe  no-throw
     */
    void sell(ID id) noexcept{ vtravel_.insert(id); }

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
    static std::ostream& print(ForwardIterator first, ForwardIterator last, std::string f, std::ostream& os);

    /**
     * Compare clients (meant for comparator in std::set)
     * @param obj right-hand side of the comparison
     * @return    true if *this is smaller than obj, false otherwise
     * @exceptsafe no-throw
     */
    bool operator<(const Client& obj) const noexcept;
};

/**
 * Extracts content to fill 'Client' object
 * Destined to be used to read from files
 * @param is input stream where Client will be read from
 * @param c  receiver of the extracted information
 * @return   the same parameter as is
 * @throws   when vin(), is throw
 */
std::istream& operator>>(std::istream& is, Client& c);

/**
 * Inserts the content of a 'Client' object into a ostream
 * Destined to be used to write to files
 * @param os output stream
 * @param c  'Client' object with the content to insert
 * @return   the same as parameter os
 * @throws   when os throws
 */
std::ostream& operator<<(std::ostream& os, const Client& c);

#endif
