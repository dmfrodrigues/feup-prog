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
    std::string agencypath, travelpath, clientpath;
    std::string name;
    NIF nif;
    URL url;
    Address address;
    std::multiset<Client    > vclient;
    std::map<ID, TravelPack> vtravel; unsigned lasttravel;

    /**
    Loads client list from content of file
    @param  fpath   string containing the location of the input file
    */
    void loadClients(std::string fpath);
    /***/
    void loadPacks(std::string fpath);
    /***/
    void addClient();
    /***/
    std::pair<unsigned, bool> seeClient() const;
    /***/
    void changeClient();
    /***/
    void deleteClient();
    /***/
    void addPack();
    /***/
    std::pair<unsigned, bool> seePack() const;
    /***/
    void changePack();
    /***/
    void deletePack();
    /***/
    void findPack();
    /***/
    void save() const;
public:
    /**
    Constructs Agency object from content of file.
    @param fpath string containing the location of the input file
    */
    Agency();

    /***/
    void run();

    /***/
    std::ostream& print(std::ostream& os = std::cout);

    /***/
    std::ostream& printHelp(std::ostream& os = std::cout) const;
};

/***/
std::istream& operator>>(std::istream& is, Agency& a);

/***/
std::ostream& operator<<(std::ostream& os, const Agency& a);


#endif
