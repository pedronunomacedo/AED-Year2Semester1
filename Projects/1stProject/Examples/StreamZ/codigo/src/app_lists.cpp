#include "app.h"

#include <cassert> //#DEV

template<class T> bool App::extra_commands(const std::vector<std::string> &s, std::vector<const T*> &v){
    return false;
}
template<> bool App::extra_commands<Service>(const std::vector<std::string> &s, std::vector<const Service*> &v){
    if(s[0] == "time" && s.size() == 3){
        Time t1, t2;
        try{ t1.input_date(s[1]); }catch(...){ try{ t1.input_time(s[1]); }catch(...){ return false; } }
        try{ t2.input_date(s[2]); }catch(...){ try{ t2.input_time(s[2]); }catch(...){ return false; } }
        v = utils::filter(v, [t1, t2](const Service *p){
            return (t1 <= p->get_tbegin() && p->get_tbegin() < t2);
        });
        return true;
    }else return false;
}

template<class T> void App::list_commands(const User::Type &t){ T::unimplemented_function; }
template<> void App::list_commands<Client >(const User::Type &t){
    std::cout << "\n"
              << "COMMANDS:\n\n"
              << "    sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0-4].\n"
              << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0-4].\n"
              << "    details \"\033[4mSTR\033[0m\"       Print details of client with username \033[4mSTR\033[0m\n"
              << "    reset               Reset to initial selection.\n"
              << "    back                Go back.\n";
    std::cout << std::endl;
}
template<> void App::list_commands<Driver >(const User::Type &t){
    std::cout << "\n"
              << "COMMANDS:\n\n"
              << "    sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0-7].\n"
              << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0-7].\n"
              << "    details \"\033[4mSTR\033[0m\"       Print details of driver with username \033[4mSTR\033[0m\n"
              << "    reset               Reset to initial selection.\n"
              << "    back                Go back.\n";
    std::cout << std::endl;
}
template<> void App::list_commands<Manager>(const User::Type &t){
    std::cout << "\n"
              << "COMMANDS:\n\n"
              << "    sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0-5].\n"
              << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0-5].\n"
              << "    details \"\033[4mSTR\033[0m\"       Print details of manager with username \033[4mSTR\033[0m\n"
              << "    reset               Reset to initial selection.\n"
              << "    back                Go back.\n";
    std::cout << std::endl;
}
template<> void App::list_commands<Truck  >(const User::Type &t){
    std::cout << "\n"
              << "COMMANDS:\n\n"
              << "    sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0-10].\n"
              << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0-10].\n"
              << "    details \"\033[4mSTR\033[0m\"       Print details of truck with number plate \033[4mSTR\033[0m\n"
              << "    reset               Reset to initial selection.\n"
              << "    back                Go back.\n";
    std::cout << std::endl;
}
template<> void App::list_commands<Service>(const User::Type &t){
    if(t == User::Type::client){
        std::cout << "\n"
                  << "COMMANDS:\n\n"
                  << "    time \033[4mDATE1\033[0m \033[4mDATE2\033[0m    Restrict list to services started between two time points.\n"
                  << "    sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0-10,12].\n"
                  << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0-12].\n"
                  << "    details \"\033[4mSTR\033[0m\"       Print details of service with ID \033[4mSTR\033[0m\n"
                  << "    reset               Reset to initial selection.\n"
                  << "    back                Go back.\n\n"
                  << std::flush;
    }else{
        std::cout << "\n"
                  << "COMMANDS:\n\n"
                  << "    time \033[4mDATE1\033[0m \033[4mDATE2\033[0m    Restrict list to services started between two time points.\n"
                  << "    sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0-10,12-13].\n"
                  << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0-13].\n"
                  << "    details \"\033[4mSTR\033[0m\"       Print details of service with ID \033[4mSTR\033[0m\n"
                  << "    reset               Reset to initial selection.\n"
                  << "    back                Go back.\n\n"
                  << std::flush;
    }
}
template<> void App::list_commands<Workshop  >(const User::Type &t){
    std::cout << "\n"
              << "COMMANDS:\n\n"
              << "    sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0-9].\n"
              << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0-9].\n"
              << "    details \"\033[4mSTR\033[0m\"       Print details of workshop with ID \033[4mSTR\033[0m\n"
              << "    reset               Reset to initial selection.\n"
              << "    back                Go back.\n";
    std::cout << std::endl;
}

