/**
 * @file utils.h
 */

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <string>
#include <stdexcept>
#include <vector>
#include <regex>
#include <iostream>

namespace utils{
    template<class T> class ufloat;
}

/** @brief Overload of operator>> for utils::ufloat. */
template<class T> std::istream& operator>>(std::istream &is,       utils::ufloat<T> &u);
/** @brief Overload of operator<< for utils::ufloat. */
template<class T> std::ostream& operator<<(std::ostream &os, const utils::ufloat<T> &u);

/** @brief Utilities */
namespace utils {
    /**
     * Get date and time now, as a string.
     * @return Time as string in format "%YYYY%mm%dd_%HH%MM%SS"
     */
    std::string get_now();
    /**
     * @brief Joins a list of words by a delimiter.
     * @param elems     Vector containing the strings
     * @param delim     Word delimiter
     * @return Joined string
     */
    std::string join(const std::vector<std::string>& elems, const std::string &delim);
    /**
     * @brief Trims all spaces from the start of the string (in-place).
     * @param s String to be trimmed
     * @throws  Throws if any of the function calls, the assignments or the operations on iterators throws.
     */
    void ltrim(std::string &s);

    /**
     * @brief Trims all spaces from the end of the string (in-place).
     * @param s String to be trimmed
     * @throws  Throws if any of the function calls, the assignments or the operations on iterators throws.
     */
    void rtrim(std::string &s);

    /**
     * @brief Trims all spaces from both ends of the string (in-place).
     * @param s String to be trimmed
     * @throws  Throws if any of the function calls, the assignments or the operations on iterators throws.
     */
    void trim(std::string &s);

    /**
     * @brief Converts all characters in string to lowercase.
     * @param s String to be transformed
     * @throws  Throws if any of the function calls, the assignments or the operations on iterators throws.
     */
    void to_lower(std::string &s);

    /**
     * @brief Capitalizes the first letter of each word in the string.
     * String must be trimmed, this is no space characters in the beginning nor at the end of the string.
     * @param   s   String to be capatilized, original string isn't changed.
     * @throws  Throws if any of the function calls throws, can be caused due to non-trimmed strings.
     * @return  The string capitilized.
     */
    std::string capitalize(const std::string &s);

    /**
     * @brief       Convert integer to string.
     * @param   i   Integer to convert
     * @return      String that resulted from converting \a i.
     * @throws  Throws if extractor operator on stringstream throws.
     */
    std::string itos(const long long int &i);

    /**
     * @brief       Convert double to std::string using specified format.
     * @param   fmt Format to output
     * @param   n   Number to convert to std::string
     * @return      Converted std::string
     * @throws      Throws if string constructor throws.
     */
    std::string ftos(const std::string &fmt, const double &n);

    /**
     * @brief       Convert string to integer.
     * @param   str String containing integer
     * @return      Result of the conversion to integer
     * @throws      std::invalid_argument If string can't be converted to number.
                    std::out_of_range If number can't be representable in int.
     */
    int stoi(const std::string &str);

    /**
     * @brief       Replace all occurences of a string.
     * @param   s   Original string
     * @param   fr  String to be replaced
     * @param   to  String to replace \a fr
     * @return      String with replaced occurences
     * @throws  Throws if any of the function calls, the assignments throws.
                If string isn't long enough, it causes undefined behaviour.
     */
    std::string strrep(const std::string &s, const std::string &fr, const std::string &to);

    /**
     * @brief       URL-encode string.
     * @param   s   Original string
     * @return      URL-encoded string
     * @throws  Throws if any of the function calls, the assignments throws.
     */
     std::string urlencode(const std::string &s);

    /**
     * @brief       URL-decode string.
     * @param   s   URL-encoded string
     * @return      Decoded string
     * @throws      std::invalid_argument On receiving invalid URL code on string.
                    Also throws if any of the function calls, the assignments throws.
     */
    std::string urldecode(const std::string &s);

    /**
    @brief Left-justifies text by adding spaces to the end of the string
    Truncates string if its size is greater than sz
    @param  s   string to left-justify
    @param  sz  size of the returned string
    @return     string padded with spaces at the end
    @throws     std::invalid_argument If size of final string is less than 3.
    */
    std::string ljust(std::string s, size_t sz);

    /**
    @brief Right-justifies text by adding spaces to the end of the string
    Truncates string if its size is greater than sz
    @param  s   string to right-justify
    @param  sz  size of the returned string
    @return     string padded with spaces at the beginning
    @throws     std::invalid_argument If size of final string is less than 3.
    */
    std::string rjust(std::string s, size_t sz);

