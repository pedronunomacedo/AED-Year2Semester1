#include "Time.h"

#include <sstream>
#include <iomanip>
#include <regex>
#include <chrono>
#include "../include/utils.h"


Time::TimeDiff::TimeDiff(double Dt):dt(Dt){}
Time::TimeDiff Time::TimeDiff::operator+(const TimeDiff &t) const{
    TimeDiff ret;
    ret.dt = dt + t.dt;
    return ret;
}
Time::TimeDiff& Time::TimeDiff::operator+=(const TimeDiff &t){
    *this = *this+t;
    return *this;
}
double Time::TimeDiff::hours() const{
    return dt/3600.0;
}
bool Time::TimeDiff::operator<(const Time::TimeDiff &t) const{
    return (dt < t.dt);
}

const std::string Time::DEFAULT_FORMAT = "%Y%m%d_%H%M%S";
const std::string Time::DEFAULT_TIME_REGEX = "^(\\d{4})/(\\d{2})/(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2})$";
const std::string Time::DEFAULT_DATE_REGEX = "^(\\d{4})/(\\d{2})/(\\d{2})$";
const std::string Time::DEFAULT_TIME   = "00010101_000000";

Time::Time(const std::string &s){
    std::stringstream ss(s);
    ss >> std::get_time(&t_, Time::DEFAULT_FORMAT.c_str());
    if (t_.tm_sec   >= 60 ||
        t_.tm_min   >= 60 ||
        t_.tm_hour  >= 24 ||
        t_.tm_mday  <= 0  ||
        t_.tm_mday  >  31 ||
        t_.tm_mon   >= 12)
        throw InvalidTime(s);
}

void Time::incrementDays(int no_days) {
    t_.tm_mday += no_days;
    t_.tm_hour++;
    ::mktime(&t_);
}

Time Time::get_current_date(void) {
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();


    std::time_t time_now = std::chrono::system_clock::to_time_t(now);

    std::tm *tm_p = std::localtime(&time_now);

    if (tm_p == NULL) throw std::runtime_error("Failed to get current time.");

    std::string y = utils::itos(tm_p->tm_year + 1900);
    std::string m = utils::itos(tm_p->tm_mon + 1);
    std::string d = utils::itos(tm_p->tm_mday);

    y = std::string(4 - y.size(), '0') + y;
    m = std::string(2 - m.size(), '0') + m;
    d = std::string(2 - d.size(), '0') + d;

    std::string tm_formatted = y + m + d + "_000000";

    return Time(tm_formatted);
}

int Time::get_year(void) const { return t_.tm_year + 1900; }

void Time::set_year(int year) {
    t_.tm_year = year - 1900;
}

std::string Time::format(const std::string &fmt) const{
    char buff[100];
    if(std::strftime(buff, sizeof(buff), fmt.c_str(), &t_)==0)
        throw InvalidTimeFormat(fmt);
    return std::string(buff);
}

void Time::input_time(const std::string &time) {
    static std::regex time_regex(DEFAULT_TIME_REGEX);
    std::smatch matches;

    if (std::regex_match(time, matches, time_regex)) {
        std::string tm_formatted = matches[1].str() + matches[2].str() + matches[3].str() +
                                    "_" + matches[4].str() + matches[5].str() + matches[6].str();

        Time new_time = Time(tm_formatted);
        this->t_ = new_time.t_;
    } else {
        throw Time::InvalidTimeFormat(time);
    }
}
void Time::input_date(const std::string &date) {
    static std::regex hour_regex(DEFAULT_DATE_REGEX);
    std::smatch matches;

    if (std::regex_match(date, matches, hour_regex)) {

        std::string tm_formatted = matches[1].str() + matches[2].str() + matches[3].str() + "_000000";

        Time new_time = Time(tm_formatted);
        this->t_ = new_time.t_;
    } else {
        throw Time::InvalidTimeFormat(date);
    }
}

int num_month[] = {0,3,2,5,0,3,5,1,4,6,2,4};
Time::DayOfWeek Time::get_dayofweek() const{
    int y = 1900+t_.tm_year;
    int m = t_.tm_mon + 1;
    int d = t_.tm_mday;
    y -= (m < 3);
    int ret = (y+y/4-y/100+y/400+num_month[m-1]+d+6)%7;
    return static_cast<Time::DayOfWeek>(ret);
}

bool Time::is_leap_year() const{
    int y = 1900+t_.tm_year;
    bool isLeapYear = false;
    if (y % 4 == 0) {
       if (y % 100 == 0) {
          if (y % 400 == 0) {
             isLeapYear = true;
          }
       }
       else isLeapYear = true;
    }
    return isLeapYear;
}

int Time::days_in_month() const{
    static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[t_.tm_mon] + (is_leap_year() && t_.tm_mon == 1 ? 1 : 0);
}

Time Time::first_day_month() const{
    Time t = *this;
    t.t_.tm_mday = 1;
    t.t_.tm_hour = 0;
    t.t_.tm_min  = 0;
    t.t_.tm_sec  = 0;
    return t;
}

Time Time::last_day_month() const{
    Time t = *this;
    t.t_.tm_mday = days_in_month();
    t.t_.tm_hour = 0;
    t.t_.tm_min  = 0;
    t.t_.tm_sec  = 0;
    return t;
}

bool Time::operator==(const Time &t) const{ return (format() == t.format()); }
bool Time::operator!=(const Time &t) const{ return !(*this == t); }
bool Time::operator< (const Time &t) const{ return (format() < t.format()); }
bool Time::operator> (const Time &t) const{ return (t < *this); }
bool Time::operator<=(const Time &t) const{ return !(*this > t); }
bool Time::operator>=(const Time &t) const{ return !(*this < t); }

Time::TimeDiff Time::operator-(const Time &t) const{
    tm t1 = t_, t2 = t.t_;
    time_t time_t1 = mktime(&t1);
    time_t time_t2 = mktime(&t2);
    return TimeDiff(difftime(time_t1, time_t2));
}

std::istream& operator>>(std::istream &is,       Time &t){
    std::string s;
    try{
        is >> s; t = Time(utils::urldecode(s));
    }catch(...){
        is.setstate(std::ios::failbit);
    }
    return is;
}
std::ostream& operator<<(std::ostream &os, const Time &t){
    return (os << utils::urlencode(t.format()));
}

Time::InvalidTime::InvalidTime(const std::string &date):
    std::invalid_argument("Invalid date: "+date),
    date_(date){}

const std::string& Time::InvalidTime::get_date() const { return date_; }

Time::InvalidTimeFormat::InvalidTimeFormat(const std::string &fmt):
    std::invalid_argument("Invalid time format ("+fmt+")"),
    fmt_(fmt){}
const std::string& Time::InvalidTimeFormat::get_format() const{ return fmt_; }
