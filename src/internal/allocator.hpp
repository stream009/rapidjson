#ifndef JSON_ALLOCATOR_HPP
#define JSON_ALLOCATOR_HPP

#include <rapidjson/allocators.h>

namespace json {

// thread-local allocator
rapidjson::MemoryPoolAllocator<>& allocator();

} // namespace json

#endif // JSON_ALLOCATOR_HPP
