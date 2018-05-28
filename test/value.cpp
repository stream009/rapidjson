#include <boost/test/unit_test.hpp>

#include <json/json.hpp>
#include <json/value.hpp>
#include <json/array.hpp>

namespace json::testing {

BOOST_AUTO_TEST_SUITE(value_)

BOOST_AUTO_TEST_CASE(elementary)
{
    auto const text = R"({ "foo": "bar" })";

    auto value = json::parse(text);
}

BOOST_AUTO_TEST_SUITE(constructor)

    BOOST_AUTO_TEST_CASE(default_constructor)
    {
        json::value v;
        BOOST_TEST(v.is_null());
    }

    BOOST_AUTO_TEST_CASE(copy)
    {
        json::value v1;

        BOOST_TEST(v1.is_null());

        v1 = true;

        BOOST_TEST(v1 == true);

        json::value v2 { v1 };

        BOOST_TEST(v2 == v1);
    }

    BOOST_AUTO_TEST_CASE(move)
    {
        json::value v1;

        BOOST_TEST(v1.is_null());

        v1 = true;

        BOOST_TEST(v1 == true);

        json::value v2 { std::move(v1) };

        BOOST_TEST(v2 == true);
    }

    BOOST_AUTO_TEST_CASE(bool_)
    {
        json::value v { true };

        BOOST_TEST(v == true);

        json::value v2 = false; // conversion
        BOOST_TEST(v2 == false);
    }

