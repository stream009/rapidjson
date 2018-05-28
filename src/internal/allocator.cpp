#include "allocator.hpp"

namespace json {

rapidjson::MemoryPoolAllocator<>&
allocator()
{
    static thread_local rapidjson::MemoryPoolAllocator alloc;
    return alloc;
}

} // namespace json
