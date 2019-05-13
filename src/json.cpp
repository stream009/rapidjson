#include <json/json.hpp>

#include <json/error.hpp>

#include "internal/allocator.hpp"
#include "internal/underlying_value.hpp"

#include <istream>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/pointer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace json {

namespace rj = rapidjson;

value
parse(std::string_view const str)
{
    base_document_t doc { &allocator() };
    doc.Parse(str.data(), str.size());

    if (doc.HasParseError()) {
        throw parse_error(
            make_parse_error_code(doc.GetParseError()),
            doc.GetErrorOffset());
    }

    value result;
    new (&result.base_value()) base_value_t { doc, allocator() };

    return result;
}

value
parse(std::istream& is)
{
    base_document_t doc { &allocator() };
    rj::IStreamWrapper wrapper { is };

    doc.ParseStream(wrapper);

    if (doc.HasParseError()) {
        throw parse_error(
            make_parse_error_code(doc.GetParseError()),
            doc.GetErrorOffset());
    }

    value result;
    new (&result.base_value()) base_value_t { doc, allocator() };

    return result;
}

std::string
stringify(value const& v)
{
    rj::StringBuffer sb;
    rj::Writer writer { sb };

    reinterpret_cast<base_value_t const&>(v).Accept(writer);

    return sb.GetString();
}

} // namespace json
