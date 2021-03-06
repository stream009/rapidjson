#include <stream9/json/value.hpp>

#include <stream9/json/array.hpp>
#include <stream9/json/error.hpp>
#include <stream9/json/object.hpp>
#include <stream9/json/pointer.hpp>

#include "internal/allocator.hpp"
#include "internal/convert.hpp"
#include "internal/underlying_value.hpp"

#include <cmath>
#include <istream>
#include <ostream>
#include <stdexcept>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/pointer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

//#define DEBUG_VERBOSE

#ifdef DEBUG_VERBOSE
    #include <iostream>
    #define LOG(x) std::cout << x << std::endl
#else
    #define LOG(x) (void)0
#endif

namespace stream9::json {

namespace rj = rapidjson;

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
value(array&& a)
    : base { std::move(a) }
{
    LOG("value(array&&)");
}

value::
value(object const& o)
    : base { o }
{
    LOG("value(object const&)");
}

value::
value(object&& o)
    : base { std::move(o) }
{
    LOG("value(object&&)");
}

value::
value(null_t)
    : value {}
{
    LOG("value(null_t)");
}

value::
value(undefined_t)
    : value {}
{
    LOG("value(undefined_t)");
    base::set_undefined(true);
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
    if (this->is_undefined()) {
        return type::undefined;
    }

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
    return !this->is_undefined() && this->base_value().IsBool();
}

bool value::
is_int32() const
{
    return !this->is_undefined() && this->base_value().IsInt();
}

bool value::
is_uint32() const
{
    return !this->is_undefined() && this->base_value().IsUint();
}

bool value::
is_int64() const
{
    return !this->is_undefined() && this->base_value().IsInt64();
}

bool value::
is_uint64() const
{
    return !this->is_undefined() && this->base_value().IsUint64();
}

bool value::
is_number() const
{
    return !this->is_undefined() && this->base_value().IsNumber();
}

bool value::
is_string() const
{
    return !this->is_undefined() && this->base_value().IsString();
}

bool value::
is_array() const
{
    return !this->is_undefined() && this->base_value().IsArray();
}

bool value::
is_object() const
{
    return !this->is_undefined() && this->base_value().IsObject();
}

bool value::
is_null() const
{
    return !this->is_undefined() && this->base_value().IsNull();
}

bool value::
is_undefined() const
{
    return base::is_undefined();
}

std::optional<bool> value::
get_bool() const
{
    if (this->is_undefined() || !is_bool()) {
        return std::nullopt;
    }

    return this->base_value().GetBool();
}

std::optional<int32_t> value::
get_int32() const
{
    if (this->is_undefined() || !is_int32()) {
        return std::nullopt;
    }

    return this->base_value().GetInt();
}

std::optional<uint32_t> value::
get_uint32() const
{
    if (this->is_undefined() || !is_uint32()) {
        return std::nullopt;
    }

    return this->base_value().GetUint();
}

std::optional<int64_t> value::
get_int64() const
{
    if (this->is_undefined() || !is_int64()) {
        return std::nullopt;
    }

    return this->base_value().GetInt64();
}

std::optional<uint64_t> value::
get_uint64() const
{
    if (this->is_undefined() || !is_uint64()) {
        return std::nullopt;
    }

    return this->base_value().GetUint64();
}

std::optional<value::number_t> value::
get_number() const
{
    if (this->is_undefined() || !is_number()) {
        return std::nullopt;
    }

    return this->base_value().GetDouble();
}

std::optional<value::string_t> value::
get_string() const
{
    if (this->is_undefined() || !is_string()) {
        return std::nullopt;
    }

    auto& base = this->base_value();

    return string_t { base.GetString(), base.GetStringLength() };
}

array* value::
get_array()
{
    if (this->is_undefined() || !is_array()) {
        return nullptr;
    }

    return reinterpret_cast<array*>(this);
}

array const* value::
get_array() const
{
    if (this->is_undefined() || !is_array()) {
        return nullptr;
    }

    return reinterpret_cast<array const*>(this);
}

object* value::
get_object()
{
    if (this->is_undefined() || !is_object()) {
        return nullptr;
    }

    return reinterpret_cast<object*>(this);
}

object const* value::
get_object() const
{
    if (this->is_undefined() || !is_object()) {
        return nullptr;
    }

    return reinterpret_cast<object const*>(this);
}

void value::
set_bool(bool const v)
{
    this->base_value().SetBool(v);
    base::set_undefined(false);
}

void value::
set_int32(int32_t const i)
{
    this->base_value().SetInt(i);
    base::set_undefined(false);
}

void value::
set_int64(int64_t const i)
{
    this->base_value().SetInt64(i);
    base::set_undefined(false);
}

void value::
set_uint32(uint32_t const i)
{
    this->base_value().SetUint(i);
    base::set_undefined(false);
}

void value::
set_uint64(uint64_t const i)
{
    this->base_value().SetUint64(i);
    base::set_undefined(false);
}

void value::
set_number(number_t const v)
{
    this->base_value().SetDouble(v);
    base::set_undefined(false);
}

void value::
set_string(string_t const v)
{
    this->base_value().SetString(
        v.data(),
        to_rj_size(v.size()),
        allocator()
    );
    base::set_undefined(false);
}

void value::
set_array(array const& a)
{
    value v { a };
    *this = v;
    base::set_undefined(false);
}

void value::
set_object(object const& o)
{
    value v { o };
    *this = v;
    base::set_undefined(false);
}

void value::
set_null()
{
    this->base_value().SetNull();
    base::set_undefined(false);
}

value const& value::
find(pointer const& p) const
{
    auto const& base = reinterpret_cast<base_pointer_t const&>(p);

    auto* const v = reinterpret_cast<value const*>(
        base.Get(reinterpret_cast<base::value_type const&>(*this))
    );

    if (v) {
        return *v;
    }
    else {
        return undefined();
    }
}

value& value::
emplace(pointer const& p)
{
    auto const& base = reinterpret_cast<base_pointer_t const&>(p);

    return reinterpret_cast<value&>(
        base.Create(reinterpret_cast<base::value_type&>(*this), allocator())
    );
}

void value::
erase(pointer const& p)
{
    auto const& base = reinterpret_cast<base_pointer_t const&>(p);
    base.Erase(reinterpret_cast<base::value_type&>(*this));
}

bool value::
contains(pointer const& p) const
{
    return !find(p).is_undefined();
}

template<>
value::
operator bool() const
{
    if (is_undefined()) return false;
    if (is_bool()) {
        return *get_bool();
    }
    if (is_number()) {
        auto const n = *get_number();
        return n != 0 && !std::isnan(n);
    }
    if (is_string()) {
        return !get_string()->empty();
    }
    if (is_array() || is_object()) {
        return true;
    }
    return false;
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

bool value::
operator==(undefined_t) const
{
    LOG("operator==(undefined_t)");
    return this->is_undefined();
}

template<>
bool value::
operator==<bool, void>(bool const rhs) const
{
    LOG("operator==(bool)");
    return this->base_value() == rhs;
}

value const& value::
undefined()
{
    static value const v { json::undefined };
    return v;
}

value
parse(std::string_view const str)
{
    base_document_t doc { &allocator() };
    doc.Parse(str.data(), str.size());

    if (doc.HasParseError()) {
        throw parse_error(
            make_parse_error_code(doc.GetParseError()),
            doc.GetErrorOffset());
    }

    value result;
    new (&result.base_value()) base_value_t { doc, allocator() };

    return result;
}

value
parse(std::istream& is)
{
    base_document_t doc { &allocator() };
    rj::IStreamWrapper wrapper { is };

    doc.ParseStream(wrapper);

    if (doc.HasParseError()) {
        throw parse_error(
            make_parse_error_code(doc.GetParseError()),
            doc.GetErrorOffset());
    }

    value result;
    new (&result.base_value()) base_value_t { doc, allocator() };

    return result;
}

std::string
stringify(value const& v)
{
    rj::StringBuffer sb;
    rj::Writer writer { sb };

    reinterpret_cast<base_value_t const&>(v).Accept(writer);

    return sb.GetString();
}

std::string
stringify(value const& v, size_t const space)
{
    rj::StringBuffer sb;
    rj::PrettyWriter writer { sb };

    writer.SetIndent(' ', static_cast<unsigned>(space));

    reinterpret_cast<base_value_t const&>(v).Accept(writer);

    return sb.GetString();
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

std::ostream&
operator<<(std::ostream& os, undefined_t)
{
    os << "undefined";
    return os;
}

} // namespace stream9::json
