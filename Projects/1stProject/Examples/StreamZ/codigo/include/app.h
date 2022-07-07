/**
 * @file app.h
 */

#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include "person.h"
#include "truck.h"
#include "service.h"
#include "schedule.h"
#include "workshop.h"

#include <unordered_set>
#include <fstream>
#include <queue>
#include <map>

#if defined(_WIN32)
    #define CLEAR_MACRO() system("cls"  )
#elif defined(unix) || defined(__unix__) || defined(__unix)
    #define CLEAR_MACRO() system("clear")
#endif

/**
 * @brief Clears the screen.
 *
 * Designed to work at least in Windows32/64 and Unix.
 */
void CLEAR();

/** @brief Main class of the application. */
class App{
public:
    /** @brief Profit rate of the agency */
    static const float rate;

    /** @brief Compare drivers by time of service in current month. */
    struct comp_drivers{
    private:
        /**
         * @brief Parent of the comparator.
         *
         * The parent is used to get the current time, thus allowing to sort
         * drivers by the time they worked the current month.
         */
        const App *p;
    public:
        /**
         * @brief Construct from App.
         * @param   p_  Parent of the comparator
         */
        comp_drivers(const App *p_);
        /**
         * @brief Comparator; overload of <em>operator()</em>.
         * @param   d1  Driver 1
         * @param   d2  Driver 2
         * @return  True if d1 comes before d2, false otherwise
         */
        bool operator()(const Driver *d1, const Driver *d2) const;
    };
private:
    ///PRIVATE VARIABLES
    /// @brief Operation string displayed before any command input.
    static const std::string OPSTR;
    /// @brief Today
    const Time today;
    //Paths
    /// @brief Base path for data files of application.
    const std::string base_path_        ;
    /// @brief Path from base to managers data files of application.
    const std::string managers_path_    ;
    /// @brief Path from base to drivers data files of application.
    const std::string drivers_path_     ;
    /// @brief Path from base to clients data files of application.
    const std::string clients_path_     ;
    /// @brief Path from base to brands data files of application.
    const std::string brands_path_      ;
    /// @brief Path from base to trucks data files of application.
    const std::string trucks_path_      ;
    /// @brief Path from base to services data files of application.
    const std::string services_path_    ;
    /// @brief Path from base to workshops data files of application.
    const std::string workshops_path_   ;
    //Vectors
    /// @brief Existing user accounts on agency.
    std::vector<User*> users_ ;
    /// @brief Existing trucks on agency.
    std::vector<Truck*> trucks_  ;
    /// @brief Existing services on agency.
    std::vector<Service*> services_;
	///Maps
	/// @brief Existing user accounts on agency.
	std::map<User::Username, User*> musers_;
	/// @brief Existing trucks on agency.
	std::map<Truck::NumberPlate, Truck*> mtrucks_;
	/// @brief Existing services on agency.
	std::map<Service::ID, Service*> mservices_;
    //Hash Tables
    /// @brief Hash Function for User (pointer)
    typedef std::hash<User*> UserHash;
    /// @brief Equality Function for User (pointer)
    struct UserEq {
        /**
         * @brief Function comparator of two pointers for User.
         * @param u1    Pointer to first user.
         * @param u2    Pointer to second user.
         * @return The return value of operator< for User.
         */
        bool operator() (const User* u1, const User* u2) const;
    };
    /// @brief Inactive clients on agency.
    std::unordered_set<Client*, UserHash, UserEq> inactive_clients_;
    // PRIORITY QUEUES
    /// @brief Comparator for Workshop (pointer)
    struct WorkshopCmp {
        /**
         * @brief Function comparator of two pointers for Workshops.
         * @param w1    Pointer to first workshop.
         * @param w2    Pointer to second workshop.
         * @return The return value of operator< for Workshop.
         */
        bool operator() (const Workshop *w1, const Workshop *w2) const;
    };
    /// @brief Workshops available on agency database.
    std::priority_queue<Workshop*, std::vector<Workshop*>, WorkshopCmp> workshops_;
    ///PRIVATE FUNCTIONS
    ///File IO
    /**
     * @brief Loads data file.
     * @param is    Input data file
     * @param m_in  Vector to store all data
     * @return Number of objects of Base loaded
     * @throws  App::RepeatedId If a repeated object gets loaded (objects with same identification)
     */
    template<class Base, class Deriv, class ID> static size_t load_ptr(std::ifstream &is,       std::vector<Base*> &m_in );
    /**
     * @brief Loads data file.
     * @param is    Input data file
     * @param m_in  Vector to store all data
     * @return Number of objects of T loaded
     * @throws  App::RepeatedId If a repeated object gets loaded (objects with same identification)
     */
    size_t load_str(std::ifstream &is, std::vector<std::string> &m_in);
    /**
     * @brief Saves information into data file.
     * @param os    Output data file
     * @param m_out  Vector containing all data
     * @return Number of objects of Base saved
     */
    template<class Base, class Deriv          > static size_t save_ptr(std::ofstream &os, const std::vector<Base*> &m_out);
    /**
     * @brief Saves information into data file.
     * @param os    Output data file
     * @param m_out  Vector containing all data
     * @return Number of objects of Base saved
     */
    size_t save_str(std::ofstream &os, const std::vector<std::string> &m_out);
    /// @brief Loads all information stored in data files specified in constructor.
    void load_all();
    /// @brief Saves all current information stored in runtime to data files.
    void save_all();
    ///Loading Function
    void load_inactive_clients(void);
    ///Display
    /**
     * @brief Prints list of all managers in the vector.
     * @param v     Vector containing all the managers
     * @param t     Type of user that information will be displayed to
     */
    static void print_list(const std::vector<const Manager*> &v, const User::Type &t);
    /**
     * @brief Prints list of all drivers in the vector.
     * @param v     Vector containing all the drivers
     * @param t     Type of user that information will be displayed to
     */
           void print_list(const std::vector<const Driver *> &v, const User::Type &t) const;
    /**
     * @brief Prints list of all clients in the vector.
     * @param v     Vector containing all the clients
     * @param t     Type of user that information will be displayed to
     */
    static void print_list(const std::vector<const Client *> &v, const User::Type &t);
    /**
     * @brief Prints list of all trucks in the vector.
     * @param v     Vector containing all the trucks
     * @param t     Type of user that information will be displayed to
     */
    static void print_list(const std::vector<const Truck  *> &v, const User::Type &t);
    /**
     * @brief Prints list of all services in the vector.
     * @param v     Vector containing all the services
     * @param t     Type of user that information will be displayed to
     */
           void print_list(const std::vector<const Service*> &v, const User::Type &t) const;
    /**
     * @brief Prints list of all services in the vector.
     * @param v     Vector containing all the services
     * @param t     Type of user that information will be displayed to
     */
    void print_list(const std::vector<const Workshop  *> &v, const User::Type &t) const;
    /**
     * @brief Prints detailed information about one client.
     * @param p     Client to be displayed
     * @param t     Type of user that information will be displayed to
     */
    static void display(const Client                 *p, const User::Type &t);
    /**
     * @brief Prints detailed information about one driver.
     * @param p     Driver to be displayed
     * @param t     Type of user that information will be displayed to
     */
    static void display(const Driver                 *p, const User::Type &t);
    /**
     * @brief Prints detailed information about one manager.
     * @param p     Manager to be displayed
     * @param t     Type of user that information will be displayed to
     */
    static void display(const Manager                *p, const User::Type &t);
    /**
     * @brief Prints detailed information about one truck.
     * @param p     Truck to be displayed
     * @param t     Type of user that information will be displayed to
     */
    static void display(const Truck                  *p, const User::Type &t);
    /**
     * @brief Prints detailed information about one cargo.
     * @param p     Cargo to be displayed
     * @param t     Type of user that information will be displayed to
     */
    static void display(const Cargo                  *p, const User::Type &t);
    /**
     * @brief Prints detailed information about one cargo.
     * @param p     Cargo to be displayed
     * @param t     Type of user that information will be displayed to
     */
    static void display(const CargoAnimal            *p, const User::Type &t);
    /**
     * @brief Prints detailed information about one cargo.
     * @param p     Cargo to be displayed
     * @param t     Type of user that information will be displayed to
     */
    static void display(const CargoRefrigerated      *p, const User::Type &t);
    /**
     * @brief Prints detailed information about one cargo.
     * @param p     Cargo to be displayed
     * @param t     Type of user that information will be displayed to
     */
    static void display(const CargoDangerous         *p, const User::Type &t);
    /**
     * @brief Prints detailed information about one cargo.
     * @param p     Cargo to be displayed
     * @param t     Type of user that information will be displayed to
     */
    static void display(const CargoTrans             *p, const User::Type &t);
    /**
     * @brief Prints detailed information about one cargo.
     * @param p     Cargo to be displayed
     * @param t     Type of user that information will be displayed to
     */
    static void display(const CargoTransAnimal       *p, const User::Type &t);
    /**
     * @brief Prints detailed information about one cargo.
     * @param p     Cargo to be displayed
     * @param t     Type of user that information will be displayed to
     */
    static void display(const CargoTransRefrigerated *p, const User::Type &t);
    /**
     * @brief Prints detailed information about one cargo.
     * @param p     Cargo to be displayed
     * @param t     Type of user that information will be displayed to
     */
    static void display(const CargoTransDangerous    *p, const User::Type &t);
    /**
     * @brief Prints detailed information about one service.
     * @param p     Service to be displayed
     * @param t     Type of user that information will be displayed to
     */
     void display(const Service                *p, const User::Type &t) const;

