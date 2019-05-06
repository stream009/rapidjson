#ifndef JSON_JSON_HPP
#define JSON_JSON_HPP

#include <iosfwd>
#include <string>
#include <string_view>

#include <json/value.hpp>
#include <json/object.hpp>
#include <json/array.hpp>
#include <json/pointer.hpp>
#include <json/error.hpp>

namespace json {

value parse(std::string_view);
value parse(std::istream&);

std::string stringify(value const&);

} // namespace json

#endif // JSON_JSON_HPP
