#include "cargo.h"

#include <cmath>
#include <algorithm>

#include "app.h"

const Currency    CargoTrans  ::P_B_(25.0);
const Currency    CargoTransAnimal ::P_B_(35.0);
const Currency    CargoTransRefrigerated::P_B_(50.0);
const Temperature CargoTransRefrigerated::T0_(20.0);
const Currency    CargoTransDangerous   ::P_B_(75.0);

std::string Cargo::type_string(const Type &t){
    switch(t){
        case Cargo::Type::Normal : return "Normal" ;
        case Cargo::Type::Animal : return "Animal" ;
        case Cargo::Type::Refrigerated: return "Refrigerated";
        case Cargo::Type::Dangerous   : return "Dangerous"   ;
        default: throw std::invalid_argument("invalid Cargo::Type");
    }
}

std::string Cargo::dangerlevel_string(const DangerLevel &d){
    switch(d){
        case Cargo::DangerLevel::None  : return "None"  ;
        case Cargo::DangerLevel::Miscellaneous   : return "Miscellaneous"   ;
        case Cargo::DangerLevel::Gases : return "Gases" ;
        case Cargo::DangerLevel::Flammable_Liq   : return "Flammable_Liq"   ;
        case Cargo::DangerLevel::Flammable_Sol   : return "Flammable_Sol"   ;
        case Cargo::DangerLevel::Oxydizing_Agents: return "Oxydizing_Agents";
        case Cargo::DangerLevel::Explosives : return "Explosives" ;
        case Cargo::DangerLevel::Corrosive  : return "Corrosive"  ;
        case Cargo::DangerLevel::Toxic : return "Toxic" ;
        case Cargo::DangerLevel::Radioactive: return "Radioactive";
        default: throw std::invalid_argument("invalid Cargo::DangerLevel");
    }
}

std::istream& input_Cargo (std::istream &is,  Cargo *&c){
    if(c != NULL) delete c;
    int t; is >> t;
    switch(t){
        case Cargo::Type::Normal : c = new Cargo  (); break;
        case Cargo::Type::Animal : c = new CargoAnimal (); break;
        case Cargo::Type::Refrigerated: c = new CargoRefrigerated(); break;
        case Cargo::Type::Dangerous   : c = new CargoDangerous   (); break;
        default: is.setstate(std::ios::failbit); break;
    }
    return c->input(is);
}
std::ostream& output_Cargo(std::ostream &os, const Cargo  *c){
    if(c == NULL) throw std::invalid_argument("*c is a null pointer");
    os << (int)c->get_type() << "\n";
    return c->output(os);
}

std::istream& input_CargoTrans(std::istream &is,  CargoTrans *&c){
    if(c != NULL) delete c;
    int t; is >> t;
    switch(t){
        case Cargo::Type::Normal : c = new CargoTrans  (); break;
        case Cargo::Type::Animal : c = new CargoTransAnimal (); break;
        case Cargo::Type::Refrigerated: c = new CargoTransRefrigerated(); break;
        case Cargo::Type::Dangerous   : c = new CargoTransDangerous   (); break;
        default: is.setstate(std::ios::failbit); break;
    }
    return c->input(is);
}
std::ostream& output_CargoTrans(std::ostream &os, const CargoTrans *c){
    if(c == NULL) throw std::invalid_argument("*c is a null pointer");
    os << (int)c->get_type() << "\n";
    return c->output(os);
}

//CARGO
std::istream& Cargo::input(std::istream &is){
    std::string s;
    is >> W_ >> s;
    try{
        description_ = utils::urldecode(s);
    }catch(...){
        is.setstate(std::ios::failbit);
    }
    return is;
}
std::ostream& Cargo::output(std::ostream &os) const{
    os << W_    << "\n"
    << utils::urlencode(description_);
    return os;
}

Cargo::Cargo(): W_(0){}
Cargo::~Cargo(){}

Cargo::Type        Cargo::get_type       () const{ return Cargo::Type::Normal; }
const utils::Weight&      Cargo::get_W          () const{ return W_  ;                }
const std::string& Cargo::get_description() const{ return description_  ;      }


