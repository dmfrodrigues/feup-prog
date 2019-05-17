#include "vat.h"

#include "helpers.h"

VAT::VAT(string s){
    s = trim(s);
    //Some validity checks
    for(const auto& c:s) if(!isdigit(c)) throw invalid_argument("VAT has nonnumeric character");
    if(s.size() != VATsize) throw invalid_argument("VAT has wrong size");
    //VAT digit check
    {
        unsigned sum = 0; for(unsigned i = 0; i < 8; ++i) sum += (9-i)*unsigned(s[i]-'0');
        sum = max(sum%11, 1u); sum = (11-sum)%10;
        if(unsigned(s[8]-'0') != sum) throw invalid_argument("VAT number is not valid");
    }
    string::operator=(s);
}
