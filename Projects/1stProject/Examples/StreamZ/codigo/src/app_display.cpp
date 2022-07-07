#include "app.h"

void App::print_list(const std::vector<const Client *> &v, const User::Type &t){
    std::cout << "\n"
                 " ╭─╴╷   ┬ ╭─╴╷ ╷╶┬╴╭─╴ \n"
                 " │  │   │ ├─╴│╲│ │ ╰─╮ \n"
                 " ╰─╴╰─╴ ┴ ╰─╴╵ ╵ ╵ ╶─╯ \n"
                 "\n"
                 "╒════════════════╤═══════════════════════════════════════╤═══════════════════════════════╤═══════════════════════╤══════════════════╕\n"
                 "│ Username [0]   │ Name [1]                              │ Address [2]                   │ Phone number [3]      │ VAT [4]          │\n"
                 "╞════════════════╪═══════════════════════════════════════╪═══════════════════════════════╪═══════════════════════╪══════════════════╡\n";
    for(const Client* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_username()                 ,13) << "\t │ "
                  << utils::ljust((std::string)p->get_name()                     ,36) << "\t │ "
                  << utils::ljust((std::string)p->get_address().format("%street"),28) << "\t │ "
                  << utils::ljust((std::string)p->get_phonenumber()              ,20) << "\t │ "
                  << utils::rjust((std::string)p->get_vat()                      ,16) <<   " │"
                  << std::endl;
    }
    std::cout << "╘════════════════╧═══════════════════════════════════════╧═══════════════════════════════╧═══════════════════════╧══════════════════╛\n"
              << std::flush;
}
void App::print_list(const std::vector<const Driver *> &v, const User::Type &t) const{
    std::cout << "\n"
                 " ┌─╮┌─╮ ┬ ╷  ╭─╴┌─╮╭─╴ \n"
                 " │ │├┬╯ │ │ ╱├─╴├┬╯╰─╮ \n"
                 " └─╯╵╰  ┴ │╱ ╰─╴╵╰ ╶─╯ \n"
                 "\n"
                 "╒════════════════╤═══════════════════════════════════════╤═══════════════════════════════╤═══════════════════════╤══════════════════╤════════════╤═══════════╤════════════════╕\n"
                 "│ Username [0]   │ Name [1]                              │ Address [2]                   │ Phone number [3]      │ VAT [4]          │ Base       │ Work      │ Work hours     │\n"
                 "│                │                                       │                               │                       │                  │ salary [5] │ hours [6] │ this month [7] │\n"
                 "╞════════════════╪═══════════════════════════════════════╪═══════════════════════════════╪═══════════════════════╪══════════════════╪════════════╪═══════════╪════════════════╡\n";
    for(const Driver* p:v){
        Schedule sch = get_schedule(p);
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_username()                  ,13) << "\t │ "
                  << utils::ljust((std::string)p->get_name()                      ,36) << "\t │ "
                  << utils::ljust((std::string)p->get_address().format("%street") ,28) << "\t │ "
                  << utils::ljust((std::string)p->get_phonenumber()               ,20) << "\t │ "
                  << utils::rjust((std::string)p->get_vat()                       ,16) <<   " │ "
                  << utils::rjust(utils::ftos("%.2f",(double)p->get_base_salary()),10) <<   " │ "
                  << utils::rjust(utils::ftos("%.1f",sch.work      (     ).hours()), 9) <<   " │ "
                  << utils::rjust(utils::ftos("%.1f",sch.work_month(today).hours()),14) <<   " │\n";
    }
    std::cout << "╘════════════════╧═══════════════════════════════════════╧═══════════════════════════════╧═══════════════════════╧══════════════════╧════════════╧═══════════╧════════════════╛\n"
              << std::flush;
}
void App::print_list(const std::vector<const Manager*> &v, const User::Type &t){
    std::cout << "\n"
                 " ╭┬╮╭─╮╷ ╷╭─╮╭─╮╭─╴┌─╮╭─╴ \n"
                 " │╵│├─┤│╲│├─┤│ ╮├─╴├┬╯╰─╮ \n"
                 " ╵ ╵╵ ╵╵ ╵╵ ╵╰─╯╰─╴╵╰╴╶─╯ \n"
                 "\n"
                 "╒════════════════╤═══════════════════════════════════════╤═══════════════════════════════╤═══════════════════════╤══════════════════╤═════════════════╕\n"
                 "│ Username [0]   │ Name [1]                              │ Address [2]                   │ Phone number [3]      │ VAT [4]          │ Base salary [5] │\n"
                 "╞════════════════╪═══════════════════════════════════════╪═══════════════════════════════╪═══════════════════════╪══════════════════╪═════════════════╡\n";
    for(const Manager* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_username()                  ,13) << "\t │ "
                  << utils::ljust((std::string)p->get_name()                      ,36) << "\t │ "
                  << utils::ljust((std::string)p->get_address().format("%street") ,28) << "\t │ "
                  << utils::ljust((std::string)p->get_phonenumber()               ,20) << "\t │ "
                  << utils::rjust((std::string)p->get_vat()                       ,16) <<   " │ "
                  << utils::rjust(utils::ftos("%.2f",(double)p->get_base_salary()),15) <<   " │\n";
    }
    std::cout << "╘════════════════╧═══════════════════════════════════════╧═══════════════════════════════╧═══════════════════════╧══════════════════╧═════════════════╛\n"
              << std::flush;
}
void App::print_list(const std::vector<const Truck  *> &v, const User::Type &t){
    std::cout << "\n"
                 " ╶┬╴┌─╮╷ ╷╭─╴╷ ╱╭─╴ \n"
                 "  │ ├┬╯│ ││  │╱ ╰─╮ \n"
                 "  ╵ ╵╰╴╰─╯╰─╴│ ╲╶─╯ \n"
                 "\n"
                 "╒══════════════╤════════════╤══════════════╤══════════╤══════════╤══════════════╤══════════════╤════════════╤════════════════╤════════════╤═════════════╕\n"
                 "│ Number       │ Date [1]   │ Fuel [2]     │ Range    │ Category │ Brand [5]    │ Cargo type   │ Cargo      │ Price base [8] │ Distance   │ Weight      │\n"
                 "│ plate [0]    │            │              │ (km) [3] │ [4]      │              │ [6]          │ weight [7] │                │ factor [9] │ factor [10] │\n"
                 "╞══════════════╪════════════╪══════════════╪══════════╪══════════╪══════════════╪══════════════╪════════════╪════════════════╪════════════╪═════════════╡\n";
    for(const Truck* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_numberplate()                     ,12) << " │ "
                  << p->get_plateregisterdate().format("%Y/%m/%d")                           << " │ "
                  << utils::ljust(Truck::fuel_string(p->get_fuel())                     ,12) << " │ "
                  << utils::rjust(utils::ftos("%.1f", (double)p->get_range())           , 8) << " │ "
                  << utils::ljust(std::string(p->get_category())                        , 8) << " │ "
                  << utils::ljust(std::string(p->get_brand())                           ,12) << " │ "
                  << utils::ljust(Cargo::type_string(p->get_cargo()->get_type())        ,12) << " │ "
                  << utils::rjust(utils::ftos("%.1f", (double)p->get_cargo()->get_W())  ,10) << " │ "
                  << utils::rjust(utils::ftos("%+.2f",(double)p->get_cargo()->get_P_B()),14) << " │ "
                  << utils::rjust(utils::ftos("%.4f", p->get_cargo()->get_E_D())        ,10) << " │ "
                  << utils::rjust(utils::ftos("%.3fE-4",p->get_cargo()->get_E_W()*10000),11) << " │\n";
    }
    std::cout << "╘══════════════╧════════════╧══════════════╧══════════╧══════════╧══════════════╧══════════════╧════════════╧════════════════╧════════════╧═════════════╛\n"
              << std::flush;
}
void App::print_list(const std::vector<const Service*> &v, const User::Type &t) const{
    Currency EXPENSES(0), PRICE(0);
    for(const Service *p:v){
        EXPENSES += p->get_cost   ();
        PRICE    += p->get_revenue();
    }
    if(t == User::Type::manager){
        EXPENSES = -EXPENSES;
        std::cout << "\n"
                     " ╭─╴╭─╴┌─╮╷   ┬ ╭─╴╭─╴╭─╴ \n"
                     " ╰─╮├─╴├┬╯│ ╱ │ │  ├─╴╰─╮ \n"
                     " ╶─╯╰─╴╵╰╴│╱  ┴ ╰─╴╰─╴╶─╯ \n"
                     "\n"
                     "╒═════╤══════════════╤═══════════════════════════════════╤══════════════════╤════════════════════════════╤═══════════════╤═══════════════════════════╤═════════════╤═════════════╕\n"
                     "│ ID  │ Client [1]   │ Contact 1 [2]                     │ Time begin [4]   │ Address begin [6]          │ Cargo:        │ [11] Truck/driver         │ Revenue     │ Costs       │\n"
                     "│ [0] │              │ Contact 2 [3]                     │ Time end   [5]   │ Address end   [7]          │ Type   [ 9]   │                           │ [12]        │ [13]        │\n"
                     "│     │              │                                   │                  │ Distance (km) [8]          │ Weight [10]   │                           │             │             │\n"
                     "╞═════╪══════════════╪═══════════════════════════════════╪══════════════════╪════════════════════════════╪═══════════════╪═══════════════════════════╪═════════════╪═════════════╡\n";
        for(size_t k = 0; k < v.size(); ++k){
            const Service* p = v[k];
            const User *c = App::find_user(p->get_client());
            const std::vector<Truck::NumberPlate> &tv = p->get_trucks ();
            const std::vector<Driver::Username  > &dv = p->get_drivers();
            ///LINE 1 ==============================================================
            std::cout << "│ "
                      << utils::rjust(p->get_id()                                                                                           , 3) <<   " │ "
                      << utils::ljust(std::string(c->get_username())                                                                        ,12) <<   " │ "
                      << utils::ljust(utils::ljust(p->get_contact1().get_name()  ,11)+" / "+std::string(p->get_contact1().get_phonenumber()),32) << "\t │ "
                      << p->get_tbegin().format("%Y/%m/%d %H:%M")                                                                                <<   " │ "
                      << utils::ljust(p->get_abegin().format("(%district) %city")                                                           ,25) << "\t │ "
                      << utils::ljust(Cargo::type_string(p->get_cargo()->get_type())                                                        ,13) <<   " │ "
                      << utils::ljust(std::string(tv[0]), 12) + " " + utils::ljust(std::string(dv[0])                                       ,12) <<   " │ "
                      << utils::rjust(utils::ftos("%+.2f", +double(p->get_revenue()))                                                       ,11) <<   " │ "
                      << utils::rjust(utils::ftos("%+.2f", -double(p->get_cost   ()))                                                       ,11) <<   " │\n";
            ///LINE 2 ==============================================================
            std::cout << "│     │ ";
            if(c == NULL) std::cout << "(DELETED)    │ ";
            else          std::cout << "             │ ";
            std::cout << utils::ljust(utils::ljust(p->get_contact2().get_name()  ,11)+" / "+std::string(p->get_contact2().get_phonenumber()),32) << "\t │ "
                      << p->get_tend  ().format("%Y/%m/%d %H:%M")                                                                                <<   " │ "
                      << utils::ljust(p->get_aend  ().format("(%district) %city")                                                           ,25) << "\t │ "
                      << utils::rjust(utils::ftos("%.1fT", double(p->get_cargo()->get_W())/1000.0)                                          ,13) <<   " │ ";
            if(tv.size() > 1) std::cout << utils::ljust(std::string(tv[1]), 12) + " " + utils::ljust(std::string(dv[1]), 12) << " │             │             │\n";
            else              std::cout << "                          │             │             │\n";
            ///LINE 3 ==============================================================
            std::cout << "│     │              │                                   │                  │"
                      << utils::rjust(utils::ftos("%.1f", double(p->get_distance())), 25) << "\t │               │ ";
            if(tv.size() > 2) std::cout << utils::ljust(std::string(tv[2]), 12) + " " + utils::ljust(std::string(dv[2]), 12) << " │             │             │\n";
            else              std::cout << "                          │             │             │\n";
            ///LINE >=4 ============================================================
            for(size_t i = 3; i < tv.size(); ++i){
                std::cout << "│     │              │                                   │                  │                            │               │ "
                          << utils::ljust(std::string(tv[i]), 12) + " " + utils::ljust(std::string(dv[i]), 12) << " │             │             │\n";
            }
            ///LAST LINE =======================================================
            if(k+1 != v.size()) std::cout << "├─────┼──────────────┼───────────────────────────────────┼──────────────────┼────────────────────────────┼───────────────┼───────────────────────────┼─────────────┼─────────────┤\n";
        }
        std::cout << "╘═════╧══════════════╧═══════════════════════════════════╧══════════════════╧════════════════════════════╧═══════════════╪═══════════════════════════╪═════════════╪═════════════╡\n"
                  << "                                                                                                                         │                     TOTAL │ "+utils::rjust(utils::ftos("%+.2f", double(PRICE)), 11)
                                                                                                                                                                                      +" │ "+utils::rjust(utils::ftos("%+.2f", double(EXPENSES)), 11)+" │\n"
                  << "                                                                                                                         ╘═══════════════════════════╧═════════════╧═════════════╛\n"
                  << std::flush;
    }else{
        std::cout << "\n"
                     " ╭─╴╭─╴┌─╮╷   ┬ ╭─╴╭─╴╭─╴ \n"
                     " ╰─╮├─╴├┬╯│ ╱ │ │  ├─╴╰─╮ \n"
                     " ╶─╯╰─╴╵╰╴│╱  ┴ ╰─╴╰─╴╶─╯ \n"
                     "\n"
                     "╒═════╤══════════════╤═══════════════════════════════════╤══════════════════╤════════════════════════════╤═══════════════╤═══════════════════════════╤═════════════╕\n"
                     "│ ID  │ Client [1]   │ Contact 1 [2]                     │ Time begin [4]   │ Address begin [6]          │ Cargo:        │ [11] Truck/driver         │ Price [12]  │\n"
                     "│ [0] │              │ Contact 2 [3]                     │ Time end   [5]   │ Address end   [7]          │ Type   [ 9]   │                           │             │\n"
                     "│     │              │                                   │                  │ Distance (km) [8]          │ Weight [10]   │                           │             │\n"
                     "╞═════╪══════════════╪═══════════════════════════════════╪══════════════════╪════════════════════════════╪═══════════════╪═══════════════════════════╪═════════════╡\n";
        for(const Service* p:v){
            const User *c = App::find_user(p->get_client());
            const std::vector<Truck::NumberPlate> &tv = p->get_trucks ();
            const std::vector<Driver::Username  > &dv = p->get_drivers();
            ///LINE 1 ==============================================================
            std::cout << "│ "
                      << utils::rjust(p->get_id()                                                                                           , 3) <<   " │ "
                      << utils::ljust(std::string(c->get_username())                                                                        ,12) <<   " │ "
                      << utils::ljust(utils::ljust(p->get_contact1().get_name()  ,11)+" / "+std::string(p->get_contact1().get_phonenumber()),32) << "\t │ "
                      << p->get_tbegin().format("%Y/%m/%d %H:%M")                                                                                <<   " │ "
                      << utils::ljust(p->get_abegin().format("(%district) %city")                                                           ,25) << "\t │ "
                      << utils::ljust(Cargo::type_string(p->get_cargo()->get_type())                                                        ,13) <<   " │ "
                      << utils::ljust(std::string(tv[0]), 12) + " " + utils::ljust(std::string(dv[0])                                       ,12) <<   " │ "
                      << utils::rjust(utils::ftos("%+.2f", double(p->get_revenue()))                                                        ,11) <<   " │\n";
            ///LINE 2 ==============================================================
            std::cout << "│     │ ";
            if(c == NULL) std::cout << "(DELETED)    │ ";
            else          std::cout << "             │ ";
            std::cout << utils::ljust(utils::ljust(p->get_contact2().get_name()  ,11)+" / "+std::string(p->get_contact2().get_phonenumber()),32) << "\t │ "
                      << p->get_tend  ().format("%Y/%m/%d %H:%M")                                                                                <<   " │ "
                      << utils::ljust(p->get_aend  ().format("(%district) %city")                                                           ,25) << "\t │ "
                      << utils::rjust(utils::ftos("%.1fT", double(p->get_cargo()->get_W())/1000.0)                                          ,13) <<   " │ ";
            if(tv.size() > 1) std::cout << utils::ljust(std::string(tv[1]), 12) + " " + utils::ljust(std::string(dv[1]), 12) << " │             │\n";
            else              std::cout << std::string(25,' ')                                                               << " │             │\n";
            ///LINE 3 ==============================================================
            std::cout << "│     │              │                                   │                  │"
                      << utils::rjust(utils::ftos("%.1f", double(p->get_distance())), 25) << "\t │               │ ";
            if(tv.size() > 2) std::cout << utils::ljust(std::string(tv[2]), 12) + " " + utils::ljust(std::string(dv[2]), 12) << " │             │\n";
            else              std::cout << std::string(25,' ')                                                               << " │             │\n";
            ///LINE >=4 ============================================================
            for(size_t i = 3; i < tv.size(); ++i){
                std::cout << "│        │              │                                   │                  │                            │                       │ "
                                        << utils::ljust(std::string(tv[i]), 12) + " " + utils::ljust(std::string(dv[i]), 13) << " │             │\n";
            }
        }
        std::cout << "╘═════╧══════════════╧═══════════════════════════════════╧══════════════════╧════════════════════════════╧═══════════════╪═══════════════════════════╪═════════════╡\n"
                  << "                                                                                                                         │                     TOTAL │ "+utils::rjust(utils::ftos("%+.2f", double(EXPENSES)), 11)+" │\n"
                  << "                                                                                                                         ╘═══════════════════════════╧═════════════╛\n"
                  << std::flush;
    }
}

