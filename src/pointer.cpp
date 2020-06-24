#include <stream9/json/pointer.hpp>

#include <stream9/json/error.hpp>

#include "internal/underlying_value.hpp"

#include <rapidjson/pointer.h>
#include <rapidjson/stringbuffer.h>

namespace stream9::json {

namespace rj = rapidjson;

static base_pointer_t&
to_base(pointer& p)
{
    return reinterpret_cast<base_pointer_t&>(p);
}

static base_pointer_t const&
to_base(pointer const& p)
{
    return reinterpret_cast<base_pointer_t const&>(p);
}

//
// pointer
//
pointer::
pointer()
{
    static_assert(sizeof(m_impl) >= sizeof(base_pointer_t));
    new (&m_impl) base_pointer_t;
}

pointer::
pointer(std::string_view const s)
{
    new (&m_impl) base_pointer_t { s.data(), s.size() };

    auto const& base = to_base(*this);
    if (!base.IsValid()) {
        throw pointer_error {
            make_pointer_error_code(base.GetParseErrorCode()),
            base.GetParseErrorOffset() };
    }
}

pointer::
pointer(pointer const& other)
{
    new (&m_impl) base_pointer_t { to_base(other) };
}

pointer::
pointer(pointer&& other) noexcept
{
    new (&m_impl) base_pointer_t;
    swap(other);
}

pointer& pointer::
operator=(pointer const& rhs)
{
    pointer copy { rhs };
    swap(copy);

    return *this;
}

pointer& pointer::
operator=(pointer&& rhs) noexcept
{
    swap(rhs);

    return *this;
}

pointer::
~pointer() noexcept
{
    to_base(*this).~base_pointer_t();
}

std::string pointer::
to_string() const
{
    rj::StringBuffer sb;

    to_base(*this).Stringify(sb);

    return sb.GetString();
}

void pointer::
swap(pointer& other) noexcept
{
    to_base(*this).Swap(to_base(other));
}

std::ostream&
operator<<(std::ostream& os, pointer const& p)
{
    return os << p.to_string();
}

bool
operator==(pointer const& lhs, pointer const& rhs)
{
    return to_base(lhs) == to_base(rhs);
}

bool
operator!=(pointer const& lhs, pointer const& rhs)
{
    return !(lhs == rhs);
}

} // namespace stream9::json
