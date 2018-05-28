#ifndef JSON_JSON_HPP
#define JSON_JSON_HPP

#include <string_view>

namespace json {

class value;

value parse(std::string_view);

} // namespace json

#endif // JSON_JSON_HPP
