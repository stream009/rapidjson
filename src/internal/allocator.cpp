#include "allocator.hpp"

namespace json {

rapidjson::CrtAllocator&
allocator()
{
    static thread_local rapidjson::CrtAllocator alloc;
    return alloc;
}

} // namespace json
