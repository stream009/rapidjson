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
    auto doc = std::make_unique<rj::Document>(&allocator());
    doc->Parse(str.data(), str.size());

    if (doc->HasParseError()) {
        throw "parse error"; //TODO
    }

    return std::unique_ptr<value::value_type> {
        static_cast<value::value_type*>(
            static_cast<rj::Value*>(doc.release()))
    };
}

} // namespace json
