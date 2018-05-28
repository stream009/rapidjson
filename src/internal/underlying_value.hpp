#ifndef JSON_UNDERLYING_VALUE
#define JSON_UNDERLYING_VALUE

#include "../base.hpp"
#include "allocator.hpp"

#include <rapidjson/document.h>

namespace json {

class base::value_type : public rapidjson::Value
{
public:
    using rapidjson::Value::Value;

    value_type(value_type const& v)
        : rapidjson::Value { v, allocator() }
    {}

};

} // namespace json

#endif // JSON_UNDERLYING_VALUE