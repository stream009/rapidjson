#ifndef JSON_JSON_HPP
#define JSON_JSON_HPP

#include <string_view>
#include <string>

#include <json/value.hpp>
#include <json/object.hpp>
#include <json/array.hpp>
#include <json/pointer.hpp>
#include <json/error.hpp>

namespace json {

value parse(std::string_view);

std::string stringify(value const&);

} // namespace json

#endif // JSON_JSON_HPP