bool Cargo::in(std::istream &is, std::ostream &os) {
    if (!utils::input("Weight: ", W_, is, os)||
        !utils::input("Description: ", description_, is, os)) return false;
    return true;
}
bool Cargo::edit(int property, std::istream &is, std::ostream &os) {
    switch(property) {
        case 0: return utils::input("Weight: ", W_, is, os);
        case 1: return utils::input("Description: ", description_, is, os);
        default: return false;
    }
}

//CARGOANIMAL
std::istream& CargoAnimal::input(std::istream &is){ return Cargo::input(is); }
std::ostream& CargoAnimal::output(std::ostream &os) const{ return Cargo::output(os); }

CargoAnimal::CargoAnimal():Cargo(){}

Cargo::Type CargoAnimal::get_type() const{ return Cargo::Type::Animal; }

bool CargoAnimal::in(std::istream &is, std::ostream &os) { return Cargo::in(is, os); }
bool CargoAnimal::edit(int property, std::istream &is, std::ostream &os) { return Cargo::edit(property, is, os); }

///CARGOREFRIGERATED
std::istream& CargoRefrigerated::input(std::istream &is){ Cargo::input(is); is >> Tr_; return is; }
std::ostream& CargoRefrigerated::output(std::ostream &os) const{
    Cargo::output(os); os << "\n";
    os << Tr_;
    return os;
}

CargoRefrigerated::CargoRefrigerated():Cargo(){}

Cargo::Type CargoRefrigerated::get_type() const{ return Cargo::Type::Refrigerated; }
const TemperatureRange& CargoRefrigerated::get_Tr() const{ return Tr_; }

bool CargoRefrigerated::in(std::istream &is, std::ostream &os) {
    if(!Cargo::in(is, os)) return false;

    while (true) {
        try {
            float tmin, tmax;
            if (!utils::input("Minimum temperature: ", tmin, is, os)||
            !utils::input("Maximum temperature: ", tmax, is, os)) return false;

            TemperatureRange temp_range = TemperatureRange(Temperature(tmin), Temperature(tmax));

            Tr_ = temp_range;
            return true;
        } catch (TemperatureRange::InvalidTemperatureRange &itr) {
            std::cout << "Error: " << itr.what() << "\n";
        } catch (Temperature::InvalidTemperature &it) {
            std::cout << it.what() << "\n";
        } catch (...) {
            std::cout << "Error: Invalid input\n";
        }
    }
}
bool CargoRefrigerated::edit(int property, std::istream &is, std::ostream &os) {
    if (property < 2)
    if (!Cargo::edit(property, is, os)) return false;

    switch (property) {
        case 2:
            while (true) {
                try {
                    float tmin, tmax;
                    if (!utils::input("Minimum temperature: ", tmin, is, os)||
                    !utils::input("Maximum temperature: ", tmax, is, os)) return false;

                    TemperatureRange temp_range = TemperatureRange(Temperature(tmin), Temperature(tmax));

                    Tr_ = temp_range;
                    return true;
                } catch (TemperatureRange::InvalidTemperatureRange &itr) {
                    std::cout << "Error: " << itr.what() << "\n";
                } catch (Temperature::InvalidTemperature &it) {
                    std::cout << it.what() << "\n";
                } catch (...) {
                    std::cout << "Error: Invalid input\n";
                }
            }
            break;
        default:
            return false;
            break;
    }
}

///CARGODANGEROUS
std::istream& CargoDangerous::input(std::istream &is){
    Cargo::input(is);
    unsigned i; is >> i; danger_level_ = static_cast<Cargo::DangerLevel>(i);
    return is;
}
std::ostream& CargoDangerous::output(std::ostream &os) const{
    Cargo::output(os); os << "\n";
    os << (int)danger_level_;
    return os;
}

CargoDangerous::CargoDangerous():Cargo(){}

Cargo::Type CargoDangerous::get_type() const{ return Cargo::Type::Dangerous; }
const Cargo::DangerLevel& CargoDangerous::get_dangerlevel() const{ return danger_level_; }

