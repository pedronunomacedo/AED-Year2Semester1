/**
 * @file temperature.h
 */

#ifndef TEMPERATURE_H_INCLUDED
#define TEMPERATURE_H_INCLUDED

#include <iostream>

/** Store temperature in degrees Celsius, providing validation for
 *  absolute zero (-273.15) and boiling temperature (+100).
 */
class Temperature{
private:
    /// @brief Temperature value
    double temp_;
public:
    /// @brief Empty constructor
    Temperature();
    /**
     * @brief Constructor accepting temperature.
     *
     * Makes necessary checks and throws exception of type Temperature::InvalidTemperature if needed.
     * @param   temp    %Temperature from which to initialize object
     */
    explicit Temperature(double temp);

    /// @brief Overload of <em>operator+</em>.
    double      operator+(const Temperature &t) const;
    /// @brief Overload of <em>operator-</em>.
    double      operator-(const Temperature &t) const;

    /// @brief Overload of <em>operator==</em>.
    bool operator==(const Temperature &t)const;
    /// @brief Overload of <em>operator< </em>.
    bool operator< (const Temperature &t)const;
    /// @brief Overload of <em>operator> </em>.
    bool operator> (const Temperature &t)const;
    /// @brief Overload of <em>operator>=</em>.
    bool operator>=(const Temperature &t)const;
    /// @brief Overload of <em>operator<=</em>.
    bool operator<=(const Temperature &t)const;

    /// @brief Conversion to double
    explicit operator double() const{ return temp_; }

    /// @brief Overload of <em> operator>> </em>.
    friend std::istream& operator>>(std::istream &is,       Temperature &t);
    /// @brief Overload of <em> operator<< </em>.
    friend std::ostream& operator<<(std::ostream &os, const Temperature &t);

    /**
     * @brief Exception for reporting invalid temperature.
     */
    class InvalidTemperature: public std::invalid_argument{
    private:
        /// @brief Temperature value that caused exception.
        double temp_;
    public:
        /**
         * @brief Constructor accepting offending temperature value.
         * @param   temp    %Temperature value that caused the exception
         */
        InvalidTemperature(const double &temp);
        /// @brief Get temperature that caused the exception
        const double& get_temperature()const;
    };
};

/**
 * @brief Store temperature range as a min/max pair, providing validation for min<max.
 */
class TemperatureRange{
public:
    /// @brief Maximum value of the range.
    Temperature min;
    /// @brief Minimum value of the range.
    Temperature max;

    /// @brief Empty constructor.
    TemperatureRange();
    /**
     * @brief Constructor accepting range of temperatures [tmin, tmax]. Throws appropriate exception if necessary.
     * @param   tmin    Minimum temperature of the range
     * @param   tmax    Maximum temperature of the range
     */
    TemperatureRange(const Temperature &tmin, const Temperature &tmax);

    /// @brief Overload of <em> operator>> </em>.
    friend std::istream& operator>>(std::istream &is,       TemperatureRange &r);
    /// @brief Overload of <em> operator<< </em>.
    friend std::ostream& operator<<(std::ostream &os, const TemperatureRange &r);

    /**
     * @brief Exception for reporting invalid temperature range.
     */
    class InvalidTemperatureRange: public std::invalid_argument{
    private:
        /// @brief Minimum temperature of pair of values that caused exception.
        Temperature min;
        /// @brief Maximum temperature of pair of values that caused exception.
        Temperature max;
    public:
        /**
         * @brief Constructor accepting the extreme values of the range that caused the exception.
         * @param   tmin    Minimum temperature of the offending range
         * @param   tmax    Maximum temperature of the offending range
         */
        InvalidTemperatureRange(const Temperature &tmin, const Temperature &tmax);
        /// @brief Get temperature range that caused the exception as a pair.
        std::pair<Temperature,Temperature> get_temperature_range() const;
    };
};

#endif //TEMPERATURE_H_INCLUDED
