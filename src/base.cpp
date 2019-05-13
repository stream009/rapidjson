#include <json/base.hpp>

#include "internal/allocator.hpp"
#include "internal/convert.hpp"
#include "internal/underlying_value.hpp"

#include <string_view>

namespace json {

namespace rj = rapidjson;

struct Flag {
#if RAPIDJSON_48BITPOINTER_OPTIMIZATION
    char payload[sizeof(rj::SizeType) * 2 + 6];     // 2 x SizeType + lower 48-bit pointer
#elif RAPIDJSON_64BIT
    char payload[sizeof(rj::SizeType) * 2 + sizeof(void*) + 6]; // 6 padding bytes
#else
    char payload[sizeof(rj::SizeType) * 2 + sizeof(void*) + 2]; // 2 padding bytes
#endif
    uint16_t flags;
};

static uint16_t
get_flag(base::value_type const& v)
{
    return reinterpret_cast<Flag const&>(v).flags;
}

static uint16_t&
get_flag(base::value_type& v)
{
    return reinterpret_cast<Flag&>(v).flags;
}

//
// base
//
base::
base()
{
    static_assert(sizeof(m_value) == sizeof(value_type));
    new (&m_value) value_type;
}

base::~base()
{
    base_value().~value_type();
}

base::
base(base const& other)
{
    new (&m_value) value_type { other.base_value() };
}

base::
base(base&& other) noexcept
{
    new (&m_value) value_type;
    swap(other);
}

base& base::
operator=(base const& rhs)
{
    base tmp { rhs };

    swap(tmp);

    return *this;
}

base& base::
operator=(base&& rhs) noexcept
{
    base tmp { std::move(rhs) };

    swap(tmp);

    return *this;
}

base::
base(bool const v)
{
    new (&m_value) value_type { v };
}

base::
base(int32_t const v)
{
    new (&m_value) value_type { v };
}

base::
base(uint32_t const v)
{
    new (&m_value) value_type { v };
}

base::
base(int64_t const v)
{
    new (&m_value) value_type { v };
}

base::
base(uint64_t const v)
{
    new (&m_value) value_type { v };
}

base::
base(long long const v)
{
    new (&m_value) value_type { static_cast<int64_t>(v) };
}

base::
base(unsigned long long const v)
{
    new (&m_value) value_type { static_cast<uint64_t>(v) };
}

base::
base(double const v)
{
    new (&m_value) value_type { v };
}

base::
base(std::string_view const v)
{
    new (&m_value) value_type { v.data(), to_rj_size(v.size()), allocator() };
}

void base::
swap(base& other) noexcept
{
    base_value().Swap(other.base_value());
}

base::value_type& base::
base_value()
{
    return reinterpret_cast<value_type&>(m_value);
}

base::value_type const& base::
base_value() const
{
    return reinterpret_cast<value_type const&>(m_value);
}

bool base::
is_undefined() const
{
    return get_flag(base_value()) & 0x8000;
}

void base::
set_undefined(bool const undefined)
{
    if (undefined) {
        get_flag(base_value()) |= static_cast<uint16_t>(0x8000);
    }
    else {
        get_flag(base_value()) &= static_cast<uint16_t>(~0x8000);
    }
}

} // namespace json