bool CargoDangerous::edit(int property, std::istream &is, std::ostream &os) {
    if (property < 2)
    if (!Cargo::edit(property, is, os)) return false;

    switch (property) {
        case 2:
            {
                std::string input;
                std::string msg = "Danger Levels -> None(0) | Miscellaneous(1) | Gases(2)\n"
                "  Flammable Liquids(3) | Flammable Solids(4) | Oxydizing Agents(5)\n"
                "  Explosives(6) | Corrosive(7) | Toxic (8) | Radioactive(9)\nDanger Level: ";
                while (true) {
                    if (!utils::input(msg, input, is, os)) return false;
                    utils::to_lower(input);
                    if (input == "none"  ||  input == "0")   { danger_level_ = Cargo::DangerLevel::None;   break; }
                    if (input == "miscellaneous"   ||  input == "1")   { danger_level_ = Cargo::DangerLevel::Miscellaneous;    break; }
                    if (input == "gases" ||  input == "2")   { danger_level_ = Cargo::DangerLevel::Gases;  break; }
                    if (input == "flammable liquids"    ||  input == "3")   { danger_level_ = Cargo::DangerLevel::Gases;  break; }
                    if (input == "flammable solids"||  input == "4")   { danger_level_ = Cargo::DangerLevel::Gases;  break; }
                    if (input == "oxydizing agents"||  input == "5")   { danger_level_ = Cargo::DangerLevel::Gases;  break; }
                    if (input == "explosives" ||  input == "6")   { danger_level_ = Cargo::DangerLevel::Gases;  break; }
                    if (input == "corrosive"  ||  input == "7")   { danger_level_ = Cargo::DangerLevel::Gases;  break; }
                    if (input == "toxic" ||  input == "8")   { danger_level_ = Cargo::DangerLevel::Gases;  break; }
                    if (input == "radioactive"||  input == "9")   { danger_level_ = Cargo::DangerLevel::Gases;  break; }
                    else { std::cout << "Error: Invalid danger level.\n"; }
                }
                return true;
            }
            break;
        default:
            return false;
            break;
    }
}
bool CargoDangerous::in(std::istream &is, std::ostream &os) {
    if(!Cargo::in(is, os)) return false;
    std::string input;
    std::string msg = "Danger Levels -> None(0) | Miscellaneous(1) | Gases(2)\n"
    "  Flammable Liquids(3) | Flammable Solids(4) | Oxydizing Agents(5)\n"
    "  Explosives(6) | Corrosive(7) | Toxic (8) | Radioactive(9)\nDanger Level: ";
    while (true) {
        if (!utils::input(msg, input, is, os)) return false;
        utils::to_lower(input);
        if (input == "none"  ||  input == "0")   { danger_level_ = Cargo::DangerLevel::None; break; }
        if (input == "miscellaneous"   ||  input == "1")   { danger_level_ = Cargo::DangerLevel::Miscellaneous;  break; }
        if (input == "gases" ||  input == "2")   { danger_level_ = Cargo::DangerLevel::Gases;break; }
        if (input == "flammable liquids"    ||  input == "3")   { danger_level_ = Cargo::DangerLevel::Flammable_Liq;  break; }
        if (input == "flammable solids"||  input == "4")   { danger_level_ = Cargo::DangerLevel::Flammable_Sol;  break; }
        if (input == "oxydizing agents"||  input == "5")   { danger_level_ = Cargo::DangerLevel::Oxydizing_Agents;    break; }
        if (input == "explosives" ||  input == "6")   { danger_level_ = Cargo::DangerLevel::Explosives;break; }
        if (input == "corrosive"  ||  input == "7")   { danger_level_ = Cargo::DangerLevel::Corrosive; break; }
        if (input == "toxic" ||  input == "8")   { danger_level_ = Cargo::DangerLevel::Toxic;break; }
        if (input == "radioactive"||  input == "9")   { danger_level_ = Cargo::DangerLevel::Radioactive;    break; }
        else { std::cout << "Error: Invalid danger level.\n"; }
    }
    return true;
}

///CARGOTRANS
std::istream& CargoTrans::input(std::istream &is){
    Cargo::input(is);
    is >> E_D_
    >> E_W_;
    return is;
}
std::ostream& CargoTrans::output(std::ostream &os) const{
    Cargo::output(os); os << "\n";
    os << E_D_ << "\n"
    << E_W_;
    return os;
}

