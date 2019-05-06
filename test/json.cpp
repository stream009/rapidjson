#include <json/json.hpp>

#include <sstream>

#include <boost/test/unit_test.hpp>

namespace json::testing {

BOOST_AUTO_TEST_SUITE(json_)

BOOST_AUTO_TEST_SUITE(parse_)

    BOOST_AUTO_TEST_CASE(from_stream_)
    {
        std::stringstream ss;
        ss << R"({ "foo": "bar" })";

        auto const v = json::parse(ss);

        BOOST_ASSERT(v.is_object());
        auto const obj = v.get_object();

        BOOST_ASSERT(obj.contains("foo"));
        BOOST_TEST(obj["foo"] == "bar");
    }

BOOST_AUTO_TEST_SUITE_END() // parse_

BOOST_AUTO_TEST_SUITE_END() // json_

} // namespace json::testing
