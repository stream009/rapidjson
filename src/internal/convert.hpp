#ifndef JSON_INTERNAL_CONVERT_HPP
#define JSON_INTERNAL_CONVERT_HPP

#include <stdexcept>
#include <limits>

#include <rapidjson/rapidjson.h>

namespace json {

namespace rj = rapidjson;

inline rj::SizeType
to_rj_size(size_t const i)
{
    if (i > std::numeric_limits<rj::SizeType>::max()) {
        throw std::out_of_range("json");
    }
    return static_cast<rj::SizeType>(i);
}

} // namespace json

#endif // JSON_INTERNAL_CONVERT_HPP
