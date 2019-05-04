#ifndef JSON_JSON_HPP
#define JSON_JSON_HPP

#include <string_view>
#include <string>

#include <json/value.hpp>

namespace json {

value parse(std::string_view);

std::string stringify(value const&);

} // namespace json

#endif // JSON_JSON_HPP
