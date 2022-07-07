#include "service.h"

#include "utils.h"
#include "time.h"

int Service::next_id_ = 0;

Service::Service():Service(Client::Username("")){}
Service::Service(const Client::Username &client_user):
    cost_(0), revenue_(0), id_(utils::itos(-1)), client_user_(client_user){}
Service::~Service() { if(cargo_ != NULL) delete cargo_; }

void Service::assign_new_id(){
    id_ = utils::itos(next_id_++);
}

const std::string&      Service::get_id      () const{ return id_         ; }
const Client::Username& Service::get_client  () const{ return client_user_; }
const Person&           Service::get_contact1() const{ return contact1_   ; }
const Person&           Service::get_contact2() const{ return contact2_   ; }
const Time&             Service::get_tbegin  () const{ return t_begin_    ; }
const Time&             Service::get_tend    () const{ return t_end_      ; }
const Address&          Service::get_abegin  () const{ return a_begin_    ; }
const Address&          Service::get_aend    () const{ return a_end_      ; }
const utils::Distance&  Service::get_distance() const{ return distance_   ; }
const Cargo*            Service::get_cargo   () const{ return cargo_      ; }
const std::vector<Truck ::NumberPlate>& Service::get_trucks () const{ return trucks_ ; }
const std::vector<Driver::Username   >& Service::get_drivers() const{ return drivers_; }
const Currency& Service::get_cost   () const { return cost_; }
const Currency& Service::get_revenue() const { return revenue_   ; }

void Service::set_tbegin(const Time &t){ t_begin_ = t; }

bool Service::in(std::istream &is, std::ostream &os) {
    os << "Person to contact on pick-up of merchandise:\n";
    if (!contact1_.in(is, os)) return false;
    os << "Address to pick-up merchandise:\n";
    if (!a_begin_.in(is, os)) return false;

    os << "Person to contact on delivery of merchandise:\n";
    if (!contact2_.in(is, os)) return false;
    os << "Address to delivery merchandise:\n";
    if (!a_end_.in(is, os)) return false;

    if (!utils::input("Distance: ", distance_, is, os)) return false;

    while (true) {
        if (!utils::input("Time to start the service (YYYY/mm/dd HH:MM:SS): ", [](Time &time, const std::string &input) { time.input_time(input); }, t_begin_, is, os)||
            !utils::input("Time to end service (YYYY/mm/dd HH:MM:SS): ",       [](Time &time, const std::string &input) { time.input_time(input); }, t_end_,   is, os)) return false;

        if (t_begin_ > t_end_) {
            os << "Error: Initial time must be before end time\n";
            continue;
        }
        Time::TimeDiff diff = t_end_ - t_begin_;
        if (diff.hours() < 0.5) {
            os << "Error: Service duration must be atleast 30 minutes.\n";
            continue;
        }
        if ((double)(distance_)/diff.hours() <= 150) break;
        os << "Error: Time too short, our trucks can't surpass 150km/h.\n";
    }

    std::string type;
    while (true) {
        if (!utils::input("Types available: Normal, Animal, Refrigerated, Dangerous.\nCargo Type: ", type, is, os)) return false;

        utils::to_lower(type);
        if (type == "normal") {
            Cargo *cargo = new Cargo();
            if (!cargo->in(is, os)) { delete cargo; return false; }
            cargo_ = cargo;
            break;
        } else if (type == "animal") {
            CargoAnimal *cargo = new CargoAnimal();
            if (!cargo->in(is, os)) { delete cargo; return false; }
            cargo_ = cargo;
            break;
        } else if (type == "refrigerated") {
            CargoRefrigerated *cargo = new CargoRefrigerated();
            if (!cargo->in(is, os)) { delete cargo; return false; }
            cargo_ = cargo;
            break;
        } else if (type == "dangerous") {
            CargoDangerous *cargo = new CargoDangerous();
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

bool Service::allocate(std::vector<const Truck*> tv, std::vector<const Driver*> dv){
    utils::mergesort(tv, [](const Truck *p1, const Truck *p2){
        return (p1->get_cargo()->get_W() > p2->get_cargo()->get_W());
    });
    size_t sz = std::min(tv.size(), dv.size());
    utils::Weight done(0.0); size_t i = 0;
    while(i < sz && done < cargo_->get_W() && !utils::feq(double(done), double(cargo_->get_W()), 1.0)){
        trucks_.push_back(tv[i]->get_numberplate());
        drivers_.push_back(dv[i]->get_username());
        done += tv[i]->get_cargo()->get_W();
        i++;
    }
    if(done < cargo_->get_W() && !utils::feq(double(done), double(cargo_->get_W()), 1.0)){
        trucks_.clear(); drivers_.clear(); return false;
    }else{
        cost_ = 0.0;
        utils::Weight W(0.0), dW;
        for(const Truck *t:tv){
            dW = std::min(t->get_cargo()->get_W(), cargo_->get_W() - W);
            if(t->get_cargo()->get_type() == Cargo::Type::Refrigerated){
                const CargoTransRefrigerated *p = dynamic_cast<const CargoTransRefrigerated*>(t->get_cargo());
                const CargoRefrigerated      *q = dynamic_cast<const CargoRefrigerated     *>(cargo_);
                cost_    += p->get_E(distance_, dW, q->get_Tr());
                revenue_ += p->get_P(distance_, dW, q->get_Tr());
            }else{
                cost_    += t->get_cargo()->get_E(distance_, dW);
                revenue_ += t->get_cargo()->get_P(distance_, dW);
            } W += dW;
        } return true;
    }
}

std::istream& operator>>(std::istream &is,       Service &s){
    is >> s.id_
       >> s.client_user_
       >> s.contact1_
       >> s.contact2_
       >> s.t_begin_
       >> s.t_end_
       >> s.a_begin_
       >> s.a_end_
       >> s.distance_;
    input_Cargo(is, s.cargo_);
    size_t sz; is >> sz;
    s.trucks_ .resize(sz); s.drivers_.resize(sz);
    for(size_t i = 0; i < sz; ++i) is >> s.trucks_[i] >> s.drivers_[i];
    is >> s.cost_
       >> s.revenue_;

   if (s.t_begin_ > s.t_end_) is.setstate(std::ios::failbit);
   else {
       Time::TimeDiff diff = s.t_end_ - s.t_begin_;
       if (diff.hours() < 0.5) is.setstate(std::ios::failbit);
       else if ((double)s.distance_/diff.hours() > 150) is.setstate(std::ios::failbit);
   }
   return is;
}
std::ostream& operator<<(std::ostream &os, const Service &s){
    os << s.id_           << "\n"
       << s.client_user_  << "\n"
       << s.contact1_     << "\n"
       << s.contact2_     << "\n"
       << s.t_begin_      << "\n"
       << s.t_end_        << "\n"
       << s.a_begin_      << "\n"
       << s.a_end_        << "\n"
       << s.distance_     << "\n";
    output_Cargo(os, s.cargo_); os << "\n";
    size_t sz = s.trucks_.size();
    os << sz << "\n";
    for(size_t i = 0; i < sz; ++i) os << s.trucks_[i] << " " << s.drivers_[i] << "\n";
    os << s.cost_ << "\n"
       << s.revenue_;
    return os;
}
