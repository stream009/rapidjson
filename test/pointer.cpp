#include <boost/test/unit_test.hpp>

#include <json/json.hpp>
#include <json/pointer.hpp>
#include <json/error.hpp>

#include <iostream> //TODO

namespace json::testing {

BOOST_AUTO_TEST_SUITE(pointer_)

BOOST_AUTO_TEST_SUITE(constructor_)

    BOOST_AUTO_TEST_CASE(copy_)
    {
        json::pointer const p1 { "/foo" };
        json::pointer const p2 { p1 };

        BOOST_TEST(p1 == p2);
    }

    BOOST_AUTO_TEST_CASE(move_)
    {
        json::pointer const p1 { "/foo" };
        json::pointer       p2 { p1 };
        json::pointer const p3 { std::move(p2) };

        BOOST_TEST(p1 == p3);
    }

    BOOST_AUTO_TEST_CASE(copy_assignment_)
    {
        json::pointer const p1 { "/foo" };
        json::pointer p2;

        p2 = p1;

        BOOST_TEST(p1 == p2);
    }

    BOOST_AUTO_TEST_CASE(move_assignment)
    {
        json::pointer const p1 { "/foo" };
        json::pointer       p2 { p1 };
        json::pointer       p3;

        p3 = std::move(p2);

        BOOST_TEST(p1 == p3);
    }

    BOOST_AUTO_TEST_CASE(error_)
    {
        BOOST_CHECK_THROW(
            []() { json::pointer p { "bar" }; }(),
            json::pointer_error
        );
    }

BOOST_AUTO_TEST_SUITE_END() // constructor_

BOOST_AUTO_TEST_SUITE(find_)

    BOOST_AUTO_TEST_CASE(const_)
    {
        json::pointer p { "/foo/bar" };
        auto const v1 = json::parse(R"({
            "foo": {
                "bar": 1
            }
        })");

        auto* const v2 = v1.find(p);
        BOOST_ASSERT(v2 != nullptr);

        BOOST_TEST(*v2 == 1);
    }

    BOOST_AUTO_TEST_CASE(non_const_)
    {
        json::pointer p { "/foo/bar" };
        auto v1 = json::parse(R"({
            "foo": {
                "bar": 1
            }
        })");

        auto* const v2 = v1.find(p);
        BOOST_ASSERT(v2 != nullptr);

        BOOST_TEST(*v2 == 1);
    }

BOOST_AUTO_TEST_SUITE_END() // find_

BOOST_AUTO_TEST_SUITE(via_)

    BOOST_AUTO_TEST_CASE(defined_)
    {
        json::pointer p { "/foo/bar" };
        auto const v1 = json::parse(R"({
            "foo": {
                "bar": 1
            }
        })");

        auto const& v2 = v1.via("/foo/bar");
        BOOST_TEST(!v2.is_undefined());
        BOOST_TEST(v2 == 1);
    }

    BOOST_AUTO_TEST_CASE(undefined_)
    {
        json::pointer p { "/foo/bar" };
        auto const v1 = json::parse(R"({
            "foo": {
                "bar": 1
            }
        })");

        auto const& v2 = v1.via("/foo/baz");
        BOOST_TEST(v2.is_undefined());
    }

BOOST_AUTO_TEST_SUITE_END() // via_

BOOST_AUTO_TEST_SUITE(at_)

    BOOST_AUTO_TEST_CASE(const_)
    {
        auto const v1 = json::parse(R"({
            "foo": {
                "bar": 1
            }
        })");

        json::pointer p { "/foo/bar" };

        auto const& v2 = v1.at(p);
        BOOST_TEST(v2 == 1);
    }

    BOOST_AUTO_TEST_CASE(non_const_)
    {
        auto v1 = json::parse(R"({
            "foo": {
                "bar": 1
            }
        })");

        json::pointer p { "/foo/bar" };

        auto const& v2 = v1.at(p);
        BOOST_TEST(v2 == 1);
    }

    BOOST_AUTO_TEST_CASE(out_of_range_)
    {
        auto const v1 = json::parse(R"({
            "foo": {
                "bar": 1
            }
        })");

        std::string const p = "/foo/baz";
        BOOST_CHECK_THROW(v1.at(p), std::out_of_range);
    }

BOOST_AUTO_TEST_SUITE_END() // at_

BOOST_AUTO_TEST_SUITE(subscript_)

    BOOST_AUTO_TEST_CASE(path_exists_)
    {
        auto v1 = json::parse(R"({
            "foo": {
                "bar": 1
            }
        })");

        json::pointer p { "/foo/bar" };

        BOOST_TEST(v1[p] == 1);
    }

    BOOST_AUTO_TEST_CASE(path_doesnt_exists_)
    {
        auto v1 = json::parse(R"({
            "foo": {
                "bar": 1
            }
        })");

        BOOST_TEST(v1["/foo/baz"] == json::null);

        auto const p = "/xyzzy";
        v1[p] = 2;
        BOOST_TEST(v1.at(p) == 2);
    }

BOOST_AUTO_TEST_SUITE_END() // operator[]_

BOOST_AUTO_TEST_SUITE(erase_)

    BOOST_AUTO_TEST_CASE(success_)
    {
        auto v1 = json::parse(R"({
            "foo": {
                "bar": 1
            }
        })");

        json::pointer const p { "/foo/bar" };

        v1.erase(p);
        BOOST_TEST(v1.find(p) == nullptr);
    }

    BOOST_AUTO_TEST_CASE(path_doesnt_exists_)
    {
        auto v1 = json::parse(R"({
            "foo": {
                "bar": 1
            }
        })");

        auto const v2 = v1;
        json::pointer const p { "/foo/baz" };

        v1.erase(p);
        BOOST_TEST(v1 == v2);
    }


BOOST_AUTO_TEST_SUITE_END() // erase_

BOOST_AUTO_TEST_SUITE(contains_)

    BOOST_AUTO_TEST_CASE(ok_)
    {
        auto v1 = json::parse(R"({
            "foo": {
                "bar": 1
            }
        })");

        BOOST_TEST(v1.contains("/foo"));
        BOOST_TEST(v1.contains("/foo/bar"));
        BOOST_TEST(!v1.contains("/foo/xyzzy"));
    }

BOOST_AUTO_TEST_SUITE_END() // contains_

BOOST_AUTO_TEST_SUITE(swap_)

    BOOST_AUTO_TEST_CASE(ok_)
    {
        json::pointer p1 { "/foo" };
        json::pointer p2 { "/bar" };

        BOOST_ASSERT(p1.to_string() == "/foo");
        BOOST_ASSERT(p2.to_string() == "/bar");

        p1.swap(p2);

        BOOST_ASSERT(p1.to_string() == "/bar");
        BOOST_ASSERT(p2.to_string() == "/foo");
    }

BOOST_AUTO_TEST_SUITE_END() // swap_

BOOST_AUTO_TEST_SUITE_END() // pointer_

} // namespace json::testing
