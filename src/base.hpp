#ifndef JSON_BASE_HPP
#define JSON_BASE_HPP

#include <string_view>


namespace json {

class base
{
public:
    class value_type;

protected:
    base();
    base(bool);
    base(double);
    base(std::string_view);

    base(base const&);
    base(base&&);

    ~base();

    base& operator=(base const&);
    base& operator=(base&&);

    void swap(base& b);

    value_type& base_value();
    value_type const& base_value() const;

private:
    std::aligned_storage_t<16> m_value;
};

} // namespace json

#endif // JSON_BASE_HPP
