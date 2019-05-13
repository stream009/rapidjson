#include <json/array.hpp>

#include <json/value.hpp>

#include "internal/convert.hpp"
#include "internal/underlying_value.hpp"

namespace json {

namespace rj = rapidjson;

array::
array()
{
    this->base_value().SetArray();
}

array::size_type array::
size() const
{
    return this->base_value().Size();
}

array::size_type array::
capacity() const
{
    return this->base_value().Capacity();
}

bool array::
empty() const
{
    return this->base_value().Empty();
}

value& array::
at(size_type const index)
{
    assert(index < size());

    auto& v = this->base_value().operator[](to_rj_size(index));
    return reinterpret_cast<value&>(v);
}

value const& array::
at(size_type const index) const
{
    assert(index < size());

    auto& v = this->base_value().operator[](to_rj_size(index));
    return reinterpret_cast<value const&>(v);
}

value& array::
operator[](size_type const index)
{
    auto& v = this->base_value().operator[](to_rj_size(index));
    return reinterpret_cast<value&>(v);
}

value const& array::
operator[](size_type const index) const
{
    auto& v = this->base_value().operator[](to_rj_size(index));
    return reinterpret_cast<value const&>(v);
}

value& array::
front()
{
    return operator[](0);
}

value const& array::
front() const
{
    return operator[](0);
}

value& array::
back()
{
    return operator[](size() - 1);
}

value const& array::
back() const
{
    return operator[](size() - 1);
}

array::iterator array::
begin()
{
    return reinterpret_cast<iterator>(this->base_value().Begin());
}

array::iterator array::
end()
{
    return reinterpret_cast<iterator>(this->base_value().End());
}

array::const_iterator array::
begin() const
{
    return reinterpret_cast<const_iterator>(this->base_value().Begin());
}

array::const_iterator array::
end() const
{
    return reinterpret_cast<const_iterator>(this->base_value().End());
}

void array::
clear()
{
    this->base_value().Clear();
}

void array::
reserve(size_type const s)
{
    this->base_value().Reserve(to_rj_size(s), allocator());
}

void array::
push_back(value const& v)
{
    auto copy = v;
    this->base_value().PushBack(
                reinterpret_cast<base::value_type&>(copy), allocator());
}

void array::
push_back(value&& v)
{
    this->base_value().PushBack(
                reinterpret_cast<base::value_type&>(v).Move(), allocator());
}

void array::
erase(const_iterator const it)
{
    this->base_value().Erase(
                reinterpret_cast<base::value_type::ConstValueIterator>(it));
}

void array::
erase(const_iterator const first, const_iterator const last)
{
    this->base_value().Erase(
                reinterpret_cast<base::value_type::ConstValueIterator>(first),
                reinterpret_cast<base::value_type::ConstValueIterator>(last));
}

std::ostream&
operator<<(std::ostream& os, array const& a)
{
    os << static_cast<value const&>(a);

    return os;
}

} // namespace json
