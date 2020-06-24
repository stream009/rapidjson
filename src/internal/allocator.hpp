#ifndef STREAM9_JSON_ALLOCATOR_HPP
#define STREAM9_JSON_ALLOCATOR_HPP

#include <rapidjson/allocators.h>

namespace stream9::json {

rapidjson::CrtAllocator& allocator();

} // namespace stream9::json

#endif // STREAM9_JSON_ALLOCATOR_HPP
