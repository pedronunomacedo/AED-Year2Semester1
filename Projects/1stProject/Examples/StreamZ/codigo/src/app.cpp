#include "app.h"

#include <stdexcept>
#include <cassert>

void CLEAR(){
    int ev;
    if((ev = CLEAR_MACRO()))
        throw std::system_error(ev, std::system_category());
}

const float App::rate = 0.03;

const std::string App::OPSTR = "Operation$ ";

App::App(const std::string &base      ,
         const std::string &managers  , const std::string &drivers ,
         const std::string &clients   , const std::string &brands  ,
         const std::string &trucks    , const std::string &services,
         const std::string &workshops                              ):
         today(utils::get_now()),
         managers_path_(base+managers), drivers_path_ (base+drivers ),
         clients_path_ (base+clients ), brands_path_  (base+brands  ),
         trucks_path_  (base+trucks  ), services_path_(base+services),
         workshops_path_(base+workshops){
    std::cout << "Starting app..." << std::endl;
    load_all();
}

App::~App() {
    for (User *user : users_)
        if (user != NULL)
            delete user;
    users_.clear();

    for (Truck *truck : trucks_)
        if (truck != NULL)
            delete truck;
    trucks_.clear();

    for (Service *service : services_)
        if (service != NULL)
            delete service;
    services_.clear();

    while(!workshops_.empty()) {
        if (workshops_.top() != NULL)
            delete workshops_.top();
        workshops_.pop();
    }
}

std::string App::prompt(){
    std::cout << OPSTR;
    std::string ret;
    std::getline(std::cin, ret);
    return ret;
}

void App::wait(){
    std::string b;
    std::cout << "(Press 'Enter' to continue)";
    std::getline(std::cin, b);
}

bool App::UserEq::operator()(const User *u1, const User *u2) const {
    return u1->get_id() == u2->get_id();
}

void App::load_inactive_clients(void) {
    std::vector<User*> v;
    for (auto p: musers_) v.push_back(p.second);
    std::vector<User*> clients = filter_user_by_type(v, User::Type::client);
    std::vector<Service*> w;
    for (auto p: mservices_) w.push_back(p.second);

    Time last_year = Time::get_current_date();
    last_year.set_year(last_year.get_year() - 1);

    for (User *client : clients) {
        bool inactive = true;
        for (const Service *service : w) {
            if (service->get_client() == client->get_id() && service->get_tend() >= last_year) {
                inactive = false;
                break;
            }
        }
        if (inactive) inactive_clients_.insert(dynamic_cast<Client*>(client));
    }
}

bool App::WorkshopCmp::operator() (const Workshop *w1, const Workshop *w2) const {
    return *w1 < *w2;
}

bool App::confirm(const std::string &msg) {
    std::string input;
    while (true) {
        if (!utils::input(msg, input, std::cin, std::cout)) return false;
        utils::to_lower(input);
        if (input == "yes" || input == "y" || input == "no" || input == "n") break;
        std::cout << "Error: Only \'yes\'/\'y\' or \'no\'/\'n\' are valid options.\n";
    }
    if (input == "yes" || input == "y") return true;
    std::cout << "Operation cancelled.\n"; return false;
}

void App::error(const std::string &s){
    std::cerr << "Error: " << s << std::endl;
    wait();
}

Schedule App::get_schedule(const Driver *p) const{
    Schedule sch;
    Driver::Username u = p->get_username();
    std::vector<Service*> w;
    for (auto p_: mservices_) w.push_back(p_.second);
    std::vector<const Service*> vs;{
        std::vector<Service*> v = utils::filter(w, [u](const Service *q){
            for(const auto &d:q->get_drivers()){
                if(d == u) return true;
            } return false;
        });
        vs = std::vector<const Service*>(v.begin(), v.end());
    }
    for(const Service *q:vs) sch.add_service(q);
    return sch;
}