CargoTrans::CargoTrans(){}

Cargo::Type     CargoTrans::get_type() const{ return Cargo::Type::Normal; }
const Currency& CargoTrans::get_P_B() const{ return P_B_; }
const double&   CargoTrans::get_E_D() const{ return E_D_; }
const double&   CargoTrans::get_E_W() const{ return E_W_; }

bool CargoTrans::in(std::istream &is, std::ostream &os) {
    if(!Cargo::in(is, os)) return false;
    if(!utils::input("Distance factor: ", E_D_, is, os)) return false;
    if(!utils::input("Weight factor: ", E_W_, is, os))   return false;
    else                                                 return true;
}
bool CargoTrans::edit(int property, std::istream &is, std::ostream &os) {
    if (property < 2 && !Cargo::edit(property, is, os)) return false;
    switch (property) {
        case 2: std::cout << "Error: Base price can't be changed.\n"; return false;
        case 3: return utils::input("Distance factor: ", E_D_, is, os);
        case 4: return utils::input("Weight factor: ", E_W_, is, os);
        default: return false;
    }
}

///CARGOTRANSANIMAL
std::istream& CargoTransAnimal::input(std::istream &is){ return CargoTrans::input(is); }
std::ostream& CargoTransAnimal::output(std::ostream &os) const{ return CargoTrans::output(os); }

CargoTransAnimal::CargoTransAnimal():CargoTrans(){}

Cargo::Type CargoTransAnimal::get_type() const{ return Cargo::Type::Animal; }
const Currency& CargoTransAnimal::get_P_B() const{ return P_B_; }

bool CargoTransAnimal::in(std::istream &is, std::ostream &os) { return CargoTrans::in(is, os); }
bool CargoTransAnimal::edit(int property, std::istream &is, std::ostream &os) { return CargoTrans::edit(property, is, os); }

///CARGOTRANSREFRIGERATED
std::istream& CargoTransRefrigerated::input(std::istream &is){ CargoTrans::input(is); return is >> E_T_ >> Tr_; }
std::ostream& CargoTransRefrigerated::output(std::ostream &os) const{ CargoTrans::output(os); return os << "\n" << E_T_ << "\n" << Tr_; }

CargoTransRefrigerated::CargoTransRefrigerated():CargoTrans(){}

Cargo::Type CargoTransRefrigerated::get_type() const{ return Cargo::Type::Refrigerated; }
const TemperatureRange& CargoTransRefrigerated::get_Tr() const{ return Tr_; }
const Currency& CargoTransRefrigerated::get_P_B    () const{ return P_B_     ; }
const Temperature& CargoTransRefrigerated::get_T0() const{ return T0_; }
const double& CargoTransRefrigerated::get_E_T() const{ return E_T_; }

bool CargoTransRefrigerated::in(std::istream &is, std::ostream &os) {
    if(!CargoTrans::in(is, os)) return false;

    while (true) {
        try {
            float tmin, tmax;
            if (!utils::input("Minimum temperature: ", tmin, is, os)||
            !utils::input("Maximum temperature: ", tmax, is, os)) return false;

            TemperatureRange temp_range = TemperatureRange(Temperature(tmin), Temperature(tmax));

            Tr_ = temp_range;
            break;
        } catch (TemperatureRange::InvalidTemperatureRange &itr) {
            std::cout << "Error: " << itr.what() << "\n";
        } catch (Temperature::InvalidTemperature &it) {
            std::cout << it.what() << "\n";
        } catch (...) {
            std::cout << "Error: Invalid input\n";
        }
    }

    if (!utils::input("Temperature factor: ", E_T_, is, os)) return false;
    else   return true;
}
bool CargoTransRefrigerated::edit(int property, std::istream &is, std::ostream &os) {
    if (property <= 4)
        if (!CargoTrans::edit(property, is, os)) return false;

    switch (property) {
        case 5:
        while (true) {
            try {
                float tmin, tmax;
                if (!utils::input("Minimum temperature: ", tmin, is, os)||
                !utils::input("Maximum temperature: ", tmax, is, os)) return false;

                TemperatureRange temp_range = TemperatureRange(Temperature(tmin), Temperature(tmax));

                Tr_ = temp_range;
                return true;
                break;
            } catch (TemperatureRange::InvalidTemperatureRange &itr) {
                std::cout << "Error: " << itr.what() << "\n";
            } catch (Temperature::InvalidTemperature &it) {
                std::cout << it.what() << "\n";
            } catch (...) {
                std::cout << "Error: Invalid input\n";
            }
        }
        break;
        case 6:
        std::cout << "Error: Reference temperature can't be changed.\n";
        return false;
        break;
        case 7:
        if (!utils::input("Temperature factor: ", E_T_, is, os)) return false;
        else   return true;
        break;
        default:
        return false;
        break;
    }
}

