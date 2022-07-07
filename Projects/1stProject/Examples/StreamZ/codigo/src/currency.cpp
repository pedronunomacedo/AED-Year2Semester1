#include "currency.h"

#include <iomanip>
#include <sstream>

Currency::Currency(double amount):cents_(100.0L*amount+(amount > 0.0L ? 0.5L : -0.5L)){}

Currency  Currency::operator+ (const Currency &c) const { Currency d; d.cents_ = cents_+c.cents_; return d; }
Currency  Currency::operator- (const Currency &c) const { Currency d; d.cents_ = cents_-c.cents_; return d; }
Currency  Currency::operator+ ()                  const { Currency d; d.cents_ = +cents_; return d; }
Currency  Currency::operator- ()                  const { Currency d; d.cents_ = -cents_; return d; }
Currency& Currency::operator+=(const Currency &c)       { cents_ += c.cents_; return *this; }
Currency& Currency::operator-=(const Currency &c)       { cents_ -= c.cents_; return *this; }

bool      Currency::operator==(const Currency &c) const { return (cents_ == c.cents_); }
bool      Currency::operator!=(const Currency &c) const { return (cents_ != c.cents_); }
bool      Currency::operator< (const Currency &c) const { return (cents_ <  c.cents_); }
bool      Currency::operator> (const Currency &c) const { return (cents_ >  c.cents_); }
bool      Currency::operator<=(const Currency &c) const { return (cents_ <= c.cents_); }
bool      Currency::operator>=(const Currency &c) const { return (cents_ >= c.cents_); }

Currency& Currency::operator= (const double   &n)       { return (*this = Currency(n)); }
          Currency::operator double()             const { return double(cents_)/100.0; }

std::ostream& operator<<(std::ostream &os, const Currency &c){
    std::stringstream ss;
    if(c.cents_ < 0) ss << "-";
    ss << abs(c.cents_/100) << "." << std::setw(2) << std::setfill('0') << abs(c.cents_%100);
    return (os << ss.str());
}

std::istream& operator>>(std::istream &is,       Currency &c){
    std::string s;
    is >> s;
    try{
        auto i = s.find(".");
        if(i != std::string::npos){
            c.cents_ = 100*stol(s.substr(0,i));
            s = s.substr(i+1,i+3);
            while(s.size() < 2) s += "0";
            long long int n = stol(s);
            c.cents_ += (c.cents_ >= 0 ? n : -n);
        }else{
            c.cents_ = 100*stol(s);
        }
    }catch(...){
        is.setstate(std::ios::failbit);
    }
    return is;
}

long long int Currency::getCents(void) const { return cents_; }
