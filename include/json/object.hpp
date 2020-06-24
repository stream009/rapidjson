#ifndef JSON_OBJECT_HPP
#define JSON_OBJECT_HPP

#include <iosfwd>
#include <string>

#include <json/base.hpp>
#include <json/value.hpp>

namespace json {

class object : public base
{
public:
    using size_type = std::size_t;
    using key_type = std::string_view;
    using value_type = value;
    class iterator;
    class const_iterator;

    struct member {
        value_type name;
        value_type value;
    };

public:
    object();

    object(object const&) = default;
    object(object&&) = default;

    object& operator=(object const&) = default;
    object& operator=(object&&) = default;

    ~object() = default;

    // query
    size_type size() const;
    size_type capacity() const;
    bool empty() const;
    bool contains(key_type) const;

    // accessor
    value& at(key_type);
    value const& at(key_type) const;

    value& operator[](key_type);
    value const& operator[](key_type const key) const { return at(key); }

    value& as_value();
    value const& as_value() const;

    // iterator
    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    // lookup
    iterator find(key_type);
    const_iterator find(key_type) const;

    // modifier
    void clear();
    void reserve(size_type);

    void erase(const_iterator);
    void erase(const_iterator first, const_iterator last);
    bool erase(key_type);

    // operator
    bool operator==(object const&) const;
    bool operator!=(object const& other) const { return !(*this == other); }
};

class object::iterator
{
public:
    using value_type = object::member;
    using reference = value_type&;
    using pointer = value_type*;
    using difference_type = std::ptrdiff_t;

public:
    iterator();

    iterator(iterator const&);

    iterator& operator=(iterator const&);

    ~iterator();

    // accessor
    reference operator*() const;
    pointer operator->() const;
    reference operator[](difference_type) const;

    // modifier
    iterator& operator++();
    iterator& operator--();

    iterator operator++(int);
    iterator operator--(int);

    iterator& operator+=(difference_type);
    iterator& operator-=(difference_type);

    // operator
    iterator operator+(difference_type) const;
    iterator operator-(difference_type) const;

    difference_type operator-(const_iterator) const;

    // comparator
    bool operator==(const_iterator) const;
    bool operator!=(const_iterator) const;
    bool operator<=(const_iterator) const;
    bool operator>=(const_iterator) const;
    bool operator<(const_iterator) const;
    bool operator>(const_iterator) const;

private:
    std::aligned_storage_t<8, 8> m_it;
};

class object::const_iterator
{
public:
    using value_type = object::member const;
    using reference = value_type const&;
    using pointer = value_type const*;
    using difference_type = std::ptrdiff_t;

public:
    const_iterator();

    const_iterator(const_iterator const&);
    const_iterator(iterator const&);

    const_iterator& operator=(const_iterator const&);
    const_iterator& operator=(iterator const&);

    ~const_iterator();

    // accessor
    reference operator*() const;
    pointer operator->() const;
    reference operator[](difference_type) const;

    // modifier
    const_iterator& operator++();
    const_iterator& operator--();

    const_iterator operator++(int);
    const_iterator operator--(int);

    const_iterator& operator+=(difference_type);
    const_iterator& operator-=(difference_type);

    const_iterator operator+(difference_type) const;
    const_iterator operator-(difference_type) const;

    difference_type operator-(const_iterator) const;

    // comparator
    bool operator==(const_iterator) const;
    bool operator!=(const_iterator) const;
    bool operator<=(const_iterator) const;
    bool operator>=(const_iterator) const;
    bool operator<(const_iterator) const;
    bool operator>(const_iterator) const;

private:
    std::aligned_storage_t<8, 8> m_it;
};

std::string stringify(object const&);

std::ostream& operator<<(std::ostream&, object const&);

} // namespace json

#endif // JSON_OBJECT_HPP
