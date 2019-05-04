#include <json/json.hpp>

#include <json/error.hpp>

#include "internal/allocator.hpp"
#include "internal/underlying_value.hpp"

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/pointer.h>

namespace json {

namespace rj = rapidjson;

value
parse(std::string_view const str)
{
    rj::Document doc { &allocator() };
    doc.Parse(str.data(), str.size());

    if (doc.HasParseError()) {
        throw parse_error(
            make_parse_error_code(doc.GetParseError()),
            doc.GetErrorOffset());
    }

    value result;
    new (&result.base_value()) rj::Value { doc, allocator() };

    return result;
}

std::string
stringify(value const& v)
{
    rj::StringBuffer sb;
    rj::Writer writer { sb };

    reinterpret_cast<rj::Value const&>(v).Accept(writer);

    return sb.GetString();
}

} // namespace json