    /**
     * @brief        Parse string into a vector of arguments, similar to how shell parsing works.
     * @param    s   Command to parse with arguments
     * @return       Vector with command elements
     * @throws  Throws if any of the function calls, the assignments throws.
     */
    std::vector<std::string> parse_command(const std::string &s);

    /**
     * @brief       Evaluate if two doubles are similar enough to be considered equal.
     *
     * If the absolute difference between n1 and n2 is smaller than e, the function
     * returns true; otherwise, it returns false.
     * @param   n1  First number
     * @param   n2  Second number
     * @param   e   Maximum difference below which two numbers are considered equal
     */
    bool feq(double n1, double n2, double e);

    /**
     * @brief       Filters std::vector using a function as argument.
     *
     * The function returns a vector of pointers corresponding to the elements of v
     * that evaluated as true in valid.
     * @param   v       vector of pointers
     * @param   valid   Boolean function to filter vector
     * @return          vector of elements of v that evaluated true
     * @throws  Throws if any of the function calls, the assignments throws.
     */
    template<class T, class Valid> std::vector<T*> filter(const std::vector<T*> &v, Valid valid);

    /** @brief Unsigned floats. Makes necessary checks. */
    template<class T>
    class ufloat{
    private:
        /// @brief Value of the unsigned floating point number (no precision specified).
        T u_;
    public:
        /**
         * @brief Empty constructor.
         */
        explicit ufloat():u_(0){}
        /**
         * @brief Constructor accepting value to be assigned to it.
         * @throws utils::ufloat<T>::InvalidUFloat If value is negative
         */
        explicit ufloat(const T &u);

        /** @brief Overload of operator==. */
        bool operator==(const ufloat<T> &s) const;
        /** @brief Overload of operator!=. */
        bool operator!=(const ufloat<T> &s) const;
        /** @brief Overload of operator<. */
        bool operator< (const ufloat<T> &s) const;
        /** @brief Overload of operator>. */
        bool operator> (const ufloat<T> &s) const;
        /** @brief Overload of operator<= .*/
        bool operator<=(const ufloat<T> &s) const;
        /** @brief Overload of operator<= .*/
        bool operator>=(const ufloat<T> &s) const;

        /** @brief Overload of operator+= */
        ufloat<T>& operator+=(const ufloat<T> &t);
        /**
         * @brief overload of operator-
         * @throws utils::ufloat<T>::InvalidUFloat If operation results in an negative number.
         */
        ufloat<T> operator-(const ufloat<T> &t) const;

        /**
         * @brief Conversion to underlying type.
         */
        explicit operator T() const;

        /**
         * @brief Overload of operator>>
         * @throws If extract operator throws.
         */
        friend std::istream& operator>> <>(std::istream &is,       utils::ufloat<T> &u);
        /**
         * @brief Overload of operator<<
         * @throws If insert operator throws
         */
        friend std::ostream& operator<< <>(std::ostream &os, const utils::ufloat<T> &u);

        /** @brief Exception class for reporting invalid UFloat (usually because it is negative) */
        class InvalidUFloat: public std::invalid_argument{
        private:
            /// @brief Value that caused exception.
            T u_;
        public:
            /**
             * @brief Constructor
             * @param   u   Number that caused exception
             */
            explicit InvalidUFloat(const T &u);

            /**
             * @brief Get number that caused exception.
             */
            const T& get_ufloat() const;
        };
    };
    /** @brief %Weight */
    typedef ufloat<double> Weight;
    /** @brief %Distance */
    typedef ufloat<double> Distance;
    /**
     * @brief String restricted by regex. Throws @ref FailedRegex when assigned with non-conformant string
     */
    class string_regex{
    private:
        /// @brief String stored.
        std::string s_;
        /// @brief Regular expression that string must follow.
        std::string REGEX_STR_;
    public:
        /**
         * @brief Constructor accepting regex the strings is supposed to match.
         * @param   REGEX_STR   Regex the strings are supposed to match.
         */
        explicit string_regex(const std::string &REGEX_STR):REGEX_STR_(REGEX_STR){}
        /**
         * @brief Overload of operator=
         * @throws utils::string_regex::FailedRegex If input string doesn't match regular expression
         */
        string_regex& operator=(const std::string &s);

        /** @brief Conversion of regex-checked string to std::string. */
        explicit operator std::string() const;

        /** @brief Overload of operator==. */
        bool operator==(const utils::string_regex &s) const;
        /** @brief Overload of operator!=. */
        bool operator!=(const utils::string_regex &s) const;
        /** @brief Overload of operator<. */
        bool operator< (const utils::string_regex &s) const;
        /** @brief Overload of operator>. */
        bool operator> (const utils::string_regex &s) const;
        /** @brief Overload of operator<= .*/
        bool operator<=(const utils::string_regex &s) const;
        /** @brief Overload of operator<= .*/
        bool operator>=(const utils::string_regex &s) const;

