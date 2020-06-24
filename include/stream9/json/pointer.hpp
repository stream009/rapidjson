#ifndef STREAM9_JSON_POINTER_HPP
#define STREAM9_JSON_POINTER_HPP

#include <string>
#include <string_view>
#include <type_traits>

namespace stream9::json {

class value;

class pointer
{
    using const_iterator = void;
public:
    pointer();
    pointer(std::string_view);

    pointer(pointer const&);
    pointer(pointer&&) noexcept;

    pointer& operator=(pointer const&);
    pointer& operator=(pointer&&) noexcept;

    ~pointer() noexcept;

    // for indirect conversion
    template<typename T,
        typename = std::enable_if_t<!std::is_same_v<T, std::string_view>> >
    pointer(T const& v)
        : pointer { std::string_view { v } } {}

    // iterator
    //const_iterator begin() const; //TODO
    //const_iterator end() const;

    // conversion
    std::string to_string() const;
    std::string to_url_fragment() const;

    void swap(pointer&) noexcept;

    // operator
    pointer operator/(std::string_view) const;

private:
    friend class value;

    static constexpr auto impl_size = sizeof(void*) * 7;

    std::aligned_storage_t<impl_size> m_impl;
};

// streaming
std::ostream& operator<<(std::ostream&, pointer const&);

// comparison
bool operator==(pointer const& lhs, pointer const& rhs);
bool operator!=(pointer const& lhs, pointer const& rhs);

} // namespace stream9::json

#endif // STREAM9_JSON_POINTER_HPP
