#include <json/object.hpp>

#include <json/value.hpp>

#include "internal/convert.hpp"
#include "internal/underlying_value.hpp"

namespace json {

namespace rj = rapidjson;

// types

using member_base = base::value_type::Member;
using iterator_base = base::value_type::MemberIterator;
using const_iterator_base = base::value_type::ConstMemberIterator;

// utility

static auto&
to_base(object::iterator& it)
{
    return reinterpret_cast<iterator_base&>(it);
}

static auto&
to_base(object::iterator const& it)
{
    return reinterpret_cast<iterator_base const&>(it);
}

static auto&
to_base(object::const_iterator& it)
{
    return reinterpret_cast<const_iterator_base&>(it);
}

static auto&
to_base(object::const_iterator const& it)
{
    return reinterpret_cast<const_iterator_base const&>(it);
}

static auto&
to_iterator(iterator_base& base)
{
    return reinterpret_cast<object::iterator&>(base);
}

static auto&
to_iterator(iterator_base const& base)
{
    return reinterpret_cast<object::iterator const&>(base);
}

static auto&
to_const_iterator(const_iterator_base& base)
{
    return reinterpret_cast<object::const_iterator&>(base);
}

static auto&
to_const_iterator(const_iterator_base const& base)
{
    return reinterpret_cast<object::const_iterator const&>(base);
}

static auto&
to_member(member_base& base)
{
    return reinterpret_cast<object::member&>(base);
}

static auto&
to_member(member_base const& base)
{
    return reinterpret_cast<object::member const&>(base);
}

// object

object::
object()
{
    this->base_value().SetObject();
}

object::size_type object::
size() const
{
    return this->base_value().MemberCount();
}

object::size_type object::
capacity() const
{
    return this->base_value().MemberCapacity();
}

bool object::
empty() const
{
    return this->base_value().ObjectEmpty();
}

bool object::
contains(key_type const key) const
{
    base::value_type const k { key.data(), to_rj_size(key.size()) };

    return this->base_value().HasMember(k);
}

value& object::
at(key_type const key)
{
    assert(contains(key));
    return operator[](key);
}

value const& object::
at(key_type const key) const
{
    if (!contains(key)) {
        throw std::out_of_range("json::object::at");
    }

    base::value_type const k { key.data(), to_rj_size(key.size()) };
    auto const& v = this->base_value().operator[](k);

    return reinterpret_cast<value const&>(v);
}

value& object::
operator[](key_type const key)
{
    if (!contains(key)) {
        auto& a = allocator();
        base::value_type k { key.data(), to_rj_size(key.size()) };
        base::value_type v;

        this->base_value().AddMember(k, v, a);
    }

    base::value_type const k { key.data(), to_rj_size(key.size()) };
    auto& v = this->base_value().operator[](k);

    return reinterpret_cast<value&>(v);
}

object::iterator object::
begin()
{
    return to_iterator(this->base_value().MemberBegin());
}

object::iterator object::
end()
{
    return to_iterator(this->base_value().MemberEnd());
}

object::const_iterator object::
begin() const
{
    return to_const_iterator(this->base_value().MemberBegin());
}

object::const_iterator object::
end() const
{
    return to_const_iterator(this->base_value().MemberEnd());
}

object::iterator object::
find(key_type const key)
{
    base::value_type const k { key.data(), to_rj_size(key.size()) };

    return to_iterator(this->base_value().FindMember(k));
}

object::const_iterator object::
find(key_type const key) const
{
    base::value_type const k { key.data(), to_rj_size(key.size()) };

    return to_const_iterator(this->base_value().FindMember(k));
}

void object::
clear()
{
    this->base_value().RemoveAllMembers();
}

void object::
reserve(size_type const s)
{
    this->base_value().MemberReserve(to_rj_size(s), allocator());
}

void object::
erase(const_iterator const it)
{
    this->base_value().EraseMember(to_base(it));
}

void object::
erase(const_iterator const first, const_iterator const last)
{
    this->base_value().EraseMember(to_base(first), to_base(last));
}

bool object::
erase(key_type const key)
{
    base::value_type const k { key.data(), to_rj_size(key.size()) };

    return this->base_value().EraseMember(k);
}

// object::iterator

object::iterator::
iterator()
{
    static_assert(sizeof(iterator_base) == sizeof(m_it));

    new (&m_it) iterator_base;
}

object::iterator::
iterator(iterator const& other)
{
    new (&m_it) iterator_base { to_base(other) };
}

object::iterator& object::iterator::
operator=(iterator const& rhs)
{
    to_base(*this) = to_base(rhs);

    return *this;
}

object::iterator::
~iterator()
{
    to_base(*this).~iterator_base();
}

object::iterator::reference object::iterator::
operator*() const
{
    return to_member(to_base(*this).operator*());
}

object::iterator::pointer object::iterator::
operator->() const
{
    return &to_member(*to_base(*this).operator->());
}

object::iterator::reference object::iterator::
operator[](difference_type const n) const
{
    return to_member(to_base(*this).operator[](n));
}

object::iterator& object::iterator::
operator++()
{
    return to_iterator(to_base(*this).operator++());
}

object::iterator& object::iterator::
operator--()
{
    return to_iterator(to_base(*this).operator--());
}

object::iterator object::iterator::
operator++(int)
{
    return to_iterator(to_base(*this).operator++(1));
}

object::iterator object::iterator::
operator--(int)
{
    return to_iterator(to_base(*this).operator--(1));
}

object::iterator& object::iterator::
operator+=(difference_type const n)
{
    return to_iterator(to_base(*this).operator+=(n));
}

object::iterator& object::iterator::
operator-=(difference_type const n)
{
    return to_iterator(to_base(*this).operator-=(n));
}

object::iterator object::iterator::
operator+(difference_type const n) const
{
    return to_iterator(to_base(*this).operator+(n));
}

object::iterator object::iterator::
operator-(difference_type const n) const
{
    return to_iterator(to_base(*this).operator-(n));
}

object::iterator::difference_type object::iterator::
operator-(const_iterator const rhs) const
{
    return to_base(*this).operator-(to_base(rhs));
}

bool object::iterator::
operator==(const_iterator const it) const
{
    return to_base(*this).operator==(to_base(it));
}

bool object::iterator::
operator!=(const_iterator const it) const
{
    return to_base(*this).operator!=(to_base(it));
}

bool object::iterator::
operator<=(const_iterator const it) const
{
    return to_base(*this).operator<=(to_base(it));
}

bool object::iterator::
operator>=(const_iterator const it) const
{
    return to_base(*this).operator>=(to_base(it));
}

bool object::iterator::
operator<(const_iterator const it) const
{
    return to_base(*this).operator<(to_base(it));
}

bool object::iterator::
operator>(const_iterator const it) const
{
    return to_base(*this).operator>(to_base(it));
}

// object::const_iterator

object::const_iterator::
const_iterator()
{
    static_assert(sizeof(const_iterator_base) == sizeof(m_it));

    new (&m_it) const_iterator_base;
}

object::const_iterator::
const_iterator(const_iterator const& other)
{
    new (&m_it) const_iterator_base { to_base(other) };
}

object::const_iterator::
const_iterator(iterator const& other)
{
    new (&m_it) const_iterator_base { to_base(other) };
}

object::const_iterator& object::const_iterator::
operator=(const_iterator const& rhs)
{
    to_base(*this) = to_base(rhs);

    return *this;
}

object::const_iterator& object::const_iterator::
operator=(iterator const& rhs)
{
    to_base(*this) = to_base(rhs);

    return *this;
}

object::const_iterator::
~const_iterator()
{
    to_base(*this).~const_iterator_base();
}

object::const_iterator::reference object::const_iterator::
operator*() const
{
    return to_member(to_base(*this).operator*());
}

object::const_iterator::pointer object::const_iterator::
operator->() const
{
    return &to_member(*to_base(*this).operator->());
}

object::const_iterator::reference object::const_iterator::
operator[](difference_type const n) const
{
    return to_member(to_base(*this).operator[](n));
}

object::const_iterator& object::const_iterator::
operator++()
{
    return to_const_iterator(to_base(*this).operator++());
}

object::const_iterator& object::const_iterator::
operator--()
{
    return to_const_iterator(to_base(*this).operator--());
}

object::const_iterator object::const_iterator::
operator++(int)
{
    return to_const_iterator(to_base(*this).operator++(1));
}

object::const_iterator object::const_iterator::
operator--(int)
{
    return to_const_iterator(to_base(*this).operator--(1));
}

object::const_iterator& object::const_iterator::
operator+=(difference_type const n)
{
    return to_const_iterator(to_base(*this).operator+=(n));
}

object::const_iterator& object::const_iterator::
operator-=(difference_type const n)
{
    return to_const_iterator(to_base(*this).operator-=(n));
}

object::const_iterator object::const_iterator::
operator+(difference_type const n) const
{
    return to_const_iterator(to_base(*this).operator+(n));
}

object::const_iterator object::const_iterator::
operator-(difference_type const n) const
{
    return to_const_iterator(to_base(*this).operator-(n));
}

object::const_iterator::difference_type object::const_iterator::
operator-(const_iterator const rhs) const
{
    return to_base(*this).operator-(to_base(rhs));
}

bool object::const_iterator::
operator==(const_iterator const it) const
{
    return to_base(*this).operator==(to_base(it));
}

bool object::const_iterator::
operator!=(const_iterator const it) const
{
    return to_base(*this).operator!=(to_base(it));
}

bool object::const_iterator::
operator<=(const_iterator const it) const
{
    return to_base(*this).operator<=(to_base(it));
}

bool object::const_iterator::
operator>=(const_iterator const it) const
{
    return to_base(*this).operator>=(to_base(it));
}

bool object::const_iterator::
operator<(const_iterator const it) const
{
    return to_base(*this).operator<(to_base(it));
}

bool object::const_iterator::
operator>(const_iterator const it) const
{
    return to_base(*this).operator>(to_base(it));
}

std::ostream&
operator<<(std::ostream& os, object const& o)
{
    os << static_cast<value const&>(o);

    return os;
}

} // namespace json
