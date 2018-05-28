#include "array.hpp"

#include "internal/underlying_value.hpp"

namespace json {

array::
array()
{
    this->base_value().SetArray();
}

array::~array() = default;

bool array::
empty() const
{
    return this->base_value().Empty();
}

value& array::
at(size_type const index)
{
    auto& v = this->base_value()[index];
    //TODO how to convert Value to value
}

} // namespace json
