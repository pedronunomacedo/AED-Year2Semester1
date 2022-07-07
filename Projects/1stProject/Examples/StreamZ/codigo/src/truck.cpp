#include "truck.h"

#include "utils.h"

#include "app.h"

///NUMBERPLATE NUMBER
const std::string Truck::NumberPlate::Number::REGEX_STR = "^[A-Z0-9 -|.]{4,12}*$";
Truck::NumberPlate::Number::Number():utils::string_regex(Truck::NumberPlate::Number::REGEX_STR){}
Truck::NumberPlate::Number::Number(const std::string &plate):Number(){
    *this = plate;
}
Truck::NumberPlate::Number& Truck::NumberPlate::Number::operator=(const std::string &s){
    string_regex::operator=(s);
    return *this;
}

///NUMBERPLATE
Truck::NumberPlate::NumberPlate(){}
Truck::NumberPlate::NumberPlate(const Number &number):number_(number){}
Truck::NumberPlate::operator std::string() const{ return (std::string)number_; }
bool Truck::NumberPlate::operator< (const NumberPlate &n) const{ return ((std::string)*this <  (std::string)n); }
bool Truck::NumberPlate::operator==(const NumberPlate &n) const{ return ((std::string)*this == (std::string)n); }
std::istream& operator>>(std::istream &is,       Truck::NumberPlate &n){
    is >> n.number_;
    return is;
}
std::ostream& operator<<(std::ostream &os, const Truck::NumberPlate &n){
    os << n.number_;
    return os;
}

///CATEGORY
const std::string Truck::Category::REGEX_STR = "^[A-Z+-]{1,4}$";
Truck::Category::Category():utils::string_regex(Truck::Category::REGEX_STR){}
Truck::Category::Category(const std::string &category):Category(){
    *this = category;
}
Truck::Category& Truck::Category::operator=(const std::string &category){
    string_regex::operator=(category);
    return *this;
}

///FUEL
std::string Truck::fuel_string(const Truck::Fuel &f){
    switch(f){
        case Fuel::Gasoline : return "Gasoline" ;
        case Fuel::Diesel   : return "Diesel"   ;
        case Fuel::Biodiesel: return "Biodiesel";
        case Fuel::Gas      : return "Gas"      ;
        case Fuel::Hydrogen : return "Hydrogen" ;
        case Fuel::Electric : return "Electric" ;
        case Fuel::Hybrid   : return "Hybrid"   ;
        default: throw std::invalid_argument("invalid argument");
    }
}

///TRUCK
Truck::Truck(){}
Truck::~Truck() {
    delete cargo_;
}

const Truck::NumberPlate& Truck::get_numberplate      () const{ return number_plate_       ; }
const Truck::NumberPlate& Truck::get_id               () const{ return get_numberplate()   ; }
const Time&               Truck::get_plateregisterdate() const{ return plate_register_date_; }
const Truck::Fuel&        Truck::get_fuel             () const{ return fuel_               ; }
const utils::Distance&    Truck::get_range            () const{ return max_reach_          ; }
const Truck::Category&    Truck::get_category         () const{ return category_           ; }
const Brand&              Truck::get_brand            () const{ return brand_              ; }
const CargoTrans*         Truck::get_cargo            () const{ return cargo_              ; }
CargoTrans*&              Truck::get_cargo_nc         ()      { return cargo_              ; }
Truck::Type               Truck::get_type             () const{ return Truck::Type::truck  ; }

Truck::Fuel Truck::processFuel(const std::string &s) {
    if (s == "gasoline") return Truck::Fuel::Gasoline;
    if (s == "diesel") return Truck::Fuel::Diesel;
    if (s == "biodiesel") return Truck::Fuel::Diesel;
    if (s == "gas") return Truck::Fuel::Diesel;
    if (s == "hydrogen") return Truck::Fuel::Diesel;
    if (s == "electric") return Truck::Fuel::Diesel;
    if (s == "hybrid") return Truck::Fuel::Diesel;
    throw std::invalid_argument("Invalid fuel type.");
}

Truck* Truck::deep_copy(const Truck *truck) {

    if (truck == NULL) throw std::invalid_argument("truck is a null pointer");

    Truck *copy = new Truck();

    copy->number_plate_         = truck->number_plate_;
    copy->plate_register_date_  = truck->plate_register_date_;
    copy->fuel_                 = truck->fuel_;
    copy->max_reach_            = truck->max_reach_;
    copy->category_             = truck->category_;
    copy->brand_                = truck->brand_;

    CargoTrans *cargo = truck->cargo_;
    if (cargo == NULL) throw std::invalid_argument("Truck has no cargo (cargo_ is a null pointer)");

    CargoTrans *cargo_copy;
    Cargo::Type cargo_type = cargo->get_type();
    switch(cargo_type) {
        case Cargo::Type::Normal:
            cargo_copy = new CargoTrans();
            *dynamic_cast<CargoTrans*>(cargo_copy) = *dynamic_cast<CargoTrans*>(cargo);
            break;
        case Cargo::Type::Animal:
            cargo_copy = new CargoTransAnimal();
            *dynamic_cast<CargoTransAnimal*>(cargo_copy) = *dynamic_cast<CargoTransAnimal*>(cargo);
            break;
        case Cargo::Type::Refrigerated:
            cargo_copy = new CargoTransRefrigerated();
            *dynamic_cast<CargoTransRefrigerated*>(cargo_copy) = *dynamic_cast<CargoTransRefrigerated*>(cargo);
            break;
        case Cargo::Type::Dangerous:
            cargo_copy = new CargoTransDangerous();
            *dynamic_cast<CargoTransDangerous*>(cargo_copy) = *dynamic_cast<CargoTransDangerous*>(cargo);
            break;
        default:
            delete copy;
            throw std::invalid_argument("Cargo has an invalid cargo type.");
    }
    if (cargo_copy != NULL)     copy->cargo_ = cargo_copy;
    else { delete copy; throw std::invalid_argument("Couldn't copy cargo."); }
    return copy;
}