void App::print_list(const std::vector<const Workshop  *> &v, const User::Type &t) const {
    std::cout << "\n"
                 " ╷ ╷╭─╮┌─╮╷ ╱╭─╴╷ ╷╭─╮┌─╮╭─╴ \n"
                 " │╷││ │├┬╯│╱ ╰─╮├─┤│ │├─╯╰─╮ \n"
                 " ╰┴╯╰─╯╵╰╴│ ╲╶─╯╵ ╵╰─╯╵  ╶─╯ \n"
                 "\n"
                 "╒══════════════════════╤════════════════════════════════════════╤══════════════════╤════════════════════════════════════════════════════════════════════════════════════════════╕\n"
                 "│ ID [0]               │ Name [1]                               │ Availability [2] │ Brands [3]                                                                                 │\n"
                 "╞══════════════════════╪════════════════════════════════════════╪══════════════════╪════════════════════════════════════════════════════════════════════════════════════════════╡\n";
    for(const Workshop* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_id()                              ,20) << " │ "
                  << utils::ljust(p->get_name()                                         ,38) << " │ ";
        Time now = Time::get_current_date();
        if (now > p->get_availability()) {
            std::cout << utils::ljust("Workshop is free"                                ,16) << " │ ";
        } else {
            std::cout << utils::ljust(p->get_availability().format("%Y/%m/%d")          ,16) << " │ ";
        }
        std::vector<std::string> aux;
        for (const Brand &b : p->get_brands()) aux.push_back((std::string)b);
        std::cout << utils::ljust(utils::join(aux, ", ")                                ,90) << " │\n";
    }
    std::cout << "╘══════════════════════╧════════════════════════════════════════╧══════════════════╧════════════════════════════════════════════════════════════════════════════════════════════╛\n"
              << std::flush;
}