     /**
      * @brief Prints detailed information about one workshop.
      * @param p     Workshop to be displayed
      * @param t     Type of user that information will be displayed to
      */
     void display(const Workshop   *p, const User::Type &t) const;

    //Lists

    /**
     * @brief Filters vector by type.
     * @param v Vector to be filtered
     * @param t Filter type
     * @return Vector filtered
     */
    template<class Base, class Deriv, class Type> static std::vector<const Deriv*> filter(const std::vector<const Base*> &v, const Type &t);
    /**
     * @brief Process extra commands (outside of the main commands).
     * @param s     Vector containing all parts of the command
     * @param v     Vector to process depending on command
     * @return  If command is valid
     */
    template<class T> static bool extra_commands(const std::vector<std::string> &s, std::vector<const T*> &v);
    /**
     * @brief Lists all commands.
     * @param t Type of user that commands will be displayed to
     */
    template<class T> static void list_commands(const User::Type &t);
    /**
     * @brief Get comparison function to sort clients.
     * @param t User type
     * @param i Property of user that will be used in comparison function
     * @param cmp Reference to function where comparison function will be stored
     */
    static void list_sort_getcomp(const User::Type &t, int i, std::function<bool(const Client *, const Client *)> &cmp);
    /**
     * @brief Get comparison function to sort drivers.
     * @param t User type
     * @param i Property of user that will be used in comparison function
     * @param cmp Reference to function where comparison function will be stored
     */
    void list_sort_getcomp(const User::Type &t, int i, std::function<bool(const Driver *, const Driver *)> &cmp) const;
    /**
     * @brief Get comparison function to sort managers.
     * @param t User type
     * @param i Property of user that will be used in comparison function
     * @param cmp Reference to function where comparison function will be stored
     */
    static void list_sort_getcomp(const User::Type &t, int i, std::function<bool(const Manager*, const Manager*)> &cmp);
    /**
     * @brief Get comparison function to sort trucks.
     * @param t User type
     * @param i Property of truck that will be used in comparison function
     * @param cmp Reference to function where comparison function will be stored
     */
    static void list_sort_getcomp(const User::Type &t, int i, std::function<bool(const Truck  *, const Truck  *)> &cmp);
    /**
     * @brief Get comparison function to sort services.
     * @param t User type
     * @param i Property of service that will be used in comparison function
     * @param cmp Reference to function where comparison function will be stored
     */
    static void list_sort_getcomp(const User::Type &t, int i, std::function<bool(const Service*, const Service*)> &cmp);
    /**
     * @brief Get comparison function to sort workshops.
     * @param t User type
     * @param i Property of workshop that will be used in comparison function
     * @param cmp Reference to function where comparison function will be stored
     */
    static void list_sort_getcomp(const User::Type &t, int i, std::function<bool(const Workshop*, const Workshop*)> &cmp);