        /**
         * @brief Overload of operator>>.
         * @throws utils::string_regex::FailedRegex If input doesn't match with regex, std::invalid_argument if input has invalid URL-encoding.
         */
        friend std::istream& operator>>(std::istream &is,       utils::string_regex &s);
        /** @brief Overload of operator<<. */
        friend std::ostream& operator<<(std::ostream &os, const utils::string_regex &s);
        /** @brief Exception thrown when string does not match regex */
        class FailedRegex: public std::invalid_argument{
        private:
            /// @brief String that caused exception.
            const std::string s_;
            /// @brief Regular expression that string should've matched.
            const std::string REGEX_STR_;
        public:
            /**
             * @brief   Constructor accepting failing string and regex it was supposed to match.
             * @param   s           Failing string
             * @param   REGEX_STR   Regex string \a s was supposed to match
             */
            FailedRegex(const std::string &s, const std::string &REGEX_STR);
            /** @brief Get infringing string. */
            const std::string& get_string()const{ return s_; }
        };
    };

    /**
     * @brief       Sort vector in range according to a sorting parameter.
     *
     * Uses mergesort for complexity O(N log N).
     * @param   v       Vector to sort
     * @param   l       First element to be sorted in v
     * @param   r       Past-the-last element to be sorted in v
     * @param   comp    Comparison function, receiving arguments of the same type as the vector
     * @throws  Throws if any of the function calls throws.
     */
    template<class T, class Compare> void mergesort(std::vector<T> &v, const size_t &l, const size_t &r, Compare comp);
    /** @overload*/
    template<class T, class Compare> void mergesort(std::vector<T> &v, Compare comp){ utils::mergesort(v, 0, v.size(), comp); }
    /** @overload*/
    template<class T               > void mergesort(std::vector<T> &v){ utils::mergesort(v, std::less<T>()); }

    /**
     * @brief           Finds first element in [l,r) that evaluates true when provided to pred.
     * @param   l       First iterator
     * @param   r       Past-the-last iterator
     * @param   pred    Boolean function with the same argument type as the type the iterators point to
     * @return      Iterator to object that first met the condition specified. If not found returns r.
     * @throws  Throws if any of the function calls, the assignments or the operations on iterators throws.
     */
    template<class Iterator, class Pred> Iterator find_if(Iterator l, Iterator r, Pred pred);
    /**
     * @brief       Finds first element in [l,r) that evaluates equal to obj.
     * @param   l   First iterator
     * @param   r   Past-the-last iterator
     * @param   obj Object to find
     * @return      Iterator to object that first met the condition specified. If not found returns r.
     * @throws  Throws if any of the function calls, the assignments or the operations on iterators throws.
     */
    template<class Iterator, class T   > Iterator find   (Iterator l, Iterator r, T obj);

    /**
     * @brief Verify is string given is cancel command ("cancel").
     * @param s String to be verified
     * @return If the string equals the string "cancel"
     */
    inline bool isCancel(const std::string &s) { return s == "cancel"; }
    /**
     * @brief Allows input from user into an object T with descriptive message.
     * @param msg       Message to be displayed before input
     * @param object    Object where input will be stored
     * @param is        Input stream
     * @param os        Output stream
     * @return True if input is valid, false if operation is cancelled
     * @throws  Throws if any of the function calls, the assignments before input throws.
     */
    template<class T> bool input(const std::string &msg, T &object, std::istream &is, std::ostream &os);
    /**
     * @brief Allows input from user into a string with descriptive message.
     *        Specialization for objects of type string.
     * @param msg       Message to be displayed before input
     * @param object    String where input will be stored
     * @param is        Input stream
     * @param os        Output stream
     * @return True if input is valid, false if operation is cancelled
     * @throws  Throws if any of the function calls, the assignments before input throws.
     */
    template<> bool input<std::string>(const std::string &msg, std::string &object, std::istream &is, std::ostream &os);
    /**
     * @brief Allows input from user into an object T with descriptive message.
     * @param msg       Message to be displayed before input
     * @param f         Function that will be used to store the input in the object instaed of default insertion operator
     * @param object    Object where input will be stored
     * @param is        Input stream
     * @param os        Output stream
     * @return True if input is valid, false if operation is cancelled
     * @throws  Throws if any of the function calls, the assignments before input throws.
     */
    template<class T, class Func> bool input(const std::string &msg, Func f ,T &object, std::istream &is, std::ostream &os);
}

