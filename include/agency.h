#ifndef AGENCY_H_INCLUDED
#define AGENCY_H_INCLUDED

#include <string>
#include <vector>
#include <set>
#include <map>
#include "globaldefs.h"
#include "address.h"
#include "travelpack.h"
#include "client.h"

typedef std::string URL;

struct Agency{
friend std::istream& operator>>(std::istream& is,       Agency& a);
friend std::ostream& operator<<(std::ostream& os, const Agency& a);
private:
    std::string agencypath, travelpath, clientpath, inputpath;
    std::string name;
    NIF nif;
    URL url;
    Address address;
    std::multiset<Client   > vclient;
    std::map<ID, TravelPack> vtravel; ID lasttravel;

    /**
    Loads client list from content of file
    @param  fpath   string containing the location of the input file
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
    std::ostream& save(std::ostream& os = std::cout) const;
public:
    /**
    Constructs Agency object from content of file.
    @param fpath string containing the location of the input file
    */
    Agency();

    /***/
    void run();

    /***/
    std::ostream& print(std::ostream& os = std::cout) const;

    /***/
    std::ostream& printHelp(std::ostream& os = std::cout) const;
};

/***/
std::istream& operator>>(std::istream& is, Agency& a);

/***/
std::ostream& operator<<(std::ostream& os, const Agency& a);


#endif