    /**
     * @brief Get comparison function to filter clients.
     * @param t     User type
     * @param i     Property of user to be used in comparison function
     * @param str   Value of property to filter.
     * @param cmp   Reference to function where comparison function will be stored
     */
    static void list_filter_getvalid(const User::Type &t, int i, const std::string &str, std::function<bool(const Client *)> &cmp);
    /**
     * @brief Get comparison function to filter drivers.
     * @param t User type
     * @param i Property of user to be used in comparison function
     * @param str   Value of property to filter.
     * @param cmp Reference to function where comparison function will be stored
     */
    void list_filter_getvalid(const User::Type &t, int i, const std::string &str, std::function<bool(const Driver *)> &cmp) const;
    /**
     * @brief Get comparison function to filter managers.
     * @param t User type
     * @param i Property of user to be used in comparison function
     * @param str   Value of property to filter.
     * @param cmp Reference to function where comparison function will be stored
     */
    static void list_filter_getvalid(const User::Type &t, int i, const std::string &str, std::function<bool(const Manager*)> &cmp);
    /**
     * @brief Get comparison function to filter trucks.
     * @param t User type
     * @param i Property of truck to be used in comparison function
     * @param str   Value of property to filter.
     * @param cmp Reference to function where comparison function will be stored
     */
    static void list_filter_getvalid(const User::Type &t, int i, const std::string &str, std::function<bool(const Truck  *)> &cmp);
    /**
     * @brief Get comparison function to filter services.
     * @param t User type
     * @param i Property of service to be used in comparison function
     * @param str   Value of property to filter.
     * @param cmp Reference to function where comparison function will be stored
     */
    static void list_filter_getvalid(const User::Type &t, int i, const std::string &str, std::function<bool(const Service*)> &cmp);
    /**
     * @brief Get comparison function to filter workshops.
     * @param t User type
     * @param i Property of workshop to be used in comparison function
     * @param str   Value of property to filter.
     * @param cmp Reference to function where comparison function will be stored
     */
    static void list_filter_getvalid(const User::Type &t, int i, const std::string &str, std::function<bool(const Workshop*)> &cmp);

