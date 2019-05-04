#ifndef JSON_VALUE_HPP
#define JSON_VALUE_HPP

#include <json/base.hpp>

#include <iosfwd>
#include <string>
#include <string_view>

namespace json {

class array;
class base;
class object;
class pointer;

struct null_t {};

extern null_t null;

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
    ~value() = default;

    value(value const&) = default;
    value(value&&) = default;
    value& operator=(value const&) = default;
    value& operator=(value&&) = default;

    template<typename Bool,
         typename = std::enable_if_t<std::is_same_v<Bool, bool>> >
    value(Bool);

    value(int32_t);
    value(uint32_t);
    value(int64_t);
    value(uint64_t);
    value(long long);
    value(unsigned long long);
    value(double);
    value(long double);

    value(char const*);
    value(std::string const&);
    value(std::string_view);

    value(array const&);
    value(object const&);
    value(null_t);

    template<typename Bool,
         typename = std::enable_if_t<std::is_same_v<Bool, bool>> >
    value& operator=(Bool);

    value& operator=(int32_t);
    value& operator=(uint32_t);
    value& operator=(int64_t);
    value& operator=(uint64_t);
    value& operator=(long long);
    value& operator=(unsigned long long);
    value& operator=(double);
    value& operator=(long double);

    value& operator=(char const*);
    value& operator=(std::string const&);
    value& operator=(std::string_view);

    value& operator=(array const&);
    value& operator=(object const&);
    value& operator=(null_t);

    // query
    type get_type() const;
    bool is_bool() const;
    bool is_int32() const;
    bool is_uint32() const;
    bool is_int64() const;
    bool is_uint64() const;
    bool is_number() const;
    bool is_string() const;
    bool is_array() const;
    bool is_object() const;
    bool is_null() const;

    // accessor
    bool          get_bool() const;
    int32_t       get_int32() const;
    uint32_t      get_uint32() const;
    int64_t       get_int64() const;
    uint64_t      get_uint64() const;
    number_t      get_number() const;
    string_t      get_string() const;
    array&        get_array();
    array const&  get_array() const;
    object&       get_object();
    object const& get_object() const;

    // modifier
    void set_bool(bool);
    void set_int32(int32_t);
    void set_int64(int64_t);
    void set_uint32(uint32_t);
    void set_uint64(uint64_t);
    void set_number(number_t);
    void set_string(string_t);
    void set_array(array const&);
    void set_object(object const&);
    void set_null();

    // pointer
    value const* find(pointer const&) const;
    value*       find(pointer const&);
    value const& at(pointer const&) const;
    value&       at(pointer const&);
    value&       operator[](pointer const&);
    void         erase(pointer const&);
    bool         contains(pointer const&) const;

    // operator
    template<typename T,
             typename = std::enable_if_t<std::is_same_v<T, bool>> >
    operator T() const
    {
        return get_bool();
    }

    bool operator==(value const&) const;

    bool operator==(number_t) const;
    bool operator==(char const*) const;
    bool operator==(std::string const&) const;
    bool operator==(std::string_view) const;
    bool operator==(array const&) const;
    bool operator==(object const&) const;
    bool operator==(null_t) const;

    template<typename T,
             typename = std::enable_if_t<std::is_same_v<T, bool>> >
    bool operator==(T) const;

    bool operator!=(value const&) const;

    bool operator!=(number_t) const;
    bool operator!=(char const*) const;
    bool operator!=(std::string const&) const;
    bool operator!=(std::string_view) const;
    bool operator!=(array const&) const;
    bool operator!=(object const&) const;
    bool operator!=(null_t) const;

    template<typename T,
             typename = std::enable_if_t<std::is_same_v<T, bool>> >
    bool operator!=(T) const;

    friend std::ostream& operator<<(std::ostream&, value const&);
    friend value parse(std::string_view);
};

inline value& value::
operator=(int32_t const i)
{
    set_int32(i);
    return *this;
}

inline value& value::
operator=(uint32_t const i)
{
    set_uint32(i);
    return *this;
}

inline value& value::
operator=(int64_t const i)
{
    set_int64(i);
    return *this;
}

inline value& value::
operator=(uint64_t const i)
{
    set_uint64(i);
    return *this;
}

inline value& value::
operator=(long long const i)
{
    set_int64(i);
    return *this;
}

inline value& value::
operator=(unsigned long long const i)
{
    set_uint64(i);
    return *this;
}

inline value& value::
operator=(double const d)
{
    set_number(d);
    return *this;
}

inline value& value::
operator=(long double const d)
{
    set_number(d);
    return *this;
}

inline value& value::
operator=(char const* const v)
{
    set_string(v);
    return *this;
}

inline value& value::
operator=(std::string const& v)
{
    set_string(v);
    return *this;
}

inline value& value::
operator=(std::string_view const v)
{
    set_string(v);
    return *this;
}

inline value& value::
operator=(array const& v)
{
    set_array(v);
    return *this;
}

inline value& value::
operator=(object const& v)
{
    set_object(v);
    return *this;
}

inline value& value::
operator=(null_t)
{
    set_null();
    return *this;
}

template<>
inline value& value::
operator=<bool, void>(bool const v)
{
    set_bool(v);
    return *this;
}

inline bool value::
operator!=(value const& rhs) const
{
    return !(*this == rhs);
}

inline bool value::
operator!=(value::number_t const rhs) const
{
    return !(*this == rhs);
}

inline bool value::
operator!=(char const* const rhs) const
{
    return !(*this == rhs);
}

inline bool value::
operator!=(std::string const& rhs) const
{
    return !(*this == rhs);
}

inline bool value::
operator!=(std::string_view const rhs) const
{
    return !(*this == rhs);
}

inline bool value::
operator!=(array const& rhs) const
{
    return !(*this == rhs);
}

inline bool value::
operator!=(object const& rhs) const
{
    return !(*this == rhs);
}

inline bool value::
operator!=(null_t const rhs) const
{
    return !(*this == rhs);
}

inline bool
operator==(value::number_t const lhs, value const& rhs)
{
    return rhs == lhs;
}

inline bool
operator==(char const* const lhs, value const& rhs)
{
    return rhs == lhs;
}

inline bool
operator==(std::string const& lhs, value const& rhs)
{
    return rhs == lhs;
}

inline bool
operator==(std::string_view const lhs, value const& rhs)
{
    return rhs == lhs;
}

inline bool
operator==(array const& lhs, value const& rhs)
{
    return rhs == lhs;
}

inline bool
operator==(object const& lhs, value const& rhs)
{
    return rhs == lhs;
}

inline bool
operator==(null_t const lhs, value const& rhs)
{
    return rhs == lhs;
}

inline bool
operator!=(value::number_t const lhs, value const& rhs)
{
    return rhs != lhs;
}

inline bool
operator!=(char const* const lhs, value const& rhs)
{
    return rhs != lhs;
}

inline bool
operator!=(std::string const& lhs, value const& rhs)
{
    return rhs != lhs;
}

inline bool
operator!=(std::string_view const lhs, value const& rhs)
{
    return rhs != lhs;
}

inline bool
operator!=(array const& lhs, value const& rhs)
{
    return rhs != lhs;
}

inline bool
operator!=(object const& lhs, value const& rhs)
{
    return rhs != lhs;
}

inline bool
operator!=(null_t const lhs, value const& rhs)
{
    return rhs != lhs;
}

std::ostream& operator<<(std::ostream&, value::type);
std::ostream& operator<<(std::ostream&, null_t);

} // namespace json

#endif // JSON_VALUE_HPP
