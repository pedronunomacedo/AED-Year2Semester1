/**
 * @file workshop.h
 */

#ifndef WORKSHOP_H_INCLUDED
#define WORKSHOP_H_INCLUDED

#include <string>
#include <set>

#include "brand.h"
#include "utils.h"
#include "Time.h"

/**
 * @brief Class representing a workshop.
 * @ref Workshop
 */
class Workshop {

public:
    /** @brief %ID class */
    class ID: public utils::string_regex {
    public:
        /// @brief Regex an ID is supposed to match.
        static const std::string ID_STR;
        /// @brief Default constructor.
        explicit ID();
        /// @brief Constructor accepting string as argument for construction.
        explicit ID(const std::string &id);
        /// @brief Overload of \a operator=.
        ID& operator=(const std::string &s);
    };
private:
    /** @brief Workshop display name */
    std::string name_;
    /** @brief Workshop ID */
    Workshop::ID id_;
    /** @brief Brands that workshop is specialized */
    std::set<Brand> brands_;
    /** @brief Date when workshop will be available */
    Time availability_;
protected:
    /**
     * @brief Allows Workshop fields to be filled from input stream.
     * @param   is  Input stream
     */
     std::istream& input(std::istream &is);
public:
    /** @brief Default Constructor. */
    Workshop();
    /** @brief Destructor */
    ~Workshop();

    /// @brief Get workshop ID. */
    const Workshop::ID&         get_id(void)            const;
    /// @brief Get workshop name. */
    const std::string&          get_name(void)          const;
    /// @brief Get brands. */
    const std::set<Brand>&      get_brands(void)        const;
    /// @brief Get workshop availability. */
    Time                        get_availability(void)  const;

    /// @brief Increase time until workshop is free.
    void increase_availability(int no_days);

    /// @brief Verify if brand is on the brands that workshop is specialized.
    /**
     * @brief Verify if brand is on the brands that workshop is specialized.
     * @param   brand       Brand to be searched.
     * @return If brand was found.
     */
    bool find_brand(const Brand& brand) const;
    /// @brief Overload of \a find_brand
    bool find_brand(const std::string& s) const;
    /**
     * @brief Inserts brand to workshop brands, if possible.
     * @param   brand       Brand to be inserted.
     * @return If brand was inserted with success.
     */
    bool insert_brand(const Brand &brand);
    /**
     * @brief Deletes brand from workshop brands, if possible.
     * @param   brand       Brand to be deleted.
     * @return If brand was deleted with success.
     */
    bool delete_brand(const Brand &brand);
    /// @brief Overload of \a operator<
    bool operator<(const Workshop& w) const;
    /// @brief Overload of \a operator==
    bool operator==(const Workshop &w) const;

    /// @brief Overload of \a operator>> .
    friend std::istream& operator>>(std::istream &is,       Workshop &p);
    /// @brief Overload of \a operator<< .
    friend std::ostream& operator<<(std::ostream &os, const Workshop &p);

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

#endif /* end of include guard: WORKSHOP_H_INCLUDED */
