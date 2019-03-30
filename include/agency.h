#pragma once
#ifndef AGENCY_H_INCLUDED
#define AGENCY_H_INCLUDED

#include <map>
#include "client.h"

typedef std::string URL;

/**
* Allows to manage a tourist Agency
*/
struct Agency{
friend std::istream& operator>>(std::istream& is,       Agency& a);
friend std::ostream& operator<<(std::ostream& os, const Agency& a);
private:
    std::string inputpath;  ///folder where all the files are
    std::string agencypath; ///name of agency file
    std::string travelpath; ///name of travelpacks' file
    std::string clientpath; ///name of clients' file
    std::string name;
    NIF nif;
    URL url;
    Address address;
    std::multiset<Client   > vclient; ///multiset with the agency clients
    std::map<ID, TravelPack> vtravel; ///map with the agency travelpacks
    ID lasttravel;                    ///ID of the last added travelpack

    std::istream& cis;                ///default input stream
    std::ostream& cos;                ///default output stream

    /**
    Loads client list from content of file to vclient
    @param  fpath   string containing the location of the input file
    @throws         std::ios_base::failure  when std::ifstream fails to open file
    */
    void loadClients(const std::string& fpath);
    /***/
    void addClient();
    /***/
    std::pair<unsigned, bool> seeClient() const;
    /***/
    void changeClient();
    /***/
    void deleteClient();
    /***/
    void loadPacks(const std::string& fpath);
    /***/
    void addPack();
    /***/
    std::pair<ID, bool> seePack() const;
    /***/
    void changePack();
    /***/
    void deletePack();
    /***/
    void findPack() const;
    /***/
    void seeSold() const;
    /***/
    void sell();
    /***/
    std::ostream& save(std::ostream& os) const;
    std::ostream& save() const{ return save(cos); }
public:
    /**
    Constructs Agency object. Asks the user for path of agency file
    @param fpath string containing the location of the input file
    @exceptsafe no-throw
    */
    Agency(std::istream& is = std::cin, std::ostream& os = std::cout) noexcept;

    /***/
    std::ostream& print(std::ostream& os) const;
    std::ostream& print() const{ return print(cos); }

    /***/
    std::ostream& printHelp(std::ostream& os) const;
    std::ostream& printHelp() const{ return printHelp(cos); }

    /**
    Runs the agency, allowing the user to execute the operations

    */
    void run();


};

/***/
std::istream& operator>>(std::istream& is, Agency& a);

/***/
std::ostream& operator<<(std::ostream& os, const Agency& a);


#endif
