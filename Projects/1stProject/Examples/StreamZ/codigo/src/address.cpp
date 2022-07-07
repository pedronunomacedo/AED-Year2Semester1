#include "address.h"

#include "utils.h"

const std::string Address::PostalCode::REGEX_STR = "^[0-9a-zA-Z -]{0,12}$";

Address::PostalCode::PostalCode():string_regex(Address::PostalCode::REGEX_STR){}
Address::PostalCode::PostalCode(const std::string &postal_code):PostalCode(){ *this = postal_code; }

Address::PostalCode& Address::PostalCode::operator=(const std::string &postal_code){
    string_regex::operator=(postal_code);
    return *this;
}

const std::string Address::DEFAULT_FORMAT = "%street\n%postal\n%city\n%district\n%country";

Address::Address(){}

std::string Address::format(const std::string &s) const{
    std::string ret = s;
    ret = utils::strrep(ret, "%street"  , street_                  );
    ret = utils::strrep(ret, "%postal"  , (std::string)postal_code_);
    ret = utils::strrep(ret, "%city"    , city_                    );
    ret = utils::strrep(ret, "%district", district_                );
    ret = utils::strrep(ret, "%country" , country_                 );
    return ret;
}

bool Address::in(std::istream &is, std::ostream &os) {
    return (utils::input("Street: "     , street_,      is, os)&&
            utils::input("Postal Code: ", postal_code_, is, os)&&
            utils::input("City: "       , city_,        is, os)&&
            utils::input("District: "   , district_,    is, os)&&
            utils::input("Country: "    , country_,     is, os));
}

std::ostream& operator<<(std::ostream &os, const Address &a){
    return os << utils::urlencode(a.street_     ) << "\n"
              <<                  a.postal_code_  << " "
              << utils::urlencode(a.city_       ) << "\n"
              << utils::urlencode(a.district_   ) << " "
              << utils::urlencode(a.country_    );
}

std::istream& operator>>(std::istream &is, Address &a){
    std::string s;
    is >> s; a.street_      = utils::urldecode(s);
    is >>    a.postal_code_                      ;
    is >> s; a.city_        = utils::urldecode(s);
    is >> s; a.district_    = utils::urldecode(s);
    is >> s; a.country_     = utils::urldecode(s);
    return is;
}
