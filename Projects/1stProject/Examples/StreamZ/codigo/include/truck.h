/**
 * @file truck.h
 */

#ifndef TRUCK_H_INCLUDED
#define TRUCK_H_INCLUDED

#include "currency.h"
#include "cargo.h"
#include "Time.h"
#include "brand.h"

#include <vector>
#include <utility>

/**
 * @brief Class representing the trucks of the company.
 * @ref   Cargo
 */
class Truck {
public:
    /** @brief Class to store number plates. */
    class NumberPlate{
    public:
        /** @brief Class to store number plate number (i.e., excluding country and other info) */
        class Number: public utils::string_regex{
        public:
            /** @brief   Regular expression string that describes a valid number plate. */
            static const std::string REGEX_STR;
            /** @brief   Empty constructor. */
            explicit Number();
            /**
             * @brief   Constructs from string containing number plate.
             * @param   plate   String with numberplate
             */
            explicit Number(const std::string &plate);
            /** @brief Overload of operator=. */
            Number& operator=(const std::string &s);
        };
        /*
        enum Country : int{
            Portugal = 0
        };
        */
    private:
        /// @brief Number of the plate.
        Number number_;
        //Country country_;
    public:
        /** @brief Empty constructor. */
        explicit NumberPlate();
        /** @brief Constructor accepting string */
        explicit NumberPlate(const Number &number);
        /** @brief Convert to std::string */
        explicit operator std::string() const;
        /** @brief Overload of operator<. */
        bool operator< (const NumberPlate &n) const;
        /** @brief Overload of operator==.*/
        bool operator==(const NumberPlate &n) const;
        /** @brief Overload of operator>> */
        friend std::istream& operator>>(std::istream &is,       NumberPlate &n);
        /** @brief Overload of operator<< */
        friend std::ostream& operator<<(std::ostream &os, const NumberPlate &n);
    };
    /** @brief Vehicle category. */
    class Category: public utils::string_regex{
    public:
        /** @brief Regex a vehicle category is supposed to match. */
        static const std::string REGEX_STR;
        /** @brief Empty constructor. */
        explicit Category();
        /** @brief Constructor accepting string as argument for construction. */
        explicit Category(const std::string &category);
        /** @brief Overload of operator= */
        Category& operator=(const std::string &category);
    };
    /** @brief %Fuel */
    enum Fuel : int{
        Biodiesel = 0,
        Diesel = 1,
        Electric,
        Gas,
        Gasoline,
        Hybrid,
        Hydrogen
    };
    /** @brief Convert Fuel to string to present in tables. */
    static std::string fuel_string(const Fuel &f);
    /** @brief Type of truck (always truck, made to conform with Users that also have types) */
    enum Type{
        truck
    };
private:
    //std::vector<Event> logs_;
    /// @brief Number plate of the truck.
    NumberPlate number_plate_;
    /// @brief Time when plate number of the truck was registered.
    Time plate_register_date_;
    /// @brief Type of fuel of the truck @ref Fuel
    Fuel fuel_;
    /// @brief Maximum distance that truck can travel.
    utils::Distance max_reach_;
    /// @brief Category of the truck.
    Category category_; //A,B,C,D
    /// @brief Brand of the truck.
    Brand brand_;

    /// Cargo that can be transported by the truck.
    CargoTrans *cargo_ = NULL;

public:
    /** @brief Default Constructor. */
    Truck();
    /** @brief Destructor */
    virtual ~Truck();

    /// @brief Get number plate.
    const NumberPlate& get_numberplate      () const;
    /// @brief Get number plate (in this case the same as number plate).
    const NumberPlate& get_id               () const;
    /// @brief Get number plate register date.
    const Time&        get_plateregisterdate() const;
    /// @brief Get fuel.
    const Fuel&        get_fuel             () const;
    /// @brief Get maximum reach/range of the truck.
    const utils::Distance&    get_range            () const;
    /// @brief Get category.
    const Category&    get_category         () const;
    /// @brief Get brand.
    const Brand&        get_brand           () const;
    /// @brief Get cargo pointer.
    const CargoTrans*  get_cargo            () const;
    /// @brief Get cargo pointer (non-const)
    CargoTrans*&       get_cargo_nc         ()      ;
    /// @brief Get type of vehicle (always Truck)
    virtual Type get_type(void) const;

    /**
     * @brief Converts string into %Fuel.
     * @param s   String containing the type of fuel
     * @return Type of %Fuel
     * @throws std::invalid_argument If type of fuel is invalid
     */
    static Fuel processFuel(const std::string &s);

    /**
     * @brief Creates a complete copy of a truck.
     * @param truck   Truck to be copied
     * @return Pointer to a new Truck object that's a copy of the original
     * @throws std::invalid_argument If any error occurs while copying
     */
    static Truck* deep_copy(const Truck *truck);

    /** @brief   Overload of <em> operator>> </em>. */
    friend std::istream& operator>>(std::istream &is,       Truck &t);
    /** @brief   Overload of <em> operator<< </em>. */
    friend std::ostream& operator<<(std::ostream &os, const Truck &t);

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    bool in(std::istream &is, std::ostream &os);
    /**
     * @brief Allows edition of property specified.
     * @param property Property to be edited
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    bool edit(int property, std::istream &is, std::ostream &os);
};

#endif /* end of include guard: TRUCK_H_INCLUDED */
