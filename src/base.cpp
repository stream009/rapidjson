#include "base.hpp"

#include "internal/allocator.hpp"
#include "internal/underlying_value.hpp"

#include <iostream>

namespace json {

base::
base()
    : m_value { std::make_unique<value_type>() }
{
    std::cout << sizeof(value_type) << std::endl;
}

base::
base(std::unique_ptr<value_type> v)
    : m_value { std::move(v) }
{}

base::
base(base const& other)
    : m_value {
        std::make_unique<value_type>(*other.m_value) }
{}

base::
base(base&& other)
    : m_value { std::move(other.m_value) }
{}

base::~base() = default;

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

void base::
swap(base& b)
{
    m_value.swap(b.m_value);
}

} // namespace json