void App::display(const Client  *p, const User::Type &t){
    std::cout << "╒═══════════════════╤════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] Username      │ " << utils::ljust((std::string)p->get_username()                       ,81) << "\t │\n"
              << "│ [1] Name          │ " << utils::ljust((std::string)p->get_name()                           ,81) << "\t │\n"
              << "│ [2] Address       │ " << utils::ljust(p->get_address().format("%street (%postal %city)")   ,81) << "\t │\n"
              << "│ [3] Phone number  │ " << utils::ljust((std::string)p->get_phonenumber()                    ,81) << "\t │\n"
              << "│ [4] VAT           │ " << utils::ljust((std::string)p->get_vat()                            ,81) << "\t │\n"
              << "╘═══════════════════╧════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}
void App::display(const Driver  *p, const User::Type &t){
    std::cout << "╒═══════════════════╤════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] Username      │ " << utils::ljust((std::string)p->get_username()                       ,81) << "\t │\n"
              << "│ [1] Name          │ " << utils::ljust((std::string)p->get_name()                           ,81) << "\t │\n"
              << "│ [2] Address       │ " << utils::ljust(p->get_address().format("%street (%postal %city)")   ,81) << "\t │\n"
              << "│ [3] Phone number  │ " << utils::ljust((std::string)p->get_phonenumber()                    ,81) << "\t │\n"
              << "│ [4] VAT           │ " << utils::ljust((std::string)p->get_vat()                            ,81) << "\t │\n"
              << "│ [5] Base salary   │ " << utils::ljust(utils::ftos("%.2f",(double)p->get_base_salary())     ,81) << "\t │\n"
              << "╘═══════════════════╧════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}
void App::display(const Manager *p, const User::Type &t){
    std::cout << "╒═══════════════════╤════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] Username      │ " << utils::ljust((std::string)p->get_username()                       ,81) << "\t │\n"
              << "│ [1] Name          │ " << utils::ljust((std::string)p->get_name()                           ,81) << "\t │\n"
              << "│ [2] Address       │ " << utils::ljust(p->get_address().format("%street (%postal %city)")   ,81) << "\t │\n"
              << "│ [3] Phone number  │ " << utils::ljust((std::string)p->get_phonenumber()                    ,81) << "\t │\n"
              << "│ [4] VAT           │ " << utils::ljust((std::string)p->get_vat()                            ,81) << "\t │\n"
              << "│ [5] Base salary   │ " << utils::ljust(utils::ftos("%.2f",(double)p->get_base_salary())     ,81) << "\t │\n"
              << "╘═══════════════════╧════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}
void App::display(const Truck   *p, const User::Type &t){
    std::cout << "╒═══════════════════╤════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] Number plate  │ " << utils::ljust((std::string)p->get_numberplate()                    ,81) << "\t │\n"
              << "│ [1] Date          │ " << utils::ljust(p->get_plateregisterdate().format("%Y/%m/%d")        ,81) << "\t │\n"
              << "│ [2] Fuel          │ " << utils::ljust(Truck::fuel_string(p->get_fuel())                    ,81) << "\t │\n"
              << "│ [3] Range (km)    │ " << utils::ljust(utils::ftos("%.1f", (double)p->get_range())          ,81) << "\t │\n"
              << "│ [4] Category      │ " << utils::ljust(std::string(p->get_category())                       ,81) << "\t │\n"
              << "│ [5] Brand         │ " << utils::ljust(std::string(p->get_brand())                          ,81) << "\t │\n";
    const CargoTrans *q = p->get_cargo();
    std::cout << "├───────────────────┴────────────────────────────────────────────────────────────────────────────────────┤\n"
              << "│ [6] Cargo         : "<< utils::ljust(Cargo::type_string(q->get_type()), 81) << "\t │\n"
              << "├───────────────────┬────────────────────────────────────────────────────────────────────────────────────┤\n";
    App::display(q, t);
    std::cout << "╘═══════════════════╧════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}
void App::display(const Service *p, const User::Type &t) const{
    const User *c = App::find_user(p->get_client());
    std::cout << "╒═══════════════════╤════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] ID            │ " << utils::ljust(p->get_id()                                          ,81) << "\t │\n";
    if(c == NULL) std::cout << "│ [1] Client        │ " << utils::ljust("["+std::string(c->get_username())+"] (DELETED)"                                                      ,81) << "\t │\n";
    else          std::cout << "│ [1] Client        │ " << utils::ljust("["+std::string(c->get_username())+"] "+c->get_name()+c->get_address().format(" (%street, %district)"),81) << "\t │\n";
    std::cout << "│ [2] Contact 1     │ " << utils::ljust(p->get_contact1().get_name()+" / "+std::string(p->get_contact1().get_phonenumber()) ,81) << "\t │\n"
              << "│ [3] Contact 2     │ " << utils::ljust(p->get_contact2().get_name()+" / "+std::string(p->get_contact2().get_phonenumber()) ,81) << "\t │\n"
              << "│ [4] Time begin    │ " << utils::ljust(p->get_tbegin().format("%Y/%m/%d %H:%M:%S")          ,81) << "\t │\n"
              << "│ [5] Time end      │ " << utils::ljust(p->get_tend  ().format("%Y/%m/%d %H:%M:%S")          ,81) << "\t │\n"
              << "│ [6] Address begin │ " << utils::ljust(p->get_abegin().format("%street (%postal, %city) [%district, %country]"),81) << "\t │\n"
              << "│ [7] Address end   │ " << utils::ljust(p->get_aend  ().format("%street (%postal, %city) [%district, %country]"),81) << "\t │\n"
              << "│ [8] Distance (km) │ " << utils::ljust(utils::ftos("%.1f",double(p->get_distance())),81) << "\t │\n";
    std::cout << "├───────────────────┴────────────────────────────────────────────────────────────────────────────────────┤\n"
              << "│ [9] Cargo         : " << utils::ljust(Cargo::type_string(p->get_cargo()->get_type())       ,81) << "\t │\n"
              << "├───────────────────┬────────────────────────────────────────────────────────────────────────────────────┤\n";
    App::display(p->get_cargo(), t);
    std::cout << "├───────────────────┴────────────────────────────────────────────────────────────────────────────────────┤\n"
              << "│ [11] Truck/driver                                                                                      │\n"
              << "├───────────────────┬────────────────────────────────────────────────────────────────────────────────────┤\n";
    const auto &tv = p->get_trucks ();
    const auto &dv = p->get_drivers();
    for(size_t i = 0; i < tv.size(); ++i){
        const User *d = find_user(dv[i]);
        std::cout << "│ Truck/driver " << utils::rjust("#"+utils::itos((long long)i), 4)
                                 << " │ " << utils::ljust("[0] Truck : " + std::string(tv[i])                  , 81) << "\t │\n";
        std::cout << "│                   │ ";
        if(d == NULL) std::cout           << utils::ljust("[1] Driver: ["+std::string(dv[i])+"] (DELETED)"                                             , 81) << "\t │\n";
        else          std::cout           << utils::ljust("[1] Driver: ["+std::string(dv[i])+"] "+d->get_name()+" / "+std::string(d->get_phonenumber()), 81) << "\t │\n";
        if(i+1 != tv.size()) std::cout << "├───────────────────┼────────────────────────────────────────────────────────────────────────────────────┤\n";
    }
    if(t == User::Type::client){
        std::cout << "├───────────────────┼────────────────────────────────────────────────────────────────────────────────────┤\n"
                  << "│ [12] Price        │ " << utils::ljust(utils::ftos("%+.2f",+double(p->get_revenue()))       ,81) << "\t │\n";
    }else if(t == User::Type::driver){
    }else if(t == User::Type::manager){
        std::cout << "├───────────────────┼────────────────────────────────────────────────────────────────────────────────────┤\n"
                  << "│ [12] Revenue      │ " << utils::ljust(utils::ftos("%+.2f",+double(p->get_revenue()))       ,81) << "\t │\n"
                  << "│ [13] Costs        │ " << utils::ljust(utils::ftos("%+.2f",-double(p->get_cost   ()))       ,81) << "\t │\n";
    }
    std::cout << "╘═══════════════════╧════════════════════════════════════════════════════════════════════════════════════╛\n"
              << std::flush;
}

void App::display(const Cargo             *p, const User::Type &t){
    std::cout << "│ [0] Weight (kg)   │ " << utils::ljust(utils::ftos("%.0f",(double)p->get_W())       ,81) << "\t │\n"
              << "│ [1] Description   │ " << utils::ljust(p->get_description()                              ,81) << "\t │\n";
    switch(p->get_type()){
      case Cargo::Animal      : display(dynamic_cast<const CargoAnimal      *>(p), t); break;
      case Cargo::Refrigerated: display(dynamic_cast<const CargoRefrigerated*>(p), t); break;
      case Cargo::Dangerous   : display(dynamic_cast<const CargoDangerous   *>(p), t); break;
      case Cargo::Normal      : break;
      default: throw std::invalid_argument("invalid Cargo type");
    }
}
void App::display(const CargoAnimal       *p, const User::Type &t){
}
void App::display(const CargoRefrigerated *p, const User::Type &t){
    std::cout << "│ [2] Temp range °C │ " << utils::ljust("["+utils::ftos("%.1f",(double)p->get_Tr().min)+", "+utils::ftos("%.1f",(double)p->get_Tr().max)+"]", 81) << "\t │\n";
}
void App::display(const CargoDangerous    *p, const User::Type &t){
    std::cout << "│ [2] Danger level  │ " << utils::ljust(Cargo::dangerlevel_string(p->get_dangerlevel())   ,81) << "\t │\n";
}

void App::display(const CargoTrans             *p, const User::Type &t){
    std::cout << "│ [0] Weight (kg)   │ " << utils::ljust(utils::ftos("%.1f",(double)p->get_W())              ,81) << "\t │\n"
              << "│ [1] Description   │ " << utils::ljust(p->get_description()                                ,81) << "\t │\n"
              << "| [2] Price base €  │ " << utils::ljust(utils::ftos("%+.2f",(double)p->get_P_B())           ,81) << "\t │\n"
              << "│ [3] Dist factor   │ " << utils::ljust(utils::ftos("%.4f",(double)p->get_E_D())            ,81) << "\t │\n"
              << "│ [4] Weight factor │ " << utils::ljust(utils::ftos("%.3fE-4",(double)p->get_E_W()*10000.0L),81) << "\t │\n";
    switch(p->get_type()){
        case Cargo::Animal      : display(dynamic_cast<const CargoTransAnimal      *>(p), t); break;
        case Cargo::Refrigerated: display(dynamic_cast<const CargoTransRefrigerated*>(p), t); break;
        case Cargo::Dangerous   : display(dynamic_cast<const CargoTransDangerous   *>(p), t); break;
        case Cargo::Normal      : break;
        default: throw std::invalid_argument("invalid Cargo type");
    }
}
void App::display(const CargoTransAnimal       *p, const User::Type &t){
}
void App::display(const CargoTransRefrigerated *p, const User::Type &t){
    std::cout << "| [5] Temp range    │ " << utils::ljust("["+utils::ftos("%.1f",(double)p->get_Tr().min)+", "+utils::ftos("%.1f",(double)p->get_Tr().max)+"]", 81) << "\t │\n"
              << "│ [6] Ref temp °C   │ " << utils::ljust(utils::ftos("%.1f",(double)p->get_T0()), 81) << "\t │\n"
              << "│ [7] Temp factor   │ " << utils::ljust(utils::ftos("%.2f",(double)p->get_E_T())    , 81) << "\t │\n";
}
void App::display(const CargoTransDangerous    *p, const User::Type &t){
    std::cout << "│ [5] Danger level  │ " << utils::ljust(Cargo::dangerlevel_string(p->get_dangerlevel())          , 81) << "\t │\n";
}

void App::display(const Workshop   *p, const User::Type &t) const{
    std::cout << "╒═══════════════════╤════════════════════════════════════════════════════════════════════════════════════╕\n"
              << "│ [0] ID            │ " << utils::ljust((std::string)p->get_id()                             ,81) << "\t │\n"
              << "│ [1] Name          │ " << utils::ljust(p->get_name()                                        ,81) << "\t │\n";

    Time now = Time::get_current_date();
    if (now > p->get_availability()) {
        std::cout << "│ [2] Availability  │ " << utils::ljust("Workshop is free"                                                ,81) << "\t │\n";
    } else {
        std::cout << "│ [2] Availability  │ " << utils::ljust(p->get_availability().format("%Y/%m/%d")                    ,81) << "\t │\n";
    }
    std::cout << "├───────────────────┴────────────────────────────────────────────────────────────────────────────────────┤\n"
              << "│ [3] Specialized Brands                                                                              \t │\n"
              << "├────────────────────────────────────────────────────────────────────────────────────────────────────────┤\n";
              for (const Brand &b : p->get_brands())
                    std::cout << "│ " << utils::ljust((std::string)b                                          ,94) << "\t │\n";
    std::cout << "╘════════════════════════════════════════════════════════════════════════════════════════════════════════╛" << std::endl;
}
