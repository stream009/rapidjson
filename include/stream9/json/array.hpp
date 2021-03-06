#ifndef STREAM9_JSON_ARRAY_HPP
#define STREAM9_JSON_ARRAY_HPP

#include <stream9/json/base.hpp>
#include <stream9/json/value.hpp>

#include <iosfwd>
#include <string>

namespace stream9::json {

class value;

class array : public base
{
public:
    using size_type = std::size_t;
    using iterator = value*;
    using const_iterator = value const*;

public:
    array();

    array(array const&) = default;
    array(array&&) = default;

    array& operator=(array const&) = default;
    array& operator=(array&&) = default;

    ~array() = default;

    // query
    size_type size() const;
    size_type capacity() const;
    bool empty() const;

    // accessor
    value& at(size_type index);
    value const& at(size_type index) const;
    value& operator[](size_type index);
    value const& operator[](size_type index) const;

    value& front();
    value const& front() const;
    value& back();
    value const& back() const;

    value& as_value();
    value const& as_value() const;

    // iterator
    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    // modifier
    void clear();
    void reserve(size_type);

    void push_back(value const&);
    void push_back(value&&);

    void erase(const_iterator);
    void erase(const_iterator first, const_iterator last);

    // operator
    bool operator==(array const&) const;
    bool operator!=(array const& other) const { return !(*this == other); }
};

std::string stringify(array const&);

std::ostream& operator<<(std::ostream&, array const&);

} // namespace stream9::json

#endif // STREAM9_JSON_ARRAY_HPP