template<class T, class Valid> std::vector<T*> utils::filter(const std::vector<T*> &v, Valid valid){
    std::vector<T*> ret;
    for(T* p:v){
        if(valid(p)){
            ret.push_back(p);
        }
    }
    return ret;
}

template<class T> utils::ufloat<T>::ufloat(const T &u){
    if(u < 0.0)
        throw utils::ufloat<T>::InvalidUFloat(u);
    u_ = u;
}

template<class T> bool utils::ufloat<T>::operator==(const ufloat<T> &t) const{
    return (u_ == t.u_);
}
template<class T> bool utils::ufloat<T>::operator!=(const ufloat<T> &t) const{
    return (u_ != t.u_);
}
template<class T> bool utils::ufloat<T>::operator< (const ufloat<T> &t) const{
    return (u_ < t.u_);
}
template<class T> bool utils::ufloat<T>::operator> (const ufloat<T> &t) const{
    return (u_ > t.u_);
}
template<class T> bool utils::ufloat<T>::operator<=(const ufloat<T> &t) const{
    return (u_ <= t.u_);
}
template<class T> bool utils::ufloat<T>::operator>=(const ufloat<T> &t) const{
    return (u_ >= t.u_);
}

template<class T> utils::ufloat<T>& utils::ufloat<T>::operator+=(const ufloat<T> &t){
    u_ += t.u_;
    return *this;
}
template<class T> utils::ufloat<T> utils::ufloat<T>::operator-(const ufloat<T> &t) const{
    return ufloat<T>(u_ - t.u_);
}
template<class T> utils::ufloat<T>::operator T() const{
    return u_;
}
template<class T> std::istream& operator>>(std::istream &is,       utils::ufloat<T> &u){ return (is >> u.u_); }
template<class T> std::ostream& operator<<(std::ostream &os, const utils::ufloat<T> &u){ return (os << u.u_); }
template<class T> utils::ufloat<T>::InvalidUFloat::InvalidUFloat(const T &u):
    std::invalid_argument("Invalid weight"),
    u_(u){}
template<class T> const T& utils::ufloat<T>::InvalidUFloat::get_ufloat()const{ return u_; }

template<class T, class Compare> void utils::mergesort(std::vector<T> &v, const size_t &l, const size_t &r, Compare comp){
    if(r-l <= 1) return;
    size_t m = l + (r-l)/2;
    utils::mergesort(v,l,m,comp); utils::mergesort(v,m,r,comp);
    size_t i = l, j = m;
    std::vector<T> w(r-l);
    size_t k = 0;
    while(i != m && j != r){
        if(!comp(v[j],v[i])) w[k++] = v[i++];
        else                 w[k++] = v[j++];
    }
    while(i != m) w[k++] = v[i++];
    while(j != r) w[k++] = v[j++];
    std::copy(w.begin(), w.end(), v.begin()+(long)l);
}

template<class Iterator, class Pred> Iterator utils::find_if(Iterator l, Iterator r, Pred pred){
    Iterator i = l;
    while(i != r){
        if(pred(*i)) break;
        ++i;
    }
    return i;
}
template<class Iterator, class T   > Iterator utils::find   (Iterator l, Iterator r, T obj){
    return utils::find_if(l, r, [obj](const T &t){ return (t == obj); });
}

template<class T> bool utils::input(const std::string &msg, T &object, std::istream &is, std::ostream &os) {
    std::string input;
    std::stringstream ss; ss.exceptions(std::stringstream::failbit | std::stringstream::badbit);

    while (true) {
        os << msg; std::getline(is, input); utils::trim(input);
        if (utils::isCancel(input)) {
            os << "Operation cancelled.\n"; return false;
        }
        ss.clear(); ss.str(input);
        try {
            ss >> object;
            return true;
        } catch (const std::ios_base::failure &ios_fail) {
            std::cerr << "ERROR: Input failed.\n";
        } catch (const std::exception &ex) {
            std::cerr << "ERROR: " << ex.what() << "\n";
        }
    }
}

template<class T, class Func> bool utils::input(const std::string &msg, Func f ,T &object, std::istream &is, std::ostream &os) {
    std::string input;

    while (true) {
        os << msg; std::getline(is, input); utils::trim(input);
        if (utils::isCancel(input)) {
            os << "Operation cancelled.\n"; return false;
        }
        try {
            f(object, input);
            return true;
        } catch (const std::ios_base::failure &ios_fail) {
            std::cerr << "ERROR: Input failed.\n";
        } catch (const std::exception &ex) {
            std::cerr << "ERROR: " << ex.what() << "\n";
        }
    }
}

#endif //UTILS_H_INCLUDED
