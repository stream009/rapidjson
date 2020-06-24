#include <boost/test/unit_test.hpp>

#include <sstream>

#include <json/value.hpp>
#include <json/array.hpp>
#include <json/object.hpp>
#include <json/pointer.hpp>

namespace json::testing {

BOOST_AUTO_TEST_SUITE(value_)

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

    BOOST_AUTO_TEST_CASE(char_array)
    {
        char s[] = "string";

        json::value v { s };
        BOOST_TEST(v == s); // make sure s doesn't get converted to bool

        // check if string is copied
        auto const sv = v.get_string();
        BOOST_ASSERT(sv);
        BOOST_TEST((void*)sv->data() != s);
        BOOST_TEST(sv->size() == strlen(s));

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
        BOOST_ASSERT(sv);
        BOOST_TEST((void*)sv->data() != s);
        BOOST_TEST(sv->size() == strlen(s));

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
        BOOST_ASSERT(sv);
        BOOST_TEST((void*)sv->data() != s.data());
        BOOST_TEST(sv->size() == s.size());

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
        BOOST_ASSERT(sv);
        BOOST_TEST((void*)sv->data() != s.data());
        BOOST_TEST(sv->size() == s.size());

        // conversion
        json::value v2 = s;
        BOOST_TEST(v2 == s);
    }

    BOOST_AUTO_TEST_CASE(array_copy)
    {
        json::array a;
        a.push_back(true);

        json::value v { a };

        BOOST_TEST(v == a);
    }

    BOOST_AUTO_TEST_CASE(array_move)
    {
        json::array a;
        a.push_back("foo");

        auto const& foo = a[0];

        json::value v { std::move(a) };

        BOOST_TEST(v.is_array());
        BOOST_TEST((&(v.get_array()->at(0)) == &foo));
    }

    BOOST_AUTO_TEST_CASE(object_copy)
    {
        json::object o;
        o["foo"] = "bar";

        json::value v { o };

        BOOST_TEST(v == o);
    }

