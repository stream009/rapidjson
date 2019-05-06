#include <json/value.hpp>

#include <json/array.hpp>
#include <json/object.hpp>
#include <json/pointer.hpp>

#include "internal/allocator.hpp"
#include "internal/convert.hpp"
#include "internal/underlying_value.hpp"

#include <stdexcept>

#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/pointer.h>
#include <rapidjson/writer.h>

//#define DEBUG_VERBOSE

#ifdef DEBUG_VERBOSE
    #include <iostream>
    #define LOG(x) std::cout << x << std::endl
#else
    #define LOG(x) (void)0
#endif

namespace json {

namespace rj = rapidjson;

null_t null;

// value

value::
value(int32_t const v)
    : base { v }
{
    LOG("value(number_t)");
}

value::
value(uint32_t const v)
    : base { v }
{
    LOG("value(number_t)");
}

value::
value(int64_t const v)
    : base { v }
{
    LOG("value(number_t)");
}

value::
value(uint64_t const v)
    : base { v }
{
    LOG("value(number_t)");
}

value::
value(long long const v)
    : base { v }
{
    LOG("value(number_t)");
}

value::
value(unsigned long long const v)
    : base { v }
{
    LOG("value(number_t)");
}

value::
value(double const v)
    : base { v }
{
    LOG("value(number_t)");
}

value::
value(char const* v)
    : base { std::string_view(v) }
{
    LOG("value(char const*)");
}

value::
value(std::string const& v)
    : base { v }
{
    LOG("value(std::string const&)");
}

value::
value(std::string_view const v)
    : base { v }
{
    LOG("value(std::string_view)");
}

value::
value(array const& a)
    : base { a }
{
    LOG("value(array const&)");
}

value::
value(object const& o)
    : base { o }
{
    LOG("value(object const&)");
}

value::
value(null_t)
    : value {}
{
    LOG("value(null_t)");
}

template<>
value::
value<bool, void>(bool const v)
    : base { v }
{
    LOG("value(bool)");
}

value::type value::
get_type() const
{
    switch (this->base_value().GetType()) {
        default:
        case rj::kNullType:
            return type::null;
        case rj::kFalseType:
        case rj::kTrueType:
            return type::boolean;
        case rj::kObjectType:
            return type::object;
        case rj::kArrayType:
            return type::array;
        case rj::kStringType:
            return type::string;
        case rj::kNumberType:
            return type::number;
    }
}

bool value::
is_bool() const
{
    return this->base_value().IsBool();
}

bool value::
is_int32() const
{
    return this->base_value().IsInt();
}

bool value::
is_uint32() const
{
    return this->base_value().IsUint();
}

bool value::
is_int64() const
{
    return this->base_value().IsInt64();
}

bool value::
is_uint64() const
{
    return this->base_value().IsUint64();
}

bool value::
is_number() const
{
    return this->base_value().IsNumber();
}

bool value::
is_string() const
{
    return this->base_value().IsString();
}

bool value::
is_array() const
{
    return this->base_value().IsArray();
}

bool value::
is_object() const
{
    return this->base_value().IsObject();
}

bool value::
is_null() const
{
    return this->base_value().IsNull();
}

bool value::
get_bool() const
{
    assert(is_bool());
    return this->base_value().GetBool();
}

int32_t value::
get_int32() const
{
    assert(is_int32());
    return this->base_value().GetInt();
}

uint32_t value::
get_uint32() const
{
    assert(is_uint32());
    return this->base_value().GetUint();
}

int64_t value::
get_int64() const
{
    assert(is_int64());
    return this->base_value().GetInt64();
}

uint64_t value::
get_uint64() const
{
    assert(is_uint64());
    return this->base_value().GetUint64();
}

value::number_t value::
get_number() const
{
    assert(is_number());
    return this->base_value().GetDouble();
}

value::string_t value::
get_string() const
{
    assert(is_string());
    auto& base = this->base_value();

    return { base.GetString(), base.GetStringLength() };
}

array& value::
get_array()
{
    assert(is_array());
    return reinterpret_cast<array&>(*this);
}

array const& value::
get_array() const
{
    assert(is_array());
    return reinterpret_cast<array const&>(*this);
}

object& value::
get_object()
{
    assert(is_object());
    return reinterpret_cast<object&>(*this);
}

object const& value::
get_object() const
{
    assert(is_object());
    return reinterpret_cast<object const&>(*this);
}

void value::
set_bool(bool const v)
{
    this->base_value().SetBool(v);
}

void value::
set_int32(int32_t const i)
{
    this->base_value().SetInt(i);
}

void value::
set_int64(int64_t const i)
{
    this->base_value().SetInt64(i);
}

void value::
set_uint32(uint32_t const i)
{
    this->base_value().SetUint(i);
}

void value::
set_uint64(uint64_t const i)
{
    this->base_value().SetUint64(i);
}

void value::
set_number(number_t const v)
{
    this->base_value().SetDouble(v);
}

void value::
set_string(string_t const v)
{
    this->base_value().SetString(
        v.data(),
        to_rj_size(v.size()),
        allocator()
    );
}

void value::
set_array(array const& a)
{
    value v { a };
    *this = v;
}

void value::
set_object(object const& o)
{
    value v { o };
    *this = v;
}

void value::
set_null()
{
    this->base_value().SetNull();
}

value const* value::
find(pointer const& p) const
{
    auto const& base = reinterpret_cast<rj::Pointer const&>(p);

    return reinterpret_cast<value const*>(
        base.Get(reinterpret_cast<rj::Value const&>(*this))
    );
}

value* value::
find(pointer const& p)
{
    return const_cast<value*>(
        const_cast<value const*>(this)->find(p)
    );
}

value const& value::
at(pointer const& p) const
{
    auto* const v = find(p);
    if (v == nullptr) {
        throw std::out_of_range("json::value::at");
    }

    return *v;
}

value& value::
at(pointer const& p)
{
    return const_cast<value&>(
        const_cast<value const*>(this)->at(p)
    );
}

value& value::
operator[](pointer const& p)
{
    auto const& base = reinterpret_cast<rj::Pointer const&>(p);

    return reinterpret_cast<value&>(
        base.Create(reinterpret_cast<rj::Value&>(*this), allocator())
    );
}

void value::
erase(pointer const& p)
{
    auto const& base = reinterpret_cast<rj::Pointer const&>(p);
    base.Erase(reinterpret_cast<rj::Value&>(*this));
}

bool value::
contains(pointer const& p) const
{
    return find(p) != nullptr;
}

bool value::
operator==(value const& rhs) const
{
    return this->base_value() == rhs.base_value();
}

bool value::
operator==(number_t const rhs) const
{
    LOG("operator==(number_t)");
    return this->base_value() == rhs;
}

bool value::
operator==(char const* const rhs) const
{
    LOG("operator==(char const*)");
    return this->base_value() == rhs;
}

bool value::
operator==(std::string const& rhs) const
{
    LOG("operator==(std::string const&)");

    value_type const v { rhs.data(), to_rj_size(rhs.size()) };
    return this->base_value() == v;
}

bool value::
operator==(std::string_view const rhs) const
{
    LOG("operator==(std::string_view)");

    value_type const v { rhs.data(), to_rj_size(rhs.size()) };
    return this->base_value() == v;
}

bool value::
operator==(array const& rhs) const
{
    LOG("operator==(array const&)");
    return this->base_value() == reinterpret_cast<value_type const&>(rhs);
}

bool value::
operator==(object const& rhs) const
{
    LOG("operator==(object const&)");
    return this->base_value() == reinterpret_cast<value_type const&>(rhs);
}

bool value::
operator==(null_t) const
{
    LOG("operator==(null_t)");
    return this->is_null();
}

template<>
bool value::
operator==<bool, void>(bool const rhs) const
{
    LOG("operator==(bool)");
    return this->base_value() == rhs;
}

std::ostream&
operator<<(std::ostream& os, value const& v)
{
    rj::OStreamWrapper osw { os };

    rj::Writer<rj::OStreamWrapper> writer { osw };

    v.base_value().Accept(writer);

    return os;
}

std::ostream&
operator<<(std::ostream& os, value::type const t)
{
    using type = value::type;

    switch (t) {
        case type::null:
            os << "null";
            break;
        case type::boolean:
            os << "bool";
            break;
        case type::number:
            os << "number";
            break;
        case type::string:
            os << "string";
            break;
        case type::array:
            os << "array";
            break;
        case type::object:
            os << "object";
            break;
        default:
            assert(false);
    }

    return os;
}

std::ostream&
operator<<(std::ostream& os, null_t)
{
    os << "null";
    return os;
}

} // namespace json
