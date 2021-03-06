#include <boost/test/unit_test.hpp>

#include <stream9/json/array.hpp>
#include <stream9/json/value.hpp>

namespace stream9::json::tesing {

BOOST_AUTO_TEST_SUITE(array)

BOOST_AUTO_TEST_SUITE(constructor)

    BOOST_AUTO_TEST_CASE(default_)
    {
        json::array a;

        BOOST_TEST(a.empty());
        BOOST_TEST(a.capacity() == 0);
    }

    BOOST_AUTO_TEST_CASE(copy)
    {
        json::array a1;
        a1.push_back(true);
        a1.push_back("string");

        BOOST_TEST(a1.size() == 2);
        BOOST_TEST(a1[0] == true);
        BOOST_TEST(a1[1] == "string");

        auto a2 = a1;

        BOOST_TEST(a2.size() == 2);
        BOOST_TEST(a2[0] == true);
        BOOST_TEST(a2[1] == "string");
        BOOST_TEST(&a2[1] != &a1[1]);
    }

    BOOST_AUTO_TEST_CASE(move)
    {
        json::array a1;
        a1.push_back(true);
        a1.push_back("string");

        BOOST_TEST(a1.size() == 2);
        BOOST_TEST(a1[0] == true);
        BOOST_TEST(a1[1] == "string");

        auto* a1_1 = &a1[1];

        auto a2 = std::move(a1);

        BOOST_TEST(a2.size() == 2);
        BOOST_TEST(a2[0] == true);
        BOOST_TEST(a2[1] == "string");
        BOOST_TEST(&a2[1] == a1_1);
    }

BOOST_AUTO_TEST_SUITE_END() // constructor

BOOST_AUTO_TEST_SUITE(assignment)

    BOOST_AUTO_TEST_CASE(copy)
    {
        json::array a1;
        a1.push_back(true);
        a1.push_back("string");

        json::array a2;
        a2 = a1;

        BOOST_TEST(a2.size() == 2);
        BOOST_TEST(a2[0] == true);
        BOOST_TEST(a2[1] == "string");
        BOOST_TEST(&a2[1] != &a1[1]);
    }

    BOOST_AUTO_TEST_CASE(move)
    {
        json::array a1;
        a1.push_back(true);
        a1.push_back("string");

        json::array a2;
        auto* a1_1 = &a1[1];
        a2 = std::move(a1);

        BOOST_TEST(a2.size() == 2);
        BOOST_TEST(a2[0] == true);
        BOOST_TEST(a2[1] == "string");
        BOOST_TEST(&a2[1] == a1_1);
    }

BOOST_AUTO_TEST_SUITE_END() // assignment

BOOST_AUTO_TEST_SUITE(query)

    BOOST_AUTO_TEST_CASE(size)
    {
        json::array a;

        a.push_back(1);
        a.push_back(true);
        a.push_back("string");
        a.push_back(json::null);

        BOOST_TEST(a.size() == 4);
    }

    BOOST_AUTO_TEST_CASE(capacity)
    {
        json::array a;

        BOOST_TEST(a.capacity() == 0);

        a.push_back(1);
        BOOST_TEST(a.capacity() > 0);
    }

    BOOST_AUTO_TEST_CASE(empty)
    {
        json::array a;

        BOOST_TEST(a.empty());
    }

BOOST_AUTO_TEST_SUITE_END() // query

BOOST_AUTO_TEST_SUITE(accessor_)

    BOOST_AUTO_TEST_CASE(as_value_)
    {
        json::array a;
        a.push_back(1);

        auto& v = a.as_value();

        BOOST_TEST(v.is_array());
        BOOST_TEST(v.get_array()->at(0) == 1);
        BOOST_TEST(((void*)&v == (void*)&a));
    }

    BOOST_AUTO_TEST_CASE(as_value_const_)
    {
        json::array a;
        a.push_back(1);
        auto const& ac = a;

        auto const& v = ac.as_value();

        BOOST_TEST(v.is_array());
        BOOST_TEST(v.get_array()->at(0) == 1);
        BOOST_TEST(((void const*)&v == (void const*)&a));
    }

BOOST_AUTO_TEST_SUITE_END() // accessor_

BOOST_AUTO_TEST_SUITE(iterator)

