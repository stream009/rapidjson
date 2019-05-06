#ifndef JSON_BASE_HPP
#define JSON_BASE_HPP

#include <string_view>
#include <type_traits>

namespace json {

class base
{
public:
    class value_type;

protected:
    base();
    ~base();

    base(base const&);
    base(base&&);

    base& operator=(base const&);
    base& operator=(base&&);

    base(bool);
    base(int32_t);
    base(uint32_t);
    base(int64_t);
    base(uint64_t);
    base(long long);
    base(unsigned long long);

    base(double);

    base(std::string_view);

    void swap(base& b);

    value_type& base_value();
    value_type const& base_value() const;

private:
    std::aligned_storage_t<16> m_value;
};

} // namespace json

#endif // JSON_BASE_HPP
