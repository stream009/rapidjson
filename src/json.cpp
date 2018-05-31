#include "json.hpp"

#include "internal/allocator.hpp"
#include "internal/underlying_value.hpp"
#include "value.hpp"

#include <memory>

#include <rapidjson/document.h>

namespace json {

namespace rj = rapidjson;

value
parse(std::string_view const str)
{
    rj::Document doc { &allocator() };
    doc.Parse(str.data(), str.size());

    if (doc.HasParseError()) {
        throw "parse error"; //TODO
    }

    value result;
    new (&result.base_value()) rj::Value { doc, allocator() };

    return result;
}

} // namespace json
