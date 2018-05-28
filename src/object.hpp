#ifndef JSON_OBJECT_HPP
#define JSON_OBJECT_HPP

#include "base.hpp"

namespace json {

class object : public base
{
public:
    using size_type = std::size_t;
    using key_type = std::string_view;

public:
    object();
    ~object();

    // query
    size_type size();
    size_type capacity();
    bool empty();
    bool contain(key_type);

    // accessor
    value& at(key_type key);
    value const& at(key_type key) const;
    value& operator[](key_type key);
    value const& operator[](key_type key) const;

    // iterator
    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    // lookup
    iterator find(key_type);
    const_iterator find(key_type) const;

    // modifiers
    void clear();
    void reserve(size_type);

    void emplace(key_type, value const&);
    void emplace(key_type, value&&);

    void erase(const_iterator);
    void erase(const_iterator first, const_iterator last);
    bool erase(key_type);
};

} // namespace json

#endif // JSON_OBJECT_HPP
