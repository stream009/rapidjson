#ifndef JSON_ERROR_POINTER_ERROR_HPP
#define JSON_ERROR_POINTER_ERROR_HPP

#include <iosfwd>
#include <system_error>

namespace json {

enum class pointer_errc {
    none,
    token_must_begin_with_solidus,
    invalid_escape,
    invalid_percent_encoding,
    character_must_percent_encode,
};

class pointer_error : public std::system_error
{
public:
    pointer_error(std::error_code, size_t offset);

    size_t offset() const noexcept { return m_offset; }

private:
    size_t m_offset;
};

class pointer_error_category_impl : public std::error_category
{
public:
    char const* name() const noexcept override;
    std::string message(int ev) const override;
    bool equivalent(
            std::error_code const&, int condition) const noexcept override;
};

std::error_category const& pointer_error_category();
std::error_condition make_error_condition(pointer_errc ev);

std::error_code make_pointer_error_code(int ev);

std::ostream& operator<<(std::ostream&, pointer_errc);

} // namespace json

namespace std {

template<>
struct is_error_condition_enum<json::pointer_errc> : public true_type {};

} // namespace std

#endif // JSON_ERROR_POINTER_ERROR_HPP
