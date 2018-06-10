#ifndef JSON_ERROR_PARSE_ERROR_HPP
#define JSON_ERROR_PARSE_ERROR_HPP

#include <iosfwd>
#include <string>
#include <system_error>

namespace json {

enum class parse_errc {
    none,
    document_empty,
    document_root_not_singular,
    value_invalid,
    object_miss_name,
    object_miss_colon,
    object_miss_comma_or_curly_bracket,
    array_miss_comma_or_square_bracket,
    string_unicode_escape_invalid_hex,
    string_unicode_surrogate_invalid,
    string_escape_invalid,
    string_miss_quotation_mark,
    string_invalid_encoding,
    number_too_big,
    number_miss_fraction,
    number_miss_exponent,
    termination,
    unspecific_syntax_error,
};

class parse_error : public std::system_error
{
public:
    parse_error(std::error_code, size_t offset);

    size_t offset() const noexcept { return m_offset; }

private:
    size_t m_offset;
};

class parse_error_category_impl : public std::error_category
{
public:
    char const* name() const noexcept override;
    std::string message(int ev) const override;
    bool equivalent(
            std::error_code const&, int condition) const noexcept override;
};

std::error_category const& parse_error_category();
std::error_condition make_error_condition(parse_errc ev);

std::error_code make_parse_error_code(int ev);

std::ostream& operator<<(std::ostream&, parse_errc);

} // namespace json

namespace std {

template<>
struct is_error_condition_enum<json::parse_errc> : public true_type {};

} // namespace std

#endif // JSON_ERROR_PARSE_ERROR_HPP
