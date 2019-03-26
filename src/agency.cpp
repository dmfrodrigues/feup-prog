#include "agency.h"

#include <fstream>
#include "vin.h"

Agency::Agency(){
    std::ifstream is;
    while(true){
        std::string fullpath = "input/agency.txt"; //#DEV
        auto n = fullpath.find_last_of('/');
        if(n != fullpath.npos){
            inputpath  = std::string(fullpath.begin(), fullpath.begin()+n+1);
            agencypath = std::string(fullpath.begin()+n+1, fullpath.end());
        }else{
            inputpath  = "";
            agencypath = fullpath;
        }

        is.clear();
        is.open(inputpath + agencypath, std::ifstream::in);
        if(is.is_open()) break;
        std::cout << "Ficheiro da agência não foi aberto\n";
    }
    is >> *this;
}

std::istream& operator>>(std::istream& is, Agency& a){
    std::stringstream dummy;
    if(!vin("",               a.name      , is, dummy) ||
       !vin("",               a.nif       , is, dummy) ||
       !vin("",               a.url       , is, dummy) ||
       !vin("", Address::set, a.address   , is, dummy) ||
       !vin("",               a.clientpath, is, dummy) ||
       !vin("",               a.travelpath, is, dummy))
        throw std::invalid_argument("failed to find one of the required fields in agency file");
    a.loadClients(a.inputpath + a.clientpath);
    a.loadPacks  (a.inputpath + a.travelpath);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Agency& a){
    os << a.name       << std::endl;
    os << a.nif        << std::endl;
    os << a.url        << std::endl;
    os << a.address    << std::endl;
    os << a.clientpath << std::endl;
    os << a.travelpath;
    return os;
}

void Agency::run(){
    this->print() << std::endl;
    this->printHelp();
    std::string b;
    while(true){
        std::cout << std::endl;
        std::cout << "Operação: "; getline(std::cin, b); b = trim(b);
        std::cout << std::endl;
        if     (b == "tclient")     Client::print(vclient.begin(), vclient.end(), "table");
        else if(b == "tpack"  ) TravelPack::print(vtravel.begin(), vtravel.end(), "table");
        else if(b == "sclient") seeClient();    else if(b == "spack") seePack();
        else if(b == "+client") addClient();    else if(b == "+pack") addPack();
        //else if(b == "#client") changeClient(); else if(b == "#pack") changePack();
        //else if(b == "-client") deleteClient(); //else if(b == "-pack") deletePack(); //#DEV
        else if(b == "help"   ) printHelp();
        else if(b == "save"   ) save();         else if(b == "exit" ) return;
    }
}

std::ostream& Agency::print(std::ostream& os){
    const int n = (120-name.size())/2;
    os << std::string(2*n+name.size(), '=')                  << std::endl;
    os << std::string(n, ' ') << name << std::string(n, ' ') << std::endl;
    os << std::string(2*n+name.size(), '=')                  << std::endl;
    os                                                       << std::endl;
    os << "NIF: " << nif                                     << std::endl;
    os << address                                            << std::endl;
    os << url                                                << std::endl;
    return os;
}

std::ostream& Agency::printHelp(std::ostream& os) const{
    os << "Mostrar clientes em tabela\t[tclient]" << "\t" << "Mostrar pacotes em tabela\t[tpack]" << std::endl;
    os << "Ver cliente               \t[sclient]" << "\t" << "Ver pacote               \t[spack]" << std::endl;
    os << "Adicionar cliente         \t[+client]" << "\t" << "Adicionar pacote         \t[+pack]" << std::endl;
    os << "Alterar cliente           \t[#client]" << "\t" << "Alterar pacote           \t[#pack]" << std::endl;
    os << "Eliminar cliente          \t[-client]" << "\t" << "Eliminar pacote          \t[-pack]" << std::endl;
    os << "Lista de comandos         \t[help]   " << "\t" << "                         \t       " << std::endl;
    os << "Guardar                   \t[save]   " << "\t" << "Sair                     \t[exit] " << std::endl;
    return os;
}

std::ostream& Agency::save(std::ostream& os) const{
    {
        std::ofstream of_agency(inputpath + agencypath);
        of_agency << *this;
        of_agency.close();
    }
    {
        std::ofstream of_client(inputpath + clientpath);
        if(vclient.size() >= 1){
            auto it = vclient.begin();
            of_client << *(it++) << std::endl;
            for(; it != vclient.end(); ++it){
                of_client << "::::::::::" << std::endl;
                of_client << *it << std::endl;
            }
        }
        of_client.close();
    }
    {
        std::ofstream of_pack(inputpath + travelpath);
        of_pack << lasttravel << std::endl;
        if(vtravel.size() >= 1){
            auto it = vtravel.begin();
            of_pack << (it++)->second << std::endl;
            for(; it != vtravel.end(); ++it){
                of_pack << "::::::::::" << std::endl;
                of_pack << it->second << std::endl;
            }
        }
    }
    return (os << "Ficheiros guardados" << std::endl);
}