void App::list_sort_getcomp(const User::Type &t, int i, std::function<bool(const Client *, const Client *)> &cmp){
    switch(i){
        case 0: cmp = [](const Client *p1, const Client *p2){ return (p1->get_username        () < p2->get_username        ()); }; break;
        case 1: cmp = [](const Client *p1, const Client *p2){ return (p1->get_name            () < p2->get_name            ()); }; break;
        case 2: cmp = [](const Client *p1, const Client *p2){ return (p1->get_address().format() < p2->get_address().format()); }; break;
        case 3: cmp = [](const Client *p1, const Client *p2){ return (p1->get_phonenumber     () < p2->get_phonenumber     ()); }; break;
        case 4: cmp = [](const Client *p1, const Client *p2){ return (p1->get_vat             () < p2->get_vat             ()); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_sort_getcomp(const User::Type &t, int i, std::function<bool(const Driver *, const Driver *)> &cmp) const{
    switch(i){
        case 0: cmp = [    ](const Driver *p1, const Driver *p2){ return (p1->get_username          () < p2->get_username          ()); }; break;
        case 1: cmp = [    ](const Driver *p1, const Driver *p2){ return (p1->get_name              () < p2->get_name              ()); }; break;
        case 2: cmp = [    ](const Driver *p1, const Driver *p2){ return (p1->get_address().format  () < p2->get_address().format  ()); }; break;
        case 3: cmp = [    ](const Driver *p1, const Driver *p2){ return (p1->get_phonenumber       () < p2->get_phonenumber       ()); }; break;
        case 4: cmp = [    ](const Driver *p1, const Driver *p2){ return (p1->get_vat               () < p2->get_vat               ()); }; break;
        case 5: cmp = [    ](const Driver *p1, const Driver *p2){ return (p1->get_base_salary       () < p2->get_base_salary       ()); }; break;
        case 6: cmp = [this](const Driver *p1, const Driver *p2){ return (get_schedule(p1).work(     ) < get_schedule(p2).work(     )); }; break;
        case 7: cmp = [this](const Driver *p1, const Driver *p2){ return (get_schedule(p1).work_month(today) < get_schedule(p2).work_month(today)); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_sort_getcomp(const User::Type &t, int i, std::function<bool(const Manager*, const Manager*)> &cmp){
    switch(i){
        case 0: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_username        () < p2->get_username        ()); }; break;
        case 1: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_name            () < p2->get_name            ()); }; break;
        case 2: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_address().format() < p2->get_address().format()); }; break;
        case 3: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_phonenumber     () < p2->get_phonenumber     ()); }; break;
        case 4: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_vat             () < p2->get_vat             ()); }; break;
        case 5: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_base_salary     () < p2->get_base_salary     ()); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_sort_getcomp(const User::Type &t, int i, std::function<bool(const Truck  *, const Truck  *)> &cmp){
    switch(i){
        case 0 : cmp = [](const Truck *p1, const Truck *p2){ return (p1->get_numberplate      () < p2->get_numberplate      ()); }; break;
        case 1 : cmp = [](const Truck *p1, const Truck *p2){ return (p1->get_plateregisterdate() < p2->get_plateregisterdate()); }; break;
        case 2 : cmp = [](const Truck *p1, const Truck *p2){ return (p1->get_fuel             () < p2->get_fuel             ()); }; break;
        case 3 : cmp = [](const Truck *p1, const Truck *p2){ return (p1->get_range            () < p2->get_range            ()); }; break;
        case 4 : cmp = [](const Truck *p1, const Truck *p2){ return (p1->get_category         () < p2->get_category         ()); }; break;
        case 5 : cmp = [](const Truck *p1, const Truck *p2){ return (p1->get_brand            () < p2->get_brand            ()); }; break;
        case 6 : cmp = [](const Truck *p1, const Truck *p2){ return (p1->get_cargo()->get_type() < p2->get_cargo()->get_type()); }; break;
        case 7 : cmp = [](const Truck *p1, const Truck *p2){ return (p1->get_cargo()->get_W   () < p2->get_cargo()->get_W   ()); }; break;
        case 8 : cmp = [](const Truck *p1, const Truck *p2){ return (p1->get_cargo()->get_P_B () < p2->get_cargo()->get_P_B ()); }; break;
        case 9 : cmp = [](const Truck *p1, const Truck *p2){ return (p1->get_cargo()->get_E_D () < p2->get_cargo()->get_E_D ()); }; break;
        case 10: cmp = [](const Truck *p1, const Truck *p2){ return (p1->get_cargo()->get_E_W () < p2->get_cargo()->get_E_W ()); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_sort_getcomp(const User::Type &t, int i, std::function<bool(const Service*, const Service*)> &cmp){
    switch(i){
        case 0 : cmp = [](const Service *p1, const Service *p2){ return (p1->get_id                              () < p2->get_id                              ()); }; break;
        case 1 : cmp = [](const Service *p1, const Service *p2){ return (p1->get_client                          () < p2->get_client                          ()); }; break;
        case 2 : cmp = [](const Service *p1, const Service *p2){ return (p1->get_contact1().get_name             () < p2->get_contact1().get_name             ()); }; break;
        case 3 : cmp = [](const Service *p1, const Service *p2){ return (p1->get_contact2().get_name             () < p2->get_contact2().get_name             ()); }; break;
        case 4 : cmp = [](const Service *p1, const Service *p2){ return (p1->get_tbegin                          () < p2->get_tbegin                          ()); }; break;
        case 5 : cmp = [](const Service *p1, const Service *p2){ return (p1->get_tend                            () < p2->get_tend                            ()); }; break;
        case 6 : cmp = [](const Service *p1, const Service *p2){ return (p1->get_abegin().format("%district %city") < p2->get_abegin().format("%district %city")); }; break;
        case 7 : cmp = [](const Service *p1, const Service *p2){ return (p1->get_aend  ().format("%district %city") < p2->get_aend  ().format("%district %city")); }; break;
        case 8 : cmp = [](const Service *p1, const Service *p2){ return (p1->get_distance                        () < p2->get_distance                        ()); }; break;
        case 9 : cmp = [](const Service *p1, const Service *p2){ return (p1->get_cargo()->get_type               () < p2->get_cargo()->get_type               ()); }; break;
        case 10: cmp = [](const Service *p1, const Service *p2){ return (p1->get_cargo()->get_W                  () < p2->get_cargo()->get_W                  ()); }; break;
        case 12: cmp = [](const Service *p1, const Service *p2){ return (p1->get_revenue                         () < p2->get_revenue                         ()); }; break;
        case 13: if(t == User::Type::client) throw std::invalid_argument("NUM outside range");
                 cmp = [](const Service *p1, const Service *p2){ return (p1->get_cost                            () < p2->get_cost                            ()); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}

void App::list_sort_getcomp(const User::Type &t, int i, std::function<bool(const Workshop*, const Workshop*)> &cmp){
    switch(i){
        case 0: cmp = [](const Workshop *p1, const Workshop *p2){ return (p1->get_id            () < p2->get_id             ()); }; break;
        case 1: cmp = [](const Workshop *p1, const Workshop *p2){ return (p1->get_name          () < p2->get_name           ()); }; break;
        case 2: cmp = [](const Workshop *p1, const Workshop *p2){ return (p1->get_availability  () < p2->get_availability   ()); }; break;
        case 3: cmp = [](const Workshop *p1, const Workshop *p2){ return (p1->get_brands        () < p2->get_brands         ()); }; break;
        default: throw std::invalid_argument("NUM outisde range");
    }
}

void App::list_filter_getvalid(const User::Type &t, int i, const std::string &str, std::function<bool(const Client *)> &cmp){
    switch(i){
        case 0: cmp = [str](const Client *p){ return (std::string(p->get_username   ()).find(str) != std::string::npos); }; break;
        case 1: cmp = [str](const Client *p){ return (std::string(p->get_name       ()).find(str) != std::string::npos); }; break;
        case 2: cmp = [str](const Client *p){ return (p->get_address().format()        .find(str) != std::string::npos); }; break;
        case 3: cmp = [str](const Client *p){ return (std::string(p->get_phonenumber()).find(str) != std::string::npos); }; break;
        case 4: cmp = [str](const Client *p){ return (std::string(p->get_vat        ()).find(str) != std::string::npos); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_filter_getvalid(const User::Type &t, int i, const std::string &str, std::function<bool(const Driver *)> &cmp) const{
    switch(i){
        case 0: cmp = [str     ](const Driver *p){ return (std::string(p->get_username   ()).find(str) != std::string::npos); }; break;
        case 1: cmp = [str     ](const Driver *p){ return (std::string(p->get_name       ()).find(str) != std::string::npos); }; break;
        case 2: cmp = [str     ](const Driver *p){ return (p->get_address().format()        .find(str) != std::string::npos); }; break;
        case 3: cmp = [str     ](const Driver *p){ return (std::string(p->get_phonenumber()).find(str) != std::string::npos); }; break;
        case 4: cmp = [str     ](const Driver *p){ return (std::string(p->get_vat        ()).find(str) != std::string::npos); }; break;
        case 5: cmp = [str     ](const Driver *p){ return (Currency(std::stod(str))                    ==p->get_base_salary());};break;
        case 6: cmp = [str,this](const Driver *p){ return (utils::ftos("%.2f", get_schedule(p).work().hours()).find(str) != std::string::npos);};break;
        case 7: cmp = [str,this](const Driver *p){ return (utils::ftos("%.2f", get_schedule(p).work_month(today).hours()).find(str) != std::string::npos);};break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_filter_getvalid(const User::Type &t, int i, const std::string &str, std::function<bool(const Manager*)> &cmp){
    switch(i){
        case 0: cmp = [str](const Manager *p){ return (std::string(p->get_username   ()).find(str) != std::string::npos); }; break;
        case 1: cmp = [str](const Manager *p){ return (std::string(p->get_name       ()).find(str) != std::string::npos); }; break;
        case 2: cmp = [str](const Manager *p){ return (p->get_address().format()        .find(str) != std::string::npos); }; break;
        case 3: cmp = [str](const Manager *p){ return (std::string(p->get_phonenumber()).find(str) != std::string::npos); }; break;
        case 4: cmp = [str](const Manager *p){ return (std::string(p->get_vat        ()).find(str) != std::string::npos); }; break;
        case 5: cmp = [str](const Manager *p){ return (Currency(std::stod(str))                    ==p->get_base_salary());};break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_filter_getvalid(const User::Type &t, int i, const std::string &str, std::function<bool(const Truck  *)> &cmp){
    switch(i){
        case 0: cmp = [str](const Truck *p){ return (std::string(p->get_numberplate())                    .find(str) != std::string::npos); }; break;
        case 1: cmp = [str](const Truck *p){ return (p->get_plateregisterdate().format("%Y/%m/%d")        .find(str) != std::string::npos); }; break;
        case 2: cmp = [str](const Truck *p){ return (Truck::fuel_string(p->get_fuel())                    .find(str) != std::string::npos); }; break;
        case 3: cmp = [str](const Truck *p){ return (utils::ftos("%.1f", (double)p->get_range())          .find(str) != std::string::npos); }; break;
        case 4: cmp = [str](const Truck *p){ return (std::string(p->get_category())                       .find(str) != std::string::npos); }; break;
        case 5: cmp = [str](const Truck *p){ return (std::string(p->get_brand())                          .find(str) != std::string::npos); }; break;
        case 6: cmp = [str](const Truck *p){ return (Cargo::type_string(p->get_cargo()->get_type())       .find(str) != std::string::npos); }; break;
        case 7: cmp = [str](const Truck *p){ return (utils::ftos("%.1f",(double)p->get_cargo()->get_W  ()).find(str) != std::string::npos); }; break;
        case 8: cmp = [str](const Truck *p){ return (utils::ftos("%.1f",(double)p->get_cargo()->get_P_B()).find(str) != std::string::npos); }; break;
        case 9: cmp = [str](const Truck *p){ return (utils::ftos("%.1f",(double)p->get_cargo()->get_E_D()).find(str) != std::string::npos); }; break;
        case 10: cmp = [str](const Truck *p){ return (utils::ftos("%.1f",(double)p->get_cargo()->get_E_W()).find(str) != std::string::npos); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_filter_getvalid(const User::Type &t, int i, const std::string &str, std::function<bool(const Service*)> &cmp){
    switch(i){
        case 0 : cmp = [str](const Service *p){ return (std::string(p->get_id())                   .find(str) != std::string::npos); }; break;
        case 1 : cmp = [str](const Service *p){ return (std::string(p->get_client())               .find(str) != std::string::npos); }; break;
        case 2 : cmp = [str](const Service *p){ return ((std::string(p->get_contact1().get_name())+" "+std::string(p->get_contact1().get_phonenumber())).find(str) != std::string::npos); }; break;
        case 3 : cmp = [str](const Service *p){ return ((std::string(p->get_contact2().get_name())+" "+std::string(p->get_contact2().get_phonenumber())).find(str) != std::string::npos); }; break;
        case 4 : cmp = [str](const Service *p){ return (p->get_tbegin().format("%Y/%m/%d %H:%M:%S").find(str) != std::string::npos); }; break;
        case 5 : cmp = [str](const Service *p){ return (p->get_tend  ().format("%Y/%m/%d %H:%M:%S").find(str) != std::string::npos); }; break;
        case 6 : cmp = [str](const Service *p){ return (p->get_abegin().format("(%district) %city").find(str) != std::string::npos); }; break;
        case 7 : cmp = [str](const Service *p){ return (p->get_aend  ().format("(%district) %city").find(str) != std::string::npos); }; break;
        case 8 : cmp = [str](const Service *p){ return (utils::ftos("%.1",double(p->get_distance())).find(str) != std::string::npos); }; break;
        case 9 : cmp = [str](const Service *p){ return (Cargo::type_string(p->get_cargo()->get_type()).find(str) != std::string::npos); }; break;
        case 10: cmp = [str](const Service *p){ return (utils::ftos("%.1T",double(p->get_cargo()->get_W())/1000.0).find(str) != std::string::npos); }; break;
        case 11: cmp = [str](const Service *p){
            const std::vector<Truck::NumberPlate> tv = p->get_trucks();
            const std::vector<Driver::Username  > dv = p->get_drivers();
            for(size_t j = 0; j < tv.size(); ++j){
                if(std::string(tv[j]).find(str) != std::string::npos ||
                   std::string(dv[j]).find(str) != std::string::npos) return true;
            }
            return false;
        }; break;
        case 12: cmp = [str](const Service *p){ return (utils::ftos("%+.2",+double(p->get_revenue())).find(str) != std::string::npos); }; break;
        case 13: if(t == User::Type::client) throw std::invalid_argument("NUM outside range");
                 cmp = [str](const Service *p){ return (utils::ftos("%+.2",-double(p->get_cost   ())).find(str) != std::string::npos); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_filter_getvalid(const User::Type &t, int i, const std::string &str, std::function<bool(const Workshop  *)> &cmp){
    switch(i){
        case 0: cmp = [str](const Workshop *p){ return (std::string(p->get_id())                             .find(str) != std::string::npos); }; break;
        case 1: cmp = [str](const Workshop *p){ return (p->get_name()                                        .find(str) != std::string::npos); }; break;
        case 2: cmp = [str](const Workshop *p){ return (p->get_availability().format("%Y/%m/%d %H:%M:%S")    .find(str) != std::string::npos); }; break;
        case 3: cmp = [str](const Workshop *p){
            std::string aux = str; utils::to_lower(aux);
            for (const Brand &brand : p->get_brands())
                if (brand.get_brand().find(aux) != std::string::npos) return true;
            return false;
        }; break;
        default: throw std::invalid_argument("NUM outisde range");
    }
}

template<class T> void App::list(std::vector<const T*> v, const User::Type &t) const{
    const std::vector<const T*> original = v;
    while(true){
        CLEAR();
        print_list(v, t);
        list_commands<T>(t);
        std::vector<std::string> s = utils::parse_command(prompt());
        if(s.size() >= 1){
            //====SORT==========================================================
            if(s[0] == "sort"){
                if(s.size() != 2){ error("wrong number of arguments"); continue; }
                int i; try{ i = utils::stoi(s[1]); } catch(const std::invalid_argument &e){ error("invalid NUM"); continue; }
                std::function<bool(const T*, const T*)> cmp;
                try{
                    list_sort_getcomp(t, i, cmp);
                    utils::mergesort(v,cmp);
                }catch(const std::invalid_argument &e){ error(e.what()); }
            }else
            //====SEARCH========================================================
            if(s[0] == "search"){
                if(s.size() != 3){ error("wrong number of arguments"); continue; }
                int i; try{ i = utils::stoi(s[1]); } catch(const std::invalid_argument &e){ error("invalid NUM"); continue; }
                std::function<bool(const T*)> cmp;
                try{
                    list_filter_getvalid(t, i, s[2], cmp);
                    v = utils::filter(v,cmp);
                }catch(const std::invalid_argument &e){ error(e.what()); }
            }else
            //====DETAILS=======================================================
            if(s[0] == "details"){
                if(s.size() != 2){ error("wrong number of arguments"); continue; }
                const std::string &u = s[1];
                auto it = utils::find_if(v.begin(), v.end(),
                  [&u](const T *p){ return (std::string(p->get_id()) == u); });
                if(it == v.end()){ error("no such username in table"); continue; }
                std::cout << std::endl;
                display(dynamic_cast<const T*>(*it), t);
                std::cout << std::endl;
                wait();
            }else
            //====RESET=========================================================
            if(s[0] == "reset"){
                if(s.size() != 1) error("wrong number of arguments");
                else              v = original;
            }else
            //====BACK==========================================================
            if(s[0] == "back"){
                if(s.size() != 1) error("wrong number of arguments");
                else              return;
            }else
            //====EXTRA COMMANDS================================================
            if(!extra_commands<T>(s, v)) error("unrecognized command");
        }
    }
}

void App::list_clients () const{
    std::vector<const User*> v;
    for (auto p: musers_) v.push_back(p.second);
    std::vector<const Client*> w = App::filter<User,Client,User::Type>(v, User::Type::client);
    list(w, User::Type::manager);
}
void App::list_inactive_clients() const {
    std::vector<const Client*> v(inactive_clients_.begin(), inactive_clients_.end());
    list(v, User::Type::manager);
}
void App::list_drivers () const{
    std::vector<const User*> v;
    for (auto p: musers_) v.push_back(p.second);
    std::vector<const Driver*> w = App::filter<User,Driver,User::Type>(v, User::Type::driver);
    list(w, User::Type::manager);
}
void App::list_managers() const{
    std::vector<const User*> v;
    for (auto p: musers_) v.push_back(p.second);
    std::vector<const Manager*> w = App::filter<User,Manager,User::Type>(v, User::Type::manager);
    list(w, User::Type::manager);
}
void App::list_trucks  () const{
    std::vector<const Truck*> v;
    for (auto p: mtrucks_) v.push_back(p.second);
    list(v, User::Type::manager);
}
void App::list_services() const{
    std::vector<const Service*> v;
    for (auto p: mservices_) v.push_back(p.second);
    list(v, User::Type::manager);
}
void App::list_services(const User *user) const{
    std::vector<Service*> temp;
    for (auto p: mservices_) temp.push_back(p.second);
    if (user->get_type() == User::Type::client) {
        std::vector<Service*> v = filter_services_by_client(temp, dynamic_cast<const Client*>(user));
        std::vector<const Service*> w(v.begin(), v.end());
        list(w, user->get_type());
    } else if (user->get_type() == User::Type::driver) {
        std::vector<Service*> v = filter_services_by_driver(temp, dynamic_cast<const Driver*>(user));
        std::vector<const Service*> w(v.begin(), v.end());
        list(w, user->get_type());
    } else {
        list_services();
    }
}

void App::list_workshops() const{
    std::vector<const Workshop*> v;
    std::priority_queue<Workshop*, std::vector<Workshop*>, WorkshopCmp> aux_queue = workshops_;
    while (!aux_queue.empty()) { v.push_back(aux_queue.top()); aux_queue.pop(); }
    list(v, User::Type::manager);
}
