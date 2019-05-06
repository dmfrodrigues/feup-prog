#include "agency.h"

#ifdef _WIN32
    #include <windows.h>
    #include <cstdio>
    #define ENABLEPT()  SetConsoleOutputCP(CP_UTF8)
#else
    #define ENABLEPT()
#endif

using namespace std;

int main(){
    ENABLEPT();
    try{
        Agency a;
        a.run();
    }catch(...){
        cout << "An error has occured" << endl;
    }
    return 0;
}
