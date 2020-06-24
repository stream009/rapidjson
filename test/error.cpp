#include <boost/test/unit_test.hpp>

#include <stream9/json/error.hpp>
#include <stream9/json/json.hpp>
#include <stream9/json/pointer.hpp>

#include <iostream>

namespace stream9::json::tesing {

BOOST_AUTO_TEST_SUITE(parse_error_)

    void test(std::string_view const text,
              parse_errc const code,
              size_t const offset)
    {
        BOOST_CHECK_EXCEPTION(
            json::parse(text),
            parse_error,
            [&](auto const& ex) {
                //std::cout << ex.what() << "\n";
                BOOST_REQUIRE_EQUAL(ex.code(), code);
                BOOST_REQUIRE_EQUAL(ex.offset(), offset);
                return true;
            }
        );
    }

    BOOST_AUTO_TEST_CASE(document_empty)
    {
        test("", parse_errc::document_empty, 0);
    }

    BOOST_AUTO_TEST_CASE(document_root_not_singular)
    {
        test("true, false", parse_errc::document_root_not_singular, 4);
    }

    BOOST_AUTO_TEST_CASE(value_invalid)
    {
        test("foo", parse_errc::value_invalid, 1);
    }

    BOOST_AUTO_TEST_CASE(object_miss_name)
    {
        test("{ : 0 }", parse_errc::object_miss_name, 2);
    }

    BOOST_AUTO_TEST_CASE(object_miss_colon)
    {
        test("{ \"a\" 0 }", parse_errc::object_miss_colon, 6);
    }

    BOOST_AUTO_TEST_CASE(object_miss_comma_or_curly_bracket)
    {
        test("{ \"a\": 0 \"b\": 1 }",
             parse_errc::object_miss_comma_or_curly_bracket, 9);
    }

    BOOST_AUTO_TEST_CASE(array_miss_comma_or_square_bracket)
    {
        test("[ 0 1 ]",
             parse_errc::array_miss_comma_or_square_bracket, 4);
    }

    BOOST_AUTO_TEST_CASE(string_unicode_escape_invalid_hex)
    {
        test("\"\\u0\"",
             parse_errc::string_unicode_escape_invalid_hex, 1);
    }

    BOOST_AUTO_TEST_CASE(string_unicode_surrogate_invalid)
    {
        //test("\"\\uD834\\uDD1E\"",
        test("\"\\uD834\"",
             parse_errc::string_unicode_surrogate_invalid, 1);
    }

    BOOST_AUTO_TEST_CASE(string_escape_invalid)
    {
        test("\"\\g\"",
             parse_errc::string_escape_invalid, 1);
    }

    BOOST_AUTO_TEST_CASE(string_miss_quotation_mark)
    {
        test("\"string",
             parse_errc::string_miss_quotation_mark, 7);
    }

    BOOST_AUTO_TEST_CASE(string_invalid_encoding)
    {
        test("\"\x1b\"",
             parse_errc::string_invalid_encoding, 1);
    }

    BOOST_AUTO_TEST_CASE(number_too_big)
    {
        test("2e+999",
             parse_errc::number_too_big, 0);
    }

    BOOST_AUTO_TEST_CASE(number_miss_fraction)
    {
        test("2.",
             parse_errc::number_miss_fraction, 2);
    }

    BOOST_AUTO_TEST_CASE(number_miss_exponent)
    {
        test("2e",
             parse_errc::number_miss_exponent, 2);
    }

    BOOST_AUTO_TEST_CASE(termination)
    {
        // wont happen
    }

    BOOST_AUTO_TEST_CASE(unspecific_syntax_error)
    {
        // wont happen
    }

BOOST_AUTO_TEST_SUITE_END() // parse_error

BOOST_AUTO_TEST_SUITE(pointer_error_)

    void test(std::string_view const pointer,
              pointer_errc const code,
              size_t const offset)
    {
        json::value v;
        BOOST_CHECK_EXCEPTION(
            v.find(pointer),
            pointer_error,
            [&](auto const& ex) {
                //std::cout << ex.what() << "\n";
                BOOST_REQUIRE_EQUAL(ex.code(), code);
                BOOST_REQUIRE_EQUAL(ex.offset(), offset);
                return true;
            }
        );
    }

    BOOST_AUTO_TEST_CASE(token_must_begin_with_solidus)
    {
        test("foo",
             pointer_errc::token_must_begin_with_solidus, 0);
    }

    BOOST_AUTO_TEST_CASE(invalid_escape)
    {
        test("/~2",
             pointer_errc::invalid_escape, 2);
    }

    BOOST_AUTO_TEST_CASE(invalid_percent_encoding)
    {
        test("#/%C3%28", // invalid utf8 sequence
             pointer_errc::invalid_percent_encoding, 2);
    }

    BOOST_AUTO_TEST_CASE(character_must_percent_encode)
    {
        test("#/\x02",
             pointer_errc::character_must_percent_encode, 2);
    }

BOOST_AUTO_TEST_SUITE_END() // pointer_error_

} // namespace stream9::json::tesing
