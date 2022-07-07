/**
 * @file person.h
 */

#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include "address.h"
#include "vat.h"
#include "phonenumber.h"
#include "currency.h"

/**
 * @brief %Person class.
 */
class Person {
private:
    /// @brief Name of the person.
    std::string name_;
    /// @brief Phone number of the person.
    PhoneNumber phonenumber_;
protected:
    /**
     * @brief Allows Person fields to be filled from info in input stream.
     * @param   is  Input stream
     * @return      Same as \p is.
     */
    virtual std::istream& input(std::istream &is);
public:
    /// @brief Empty constructor.
    Person();
    /// @brief Destructor.
    virtual ~Person();

    /// @brief Get name of person.
    virtual const std::string& get_name() const final;
    /// @brief Get phonenumber.
    virtual const PhoneNumber& get_phonenumber() const final;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);
    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);

    /// @brief Overload of \a operator>> .
    friend std::istream& operator>>(std::istream &is,       Person &p);
    /// @brief Overload of \a operator<< .
    friend std::ostream& operator<<(std::ostream &os, const Person &p);
};

/**
 * @brief %User class.
 *
 * A user must have his/her own credentials to login to the system.
 */
class User : public Person{
public:
    /** @brief %Username class. */
    class Username: public utils::string_regex{
    public:
        /// @brief Regex a username is supposed to match.
        static const std::string REGEX_STR;
        /// @brief Empty constructor.
        explicit Username();
        /// @brief Constructor accepting \a std::string as argument for construction.
        explicit Username(const std::string &username);
        /// @brief Overload of \a operator= .
        Username& operator=(const std::string &s);
    };
    /** @brief %Password class. */
    class Password: public utils::string_regex{
    public:
        /// @brief Regex a password is supposed to match.
        static const std::string REGEX_STR;
        /// @brief Empty constructor.
        explicit Password();
        /// @brief Constructor accepting string as argument for construction.
        explicit Password(const std::string &password);
        /// @brief Overload of \a operator= .
        Password& operator=(const std::string &s);
    };

    /** @brief Type of users there are. */
    enum Type {
        client,
        driver,
        manager
    };
private:
    /// @brief Username used in login and as identifier of user.
    Username username_;
    /// @brief Password used in login and validation of crucial information.
    Password password_;
    /// @brief Address of user.
    Address address_;
    /// @brief VAT of user.
    VAT vat_;
protected:
    /**
     * @brief Allows User fields to be filled from info in input stream.
     * @param   is  Input stream
     */
    virtual std::istream& input(std::istream &is);
public:
    /// @brief Empty constructor.
    User();

    /// @brief Get username.
    const Username& get_username() const;
    /// @brief Get id (which in this case is the username).
    const Username& get_id      () const;
    /// @brief Get address.
    const Address&  get_address () const;
    /// @brief Get VAT number.
    const VAT&      get_vat     () const;
    /**
     * @brief Gets the type of user.
     * @return User type
     */
    virtual User::Type get_type(void) const = 0;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);
    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);

    /**
     * @brief Tests if credentials given match with user.
     * @param password Password to verify
     * @return If the credentials are valid
     */
    bool verifyCredentials(const std::string &password) const;

    /**
     * @brief Changes password of user.
     * @param password New password
     * @throws utils::string_regex::FailedRegex If password is invalid
     */
    void change_password(const std::string &password);

    /// @brief Overload of \a operator>> .
    friend std::istream& operator>>(std::istream &is,       User &p);
    /// @brief Overload of \a operator<< .
    friend std::ostream& operator<<(std::ostream &os, const User &p);
};

/**
 * @brief %Client class.
 *
 * A client is a user with privileges to request new services.
 * In order to issue bills, a client must have an Address and a VAT number.
 */
class Client: public User {
protected:
    /**
     * @brief Allows Client fields to be filled from info in input stream.
     * @param   is  Input stream
     */
    virtual std::istream& input(std::istream &is);
public:
    /// @brief Empty constructor.
    Client();

    /**
     * @brief Gets the type of user.
     * @return UserType::client type
     */
    virtual User::Type get_type(void) const;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);
    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);

    /// @brief Overload of \a operator>> .
    friend std::istream& operator>>(std::istream &is,       Client &p);
    /// @brief Overload of \a operator<< .
    friend std::ostream& operator<<(std::ostream &os, const Client &p);
};

/**
 * @brief %Employee class.
 *
 * An employee is a User that is paid by the company.
 */
class Employee: public User {
private:
    /// @brief Base salary of employee.
    Currency base_salary_;
protected:
    virtual std::istream& input(std::istream &is);
public:
    /// @brief Empty constructor
    Employee();

    /// @brief Get base salary of employee.
    const Currency& get_base_salary() const;

    /**
     * @brief Gets the type of user.
     * @return User type
     */
    virtual User::Type get_type(void) const = 0;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);
    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);


    /// @brief Overload of \a operator>> .
    friend std::istream& operator>>(std::istream &is,       Employee &p);
    /// @brief Overload of \a operator<< .
    friend std::ostream& operator<<(std::ostream &os, const Employee &p);
};

/**
 * @brief %Manager class.
 *
 * A manager has permissions to make any modification to data in the program.
 */
class Manager: public Employee {
protected:
    virtual std::istream& input(std::istream &is);
public:
    /// @brief Empty constructor.
    Manager();

    /**
     * @brief Gets the type of user.
     * @return UserType::manager type
     */
    virtual User::Type get_type(void) const;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);

    /// @brief Overload of \a operator>> .
    friend std::istream& operator>>(std::istream &is,       Manager &p);
    /// @brief Overload of \a operator<< .
    friend std::ostream& operator<<(std::ostream &os, const Manager &p);
};

/**
 * @brief %Driver class.
 *
 * A driver makes deliveries.
 */
class Driver: public Employee {
protected:
    virtual std::istream& input(std::istream &is);
public:
    /// @brief Empty constructor.
    Driver();

    /**
     * @brief Gets the type of user.
     * @return UserType::driver type
     */
    virtual User::Type get_type(void) const;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);
    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);

    /// @brief Overload of \a operator>> .
    friend std::istream& operator>>(std::istream &is,       Driver &p);
    /// @brief Overload of \a operator<< .
    friend std::ostream& operator<<(std::ostream &os, const Driver &p);
};

#endif //PERSON_H_INCLUDED