    BOOST_AUTO_TEST_CASE(object_move)
    {
        json::object o;
        o["foo"] = "bar";

        auto const& foo = o["foo"];

        json::value v { std::move(o) };

        auto* const o2 = v.get_object();
        BOOST_TEST(o2);

        auto& v2 = o2->at("foo");
        BOOST_TEST(&v2 == &foo);
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

    BOOST_AUTO_TEST_CASE(char_array)
    {
        char s[] = "string";
        json::value v;

        v = s;

        BOOST_TEST(v == s);

        // check if string is copied
        auto const sv = v.get_string();
        BOOST_ASSERT(sv);
        BOOST_TEST((void*)sv->data() != s);
        BOOST_TEST(sv->size() == strlen(s));
    }

    BOOST_AUTO_TEST_CASE(char_ptr)
    {
        char const* s = "string";
        json::value v;

        v = s;

        BOOST_TEST(v == s);

        // check if string is copied
        auto const sv = v.get_string();
        BOOST_ASSERT(sv);
        BOOST_TEST((void*)sv->data() != s);
        BOOST_TEST(sv->size() == strlen(s));
    }

    BOOST_AUTO_TEST_CASE(string)
    {
        std::string s = "string";
        json::value v;

        v = s;

        BOOST_TEST(v == s);

        // check if string is copied
        auto const sv = v.get_string();
        BOOST_ASSERT(sv);
        BOOST_TEST((void*)sv->data() != s.data());
        BOOST_TEST(sv->size() == s.size());
    }

    BOOST_AUTO_TEST_CASE(string_view)
    {
        std::string_view s = "string";
        json::value v;

        v = s;

        BOOST_TEST(v == s);

        // check if string is copied
        auto const sv = v.get_string();
        BOOST_ASSERT(sv);
        BOOST_TEST((void*)sv->data() != s.data());
        BOOST_TEST(sv->size() == s.size());
    }

    BOOST_AUTO_TEST_CASE(array)
    {
        json::array a;
        a.push_back(true);

        json::value v;
        v = a;

        BOOST_TEST(v == a);
    }

    BOOST_AUTO_TEST_CASE(object)
    {
        json::object o;
        o["foo"] = "bar";

        json::value v;
        v = o;

        BOOST_TEST(v == o);
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

        json::array a;
        v = a;
        BOOST_TEST(v.get_type() == value::type::array);

        json::object o;
        v = o;
        BOOST_TEST(v.get_type() == value::type::object);

        BOOST_TEST(v.find("/foo").get_type() == value::type::undefined);
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

    BOOST_AUTO_TEST_CASE(is_int32)
    {
        json::value v { 1 };
        BOOST_TEST(v.is_int32());
        BOOST_TEST(v.is_number());

        v = -100;
        BOOST_TEST(v.is_int32());

        v = static_cast<int64_t>(100);
        BOOST_TEST(v.is_int32());

        v = static_cast<int64_t>(INT_MAX) + 1;
        BOOST_TEST(!v.is_int32());
    }

    BOOST_AUTO_TEST_CASE(is_uint32)
    {
        json::value v { 1u };
        BOOST_TEST(v.is_uint32());
        BOOST_TEST(v.is_number());

        v = static_cast<uint64_t>(100);
        BOOST_TEST(v.is_uint32());

        v = static_cast<uint64_t>(UINT_MAX) + 1;
        BOOST_TEST(!v.is_uint32());
    }

    BOOST_AUTO_TEST_CASE(is_int64)
    {
        json::value v { 1ll };
        BOOST_TEST(v.is_int64());
        BOOST_TEST(v.is_number());

        v = -100ll;
        BOOST_TEST(v.is_int64());

        v = static_cast<int64_t>(100);
        BOOST_TEST(v.is_int64());

        v = static_cast<int64_t>(INT_MAX) + 1;
        BOOST_TEST(v.is_int64());

        v = static_cast<int64_t>(INT_MIN) - 1;
        BOOST_TEST(v.is_int64());
    }

    BOOST_AUTO_TEST_CASE(is_uint64)
    {
        json::value v { 1ull };
        BOOST_TEST(v.is_uint64());
        BOOST_TEST(v.is_number());

        v = static_cast<int64_t>(100);
        BOOST_TEST(v.is_int64());

        v = static_cast<int64_t>(INT_MAX) + 1;
        BOOST_TEST(v.is_int64());
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

    BOOST_AUTO_TEST_CASE(is_array)
    {
        json::array a;
        json::value v { a };

        BOOST_TEST(v.is_array());
    }

    BOOST_AUTO_TEST_CASE(is_object)
    {
        json::object o;
        json::value v { o };

        BOOST_TEST(v.is_object());
    }

    BOOST_AUTO_TEST_CASE(get_bool)
    {
        json::value v { true };

        auto const b = v.get_bool();

        BOOST_ASSERT(b);
        BOOST_TEST(*b == true);
    }

    BOOST_AUTO_TEST_CASE(get_int32)
    {
        json::value v = 1;

        auto const i = v.get_int32();

        BOOST_ASSERT(i);
        BOOST_TEST(*i == 1);
    }

    BOOST_AUTO_TEST_CASE(get_uint32)
    {
        json::value v = 1u;

        auto const i = v.get_uint32();

        BOOST_ASSERT(i);
        BOOST_TEST(*i == 1);
    }

    BOOST_AUTO_TEST_CASE(get_int64)
    {
        json::value v = 1ll;

        auto const i = v.get_int64();

        BOOST_ASSERT(i);
        BOOST_TEST(*i == 1);
    }

    BOOST_AUTO_TEST_CASE(get_uint64)
    {
        json::value v = 1ull;

        auto const i = v.get_uint64();

        BOOST_ASSERT(i);
        BOOST_TEST(*i == 1);
    }

    BOOST_AUTO_TEST_CASE(get_number)
    {
        json::value v = 1;

        auto const n = v.get_number();

        BOOST_ASSERT(n);
        BOOST_TEST(*n == 1);
    }

    BOOST_AUTO_TEST_CASE(get_string)
    {
        json::value v { "string" };

        auto const s = v.get_string();

        BOOST_ASSERT(s);
        BOOST_TEST(*s == "string");
    }

    BOOST_AUTO_TEST_CASE(get_array)
    {
        json::array a1;
        a1.push_back(1);

        json::value v { a1 };

        auto const a2 = v.get_array();

        BOOST_ASSERT(a2);
        BOOST_REQUIRE(a2->size() == 1);
        BOOST_TEST((*a2)[0] == 1);
    }

    BOOST_AUTO_TEST_CASE(get_array_const)
    {
        json::array a1;
        a1.push_back(1);

        json::value v { a1 };
        auto const& vc = v;

        auto const a2 = vc.get_array();

        BOOST_ASSERT(a2);
        BOOST_REQUIRE(a2->size() == 1);
        BOOST_TEST((*a2)[0] == 1);
    }

    BOOST_AUTO_TEST_CASE(get_object)
    {
        json::object o1;
        o1["foo"] = true;

        json::value v { o1 };

        auto const o2 = v.get_object();

        BOOST_ASSERT(o2);
        BOOST_REQUIRE(o2->size() == 1);
        BOOST_TEST((*o2)["foo"] == true);
    }

    BOOST_AUTO_TEST_CASE(get_object_const)
    {
        json::object o1;
        o1["foo"] = true;

        json::value v { o1 };

        auto const& vc = v;
        auto const o2 = vc.get_object();

        BOOST_ASSERT(o2);
        BOOST_REQUIRE(o2->size() == 1);
        BOOST_TEST(o2->at("foo") == true);
    }

BOOST_AUTO_TEST_SUITE_END() // query

BOOST_AUTO_TEST_SUITE(modifier)

    BOOST_AUTO_TEST_CASE(set_bool)
    {
        json::value v;
        v.set_bool(true);

        BOOST_TEST(v == true);
    }

    BOOST_AUTO_TEST_CASE(set_int32)
    {
        json::value v;
        v.set_int32(100);

        BOOST_TEST(v.is_int32());
        BOOST_TEST(v == 100);
    }

    BOOST_AUTO_TEST_CASE(set_uint32)
    {
        json::value v;
        v.set_uint32(100);

        BOOST_TEST(v.is_uint32());
        BOOST_TEST(v == 100);
    }

    BOOST_AUTO_TEST_CASE(set_int64)
    {
        json::value v;
        v.set_int64(100);

        BOOST_TEST(v.is_int64());
        BOOST_TEST(v == 100);
    }

    BOOST_AUTO_TEST_CASE(set_uint64)
    {
        json::value v;
        v.set_uint64(100);

        BOOST_TEST(v.is_uint64());
        BOOST_TEST(v == 100);
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

        auto const sv = v.get_string();
        BOOST_ASSERT(sv);
        BOOST_TEST((void*)sv->data() != s);
        BOOST_TEST(sv->size() == strlen(s));
    }

    BOOST_AUTO_TEST_CASE(set_array)
    {
        json::array a1;
        a1.push_back(1);

        json::value v;
        v.set_array(a1);

        BOOST_TEST(v.is_array());

        auto const a2 = v.get_array();

        BOOST_ASSERT(a2);
        BOOST_TEST(a2->size() == 1);
        BOOST_TEST(a2->front() == 1);
    }

    BOOST_AUTO_TEST_CASE(set_object)
    {
        json::object o1;
        o1["foo"] = 10;

        json::value v;
        v.set_object(o1);

        BOOST_TEST(v.is_object());

        auto const o2 = v.get_object();

        BOOST_ASSERT(o2);
        BOOST_TEST(o2->size() == 1);
        BOOST_TEST(o2->at("foo") == 10);
    }

    BOOST_AUTO_TEST_CASE(set_null)
    {
        json::value v { 100 };
        v.set_null();

        BOOST_TEST(v.is_null());
    }

BOOST_AUTO_TEST_SUITE_END() // modifier

BOOST_AUTO_TEST_SUITE(conversion_op)

    BOOST_AUTO_TEST_CASE(undefined_)
    {
        json::value v;

        BOOST_TEST(!v.find("/foo"));
    }

    BOOST_AUTO_TEST_CASE(null_)
    {
        json::value v;
        BOOST_TEST(v.is_null());
        BOOST_TEST(!v);;
    }

    BOOST_AUTO_TEST_CASE(bool_)
    {
        json::value v { true };
        BOOST_TEST(!!v);

        v = false;
        BOOST_TEST(!v);
    }

    BOOST_AUTO_TEST_CASE(number_)
    {
        json::value v = 1;
        BOOST_TEST(!!v == true);

        v = 0;
        BOOST_TEST(!v);
    }

    BOOST_AUTO_TEST_CASE(string_)
    {
        json::value v = "foo";
        BOOST_TEST(!!v);

        v = "";
        BOOST_TEST(!v);
    }

    BOOST_AUTO_TEST_CASE(array_)
    {
        json::array a;
        json::value v = a;

        BOOST_TEST(!!v);
    }

    BOOST_AUTO_TEST_CASE(object_)
    {
        json::object o;
        json::value v = o;

        BOOST_TEST(!!v);
    }

BOOST_AUTO_TEST_SUITE_END() // conversion_op

BOOST_AUTO_TEST_SUITE(parse_)

    BOOST_AUTO_TEST_CASE(from_stream_)
    {
        std::stringstream ss;
        ss << R"({ "foo": "bar" })";

        auto const v = json::parse(ss);

        auto* const obj = v.get_object();

        BOOST_ASSERT(obj);
        BOOST_ASSERT(obj->contains("foo"));
        BOOST_TEST((*obj)["foo"] == "bar");
    }

BOOST_AUTO_TEST_SUITE_END() // parse_

BOOST_AUTO_TEST_SUITE(stringify_)

    BOOST_AUTO_TEST_CASE(value_)
    {
        json::value v = 1;

        BOOST_TEST(stringify(v) == "1");
    }

BOOST_AUTO_TEST_SUITE_END() // stringify_

BOOST_AUTO_TEST_SUITE_END() // value_

} // namespace json
