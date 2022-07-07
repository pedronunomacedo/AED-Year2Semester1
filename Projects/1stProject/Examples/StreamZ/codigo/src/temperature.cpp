#include "temperature.h"

#include "utils.h"

///TEMPERATURE
Temperature::Temperature():Temperature(20.0){}
Temperature::Temperature(double temp){
    if(temp < -273.15 || 100.00 < temp)
        throw InvalidTemperature(temp);
    temp_ = temp;
}
double      Temperature::operator+(const Temperature &t) const{ return temp_+t.temp_; }
double      Temperature::operator-(const Temperature &t) const{ return temp_-t.temp_; }

bool Temperature::operator==(const Temperature &t)const{ return (temp_ != t.temp_); }
bool Temperature::operator< (const Temperature &t)const{ return (temp_ < t.temp_); }
bool Temperature::operator> (const Temperature &t)const{ return (t < *this); }
bool Temperature::operator>=(const Temperature &t)const{ return !(*this < t); }
bool Temperature::operator<=(const Temperature &t)const{ return !(*this > t); }

std::istream& operator>>(std::istream &is,       Temperature &t){
    double f;
    is >> f;
    try{ t = Temperature(f); }catch(...){ is.setstate(std::ios::failbit); }
    return is;
}
std::ostream& operator<<(std::ostream &os, const Temperature &t){ return (os << t.temp_); }

///TEMPERATURERANGE
TemperatureRange::TemperatureRange(){}
TemperatureRange::TemperatureRange(const Temperature &tmin, const Temperature &tmax){
    if(tmin > tmax)
        throw TemperatureRange::InvalidTemperatureRange(tmin, tmax);
    min = tmin;
    max = tmax;
}

std::istream& operator>>(std::istream &is,       TemperatureRange &r){
    Temperature tmin, tmax;
    is >> tmin >> tmax;
    try{ r = TemperatureRange(tmin, tmax); }catch(...){ is.setstate(std::ios::failbit); }
    return is;
}
std::ostream& operator<<(std::ostream &os, const TemperatureRange &r){ return (os << r.min << " " << r.max); }

///INVALIDTEMPERATURE
Temperature::InvalidTemperature::InvalidTemperature(const double &temp):
    std::invalid_argument("invalid temperature "+utils::ftos("+%.2f", temp)),
    temp_(temp){}
const double& Temperature::InvalidTemperature::get_temperature() const{ return temp_; }

///INVALIDTEMPERATURERANGE
TemperatureRange::InvalidTemperatureRange::InvalidTemperatureRange(const Temperature &tmin, const Temperature &tmax):
    std::invalid_argument("Invalid temperature range"),
    min(tmin), max(tmax){}
std::pair<Temperature,Temperature> TemperatureRange::InvalidTemperatureRange::get_temperature_range() const{ return std::pair<Temperature,Temperature>(min,max); }