Schedule App::get_schedule(const Truck  *p) const{
    Schedule sch;
    Truck::NumberPlate u = p->get_numberplate();
    std::vector<Service*> w;
    for (auto p_: mservices_) w.push_back(p_.second);
    std::vector<const Service*> vs;{
        std::vector<Service*> v = utils::filter(w, [u](const Service *q){
            for(const auto &d:q->get_trucks()){
                if(d == u) return true;
            } return false;
        });
        vs = std::vector<const Service*>(v.begin(), v.end());
    }
    for(const Service *q:vs) sch.add_service(q);
    return sch;
}

App::comp_drivers::comp_drivers(const App *p_):p(p_){}
bool App::comp_drivers::operator()(const Driver *d1, const Driver *d2) const{
        Schedule sch1 = p->get_schedule(d1);
        Schedule sch2 = p->get_schedule(d2);
        return (sch1.work_month(p->today) < sch2.work_month(p->today));
}

std::multiset<Driver*, App::comp_drivers> App::get_available_drivers(const Service *s) const{
    comp_drivers cmp(this);
    std::multiset<Driver*, comp_drivers> ret(cmp);
    std::vector<User*> v;
    for (auto p: musers_) v.push_back(p.second);
    std::vector<User*> dv = App::filter_user_by_type(v, User::Type::driver);
    for(User *p:dv){
        Driver *q = dynamic_cast<Driver*>(p);
        Schedule sch = get_schedule(q); assert(bool(sch));
        bool available = sch.is_available(s);
        if(available) ret.insert(q);
    }
    return ret;
}
std::vector<Truck *> App::get_available_trucks (const Service *s) const{
    std::vector<Truck*> ret;
    const Cargo *c = s->get_cargo();
    std::vector<Truck*> v;
    for (auto p: mtrucks_) v.push_back(p.second);
    std::vector<Truck*> tv = utils::filter(v, [c](const Truck *p){
        return (p->get_cargo()->can_carry(c));
    });
    for(Truck *p:tv){
        Schedule sch = get_schedule(p); assert(bool(sch));
        bool available = sch.is_available(s);
        if(available) ret.push_back(p);
    }
    return ret;
}

bool App::send_truck_to_workshop() {
    CLEAR();
    std::cout << "Choose truck that needs to go to the workshop.\n";
    Truck *truck = App::chooseTruck();
    std::string type_of_service;
    while (true) {
        if (!utils::input("Choose type of service:\n"
                        "     \033[4mnormal\033[0m              Request a normal service.\n"
                        "     \033[4mspecialized\033[0m         Request a specialized service.\n", type_of_service, std::cin, std::cout)) break;
        utils::to_lower(type_of_service); utils::trim(type_of_service);
        if (type_of_service != "specialized" && type_of_service != "normal") {
            error("Type of service is invalid.");
            continue;
        }
        break;
    }
    int increment_days = (type_of_service == "normal" ? 1 : 2);

    if (increment_days == 1) { // normal
        Workshop *p = workshops_.top();

        if (!App::confirm("Confirm to send the truck \'" + std::string(truck->get_numberplate()) + "\' to this workshop \'" + p->get_name() + "\' (yes/no): ")) return false;

        p->increase_availability(increment_days);

        workshops_.pop();
        workshops_.push(p);

        return true;
    } else {
        std::vector<Workshop*> aux;
        while (!workshops_.empty()) {

            Workshop *p = workshops_.top();
            workshops_.pop();
            aux.push_back(p);
            if (p->find_brand(truck->get_brand())) {
                if (App::confirm("Confirm to send the truck \'" + std::string(truck->get_numberplate()) + "\' to this workshop \'" + p->get_name() + "\' (yes/no): ")) {
                    p->increase_availability(increment_days);
                    for (Workshop* w : aux) workshops_.push(w);
                    return true;
                } else {
                    for (Workshop* w : aux) workshops_.push(w);
                    return false;
                }
            }
        }
        for (Workshop* w : aux) workshops_.push(w);
        error("Coudln't find any workshop available for this service.");
        return false;
    }
}

