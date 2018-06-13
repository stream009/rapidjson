#include <json/error/pointer_error.hpp>

#include <cassert>
#include <ostream>

#include <rapidjson/pointer.h>

namespace json {

static rapidjson::PointerParseErrorCode
to_rapid(int ev)
{
    using e = pointer_errc;
    using namespace rapidjson;

    switch (static_cast<e>(ev)) {
        case e::none:
            return kPointerParseErrorNone;
        case e::token_must_begin_with_solidus:
            return kPointerParseErrorTokenMustBeginWithSolidus;
        case e::invalid_escape:
            return kPointerParseErrorInvalidEscape;
        case e::invalid_percent_encoding:
            return kPointerParseErrorInvalidPercentEncoding;
        case e::character_must_percent_encode:
            return kPointerParseErrorCharacterMustPercentEncode;
        default:
            assert(false && "unknown error value");
    }
}

// pointer_error
pointer_error::
pointer_error(std::error_code const code, size_t const offset)
    : std::system_error(code)
    , m_offset { offset }
{}

// pointer_error_category_impl

char const* pointer_error_category_impl::
name() const noexcept
{
    return "json::pointer";
}

std::string pointer_error_category_impl::
message(int const ev) const
{
    using namespace rapidjson;

    switch (to_rapid(ev)) {
        case kPointerParseErrorNone:
            return "The parse is successful.";
        case kPointerParseErrorTokenMustBeginWithSolidus:
            return "A token must begin with a '/'.";
        case kPointerParseErrorInvalidEscape:
            return "Invalid escape.";
        case kPointerParseErrorInvalidPercentEncoding:
            return "Invalid percent encoding in URI fragment.";
        case kPointerParseErrorCharacterMustPercentEncode:
            return "A character must percent encoded in URI fragment.";
        default:
            assert(false && "unknown error value");
    }
}

bool pointer_error_category_impl::
equivalent(std::error_code const& ec, int const condition) const noexcept
{
    return ec.value() == to_rapid(condition);
}

// free function

std::error_category const&
pointer_error_category()
{
    static pointer_error_category_impl instance;
    return instance;
}

std::error_condition
make_error_condition(pointer_errc const ev)
{
    return std::error_condition(static_cast<int>(ev), pointer_error_category());
}

std::error_code
make_pointer_error_code(int const ev)
{
    return std::error_code(ev, pointer_error_category());
}

std::ostream&
operator<<(std::ostream& os, pointer_errc const ev)
{
    using e = pointer_errc;

    switch (ev) {
        case e::none:
            os << "none";
            break;
        case e::token_must_begin_with_solidus:
            os << "token_must_begin_with_solidus";
            break;
        case e::invalid_escape:
            os << "invalid_escape";
            break;
        case e::invalid_percent_encoding:
            os << "invalid_percent_encoding";
            break;
        case e::character_must_percent_encode:
            os << "character_must_percent_encode";
            break;
        default:
            assert(false && "unknown error value");
    }

    return os;
}

} // namespace
