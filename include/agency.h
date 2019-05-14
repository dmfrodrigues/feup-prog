#pragma once
#ifndef AGENCY_H_INCLUDED
#define AGENCY_H_INCLUDED

#include "client.h"
#include <map>

#if defined(_WIN32)
    #define CLEAR() system("cls")
#elif defined(unix) || defined(__unix__) || defined(__unix)
    #define CLEAR() system("clear")
#endif

using namespace std;

typedef string URL;

/**
* Allows to manage a tourist Agency
*/
class Agency{
private:
    string inputpath;  ///folder where all the files are
    string agencypath; ///name of agency file
    string travelpath; ///name of travelpacks' file
    string clientpath; ///name of clients' file
    string name;
    NIF nif;
    URL url;
    Address address;
    multiset<Client   > vclient; ///multiset with the agency clients
    map<ID, TravelPack> vtravel; ///map with the agency travelpacks
    ID lasttravel;               ///ID of the last added travelpack

    bool InfoChanged = false;               ///

    istream& cis;                ///default input stream
    ostream& cos;                ///default output stream

    static const string opstr;
    static const int WIDTH = 74;

    /**
     * Loads agency data and client/travelpack info
     * @param  fpath path to agency file
     * @return       true if input was successfull, false otherwise
     */
    bool loadAgency(const string& fpath);

    /**
     * Loads client list from content of file to vclient
     * @param  fpath path to clients file
     * @return       true if input was successfull, false otherwise
     */
    bool loadClients(const string& fpath);

    /**
     * Display all clients in a table
     */
    void tclient() const;

    /**
     * Select and see all data of a client
     * @return pair, first element is index of selected client, second element is false if cancelled, true otherwise
     * @throws when cis, cos throw
     */
    pair<unsigned, bool> seeClient() const;

    /**
     * Allow user to see all info about a specific client
     */
    void sclient() const;

    /**
     * Add client by asking the user its data
     * @throws when cis, cos throw
     */
    void pclient();

    /**
     * Change client data through Client::userClientprop()
     */
    void cclient();

    /**
     * Delete client from vclient
     */
    void mclient();

    /**
     * Loads travelpack list from content of file to vtravel
     * @param  fpath path to clients file
     * @return       true if input was successfull, false otherwise
     */
    bool loadPacks(const string& fpath);

    /**
     * Display all travelpacks in a table
     */
    void tpack() const;

    /**
     * Select and see all data of a travelpack
     * @return pair, first element is ID of selected pack, second element is false if cancelled, true otherwise
     */
    pair<ID, bool> seePack() const;

    /**
     * Allow user to see all info about a specific travelpack
     */
    void spack() const;

    /**
     * Add client by asking the user its data
     */
    void ppack();

    /**
     * Change travelpack data through TravelPack::userPackprop()
     */
    void cpack();

    /**
     * Delete pack from vtravel
     */
    void mpack();

    /**
     * Find all packs that satisfy certain search options (destination(s), begin
     * and end date), and show them in a table
     */
    void fpack() const;

    /**
     * Print a table of most visited places
     */
    void nplaces() const;

    /**
     * Present, for each client and in a table, the most visited destination
     * that they have not visited yet
     */
    void suggest() const;

    /**
     * Display some numbers about packs sold to one client or all clients.
     * Calculates the revenue of each travelpack
     */
    void sold() const;

    /**
     * Sell travelpack to a client
     */
    void sell();

    /**
     * prints header of agency, with a sentence and '=' after that
     */
    void header(const string& s) const;

    /**
     * Save content of all data structures to files
     * @return  true if save was successfull
     */
    bool save();

    /**
     * Exit program
     * @return  true if program can correctly exit program, false otherwise
     */
    bool exit() const;

public:
    /**
     * Constructs Agency object. Asks the user for path of agency file
     * @param is input stream
     * @param os output stream
     */
    Agency(istream& is = cin, ostream& os = cout);

    /**
     *
     * Print agency details to cos
     * @return true if print was successfull, false otherwise
     */
    bool print() const;

    /**
     * Print help (list of commands) to cos
     * @return true if print was successfull, false otherwise
     */
    bool printHelp() const;

    /**
     * Runs the agency, allowing the user to execute the operations
     */
    void run();

};

#endif
