#ifndef SCHEDULE_H_INCLUDED
#define SCHEDULE_H_INCLUDED

#include "service.h"
#include "Time.h"
#include <set>

/**
 * @brief Schedule of an entity (e.g., driver or truck)
 */
class Schedule{
private:
    /**
     * @brief Comparison function to sort Services internally.
     *
     * Services are sorted by start time.
     *
     * @param   s1  Service 1
     * @param   s2  Service 2
     * @return  True if s1 comes before s2, false otherwise
     */
    static bool cmp(const Service *s1, const Service *s2);
    /// @brief Set of services that make up the schedule, sorted by start time.
    std::set<const Service *, bool(*)(const Service*, const Service*)> st;
    /// @brief Indication of the validity of the schedule (false if there is overlapping).
    bool valid;
public:
    /// @brief Empty constructor.
    Schedule();
    /**
     * @brief Check if a new Service can be fit in the current schedule without overlapping.
     * @param   s   Pointer to const Service that should be attempted to fit
     * @return      True if the insertion would be valid, false otherwise
     */
    bool is_available(const Service *s) const;
    /**
     * @brief Add service to schedule.
     * @param   s   Service to be added
     */
    void add_service (const Service *s);
    /**
     * @brief Conversion to bool, yielding true if the schedule is valid (no overlapping)
     */
    operator bool() const;
    /**
     * @brief Total work time in the schedule.
     * @return  Time of total work time
     */
    Time::TimeDiff work() const;
    /**
     * @brief Work time between two time points.
     * @param   l   First limit of the time interval
     * @param   r   Second limit of the time interval
     * @return Time of work in the given time interval
     */
    Time::TimeDiff work(const Time &l, const Time &r) const;
    /**
     * @brief Work time in the month the time provided belongs to
     * @param   t   Month to evaluate work time
     * @return  Time of work in that month
     */
    Time::TimeDiff work_month(const Time &t) const;
};

#endif //SCHEDULE_H_INCLUDED