    BOOST_AUTO_TEST_CASE(begin)
    {
        json::array a;

        a.push_back(10);

        BOOST_TEST(a.begin() == &a[0]);
    }

    BOOST_AUTO_TEST_CASE(end)
    {
        json::array a;

        a.push_back(10);

        BOOST_TEST(a.end() == &a[0] + 1);
    }

    BOOST_AUTO_TEST_CASE(const_begin)
    {
        json::array a;

        a.push_back(10);

        auto const& ca = a;

        BOOST_TEST(ca.begin() == &ca[0]);
    }

    BOOST_AUTO_TEST_CASE(const_end)
    {
        json::array a;

        a.push_back(10);

        auto const& ca = a;

        BOOST_TEST(ca.end() == &ca[0] + 1);
    }

    BOOST_AUTO_TEST_CASE(range_for)
    {
        json::array a;

        for (auto i = 0; i < 10; ++i) {
            a.push_back(i);
        }

        double sum = 0;
        for (auto& v: a) {
            sum += *v.get_number();
        }
        BOOST_TEST(sum == 45);
    }

BOOST_AUTO_TEST_SUITE_END() // iterator

BOOST_AUTO_TEST_SUITE(modifier)

    BOOST_AUTO_TEST_CASE(clear)
    {
        json::array a;

        for (auto i = 0; i < 10; ++i) {
            a.push_back(i);
        }

        a.clear();

        BOOST_TEST(a.empty());
        BOOST_TEST(a.capacity() > 0);
    }

    BOOST_AUTO_TEST_CASE(reserve)
    {
        json::array a;

        BOOST_TEST(a.capacity() == 0);

        a.reserve(100);

        BOOST_TEST(a.capacity() == 100);
    }

    BOOST_AUTO_TEST_CASE(push_back_copy)
    {
        auto const s = "string";
        json::array a;

        a.push_back(s);

        BOOST_REQUIRE(a.size() == 1);
        BOOST_TEST(a[0] == s);
        BOOST_TEST(a[0].get_string()->data() != static_cast<void const*>(s));
    }

    BOOST_AUTO_TEST_CASE(push_back_move)
    {
        // avoid short string optimization
        auto const s = "01234567890123456789012345678901234567890123456789";
        json::array a;
        json::value v = s;

        auto vptr = v.get_string()->data();

        a.push_back(std::move(v));

        BOOST_REQUIRE(a.size() == 1);
        BOOST_TEST(a[0] == s);
        BOOST_TEST((void*)(a[0].get_string()->data()) == (void*)(vptr));
    }

    BOOST_AUTO_TEST_CASE(erase_one)
    {
        json::array a;

        a.push_back(1);
        a.push_back(2);
        a.push_back(3);

        a.erase(a.begin());

        BOOST_REQUIRE(a.size() == 2);
        BOOST_TEST(a[0] == 2);
        BOOST_TEST(a[1] == 3);
    }

    BOOST_AUTO_TEST_CASE(erase_range)
    {
        json::array a;

        a.push_back(1);
        a.push_back(2);
        a.push_back(3);

        a.erase(a.begin(), a.begin() + 2);

        BOOST_REQUIRE(a.size() == 1);
        BOOST_TEST(a[0] == 3);
    }

BOOST_AUTO_TEST_SUITE_END() // modifier

BOOST_AUTO_TEST_SUITE(operator_)

    BOOST_AUTO_TEST_CASE(equal_to_array_)
    {
        json::array a1, a2;
        a1.push_back(1);
        a2.push_back(1);

        BOOST_CHECK_EQUAL(a1, a2);
    }

    BOOST_AUTO_TEST_CASE(not_equal_to_array_)
    {
        json::array a1, a2;
        a1.push_back(1);
        a2.push_back(2);

        BOOST_CHECK_NE(a1, a2);
    }

BOOST_AUTO_TEST_SUITE_END() // operator_

BOOST_AUTO_TEST_SUITE(stringify_)

    BOOST_AUTO_TEST_CASE(array_)
    {
        json::array a;
        a.push_back(1);

        BOOST_TEST(stringify(a) =="[1]");
    }

BOOST_AUTO_TEST_SUITE_END() // stringify_

BOOST_AUTO_TEST_SUITE_END() // array

} // namespace stream9::json::tesing

