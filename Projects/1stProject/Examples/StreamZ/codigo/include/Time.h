/**
 * @file Time.h
 */

#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <string>
#include <stdexcept>
#include <ctime>

/**
 * @brief Encapsulate time in a simple class with a few methods
 */
class Time {
private:
    /// @brief Time struct containing date and hour.
    std::tm t_;
public:

    /**
     * @brief Measure time differences
     */
    class TimeDiff{
    private:
        /// @brief double containing time difference in seconds.
        double dt;
    public:
        /**
         * @brief Construct time difference from value.
         * @param   Dt  Time difference in seconds
         */
        TimeDiff(double Dt = 0.0);
        /**
         * @brief Get time difference as the number of hours
         * @return  Hours as a double
         */
        double hours() const;
        /// @brief Overload of operator+.
        TimeDiff operator+(const TimeDiff &t) const;
        /// @brief Overload of operator+=.
        TimeDiff& operator+=(const TimeDiff &t);
        /// @brief Overload of operator<.
        bool operator<(const TimeDiff &t) const;
    };

    /**
     * @brief Day of week.
     *
     * The week is considered to start on a Monday.
     */
    enum DayOfWeek{
        Mon = 0,
        Tue,
        Wed,
        Thu,
        Fri,
        Sat,
        Sun
    };

    /**
     * @brief Default date format for input from files
     */
    static const std::string DEFAULT_FORMAT;
    /**
     * @brief Default full date format for input by user
     */
    static const std::string DEFAULT_TIME_REGEX;
    /**
     * @brief Default hour format for input by user
     */
    static const std::string DEFAULT_DATE_REGEX;
    /**
     * @brief Default time/date if none is set
     */
    static const std::string DEFAULT_TIME;
    /**
     * @brief Constructor accepting date in @ref DEFAULT_FORMAT.
     */
    Time(const std::string &s = DEFAULT_TIME);

    /**
     * @brief Increment date by a number of days.
     * @param no_days   Number of days to be incremented
     */
    void incrementDays(int no_days);

    /**
     * @brief Get the current date.
     * @return Current date.
     * @throws std::runtime_error If it fails to get the system current time.
     */
    static Time get_current_date(void);

    /// @brief Get year.
    int get_year(void) const;

    /**
     * @brief Change Time year.
     * @param year  Year to be set to.
     */
    void set_year(int year);

    /**
     * @brief Format date with format string.
     * @param   fmt Format string
     * @return  string with formatted date
     */
    std::string format(const std::string &fmt = Time::DEFAULT_FORMAT) const;

    /**
     * @brief Allows input of time in a friendly user way.
     * Default format for time is: YYYY-mm-dd HH:MM:SS.
     * @param time String containing input from user
     * @throws Time::InvalidTimeFormat If input doesn't follow format rules, Time::InvalidTime if input is invalid time
     */
    void input_time(const std::string &time);
    /**
     * @brief Allows input of date in a friendly user way.
     * Default format for time is: YYYY-mm-dd.
     * The hours, minutes and seconds will be set to the 00:00:00.
     * @param date String containing input from user
     * @throws Time::InvalidTimeFormat If input doesn't follow format rules, Time::InvalidTime if input is invalid time
     */
    void input_date(const std::string &date);

    /**
     * @brief Get day of week of current Time.
     * @return Day of week
     */
    Time::DayOfWeek get_dayofweek() const;
    /**
     * @brief Check if year is leap year or not.
     * @return True if leap year, false otherwise
     */
    bool is_leap_year() const;
    /**
     * @brief Get number of days in current month.
     * @return Number of days in the month.
     */
    int days_in_month() const;
    /**
     * @brief Get time of the first second of the first day of that month.
     * @return First day of the month
     */
    Time first_day_month() const;
    /**
     * @brief Get first second of the last day of that month.
     * @return Last day of the month
     */
    Time last_day_month() const;

    /// @brief Overload of <em>operator==</em>.
    bool operator==(const Time &t) const;
    /// @brief Overload of <em>operator!=</em>.
    bool operator!=(const Time &t) const;
    /// @brief Overload of <em>operator< </em>.
    bool operator< (const Time &t) const;
    /// @brief Overload of <em>operator> </em>.
    bool operator> (const Time &t) const;
    /// @brief Overload of <em>operator<=</em>.
    bool operator<=(const Time &t) const;
    /// @brief Overload of <em>operator>=</em>.
    bool operator>=(const Time &t) const;
    /// @brief Overload of <em>operator-</em>.
    TimeDiff operator-(const Time &t) const;

    /** @brief   Overload of <em> operator>> </em>. Expects input in @ref Time::DEFAULT_FORMAT. */
    friend std::istream& operator>>(std::istream &is,       Time &t);
    /** @brief   Overload of <em> operator<< </em>. Prints in @ref Time::DEFAULT_FORMAT. */
    friend std::ostream& operator<<(std::ostream &os, const Time &t);

    /**
     * @brief   Class for denoting an invalid time format
     */
    class InvalidTimeFormat: public std::invalid_argument{
    private:
        /// @brief Time format that caused exception.
        std::string fmt_;
    public:
        /**
         * @brief Constructor accepting the time format that caused the exception.
         *
         * Also sets the string returned by <em> std::exception::what() </em>.
         * @param   fmt     Time format
         */
        InvalidTimeFormat(const std::string &fmt);
        /**
         * @brief   Get time format from which the exception was constructed.
         * @return  Time format
         */
        const std::string& get_format() const;
    };

    /**
     * @brief   Class for denoting an invalid date
     */
    class InvalidTime: public std::invalid_argument {
    private:
        /// @brief Date that caused exception.
        std::string date_;
    public:
        /**
         * @brief Constructor accepting the time format that caused the exception.
         *
         * Also sets the string returned by <em> std::exception::what() </em>.
         * @param   date     String containing date that caused exception.
         */
        InvalidTime(const std::string &date);
        /**
         * @brief   Get date from which the exception was constructed.
         * @return  Date
         */
        const std::string& get_date() const;
    };
};

#endif //TIME_H_INCLUDED
