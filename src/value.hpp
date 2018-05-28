#ifndef JSON_VALUE_HPP
#define JSON_VALUE_HPP

#include <iosfwd>
#include <memory>

#include "base.hpp"
#include "json.hpp"

namespace json {

class array;
class base;
class object;

struct null_t {};

static null_t null;

// value

class value : public base
{
public:
    using number_t = double;
    using string_t = std::string_view;

    enum class type {
        null,
        boolean,
        number,
        string,
        array,
        object
    };

public:
    value() = default;

    template<typename T,
             typename = std::enable_if_t<std::is_same_v<T, bool>> >
    value(T);

    //value(bool);
    value(number_t);
    value(char const*);
    value(std::string const&);
    value(std::string_view);
    //TODO array, object
    value(null_t);

    value(std::unique_ptr<value_type>);

    value(value const&) = default;
    value(value&&) = default;
    value& operator=(value const&) = default;
    value& operator=(value&&) = default;

    template<typename T,
             typename = std::enable_if_t<std::is_same_v<T, bool>> >
    value& operator=(T);

    //value& operator=(bool);
    value& operator=(number_t);
    value& operator=(char const*);
    value& operator=(std::string const&);
    value& operator=(std::string_view);
    value& operator=(array); //TODO
    value& operator=(object); //TODO
    value& operator=(null_t);

    ~value() = default;

    // query
    type get_type() const;
    bool is_bool() const;
    bool is_number() const;
    bool is_string() const;
    bool is_array() const;
    bool is_object() const;
    bool is_null() const;

    // accessor
    bool     get_bool() const;
    number_t get_number() const;
    string_t get_string() const;
    array const&   get_array() const; //TODO
    array&   get_array(); //TODO
    object&  get_object(); //TODO

    // modifier
    void set_bool(bool);
    void set_number(number_t);
    void set_string(string_t);
    void set_array(array);
    void set_object(object);
    void set_null();

    // operator
    template<typename T,
             typename = std::enable_if_t<std::is_same_v<T, bool>> >
    operator T() const
    {
        return get_bool();
    }

    bool operator==(value const&) const;

    template<typename T,
             typename = std::enable_if_t<std::is_same_v<T, bool>> >
    bool operator==(T) const;

#if 0
    bool operator==(bool) const;
#endif
    bool operator==(number_t) const;
    bool operator==(char const*) const;
    bool operator==(std::string const&) const;
    bool operator==(std::string_view) const;
    bool operator==(null_t) const;

    friend std::ostream& operator<<(std::ostream&, value const&);
};

std::ostream& operator<<(std::ostream&, value::type);
std::ostream& operator<<(std::ostream&, null_t);

} // namespace json

#endif // JSON_VALUE_HPP
