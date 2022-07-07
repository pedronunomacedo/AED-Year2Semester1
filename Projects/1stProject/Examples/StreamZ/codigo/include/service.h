/**
 * @file service.h
 */

#ifndef SERVICE_H_INCLUDED
#define SERVICE_H_INCLUDED

#include <vector>

#include "person.h"
#include "Time.h"
#include "cargo.h"
#include "truck.h"

/**
 * @brief Class to store all the information concerning a transport service.
 */
class Service{
public:
    /** @brief ID type */
    typedef std::string ID;
private:
    /// @brief Cost to the agency to make this service.
    Currency cost_;
    /// @brief Revenue gained by the agency upon completion of the service.
    Currency revenue_;
    /// @brief Service ID.
    ID id_;
    /// @brief Service ID.
    Client::Username client_user_;
    /// @brief Person to contact on pick-up of merchandise.
    Person contact1_;
    /// @brief Person to contact on delivery of merchandise.
    Person contact2_;
    /// @brief Time to begin the service.
    Time t_begin_;
    /// @brief Time that service should be finished.
    Time t_end_;
    /// @brief Address to pick-up merchandise.
    Address a_begin_;
    /// @brief Address to delivery merchandise.
    Address a_end_;
    /// @brief Total distance travelled the service will take.
    utils::Distance distance_;
    /// @brief Merchandise request on the service.
    Cargo *cargo_ = NULL;
    /// @brief Trucks allocated by the agency to this service.
    std::vector<Truck ::NumberPlate> trucks_;
    /// @brief Drivers that will drive the trucks.
    std::vector<Driver::Username   > drivers_;
public:
    /** @brief ID of next service*/
    static int next_id_;

    /** @brief Empty constructor. */
    Service();
    /**
     * @brief Constructor creates an empty service linked to a specific user.
     * @param   client_user     Pointer to @ref Client to which the service will be provided
     */
    Service(const Client::Username &client_user);
    /** @brief Destructor */
    ~Service();
    /**
     * @brief Assign new id to current service.
     *
     * In practice it is this function that makes a Service from a collection of
     * information into an actual service that must be stored.
     */
    void assign_new_id();

    /// @brief Get ID
    const std::string&      get_id      () const;
    /// @brief Get client
    const Client::Username& get_client  () const;
    /// @brief Get contact 1
    const Person&           get_contact1() const;
    /// @brief Get contact 2
    const Person&           get_contact2() const;
    /// @brief Get time of arrival to loading address
    const Time&             get_tbegin  () const;
    /// @brief Get time of arrival to unloading address
    const Time&             get_tend    () const;
    /// @brief Get loading address
    const Address&          get_abegin  () const;
    /// @brief Get unloading address
    const Address&          get_aend    () const;
    /// @brief Get distance between the two addresses
    const utils::Distance&  get_distance() const;
    /// @brief Get pointer to cargo
    const Cargo*            get_cargo   () const;
    /// @brief Get trucks assigned to this service
    const std::vector<Truck ::NumberPlate>& get_trucks () const;
    /// @brief Get drivers assigned to this service
    const std::vector<Driver::Username   >& get_drivers() const;
    /// @brief Get cost of making this service
    const Currency& get_cost   () const;
    /// @brief Get revenue from this service
    const Currency& get_revenue() const;

    /**
     * @brief Set time the service begins.
     * @param   t   Time the service begins
     */
    void set_tbegin(const Time &t);

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allocate service to the necessary number of trucks and drivers
     * @param   tv  \a std::vector of pointers to Truck, available trucks
     * @param   dv  \a std::vector of pointers to Drivers, available drivers
     * @return  True if succeeded to allocate service, false otherwise
     */
    bool allocate(std::vector<const Truck*> tv, std::vector<const Driver*> dv);

    /** @brief Overload of <em> operator>> </em>. */
    friend std::istream& operator>>(std::istream &is,       Service &s);
    /** @brief Overload of <em> operator<< </em>. */
    friend std::ostream& operator<<(std::ostream &os, const Service &s);
};

#endif //SERVICE_H_INCLUDED
