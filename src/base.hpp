#ifndef JSON_BASE_HPP
#define JSON_BASE_HPP

#include <memory>

namespace json {

class base
{
public:
    class value_type;

protected:
    base();
    base(std::unique_ptr<value_type>);
    ~base();

    base(base const&);
    base(base&&);

    base& operator=(base const&);
    base& operator=(base&&);

    void swap(base& b);

    value_type& base_value() { return *m_value; }
    value_type const& base_value() const { return *m_value; }

private:
    std::unique_ptr<value_type> m_value;
};

} // namespace json

#endif // JSON_BASE_HPP