///CARGOTRANSDANGEROUS
std::istream& CargoTransDangerous::input(std::istream &is){
    CargoTrans::input(is);
    unsigned i; is >> i; danger_level_ = static_cast<Cargo::DangerLevel>(i);
    return is;
}
std::ostream& CargoTransDangerous::output(std::ostream &os) const{
    CargoTrans::output(os); os << "\n";
    os << (int)danger_level_;
    return os;
}

CargoTransDangerous::CargoTransDangerous():CargoTrans(){}

Cargo::Type CargoTransDangerous::get_type() const{ return Cargo::Type::Dangerous; }
const Currency& CargoTransDangerous::get_P_B() const{ return P_B_     ; }
const Cargo::DangerLevel& CargoTransDangerous::get_dangerlevel() const{ return danger_level_; }

bool CargoTransDangerous::in(std::istream &is, std::ostream &os) {
    if(!CargoTrans::in(is, os)) return false;
    std::string input;
    std::string msg = "Danger Levels -> None(0) | Miscellaneous(1) | Gases(2)\n"
    "  Flammable Liquids(3) | Flammable Solids(4) | Oxydizing Agents(5)\n"
    "  Explosives(6) | Corrosive(7) | Toxic (8) | Radioactive(9)\nDanger Level: ";
    while (true) {
        if (!utils::input(msg, input, is, os)) return false;
        utils::to_lower(input);
        if (input == "none"  ||  input == "0")   { danger_level_ = Cargo::DangerLevel::None; break; }
        if (input == "miscellaneous"   ||  input == "1")   { danger_level_ = Cargo::DangerLevel::Miscellaneous;  break; }
        if (input == "gases" ||  input == "2")   { danger_level_ = Cargo::DangerLevel::Gases;break; }
        if (input == "flammable liquids"    ||  input == "3")   { danger_level_ = Cargo::DangerLevel::Flammable_Liq;  break; }
        if (input == "flammable solids"||  input == "4")   { danger_level_ = Cargo::DangerLevel::Flammable_Sol;  break; }
        if (input == "oxydizing agents"||  input == "5")   { danger_level_ = Cargo::DangerLevel::Oxydizing_Agents;    break; }
        if (input == "explosives" ||  input == "6")   { danger_level_ = Cargo::DangerLevel::Explosives;break; }
        if (input == "corrosive"  ||  input == "7")   { danger_level_ = Cargo::DangerLevel::Corrosive; break; }
        if (input == "toxic" ||  input == "8")   { danger_level_ = Cargo::DangerLevel::Toxic;break; }
        if (input == "radioactive"||  input == "9")   { danger_level_ = Cargo::DangerLevel::Radioactive;    break; }
        else { std::cout << "Error: Invalid danger level.\n"; }
    }
    return true;
}
bool CargoTransDangerous::edit(int property, std::istream &is, std::ostream &os) {
    if (property <= 4)
    if (!CargoTrans::edit(property, is, os)) return false;

    switch (property) {
        case 5:
        {
            std::string input;
            std::string msg = "Danger Levels -> None(0) | Miscellaneous(1) | Gases(2)\n"
            "  Flammable Liquids(3) | Flammable Solids(4) | Oxydizing Agents(5)\n"
            "  Explosives(6) | Corrosive(7) | Toxic (8) | Radioactive(9)\nDanger Level: ";
            while (true) {
                if (!utils::input(msg, input, is, os)) return false;
                utils::to_lower(input);
                if (input == "none"  ||  input == "0")   { danger_level_ = Cargo::DangerLevel::None;   break; }
                if (input == "miscellaneous"   ||  input == "1")   { danger_level_ = Cargo::DangerLevel::Miscellaneous;    break; }
                if (input == "gases" ||  input == "2")   { danger_level_ = Cargo::DangerLevel::Gases;  break; }
                if (input == "flammable liquids"    ||  input == "3")   { danger_level_ = Cargo::DangerLevel::Gases;  break; }
                if (input == "flammable solids"||  input == "4")   { danger_level_ = Cargo::DangerLevel::Gases;  break; }
                if (input == "oxydizing agents"||  input == "5")   { danger_level_ = Cargo::DangerLevel::Gases;  break; }
                if (input == "explosives" ||  input == "6")   { danger_level_ = Cargo::DangerLevel::Gases;  break; }
                if (input == "corrosive"  ||  input == "7")   { danger_level_ = Cargo::DangerLevel::Gases;  break; }
                if (input == "toxic" ||  input == "8")   { danger_level_ = Cargo::DangerLevel::Gases;  break; }
                if (input == "radioactive"||  input == "9")   { danger_level_ = Cargo::DangerLevel::Gases;  break; }
                else { std::cout << "Error: Invalid danger level.\n"; }
            }
            return true;
        }
        break;
        default:
        return false;
        break;
    }
}

