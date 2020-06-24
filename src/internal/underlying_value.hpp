#ifndef STREAM9_JSON_UNDERLYING_VALUE
#define STREAM9_JSON_UNDERLYING_VALUE

#include <stream9/json/base.hpp>

#include "allocator.hpp"

#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

namespace stream9::json {

namespace rj = rapidjson;

using base_document_t = rj::GenericDocument<rj::UTF8<char>, rj::CrtAllocator>;

using base_value_t = rj::GenericValue<
        rj::UTF8<char>,
        rj::CrtAllocator
    >;

using base_pointer_t = rj::GenericPointer<base_value_t>;

class base::value_type : public base_value_t
{
public:
    using base_value_t::base_value_t;

    value_type(value_type const& v)
        : base_value_t { v, allocator(), true }
    {}

};

} // namespace stream9::json

#endif // STREAM9_JSON_UNDERLYING_VALUE