std::vector<User*> App::filter_user_by_type(const std::vector<User*> &v, const User::Type &t) const {
    std::vector<User*> ret;
    for(User *p:v){
        if(p->get_type() == t){
            ret.push_back(p);
        }
    }
    return ret;
}

std::vector<Service*> App::filter_services_by_client(const std::vector<Service*> &v, const Client *client) const {
    std::vector<Service*> ret;
    for (Service *s : v)
        if (s->get_client() == client->get_username())
            ret.push_back(s);

    return ret;
}

std::vector<Service*> App::filter_services_by_driver(const std::vector<Service*> &v, const Driver *driver) const {
    std::vector<Service*> ret;
    for (Service *s : v)
        if (std::find(s->get_drivers().begin(), s->get_drivers().end(), driver->get_username()) != s->get_drivers().end())
            ret.push_back(s);

    return ret;
}


User* App::find_user(const User::Username &u) const{
    std::vector<User*> v;
    for (auto p: musers_) v.push_back(p.second);
    auto it = utils::find_if(v.begin(), v.end(), [u](const User *m){ return (m->get_username() == u); });
    if(it != v.end()) return *it;
    else                   return NULL;
}

Truck* App::find_truck(const Truck::NumberPlate &np) const{
    std::vector<Truck*> v;
    for (auto p: mtrucks_) v.push_back(p.second);
    auto it = utils::find_if(v.begin(), v.end(), [np](const Truck *truck) { return truck->get_numberplate() == np; });
    if(it != v.end()) return *it;
    else                    return NULL;
}

Service* App::find_service(const std::string &id) const {
    std::vector<Service*> w;
    for (auto p: mservices_) w.push_back(p.second);
    auto it = utils::find_if(w.begin(), w.end(), [id](const Service *service) { return service->get_id() == id; });
    if(it != w.end()) return *it;
    else                    return NULL;
}

User* App::verifyUser(const std::string &username, const std::string &password) {
    User *it = find_user(Client::Username(username));
    if (it == NULL) throw App::InvalidCredentials("Invalid username (username not found).");
    if (it->verifyCredentials(password)) return it;
    throw App::InvalidCredentials("Invalid credentials (password doesn't match).");
}

bool App::guestMenu(User* &user) {
    try {
        while (true) {
            CLEAR();
            std::cout <<    "╒═════════════════════════════════════════════╕\n"
                            "│                 Agency SML                  │\n"
                            "╞═════════════════════════════════════════════╡\n"
                            "│  Login                                  [1] │\n"
                            "│  Exit                                   [2] │\n"
                            "╘═════════════════════════════════════════════╛\n"
                            "                                               \n";
            // LOGIN PROCESS
            std::string cmd; std::cout << "\n" << OPSTR; getline(std::cin, cmd);
            std::vector<std::string> v = utils::parse_command(cmd);
            if(v.size() != 1){
                error("Invalid operation.");
                continue;
            }

            int operation;
            try {
                operation = std::stoi(v[0]);
            } catch (std::invalid_argument &e) {
                error("Invalid operation.");
                continue;
            } catch (...) {
                error("Unkown error.");
                continue;
            }

            switch (operation) {
                case 1:
                {
                    std::string username, password;
                    if (!utils::input("Username: ", username, std::cin, std::cout)) break;
                    if (!utils::input("Password: ", password, std::cin, std::cout)) break;
                    try {
                        user = verifyUser(username, password);
                        std::cout << "Login Success\n";
                        return true;
                    } catch (App::InvalidCredentials &ic) {
                        error(ic.getMsg());
                        break;
                    } catch (utils::string_regex::FailedRegex &fr) {
                        error(fr.what());
                        break;
                    } catch (std::exception &ex) {
                        error(ex.what());
                        break;
                    }
                }
                break;
                case 2:
                    return false;
                    break;
                default:
                    error("Invalid operation.");
                    break;
            }
        }
    } catch (std::exception &ex) {
        error(std::string("Unexpected error ") + ex.what());
        return false;
    } catch (...) {
        error("Unknown error");
        return false;
    }
    return true;
}