///RELATED TO CARGOTRANS AND DESCENDANTS
bool CargoTrans            ::can_carry(const Cargo *p) const{ return (get_type() == p->get_type()); }
bool CargoTransAnimal      ::can_carry(const Cargo *p) const{ return (get_type() == p->get_type()); }
bool CargoTransRefrigerated::can_carry(const Cargo *p) const{
    if(get_type() == p->get_type()){
        const CargoRefrigerated *q = dynamic_cast<const CargoRefrigerated*>(p);
        return (utils::feq(double(get_Tr().max), double(q->get_Tr().min), 0.01) ||
        std::max(get_Tr().min, q->get_Tr().min) <
        std::min(get_Tr().max, q->get_Tr().max));
    }else return false;
}
bool CargoTransDangerous   ::can_carry(const Cargo *p) const{
    if(get_type() == p->get_type()){
        const CargoDangerous *q = dynamic_cast<const CargoDangerous*>(p);
        return (get_dangerlevel() == q->get_dangerlevel());
    }else return false;
}

Currency CargoTrans            ::get_E(utils::Distance D, utils::Weight W) const{ return Currency(double(D)*(get_E_D()+double(W)*get_E_W())); }
Currency CargoTransAnimal      ::get_E(utils::Distance D, utils::Weight W) const{ return Currency(double(D)*(get_E_D()+double(W)*get_E_W())); }
Currency CargoTransRefrigerated::get_E(utils::Distance D, utils::Weight W, TemperatureRange Tr) const{
    double DT = std::fabs(std::min(Tr_.max, Tr.max)-get_T0());
    return Currency(double(D)*(get_E_D()+double(W)*get_E_W())*(DT*get_E_T()));
}
Currency CargoTransDangerous   ::get_E(utils::Distance D, utils::Weight W) const{ return Currency(double(D)*(get_E_D()+double(W)*get_E_W()));}

Currency CargoTrans            ::get_P(utils::Distance D, utils::Weight W) const{ return Currency(double(get_E(D,W))*(1.0L+App::rate))+get_P_B(); }
Currency CargoTransAnimal      ::get_P(utils::Distance D, utils::Weight W) const{ return Currency(double(get_E(D,W))*(1.0L+App::rate))+get_P_B(); }
Currency CargoTransRefrigerated::get_P(utils::Distance D, utils::Weight W, TemperatureRange Tr) const{ return Currency(double(get_E(D,W,Tr))*(1.0L+App::rate))+get_P_B(); }
Currency CargoTransDangerous   ::get_P(utils::Distance D, utils::Weight W) const{ return Currency(double(get_E(D,W))*(1.0L+App::rate))+get_P_B(); }
