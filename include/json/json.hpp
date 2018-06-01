#ifndef JSON_JSON_HPP
#define JSON_JSON_HPP

#include <string_view>
#include <string>

#include <json/value.hpp>

namespace json {

value parse(std::string_view);

std::string stringify(value const&);

value* find(value&, std::string_view pointer);
value const* find(value const&, std::string_view pointer);

} // namespace json

#endif // JSON_JSON_HPP