    /**
     * @brief Lists all objects of T, and allows list to be modified according to commands available in %ref list_commands (and %ref extra_commands in some cases).
     * @param v     Vector of objects T to be listed
     * @param t     Type of user that list will be displayed to
     */
    template<class T> void list(std::vector<const T*> v, const User::Type &t) const;
    ///Commands
    /** @brief Application operation input system */
    static std::string prompt();
    /** @brief Wait for user input before continuing program flow */
    static void wait();
    /**
     * @brief Confirms user input via a yes/no validation.
     * @param msg Message to display before asking for input
     * @return True if input is 'yes', false if inputs a 'no'
     */
    static bool confirm(const std::string &msg);
    ///Operations
    /** @brief Lists all clients in agency */
    void list_clients () const;
    /** @brief List all inactive clients in agency */
    void list_inactive_clients() const;
    /** @brief Lists all drivers in agency */
    void list_drivers () const;
    /** @brief Lists all managers in agency */
    void list_managers() const;
    /** @brief Lists all trucks in agency */
    void list_trucks  () const;
    /** @brief Lists all services in agency */
    void list_services() const;
    /**
     * @brief Lists all services linked to user in agency
     * @param user  User to filter services
     */
    void list_services(const User *user) const;
    /** @brief Lists all workshops in agency database */
    void list_workshops() const;

    /** @brief Sends truck to workshop if any can match the service. */
    bool send_truck_to_workshop();

