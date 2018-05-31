#include "json.hpp"

#include "internal/allocator.hpp"
#include "internal/underlying_value.hpp"

#include <sstream>
#include <stdexcept>

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
        throw std::runtime_error("JSON: parse error");
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

value*
find(value& v, std::string_view const pointer)
{
    rj::Pointer const p { pointer.data(), pointer.size() };

    return reinterpret_cast<value*>(p.Get(reinterpret_cast<rj::Value&>(v)));
}

value const*
find(value const& v, std::string_view const pointer)
{
    rj::Pointer const p { pointer.data(), pointer.size() };

    return reinterpret_cast<value const*>(
                            p.Get(reinterpret_cast<rj::Value const&>(v)));
}

} // namespace json
