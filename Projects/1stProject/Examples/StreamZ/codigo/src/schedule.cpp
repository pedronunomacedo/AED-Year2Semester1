#include "schedule.h"

bool Schedule::cmp(const Service *s1, const Service *s2){
    return (s1->get_tbegin() < s2->get_tbegin());
}
Schedule::Schedule():st(Schedule::cmp),valid(true){}
bool Schedule::is_available(const Service *s) const{
    auto it = st.upper_bound(s);
    const Service *s1 = nullptr, *s2 = nullptr;
    if(it != st.end  ()) s2 = *it;
    if(it != st.begin()) s1 = *(--it);
    bool good1 = (s1 == nullptr || s1->get_tend() <= s->get_tbegin());
    bool good2 = (s2 == nullptr || s->get_tend() <= s2->get_tbegin());
    return good1 && good2;
}
void Schedule::add_service(const Service *s){
    valid = valid && is_available(s);
    st.insert(s);
}
Schedule::operator bool() const{ return valid; }
Time::TimeDiff Schedule::work() const{
    return work(Time("20000101_000000"), Time("30000101_000000"));
}
Time::TimeDiff Schedule::work(const Time &l, const Time &r) const{
    Time::TimeDiff ret(0.0);
    Service ls; ls.set_tbegin(l);
    Service rs; rs.set_tbegin(r);
    auto it1 = st.upper_bound(&ls); if(it1 != st.begin()) --it1;
    auto it2 = st.upper_bound(&rs);
    while(it1 != it2){
        Time t1 = std::max(l, std::min(r, (*it1)->get_tbegin()));
        Time t2 = std::max(l, std::min(r, (*it1)->get_tend  ()));
        ret += (t2-t1);
        ++it1;
    }
    return ret;
}
Time::TimeDiff Schedule::work_month(const Time &t) const{
    Time::TimeDiff ret;
    Time l = t.first_day_month();
    Time r = t. last_day_month();
    return work(l, r);
}
