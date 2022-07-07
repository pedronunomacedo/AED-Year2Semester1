/**
 * @file currency.h
 */

#ifndef CURRENCY_H_INCLUDED
#define CURRENCY_H_INCLUDED

#include <iostream>

/**
 * @brief Class for storing amounts of a given currency.
 *
 * Internally uses integers so the representation of the amount of currency is exact.
 */
class Currency{
private:
    /// @brief Value of currency in cents (euro cents).
    long long int cents_;
public:
    /**
     * @brief           Construct from amount of currency as a \a double.
     * @param   amount  Amount of currency
     */
    explicit Currency(double amount = 0.0L);

    /// @brief Overload of \a operator+ .
    Currency  operator+ (const Currency &c) const;
    /// @brief Overload of \a operator- .
    Currency  operator- (const Currency &c) const;
    /// @brief Overload of \a operator+ for sign changing.
    Currency  operator+ ()                  const;
    /// @brief Overload of \a operator- for sign changing.
    Currency  operator- ()                  const;
    /// @brief Overload of \a operator+= .
    Currency& operator+=(const Currency &c);
    /// @brief Overload of \a operator-= .
    Currency& operator-=(const Currency &c);

    /// @brief Overload of \a operator== .
    bool      operator==(const Currency &c) const;
    /// @brief Overload of \a operator!= .
    bool      operator!=(const Currency &c) const;
    /// @brief Overload of \a operator< .
    bool      operator< (const Currency &c) const;
    /// @brief Overload of \a operator> .
    bool      operator> (const Currency &c) const;
    /// @brief Overload of \a operator<= .
    bool      operator<=(const Currency &c) const;
    /// @brief Overload of \a operator>= .
    bool      operator>=(const Currency &c) const;

    /// @brief Assignment with \a double
    Currency& operator=(const double &n);
    /// @brief Conversion to \a double
    explicit operator double() const;

    /** @brief   Overload of \a operator>> . */
    friend std::istream& operator>>(std::istream &is,       Currency &c);

    /** @brief   Overload of \a operator<< . */
    friend std::ostream& operator<<(std::ostream &os, const Currency &c);

    /** @brief Gets the amount of money in cents.*/
    long long int getCents(void) const;

};

#endif //CURRENCY_H_INCLUDED
