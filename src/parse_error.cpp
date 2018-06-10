#include <json/error/parse_error.hpp>

#include <cassert>
#include <ostream>

#include <rapidjson/error/en.h>
#include <rapidjson/error/error.h>

namespace json {

static rapidjson::ParseErrorCode
to_rapid(int ev)
{
    using e = parse_errc;
    using namespace rapidjson;

    switch (static_cast<e>(ev)) {
        case e::none:
            return kParseErrorNone;
        case e::document_empty:
            return kParseErrorDocumentEmpty;
        case e::document_root_not_singular:
            return kParseErrorDocumentRootNotSingular;
        case e::value_invalid:
            return kParseErrorValueInvalid;
        case e::object_miss_name:
            return kParseErrorObjectMissName;
        case e::object_miss_colon:
            return kParseErrorObjectMissColon;
        case e::object_miss_comma_or_curly_bracket:
            return kParseErrorObjectMissCommaOrCurlyBracket;
        case e::array_miss_comma_or_square_bracket:
            return kParseErrorArrayMissCommaOrSquareBracket;
        case e::string_unicode_escape_invalid_hex:
            return kParseErrorStringUnicodeEscapeInvalidHex;
        case e::string_unicode_surrogate_invalid:
            return kParseErrorStringUnicodeSurrogateInvalid;
        case e::string_escape_invalid:
            return kParseErrorStringEscapeInvalid;
        case e::string_miss_quotation_mark:
            return kParseErrorStringMissQuotationMark;
        case e::string_invalid_encoding:
            return kParseErrorStringInvalidEncoding;
        case e::number_too_big:
            return kParseErrorNumberTooBig;
        case e::number_miss_fraction:
            return kParseErrorNumberMissFraction;
        case e::number_miss_exponent:
            return kParseErrorNumberMissExponent;
        case e::termination:
            return kParseErrorTermination;
        case e::unspecific_syntax_error:
            return kParseErrorUnspecificSyntaxError;
        default:
            assert(false && "unknown error value");
    }
}

// parse_error
parse_error::
parse_error(std::error_code const code, size_t const offset)
    : std::system_error(code)
    , m_offset { offset }
{}

// parse_error_category_impl

char const* parse_error_category_impl::
name() const noexcept
{
    return "json::parse";
}

std::string parse_error_category_impl::
message(int const ev) const
{
    return rapidjson::GetParseError_En(to_rapid(ev));
}

bool parse_error_category_impl::
equivalent(std::error_code const& ec, int const condition) const noexcept
{
    return ec.value() == to_rapid(condition);
}

// free function

std::error_category const&
parse_error_category()
{
    static parse_error_category_impl instance;
    return instance;
}

std::error_condition
make_error_condition(parse_errc const ev)
{
    return std::error_condition(static_cast<int>(ev), parse_error_category());
}

std::error_code
make_parse_error_code(int const ev)
{
    return std::error_code(ev, parse_error_category());
}

std::ostream&
operator<<(std::ostream& os, parse_errc const ev)
{
    using e = parse_errc;

    switch (ev) {
        case e::none:
            os << "none";
            break;
        case e::document_empty:
            os << "document_empty";
            break;
        case e::document_root_not_singular:
            os << "document_root_not_singular";
            break;
        case e::value_invalid:
            os << "value_invalid";
            break;
        case e::object_miss_name:
            os << "object_miss_name";
            break;
        case e::object_miss_colon:
            os << "object_miss_colon";
            break;
        case e::object_miss_comma_or_curly_bracket:
            os << "object_miss_comma_or_curly_bracket";
            break;
        case e::array_miss_comma_or_square_bracket:
            os << "array_miss_comma_or_square_bracket";
            break;
        case e::string_unicode_escape_invalid_hex:
            os << "string_unicode_escape_invalid_hex";
            break;
        case e::string_unicode_surrogate_invalid:
            os << "string_unicode_surrogate_invalid";
            break;
        case e::string_escape_invalid:
            os << "string_escape_invalid";
            break;
        case e::string_miss_quotation_mark:
            os << "string_miss_quotation_mark";
            break;
        case e::string_invalid_encoding:
            os << "string_invalid_encoding";
            break;
        case e::number_too_big:
            os << "number_too_big";
            break;
        case e::number_miss_fraction:
            os << "number_miss_fraction";
            break;
        case e::number_miss_exponent:
            os << "number_miss_exponent";
            break;
        case e::termination:
            os << "termination";
            break;
        case e::unspecific_syntax_error:
            os << "unspecific_syntax_error";
            break;
        default:
            assert(false && "unknown error value");
    }

    return os;
};

} // namespace
