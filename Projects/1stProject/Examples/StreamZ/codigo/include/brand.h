/**
 * @file brand.h
 */

#ifndef BRAND_H_INCLUDED
#define BRAND_H_INCLUDED

#include <unordered_set>
#include <string>
#include <stdexcept>
#include <vector>

/** @brief Class to store brand of truck */
class Brand {
    /** @brief Available brands. Any brand that isn't here won't be constructed */
    static std::unordered_set<std::string> available_brands_;
    /** @brief Brand name. */
    std::string brand_;

public:
    /**
     * @brief Initializes available brands.
     * @param   v   Vector containing the brands names to be made available.
     */
    static size_t set_brands(const std::vector<std::string> &v);

    /**
     * @brief Loads brands stored onto the vector.
     * @param v     Vector to store the brands.
     */
    static void brands_to_vector(std::vector<std::string> &v);
    /// @brief Default Constructor.
    explicit Brand();
    /**
     * @brief Constructor accepting a string that contains the brand name.
     * @param   s       Brand name
     * @throws  If brand isn't on the available brands
     */
    explicit Brand(const std::string &s);
    /// @brief Get brand name.
    const std::string& get_brand(void) const;
    /// @brief Converts brand to string.
    operator std::string() const;

    /// @brief Overload of <em>operator==</em>.
    bool operator==(const Brand &t) const;
    /// @brief Overload of <em>operator< </em>.
    bool operator< (const Brand &t) const;
    /** @brief Overload of operator=. */
    Brand& operator=(const std::string &s);
    /** @brief   Overload of <em> operator>> </em>. */
    friend std::istream& operator>>(std::istream &is,       Brand &t);
    /** @brief   Overload of <em> operator<< </em>. */
    friend std::ostream& operator<<(std::ostream &os, const Brand &t);

    /**
     * @brief   Class for denoting an invalid brand name
     */
    class InvalidBrand: public std::invalid_argument{
    private:
        /// @brief Brand name that caused exception.
        std::string brand_;
    public:
        /**
         * @brief Constructor accepting the brand name that caused the exception.
         *
         * Also sets the string returned by <em> std::exception::what() </em>.
         * @param   brand     Brand name
         */
        InvalidBrand(const std::string &brand);
        /**
         * @brief   Get brand name from which the exception was constructed.
         * @return  Brand name
         */
        const std::string& get_brand() const;
    };
};

#endif /* end of include guard: BRAND_H_INCLUDED */