    /**
     * @brief Adds user to agency.
     * @param user_type  Type of user to be added
     * @return If truck was added
     */
    bool addUser(const User::Type &user_type);
    /**
     * @brief Delete user from agency.
     * @param type  Type of user to be deleted
     * @return If truck was added
     */
    template<class Deriv> bool deleteUser(const User::Type &type);
    /**
     * @brief Displays list of users and asks to choose user by ID.
     * @param type  Type of user to be chosen
     * @return User chosen, NULL if operation is cancelled
     */
    template<class Deriv> User* chooseUser(const User::Type &type);
    /**
     * @brief Edit user from agency.
     * @param type  Type of user to be edited
     * @return If user was edited
     */
    template<class Deriv> bool editUser(const User::Type &type); // manager function
    /**
     * @brief Edit own user account.
     * @param user  User account to be edited
     * @return If user was edited
     */
    template<class Deriv> bool editUser(User *user);

    /**
     * @brief Change password of user account.
     * @param user  User which password will be changed
     * @return If password was changed
     */
    bool changePassword(User *user);

    /**
     * @brief Adds truck to agency.
     * @return If truck was added
     */
    bool addTruck();
    /**
     * @brief Choose truck from agency.
     * @return Pointer to truck chosen, NULL if operation is cancelled
     */
    Truck* chooseTruck();
    /**
     * @brief Deletes truck from agency.
     * @return If the truck was deleted
     */
    bool deleteTruck();
    /**
     * @brief Edits truck from agency.
     * @return If the truck was edited
     */
    bool editTruck();
    /**
     * @brief Changes truck from truck to a new cargo (overrides existing cargo).
     * @param   cargo   Pointer to truck's cargo
     * @param   type    Type of new cargo
     * @return  If the truck was changed
     */
    bool change_truck_cargo(CargoTrans *&cargo, const Cargo::Type &type);
    /**
     * @brief Edit truck from truck.
     * @param   cargo       Pointer to truck's cargo
     * @param   property    Property to be changed
     * @return  If the truck was edited
     */
    bool edit_truck_cargo(CargoTrans *&cargo, int property);

    /**
     * @brief Adds service to agency.
     * @return If service was added
     */
    bool addService();
    /**
     * @brief Adds service to agency.
     * @param user Add service directly linked to user
     * @return If service was added
     */
    bool addService(const User *user);
    /**
     * @brief Choose service from agency.
     * @return Pointer to service chosen, NULL if operation is cancelled
     */
    Service* chooseService();
    /**
     * @brief Choose service from agency.
     * @param user User to filter services linked to user
     * @return Pointer to service chosen, NULL if operation is cancelled
     */
    Service* chooseService(const User *user);
    /**
     * @brief Deletes service from agency.
     * @return If the service was deleted
     */
    bool deleteService();
    /**
     * @brief Deletes service from agency.
     * @return If the service was deleted
     */
    bool deleteService(const User *user);

    /**
     * @brief Adds workshop to agency database.
     * @return If workshop was added
     */
    bool addWorkshop();
    /**
     * @brief Choose workshop from agency database.
     * @return Pointer to workshop chosen, NULL if operation is cancelled
     */
    Workshop* chooseWorkshop();
    /**
     * @brief Edits workshop from agency database.
     * @return If the workshop was edited
     */
    bool editWorkshop();
    /**
     * @brief Deletes workshop from agency database.
     * @return If the workshop was deleted
     */
    bool deleteWorkshop();

