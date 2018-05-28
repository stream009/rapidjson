#include "value.hpp"

#include "internal/allocator.hpp"
#include "internal/underlying_value.hpp"

#include <rapidjson/ostreamwrapper.h>
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

// value

#if 0
value::
value(bool const v)
    : base { std::make_unique<value_type>(v) }
{
    LOG("value(bool)");
}
#endif

template<>
value::
value<bool, void>(bool const v)
    : base { std::make_unique<value_type>(v) }
{
    LOG("value(bool)");
}

value::
value(number_t const v)
    : base { std::make_unique<value_type>(v) }
{
    LOG("value(number_t)");
}

value::
value(char const* v)
    : base { std::make_unique<value_type>(v, allocator()) }
{
    LOG("value(char const*)");
}

value::
value(std::string const& v)
    : base { std::make_unique<value_type>(v.data(), v.size(), allocator()) }
{
    LOG("value(std::string const&)");
}

value::
value(std::string_view const v)
    : base { std::make_unique<value_type>(v.data(), v.size(), allocator()) }
{
    LOG("value(std::string_view)");
}

value::
value(null_t)
    : value {}
{
    LOG("value(null_t)");
}

value::
value(std::unique_ptr<value_type> v)
    : base { std::move(v) }
{}
/*
value& value::
operator=(bool const v)
{
    LOG("operator=(bool)");
    this->base_value().SetBool(v);
    return *this;
}
*/

template<>
value& value::
operator=<bool, void>(bool const v)
{
    LOG("operator=(bool)");
    set_bool(v);
    return *this;
}

value& value::
operator=(number_t const v)
{
    LOG("operator=(number_t)");
    set_number(v);
    return *this;
}

value& value::
operator=(char const* const v)
{
    LOG("operator=(char const*)");
    set_string(v);
    return *this;
}

value& value::
operator=(std::string const& v)
{
    LOG("operator=(std::string const&)");
    set_string(v);
    return *this;
}

value& value::
operator=(std::string_view const v)
{
    LOG("operator=(std::string_view)");
    set_string(v);
    return *this;
}

value& value::
operator=(null_t)
{
    LOG("operator=(null_t)");
    set_null();
    return *this;
}

value::type value::
get_type() const
{
    switch (this->base_value().GetType()) {
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
        default:
            assert(false);
    }
}

bool value::
is_bool() const
{
    return this->base_value().IsBool();
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
is_null() const
{
    return this->base_value().IsNull();
}

bool value::
get_bool() const
{
    return this->base_value().GetBool();
}

value::number_t value::
get_number() const
{
    return this->base_value().GetDouble();
}

value::string_t value::
get_string() const
{
    auto& base = this->base_value();

    return { base.GetString(), base.GetStringLength() };
}

#if 0
array& value::
get_array()
{
    auto& base = this->base_value();
    base.SetArray();
    return reinterpret_cast<array&>(*this);
}
#endif

void value::
set_bool(bool const v)
{
    this->base_value().SetBool(v);
}

void value::
set_number(number_t const v)
{
    this->base_value().SetDouble(v);
}

void value::
set_string(string_t const v)
{
    this->base_value().SetString(v.data(), v.size(), allocator());
}

void value::
set_null()
{
    this->base_value().SetNull();
}

bool value::
operator==(value const& rhs) const
{
    return this->base_value() == rhs.base_value();
}

#if 0
bool value::
operator==(bool const rhs) const
{
    LOG("operator==(bool)");
    return this->base_value() == rhs;
}
#endif

template<>
bool value::
operator==<bool, void>(bool const rhs) const
{
    LOG("operator==(bool)");
    return this->base_value() == rhs;
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
    return this->base_value() == value_type(rhs.data(), rhs.size());
}

bool value::
operator==(std::string_view const rhs) const
{
    LOG("operator==(std::string_view)");
    return this->base_value() == value_type(rhs.data(), rhs.size());
}

bool value::
operator==(null_t) const
{
    LOG("operator==(null_t)");
    return this->is_null();
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
