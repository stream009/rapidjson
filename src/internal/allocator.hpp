#ifndef JSON_ALLOCATOR_HPP
#define JSON_ALLOCATOR_HPP

#include <rapidjson/allocators.h>

namespace json {

rapidjson::CrtAllocator& allocator();

} // namespace json

#endif // JSON_ALLOCATOR_HPP
