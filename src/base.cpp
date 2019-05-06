#include <json/base.hpp>

#include "internal/allocator.hpp"
#include "internal/underlying_value.hpp"

#include <string_view>

namespace json {

namespace rj = rapidjson;

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
base(base&& other)
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
operator=(base&& rhs)
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
swap(base& other)
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


} // namespace json
