#include "allocator.hpp"

namespace stream9::json {

rapidjson::CrtAllocator&
allocator()
{
    static thread_local rapidjson::CrtAllocator alloc;
    return alloc;
}

} // namespace stream9::json