bool App::printUserMenu(User::Type user_type) {
    try {
        CLEAR();
        if (user_type == User::Type::client) {
            std::cout <<    "╒═════════════════════════════════════════════╤═════════════════════════════════════════════╕\n"
                            "│             Service Management              │             Account Management              │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│  Request service                       [11] │  Edit account                          [21] │\n"
                            "│  Cancel service                        [12] │  View account                          [22] │\n"
                            "│  Service list                          [13] │  Change password                       [23] │\n"
                            "╞═════════════════════════════════════════════╡                                             │\n"
                            "│                Other operations             │                                             │\n"
                            "╞═════════════════════════════════════════════╡                                             │\n"
                            "│  Log out                               [31] │                                             │\n"
                            "╘═════════════════════════════════════════════╧═════════════════════════════════════════════╛\n"
                            "                                                                                             \n";
        } else if (user_type == User::Type::driver) {
            std::cout <<    "╒═════════════════════════════════════════════╤═════════════════════════════════════════════╕\n"
                            "│          Information visualization          │               Account Management            │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│  Service list                          [11] │  Edit account                          [21] │\n"
                            "│  Truck list                            [12] │  View account                          [22] │\n"
                            "╞═════════════════════════════════════════════╡  Change password                       [23] │\n"
                            "│                Other operations             │                                             │\n"
                            "╞═════════════════════════════════════════════╡                                             │\n"
                            "│  Log out                               [31] │                                             │\n"
                            "╘═════════════════════════════════════════════╧═════════════════════════════════════════════╛\n"
                            "                                                                                             \n";
        } else if (user_type == User::Type::manager) {
            std::cout <<    "╒═════════════════════════════════════════════╤═════════════════════════════════════════════╕\n"
                            "│             Service Management              │               Truck Management              │\n"
                            "├─────────────────────────────────────────────┼─────────────────────────────────────────────┤\n"
                            "│  Add service                           [11] │  Add truck                             [21] │\n"
                            "│  Delete service                        [12] │  Edit truck                            [22] │\n"
                            "│                                             │  Delete truck                          [23] │\n"
                            "│                                             │  Repair truck                          [24] │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│              Client management              │               Driver Management             │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│  Add client                            [31] │  Add driver                            [41] │\n"
                            "│  Edit client                           [32] │  Edit driver                           [42] │\n"
                            "│  Delete client                         [33] │  Delete driver                         [43] │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│              Manager management             │          Information visualization          │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│  Add manager                           [51] │  Service list                          [61] │\n"
                            "│  Edit manager                          [52] │  Truck list                            [62] │\n"
                            "│  Delete manager                        [53] │  Client list                           [63] │\n"
                            "│                                             │  Inactive client list                  [64] │\n"
                            "│                                             │  Driver list                           [65] │\n"
                            "│                                             │  Manager list                          [66] │\n"
                            "│                                             │  Workshop list                         [67] │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│            Workshop management              │               Account Management            │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│  Add workshop                          [71] │  Edit account                          [81] │\n"
                            "│  Edit workshop                         [72] │  View account                          [82] │\n"
                            "│  Delete workshop                       [73] │  Change password                       [83] │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│                Other operations             │                                             │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│  Save                                  [91] │                                             │\n"
                            "│  Log out                               [92] │                                             │\n"
                            "│                                             │                                             │\n"
                            "╘═════════════════════════════════════════════╧═════════════════════════════════════════════╛\n"
                            "                                                                                             \n";
        }


    } catch(...) {
        return false;
    }
    return true;
}