    /**
     * @brief Filter vector of users by user type.
     * @param v     Vector of users
     * @param t     Filter type
     * @return  Vector of users filtered by type
     */
    std::vector<User*> filter_user_by_type(const std::vector<User*> &v, const User::Type &t) const;
    /**
     * @brief Filter vector of services by client.
     * @param v          Vector of services
     * @param client     Client to filter vector by
     * @return  Vector of services filtered by client
     */
    std::vector<Service*> filter_services_by_client(const std::vector<Service*> &v, const Client *client) const;
    /**
     * @brief Filter vector of services by driver.
     * @param v          Vector of services
     * @param driver     Driver to filter vector by
     * @return  Vector of services filtered by driver
     */
    std::vector<Service*> filter_services_by_driver(const std::vector<Service*> &v, const Driver *driver) const;
    /**
     * @brief Find user in agency.
     * @param u Username (ID) of user to find
     * @return Pointer to user if it exists, else NULL
     */
    User* find_user(const User::Username &u) const;
    /**
     * @brief Find truck in agency.
     * @param np Number plate (ID) of truck to find
     * @return Pointer to truck if it exists, else NULL
     */
    Truck* find_truck(const Truck::NumberPlate &np) const;
    /**
     * @brief Find service in agency.
     * @param id ID of service to find
     * @return Pointer to service if it exists, else NULL
     */
    Service* find_service(const Service::ID &id) const;
    /**
     * @brief Verifies user credentials.
     * @param username Username (ID) of user
     * @param password Password of user
     * @return Pointer to user if it exists, else NULL
     */
    User* verifyUser(const std::string &username, const std::string &password);
    /**
     * @brief Get available drivers to go to a service.
     * @param s     Service we want to know the availability
     * @return  Multiset containing the available drivers, ordered by least work hours in current month
     */
    std::multiset<Driver*, App::comp_drivers> get_available_drivers(const Service *s) const;
    /**
     * @brief Get available trucks to go to a service.
     * @param s     Service we want to know the availability
     * @return  Vector containing the available drivers
     */
    std::vector<Truck *> get_available_trucks (const Service *s) const;

    // Menus
    /**
     * @brief Prints menu to guests.
     * @param user User to store login account
     * @return If login was sucessful
     */
    bool guestMenu(User* &user);
    /**
     * @brief Prints menu of user.
     * @param user_type User type that menu will be displayed to
     * @return False if any error occurs, true otherwise.
     */
    bool printUserMenu(User::Type user_type);
    /**
     * @brief Main menu for user.
     * @param user      Pointer to user that did login on agency.
     * @param user_type Type of user user.
     * @return False if any error occurs, true otherwise.
     */
    bool userMenu(User *user, User::Type user_type);
public:
    /**
     * @brief Constructor.
     * @param base      Base path to all data files.
     * @param managers  Path from base to manager data file.
     * @param drivers   Path from base to drivers data file.
     * @param clients   Path from base to clients data file.
     * @param brands    Path from base to brands data file.
     * @param trucks    Path from base to trucks data file.
     * @param services  Path from base to services data file.
     * @param workshops Path from base to workshops data file.
     */
    App(const std::string &base     ,
        const std::string &managers , const std::string &drivers ,
        const std::string &clients  , const std::string &brands  ,
        const std::string &trucks   , const std::string &services,
        const std::string &workshops                             );

    /** @brief Destructor. */
    ~App();

    /**
     * @brief Outputs error message.
     * @param s     Error message
     */
    static void error(const std::string &s);

    /** @brief Runs main application */
    void start();

    /**
     * @brief Get schedule of a Driver.
     * @param   p   Pointer to Driver for which we want the schedule
     * @return  Schedule for driver
     */
    Schedule get_schedule(const Driver *p) const;
    /**
     * @brief Get schedule of a Truck.
     * @param   p   Pointer to Truck for which we want the schedule
     * @return  Schedule for truck
     */
    Schedule get_schedule(const Truck  *p) const;

    /** @brief Exception class to report invalid credentials */
    class InvalidCredentials: public std::runtime_error {
    private:
        /// @brief Message that explains what caused exception.
        std::string msg_;
    public:
        /** @brief Constructor accepting an information message to explain what caused exception */
        InvalidCredentials(const std::string &msg);
        /// @brief Get information message about the exception.
        const std::string& getMsg() const;
    };

    /** @brief Exception class to report repeated IDs */
    class RepeatedId: public std::runtime_error {
    private:
        /// @brief ID that caused exception.
        std::string id_;
    public:
        /**
         * @brief Constructor accepting ID that caused the exception.
         * @param   id  ID that caused the exception
         */
        RepeatedId(const std::string &id);
        /// @brief Get ID that caused the exception
        const std::string& get_id() const;
    };
};