std::istream& operator>>(std::istream &is,       Truck &t){
    is >> t.number_plate_;
    is >> t.plate_register_date_;
    int i; is >> i; t.fuel_ = static_cast<Truck::Fuel>(i);
    is >> t.max_reach_;
    is >> t.category_;
    is >> t.brand_;
    t.cargo_ = NULL;
    input_CargoTrans(is, t.cargo_);
    return is;
}
std::ostream& operator<<(std::ostream &os, const Truck &t){
    os << t.number_plate_         << "\n"
       << t.plate_register_date_  << "\n"
       << (int)t.fuel_            << "\n"
       << t.max_reach_            << "\n"
       << t.category_             << "\n"
       << t.brand_                << "\n";
    output_CargoTrans(os, t.cargo_);
    return os;
}

bool Truck::in(std::istream &is, std::ostream &os) {
    if (!utils::input("Number Plate: ", [](Truck::NumberPlate &np, const std::string &s) { np = Truck::NumberPlate(Truck::NumberPlate::Number(s)); }, number_plate_, is, os)|
        !utils::input("Plate Register Date: ", [](Time &time, const std::string &input) { time.input_date(input); },  plate_register_date_, is, os)|
        !utils::input("Fuel: ", [](Truck::Fuel &fuel, const std::string &s) { fuel = Truck::processFuel(s); }, fuel_, is, os)|
        !utils::input("Maximum reach: ", max_reach_, is, os)|
        !utils::input("Category: ",[](Truck::Category &cat, const std::string &s) { cat = Truck::Category(s); }, category_, is, os)|
        !utils::input("Brand: ", [](Brand &brand, const std::string &s) { brand = s; }, brand_, is, os)) return false;

    std::string type;
    while (true) {
        if (!utils::input("Types available: Normal, Animal, Refrigerated, Dangerous.\nCargo Type: ", type, is, os)) return false;

        utils::to_lower(type);
        if (type == "normal") {
            CargoTrans *cargo = new CargoTrans();
            if (!cargo->in(is, os)) { delete cargo; return false; }
            cargo_ = cargo;
            break;
        } else if (type == "animal") {
            CargoTransAnimal *cargo = new CargoTransAnimal();
            if (!cargo->in(is, os)) { delete cargo; return false; }
            cargo_ = cargo;
            break;
        } else if (type == "refrigerated") {
            CargoTransRefrigerated *cargo = new CargoTransRefrigerated();
            if (!cargo->in(is, os)) { delete cargo; return false; }
            cargo_ = cargo;
            break;
        } else if (type == "dangerous") {
            CargoTransDangerous *cargo = new CargoTransDangerous();
            if (!cargo->in(is, os)) { delete cargo; return false; }
            cargo_ = cargo;
            break;
        } else {
            std::cout << "Error: Invalid cargo type.\n";
            continue;
        }
    }
    return true;
}
bool Truck::edit(int property, std::istream &is, std::ostream &os) {
    switch (property) {
    case 0:
        if(!utils::input("Number Plate: ", [](Truck::NumberPlate &np, const std::string &s) {
                                                np = Truck::NumberPlate(Truck::NumberPlate::Number(s)); },
                                            number_plate_, is, os))                                                                         return false;
        else                                                                                                                                return true;
    break;
    case 1:
        if (!utils::input("Plate Register Date: ", [](Time &time, const std::string &input) { time.input_date(input); },  plate_register_date_, is, os))    return false;
        else                                                                                                                                return true;
    break;
    case 2:
        if (!utils::input("Fuel: ", [](Truck::Fuel &fuel, const std::string &s) { fuel = Truck::processFuel(s); }, fuel_, is, os))          return false;
        else                                                                                                                                return true;
    break;
    case 3:
        if (!utils::input("Maximum reach: ", max_reach_, is, os))                                                                           return false;
        else                                                                                                                                return true;
    break;
    case 4:
        if (!utils::input("Category :", [](Truck::Category &cat, const std::string &s) { cat = Truck::Category(s); }, category_, is, os))   return false;
        else                                                                                                                                return true;
    break;
    case 5:
        if (!utils::input("Brand: ", [](Brand &brand, const std::string &s) { brand = s; }, brand_, is, os))                                return false;
        else                                                                                                                                return true;
    break;
    default:
        std::cout << "Error: invalid command\n";
        return false;
        break;
    }
    return true;
}