bool App::userMenu(User *user, User::Type user_type) {
    try {
        int option;
        while (true) {
            if (!printUserMenu(user_type)) return false;

            if (!utils::input(App::OPSTR, option, std::cin, std::cout)) return true;

            if (user_type == User::Type::client) {
                switch (option) {
                //SERVICE MANAGEMENT                                            //ACCOUNT MANAGEMENT
                case 11: addService(user); wait();                   break;     case 21: editUser<Client>(user); wait();                    break;
                case 12: deleteService(user); wait();                break;     case 22: CLEAR(); App::display(dynamic_cast<Client*>(user), User::Type::manager); wait(); break;
                case 13: list_services(user);                        break;     case 23: changePassword(user); wait();  break;
                //OTHER OPERATIONS
                case 31: return true;                                break;
                default:
                    error("Invalid operation.");
                    break;
                }

            } else if (user_type == User::Type::driver) {
                switch (option) {
                //INFORMATION VISUALIZATION                                     //ACCOUNT MANAGEMENT
                case 11: list_services(user);                        break;     case 21: editUser<Driver>(user); wait();                    break;
                case 12: list_trucks();                              break;     case 22: CLEAR(); App::display(dynamic_cast<Driver*>(user), User::Type::manager); wait(); break;
                                                                                case 23: changePassword(user); wait();  break;
                //OTHER OPERATIONS
                case 31: return true;                                break;
                default:
                    error("Invalid operation.");
                    break;
                }

            } else if (user_type == User::Type::manager) {
                switch (option) {
                //SERVICE MANAGEMENT                                                //TRUCK MAANAGEMENT
                case 11: addService(); wait();                              break;  case 21: addTruck(); wait();                                break;
                case 12: deleteService(); wait();                           break;  case 22: editTruck(); wait();                               break;
                                                                                    case 23: deleteTruck(); wait();                             break;
                                                                                    case 24: send_truck_to_workshop(); break;

                //CLIENT MANAGEMENT                                                 //DRIVER MANAGEMENT
                case 31: addUser(User::Type::client); wait();               break;  case 41: addUser(User::Type::driver); wait();               break;
                case 32: editUser<Client>(User::Type::client); wait();      break;  case 42: editUser<Driver>(User::Type::driver); wait();      break;
                case 33: deleteUser<Client>(User::Type::client); wait();    break;  case 43: deleteUser<Driver>(User::Type::driver); wait();    break;

                //MANAGER MANAGEMENT                                            //INFORMATION VISUALIZATION
                case 51: addUser(User::Type::manager); wait();              break;  case 61: list_services();                                   break;
                case 52: editUser<Manager>(User::Type::manager); wait();    break;  case 62: list_trucks();                                     break;
                case 53: deleteUser<Manager>(User::Type::manager); wait();  break;  case 63: list_clients();                                    break;
                                                                                    case 64: list_inactive_clients();                           break;
                                                                                    case 65: list_drivers();                                    break;
                                                                                    case 66: list_managers();                                   break;
                                                                                    case 67: list_workshops();                                  break;

                case 71: addWorkshop(); wait(); break;
                case 72: editWorkshop(); wait(); break;
                case 73: deleteWorkshop(); wait(); break;

                //ACCOUNT MANAGEMENT                                                                                //OTHER OPERATIONS
                case 81: editUser<Manager>(user); wait(); wait();                                           break;  case 91: save_all();                            break;
                case 82: CLEAR(); App::display(dynamic_cast<Manager*>(user), User::Type::manager); wait();  break;  case 92: return true;                           break;
                case 83: changePassword(user); wait();                                                      break;

                default:
                    error("Invalid operation.");
                    break;
                }
            }
        }
    } catch (...) {
        return false;
    }
    return true;
}

void App::start(){
    User *user = NULL;

    while (true) {
        if (!guestMenu(user)) break;

        if (user == NULL) continue;

        User::Type user_type = user->get_type();

        if (!userMenu(user, user_type)) {
            error("Unexpected error.");
            break;
        }
    }
    save_all();
}

App::InvalidCredentials::InvalidCredentials(const std::string &msg):
    std::runtime_error(msg), msg_(msg){}

const std::string& App::InvalidCredentials::getMsg() const { return msg_; }

App::RepeatedId::RepeatedId(const std::string &id):
    runtime_error("Repeated id "+id), id_(id){}
const std::string& App::RepeatedId::get_id() const{ return id_; }
