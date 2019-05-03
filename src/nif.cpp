#include "nif.h"

#include "helpers.h"

NIF::NIF(string s){
    s = trim(s);
    //Some validity checks
    for(const auto& c:s) if(!isdigit(c)) throw invalid_argument("NIF has nonnumeric character");
    if(s.size() != NIFsize) throw invalid_argument("NIF has wrong size");
    //NIF digit check
    {
        unsigned sum = 0; for(unsigned i = 0; i < 8; ++i) sum += (9-i)*unsigned(s[i]-'0');
        sum = max(sum%11, 1u); sum = (11-sum)%10;
        if(unsigned(s[8]-'0') != sum) throw invalid_argument("NIF number is not valid");
    }
    string::operator=(s);
}
