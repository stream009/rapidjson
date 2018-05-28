#ifndef JSON_ARRAY_HPP
#define JSON_ARRAY_HPP

#include "base.hpp"

namespace json {

class value;

class array : public base
{
public:
    using size_type = std::size_t;
    using iterator = char*;
    using const_iterator = char const*;

public:
    array();
    ~array();

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
};

} // namespace json

#endif // JSON_ARRAY_HPP
