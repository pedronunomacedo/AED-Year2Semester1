#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED

/**
 * @brief Class to easen displaying data related to calendars in a month.
 *
 * This class was is not fully implemented and was not used in the project.
 */
template<class T>
class Calendar{
private:
    /// @brief Time indicating month that will be printed.
    Time t;
    /// @brief Information to be printed in the calendar.
    std::vector<T> info;
public:
    /**
     * @brief Construct from day. Will display calendar of month that day belongs to.
     * @param   t_  Time object with day the calendar will display
     */
    Calendar(const Time &t_):t(t_){}
    /**
     * @brief Set info to display in calendar.
     * @param   v   Vector of info to be displayed
     */
    void set_info(const std::vector<T> &v){ info = v; }
    /**
     * @brief Draw calendar with info.
     * @param   os  ostream the calendar will be written to
     */
    std::ostream& draw(std::ostream &os) const{
        std::cout << "Calendar\n";

        return os;
    }
};

#endif //CALENDAR_H_INCLUDED