    BOOST_AUTO_TEST_CASE(char_)
    {
        char i = 1;
        json::value v(i); // implicit narrowing
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(signed_char)
    {
        signed char i = 1;

        json::value v(i); // implicit narrowing
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(unsigned_char)
    {
        unsigned char i = 1;

        json::value v(i); // implicit narrowing
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(wchar)
    {
        wchar_t i = 1;

        json::value v(i); // implicit narrowing
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(char16)
    {
        char16_t i = 1;

        json::value v(i); // implicit narrowing
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(char32)
    {
        char32_t i = 1;

        json::value v(i); // implicit narrowing
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(short_int)
    {
        short int i = 1;

        json::value v(i); // implicit narrowing
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(unsigned_short_int)
    {
        unsigned short int i = 1;

        json::value v(i); // implicit narrowing
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(int_)
    {
        int i = 1;

        json::value v(i); // implicit narrowing
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(unsigned_int)
    {
        unsigned int i = 1;

        json::value v(i); // implicit narrowing
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(long_)
    {
        long i = 1;

        json::value v(i); // implicit narrowing
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(unsigned_long)
    {
        unsigned long i = 1;

        json::value v(i); // implicit narrowing
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(long_long)
    {
        long long i = 1;

        json::value v(i); // implicit narrowing
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(unsigned_long_long)
    {
        unsigned long long i = 1;

        json::value v(i); // implicit narrowing
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(float_)
    {
        float i = 1.0;

        json::value v(i); // implicit narrowing
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(double_)
    {
        double i = 1.0;

        json::value v { i };
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(long_double)
    {
        long double i = 1.0;

        json::value v(i); // implicit narrowing
        BOOST_TEST(v == i);

        json::value v2 = i; // conversion
        BOOST_TEST(v2 == i);
    }

    BOOST_AUTO_TEST_CASE(char_array)
    {
        char s[] = "string";

        json::value v { s };
        BOOST_TEST(v == s); // make sure s doesn't get converted to bool

        // check if string is copied
        auto const sv = v.get_string();
        BOOST_TEST((void*)sv.data() != s);
        BOOST_TEST(sv.size() == strlen(s));

        // conversion
        json::value v2 = s;
        BOOST_TEST(v2 == s);
    }

    BOOST_AUTO_TEST_CASE(char_ptr)
    {
        char const* s = "string";

        json::value v { s };
        BOOST_TEST(v == s); // make sure s doesn't get converted to bool

        // check if string is copied
        auto const sv = v.get_string();
        BOOST_TEST((void*)sv.data() != s);
        BOOST_TEST(sv.size() == strlen(s));

        // conversion
        json::value v2 = s;
        BOOST_TEST(v2 == s);
    }

    BOOST_AUTO_TEST_CASE(string)
    {
        std::string s = "string";

        json::value v { s };
        BOOST_TEST(v == s);

        // check if string is copied
        auto const sv = v.get_string();
        BOOST_TEST((void*)sv.data() != s.data());
        BOOST_TEST(sv.size() == s.size());

        // conversion
        json::value v2 = s;
        BOOST_TEST(v2 == s);
    }

    BOOST_AUTO_TEST_CASE(string_view)
    {
        std::string_view s = "string";

        json::value v { s };
        BOOST_TEST(v == s);

        // check if string is copied
        auto const sv = v.get_string();
        BOOST_TEST((void*)sv.data() != s.data());
        BOOST_TEST(sv.size() == s.size());

        // conversion
        json::value v2 = s;
        BOOST_TEST(v2 == s);
    }

    BOOST_AUTO_TEST_CASE(null_)
    {
        json::value v { null };

        BOOST_TEST(v == null);

        json::value v2 = null;
        BOOST_TEST(v2 == null);
    }

BOOST_AUTO_TEST_SUITE_END() // constructor

BOOST_AUTO_TEST_SUITE(assignment)

    BOOST_AUTO_TEST_CASE(copy_)
    {
        json::value v1 { true };
        json::value v2;

        v2 = v1;

        BOOST_TEST(v2 == v1);
    }

    BOOST_AUTO_TEST_CASE(move_)
    {
        json::value v1 { true };
        json::value v2;

        BOOST_TEST(v2.is_null());

        v2 = std::move(v1);

        BOOST_TEST(v2 == true);
    }

    BOOST_AUTO_TEST_CASE(bool_)
    {
        json::value v1;

       v1 = true;

       BOOST_TEST(v1 == true);
    }

    BOOST_AUTO_TEST_CASE(char_)
    {
        char i = 1;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(signed_char)
    {
        signed char i = 1;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(unsigned_char)
    {
        unsigned char i = 1;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(wchar)
    {
        wchar_t i = 1;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(char16)
    {
        char16_t i = 1;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(char32)
    {
        char32_t i = 1;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(short_int)
    {
        short int i = 1;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(unsigned_short_int)
    {
        unsigned short int i = 1;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(int_)
    {
        int i = 1;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(unsigned_int)
    {
        unsigned int i = 1;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(long_)
    {
        long i = 1;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(unsigned_long)
    {
        unsigned long i = 1;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(long_long)
    {
        long long i = 1;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(unsigned_long_long)
    {
        unsigned long long i = 1;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(float_)
    {
        float i = 1.0;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(double_)
    {
        double i = 1.0;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(long_double)
    {
        long double i = 1.0;
        json::value v;

        v = i;

        BOOST_TEST(v == i);
    }

    BOOST_AUTO_TEST_CASE(char_array)
    {
        char s[] = "string";
        json::value v;

        v = s;

        BOOST_TEST(v == s);

        // check if string is copied
        auto const sv = v.get_string();
        BOOST_TEST((void*)sv.data() != s);
        BOOST_TEST(sv.size() == strlen(s));
    }

    BOOST_AUTO_TEST_CASE(char_ptr)
    {
        char const* s = "string";
        json::value v;

        v = s;

        BOOST_TEST(v == s);

        // check if string is copied
        auto const sv = v.get_string();
        BOOST_TEST((void*)sv.data() != s);
        BOOST_TEST(sv.size() == strlen(s));
    }

    BOOST_AUTO_TEST_CASE(string)
    {
        std::string s = "string";
        json::value v;

        v = s;

        BOOST_TEST(v == s);

        // check if string is copied
        auto const sv = v.get_string();
        BOOST_TEST((void*)sv.data() != s.data());
        BOOST_TEST(sv.size() == s.size());
    }

    BOOST_AUTO_TEST_CASE(string_view)
    {
        std::string_view s = "string";
        json::value v;

        v = s;

        BOOST_TEST(v == s);

        // check if string is copied
        auto const sv = v.get_string();
        BOOST_TEST((void*)sv.data() != s.data());
        BOOST_TEST(sv.size() == s.size());
    }

    BOOST_AUTO_TEST_CASE(null_)
    {
        json::value v;

        v = null;

        BOOST_TEST(v == null);
    }

BOOST_AUTO_TEST_SUITE_END() // assignment

BOOST_AUTO_TEST_SUITE(query)

    BOOST_AUTO_TEST_CASE(get_type)
    {
        json::value v;
        BOOST_TEST(v.get_type() == value::type::null);

        v = true;
        BOOST_TEST(v.get_type() == value::type::boolean);

        v = false;
        BOOST_TEST(v.get_type() == value::type::boolean);

        v = 1;
        BOOST_TEST(v.get_type() == value::type::number);

        v = 1.5;
        BOOST_TEST(v.get_type() == value::type::number);

        v = "string";
        BOOST_TEST(v.get_type() == value::type::string);

        //TODO array & object
    }

    BOOST_AUTO_TEST_CASE(is_null)
    {
        json::value v { null };

        BOOST_TEST(v.is_null());
    }

    BOOST_AUTO_TEST_CASE(is_bool)
    {
        json::value v { true };
        BOOST_TEST(v.is_bool());

        v = false;
        BOOST_TEST(v.is_bool());
    }

    BOOST_AUTO_TEST_CASE(is_number)
    {
        json::value v { 1 };
        BOOST_TEST(v.is_number());

        v = 'A';
        BOOST_TEST(v.is_number());

        v = 10.5;
        BOOST_TEST(v.is_number());
    }

    BOOST_AUTO_TEST_CASE(is_string)
    {
        json::value v { "string" };
        BOOST_TEST(v.is_string());
    }

    BOOST_AUTO_TEST_CASE(get_bool) //TODO error handling
    {
        json::value v { true };

        bool b = v.get_bool();

        BOOST_TEST(b == true);
    }

    BOOST_AUTO_TEST_CASE(get_number)
    {
        json::value v = 1;

        auto b = v.get_number();

        BOOST_TEST(b == 1);
    }

    BOOST_AUTO_TEST_CASE(get_string)
    {
        json::value v { "string" };

        auto s = v.get_string();

        BOOST_TEST(s == "string");
    }

#if 0
    BOOST_AUTO_TEST_CASE(get_array)
    {
        json::value v;

        auto& a = v.get_array();

        BOOST_TEST(a.empty());
    }
#endif

BOOST_AUTO_TEST_SUITE_END() // query

BOOST_AUTO_TEST_SUITE(modifier)

    BOOST_AUTO_TEST_CASE(set_bool)
    {
        json::value v;
        v.set_bool(true);

        BOOST_TEST(v == true);
    }

    BOOST_AUTO_TEST_CASE(set_number)
    {
        json::value v;
        v.set_number(10);

        BOOST_TEST(v == 10);
    }

    BOOST_AUTO_TEST_CASE(set_string)
    {
        auto s = "string";

        json::value v;
        v.set_string(s);
        BOOST_TEST(v == s);

        auto sv = v.get_string();
        BOOST_TEST((void*)sv.data() != s);
        BOOST_TEST(sv.size() == strlen(s));
    }

    BOOST_AUTO_TEST_CASE(set_null)
    {
        json::value v { 100 };
        v.set_null();

        BOOST_TEST(v.is_null());
    }

BOOST_AUTO_TEST_SUITE_END() // modifier

BOOST_AUTO_TEST_SUITE(conversion_op)

    BOOST_AUTO_TEST_CASE(bool_)
    {
        json::value v { true };

        bool b = v;

        BOOST_TEST(b == true);
    }

BOOST_AUTO_TEST_SUITE_END() // conversion_op

BOOST_AUTO_TEST_SUITE_END() // value_

} // namespace json