template<class Base, class Deriv, class Type>
std::vector<const Deriv*> App::filter(const std::vector<const Base*> &v, const Type &t){
    std::vector<const Base*> v1 = utils::filter(v,
        [&t](const Base *p){
            return (p->get_type() == t);
        }
    );
    std::vector<const Deriv*> retv = std::vector<const Deriv*>(v1.size());
    std::transform(v1.begin(), v1.end(), retv.begin(), [](const Base *p){
        const Deriv *ret = dynamic_cast<const Deriv*>(p);
        if(ret == nullptr) throw std::bad_cast();
        return ret;
    });
    return retv;
}

template<class Deriv> User* App::chooseUser(const User::Type &type) {
    std::cout << "Choosing user.\n";
	std::vector<User*> temp;
	for (auto p: musers_) temp.push_back(p.second);
    std::vector<const User*> v(temp.begin(), temp.end());
    std::vector<const Deriv*> users_filter = App::filter<User,Deriv,User::Type>(v, type);

    print_list(users_filter, type);
    while (true) {
        std::string id;
        if (!utils::input("Choose user (username): ", id, std::cin, std::cout)) return NULL;
        User::Username username = User::Username(id);
        User *it = find_user(username);
        if (it == NULL) {
            error("User doesn't exist (username doesn't have matches).");
            continue;
        } else {
            return it;
        }
    }
}

template<class Deriv> bool App::deleteUser(const User::Type &type) {
    CLEAR();
    std::cout << "Deleting user.\n";
    while (true) {
        User *user = App::chooseUser<Deriv>(type);
        if (user == NULL) return false;
		std::vector<User*> temp;
		for (auto p: musers_) temp.push_back(p.second);
        std::vector<User*>::iterator user_it = std::find(temp.begin(), temp.end(), user);
        if (!confirm("Confirm the deletion of user \'" + std::string((*user_it)->get_username()) + "\' (yes/no): ")) return false;
        inactive_clients_.erase(dynamic_cast<Client*>(*user_it));
        delete *user_it;
        musers_.erase((*user_it)->get_username());
        std::cout << "User deleted.\n";
        return true;
    }
    return false;
}

template<class Deriv> bool App::editUser(const User::Type &type) {
    CLEAR();
    std::cout << "Editing user.\n";
    User *user = App::chooseUser<Deriv>(type);
    if (user == NULL) return false;
    User::Type user_type = user->get_type();
    int no_properties = 4 + (user_type == User::Type::manager || user_type == User::Type::driver);
    int option;
    Deriv user_copy = *dynamic_cast<Deriv*>(user);
    bool is_edited = false;
    while (true) {
        option = 0;
        App::display(&user_copy, User::Type::manager);
        if (!utils::input("Choose property to change (type cancel to finish): ", option, std::cin, std::cout)) break;
        if (option <= 0 || option > no_properties) { App::error("Option outside of range."); continue; }
        if(user_copy.edit(option, std::cin, std::cout)) is_edited = true;
    }
    if (is_edited) {
        if (!confirm("Confirm the edition of user \'" + std::string(user_copy.get_username()) + "\' (yes/no): ")) return false;
        *user = user_copy;
        std::cout << "User edited.\n";
        return true;
    }
    return false;
}

template<class Deriv> bool App::editUser(User *user) {
    CLEAR();
    std::cout << "Editing user.\n";
    User::Type user_type = user->get_type();
    int no_properties = 4 + (user_type == User::Type::manager || user_type == User::Type::driver);
    int option;

    Deriv user_copy = *dynamic_cast<Deriv*>(user);
    bool is_edited = false;
    while (true) {
        option = 0;
        App::display(&user_copy, User::Type::manager);
        if (!utils::input("Choose property to change (type cancel to finish): ", option, std::cin, std::cout)) break;
        if (option <= 0 || option > no_properties) { App::error("Option outside of range."); continue; }
        if (user_copy.edit(option, std::cin, std::cout)) is_edited = true;
    }
    if (is_edited) {
        if (!confirm("Confirm the changes (yes/no): ")) return false;
        *user = user_copy;
        std::cout << "Saved changes.\n";
        return true;
    }
    return false;
}

#endif //APP_H_INCLUDED
