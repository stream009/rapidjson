#ifndef STREAM9_JSON_BASE_HPP
#define STREAM9_JSON_BASE_HPP

#include <string_view>
#include <type_traits>

namespace stream9::json {

class base
{
public:
    class value_type;

protected:
    base();
    ~base();

    base(base const&);
    base(base&&) noexcept;

    base& operator=(base const&);
    base& operator=(base&&) noexcept;

    base(bool);
    base(int32_t);
    base(uint32_t);
    base(int64_t);
    base(uint64_t);
    base(long long);
    base(unsigned long long);

    base(double);

    base(std::string_view);

    void swap(base& b) noexcept;

    value_type& base_value();
    value_type const& base_value() const;

    bool is_undefined() const;
    void set_undefined(bool);

private:
    std::aligned_storage_t<16> m_value;
};

} // namespace stream9::json

#endif // STREAM9_JSON_BASE_HPP
