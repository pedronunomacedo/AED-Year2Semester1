#include "workshop.h"

//ID
const std::string Workshop::ID::ID_STR = "^\\w*$";
Workshop::ID::ID(): string_regex(Workshop::ID::ID_STR) {}
Workshop::ID::ID(const std::string &id): ID() {
    *this = id;
}
Workshop::ID& Workshop::ID::operator=(const std::string &s) {
    string_regex::operator=(s);
    return *this;
}

//Workshop
std::istream & Workshop::input(std::istream &is) {
    is >> id_;
    std::string s; is >> s;
    try {
        name_ = utils::urldecode(s);
    } catch (...) {
        is.setstate(std::ios::failbit);
    }
    int no_brands = 0;
    is >> no_brands;
    for (int i = 0; i < no_brands; i++) {
        Brand brand;
        try {
            is >> brand;
            brands_.insert(brand);
        } catch (...) {
            is.setstate(std::ios::failbit);
        }
    }
    is >> availability_;
    return is;
}

Workshop::Workshop() {}
Workshop::~Workshop() {}

const Workshop::ID&     Workshop::get_id()              const { return id_; }
const std::string&      Workshop::get_name()            const { return name_; }
const std::set<Brand>&  Workshop::get_brands()          const { return brands_; }
Time                    Workshop::get_availability()    const { return availability_; }

void Workshop::increase_availability(int no_days){
    Time now = Time::get_current_date();
    if (now > availability_) {
        availability_ = now;
        availability_.incrementDays(no_days);
    } else {
        availability_.incrementDays(no_days);
    }
}

bool Workshop::find_brand(const Brand& brand) const {
    return (utils::find(brands_.begin(), brands_.end(), brand) != brands_.end());
}

bool Workshop::find_brand(const std::string& s) const {
    std::string aux = s;
    utils::trim(aux); utils::to_lower(aux);
    for (auto it = brands_.begin(); it != brands_.end(); it++)
        if (it->get_brand() == s) return true;
    return false;
}

bool Workshop::insert_brand(const Brand &brand) {
    auto ret = brands_.insert(brand);
    return ret.second;
}

bool Workshop::delete_brand(const Brand &brand) {
    auto it = brands_.find(brand);
    if (it == brands_.end()) return false;

    brands_.erase(it);
    return true;
}

bool Workshop::operator<(const Workshop& w) const {
    return this->availability_ > w.availability_;
}

bool Workshop::operator==(const Workshop &w) const {
    return this->id_ == w.id_;
}

std::istream& operator>>(std::istream &is,       Workshop &w){ return w.input(is); }
std::ostream& operator<<(std::ostream &os, const Workshop &w){
    os << w.id_                     << "\n"
       << utils::urlencode(w.name_) << "\n"
       << w.brands_.size()          << "\n";
    for (auto it = w.brands_.begin(); it != w.brands_.end(); it++)
        os << *it << "\n";
    os << w.availability_;
    return os;
}

bool Workshop::in(std::istream &is, std::ostream &os) {
    if (!utils::input("Workshop ID: ", [](Workshop::ID &id, const std::string &s) { id = Workshop::ID(s); }, id_, is, os)|
        !utils::input("Name: ",         name_,        is, os)|
        !utils::input("Availability (YYYY/mm/dd): ", [](Time &time, const std::string &input) { time.input_date(input); }, availability_, is, os)) return false;

    int no_brands = 0;
    if (!utils::input("Number of brands: ",         no_brands,        is, os)) return false;
    for (int i = 0; i < no_brands; i++) {
        Brand brand;
        if (!utils::input("Brand " + utils::itos(i+1) + ": ", [](Brand &b, const std::string &s) { b = s; }, brand, is, os)) return false;

        brands_.insert(brand);
    }
    return true;
}

bool Workshop::edit(int property, std::istream &is, std::ostream &os) {
    switch (property) {
    case 0:
        if(!!utils::input("Workshop ID: ", [](Workshop::ID &id, const std::string &s) { id = Workshop::ID(s); }, id_, is, os))              return false;
        else                                                                                                                                return true;
    break;
    case 1:
        if (!utils::input("Name: ",         name_,        is, os))                                                                          return false;
        else                                                                                                                                return true;
    break;
    case 2:
        if (utils::input("Availability: ", [](Time &time, const std::string &input) { time.input_date(input); }, availability_, is, os))    return false;
        else                                                                                                                                return true;
    break;
    default:
        std::cout << "Error: invalid command\n";
        return false;
        break;
    }
    return true;
}
