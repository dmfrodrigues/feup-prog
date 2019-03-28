#include "agency.h"

#include <fstream>
#include "vin.h"

Agency::Agency(){
    std::ifstream is; is.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    while(true){
        std::string fullpath;
        std::cout << "Agency file: "; getline(std::cin, fullpath);
        //fullpath = "input/agency.txt"; //#DEV
        size_t n = fullpath.find_last_of('/');
        if(n != fullpath.npos){
            inputpath  = fullpath.substr(0,n+1);
            agencypath = fullpath.substr(n+1, fullpath.npos);
        }else{
            inputpath  = "";
            agencypath = fullpath;
        }
        is.clear();
        try{
            is.open(inputpath + agencypath, std::ifstream::in);
            is >> *this;
            break;
        }catch(const std::ios_base::failure& e){
            std::cout << "Error: file open/read failed" << std::endl;
        }
    }
}

void Agency::run(){
    this->print() << std::endl;
    this->printHelp();
    std::string b;
    while(true){
        std::cout << std::endl;
        std::cout << "Operação: "; getline(std::cin, b); b = trim(b);
        std::cout << std::endl;

        if     (b == "tclient")     Client::print(vclient.cbegin(), vclient.cend(), "table");
        else if(b == "tpack"  ) TravelPack::print(vtravel.cbegin(), vtravel.cend(), "table");
        else if(b == "sclient") seeClient();    else if(b == "spack") seePack();
        else if(b == "+client") addClient();    else if(b == "+pack") addPack();
        else if(b == "#client") changeClient(); else if(b == "#pack") changePack(); //#DEV
        else if(b == "-client") deleteClient(); else if(b == "-pack") deletePack();
        /*else if(b == "sell"   ) sell();*/     else if(b == "fpack") findPack();
        else if(b == "help"   ) printHelp();
        else if(b == "save"   ) save();         else if(b == "exit" ) return;
        else std::cout << "Comando inválido" << std::endl;
    }
}

std::ostream& Agency::print(std::ostream& os) const{
    const long unsigned n = (120-name.size())/2;
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
    os << "Mostrar clientes em tabela\t[tclient]\tMostrar pacotes em tabela\t[tpack]\n"
          "Ver cliente               \t[sclient]\tVer pacote               \t[spack]\n"
          "Adicionar cliente         \t[+client]\tAdicionar pacote         \t[+pack]\n"
          "Alterar cliente           \t[#client]\tAlterar pacote           \t[#pack]\n"
          "Eliminar cliente          \t[-client]\tEliminar pacote          \t[-pack]\n"
          "Vender pacote a um cliente\t[sell]   \tProcurar pacotes         \t[fpack]\n"
          "Lista de comandos         \t[help]   \t                         \t       \n"
          "Guardar                   \t[save]   \tSair                     \t[exit] \n";
    return os << std::flush;
}

std::ostream& Agency::save(std::ostream& os) const{
    /*Save agency*/{
        std::ofstream of_agency(inputpath + agencypath);
        of_agency << *this;
        of_agency.close();
    }
    /*Save clients*/{
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
    /*Save travel packs*/{
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
    return (os << "Files saved" << std::endl);
}

std::istream& operator>>(std::istream& is, Agency& a){
    std::stringstream dummy;
    vin(              a.name      , is);
    vin(              a.nif       , is);
    vin(              a.url       , is);
    vin(Address::set, a.address   , is);
    vin(              a.clientpath, is);
    vin(              a.travelpath, is);
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
