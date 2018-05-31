#include <boost/test/unit_test.hpp>

#include <json/object.hpp>
#include <json/value.hpp>

#include <iostream>

namespace json {

std::ostream&
operator<<(std::ostream& os, object::iterator const& it)
{
    if (it == object::iterator()) {
        os << &it << " (end)";
    }
    else {
        os << &it;
    }

    return os;
}

std::ostream&
operator<<(std::ostream& os, object::const_iterator const& it)
{
    if (it == object::iterator()) {
        os << &it << " (end)";
    }
    else {
        os << &it;
    }

    return os;
}

} // namespace json

namespace json::testing {

BOOST_AUTO_TEST_SUITE(object)

BOOST_AUTO_TEST_SUITE(constructor)

    BOOST_AUTO_TEST_CASE(default_)
    {
        json::object o;

        BOOST_TEST(o.empty());
        BOOST_TEST(o.capacity() == 0);
    }

    BOOST_AUTO_TEST_CASE(copy)
    {
        json::object o1;

        auto const s = "long_long_long_long_long_long_long_long_long_long_long_string";
        o1["foo"] = true;
        o1["bar"] = s;

        auto o1_ptr = o1["bar"].get_string().data();
        auto o2 = o1;

        BOOST_TEST(o2.size() == 2);
        BOOST_TEST(o2["foo"] == true);
        BOOST_TEST(o2["bar"] == s);
        BOOST_TEST(o2["bar"].get_string().data() != (void*)o1_ptr);
    }

    BOOST_AUTO_TEST_CASE(move)
    {
        json::object o1;

        auto const s = "long_long_long_long_long_long_long_long_long_long_long_string";
        o1["foo"] = true;
        o1["bar"] = s;

        auto o1_ptr = o1["bar"].get_string().data();
        auto o2 = std::move(o1);

        BOOST_TEST(o2.size() == 2);
        BOOST_TEST(o2["foo"] == true);
        BOOST_TEST(o2["bar"] == s);
        BOOST_TEST(o2["bar"].get_string().data() == (void*)o1_ptr);
    }

BOOST_AUTO_TEST_SUITE_END() // constructor

BOOST_AUTO_TEST_SUITE(assignment)

    BOOST_AUTO_TEST_CASE(copy)
    {
        json::object o1;

        auto const s = "long_long_long_long_long_long_long_long_long_long_long_string";
        o1["foo"] = true;
        o1["bar"] = s;

        auto o1_ptr = o1["bar"].get_string().data();

        json::object o2;
        o2 = o1;

        BOOST_TEST(o2.size() == 2);
        BOOST_TEST(o2["foo"] == true);
        BOOST_TEST(o2["bar"] == s);
        BOOST_TEST(o2["bar"].get_string().data() != (void*)o1_ptr);
    }

    BOOST_AUTO_TEST_CASE(move)
    {
        json::object o1;

        auto const s = "long_long_long_long_long_long_long_long_long_long_long_string";
        o1["foo"] = true;
        o1["bar"] = s;

        auto o1_ptr = o1["bar"].get_string().data();

        json::object o2;
        o2 = std::move(o1);

        BOOST_TEST(o2.size() == 2);
        BOOST_TEST(o2["foo"] == true);
        BOOST_TEST(o2["bar"] == s);
        BOOST_TEST(o2["bar"].get_string().data() == (void*)o1_ptr);
    }

BOOST_AUTO_TEST_SUITE_END() // assignment

BOOST_AUTO_TEST_SUITE(query)

    BOOST_AUTO_TEST_CASE(size)
    {
        json::object o;

        o["one"] = 1;
        o["two"] = 2;
        o["three"] = 3;

        BOOST_TEST(o.size() == 3);
    }

    BOOST_AUTO_TEST_CASE(capacity)
    {
        json::object o;

        BOOST_TEST(o.capacity() == 0);

        o["one"] = 1;
        o["two"] = 2;
        o["three"] = 3;

        BOOST_TEST(o.capacity() > 0);
    }

    BOOST_AUTO_TEST_CASE(empty)
    {
        json::object o;

        BOOST_TEST(o.empty());
    }

    BOOST_AUTO_TEST_CASE(contain)
    {
        json::object o;

        o["foo"] = true;
        o["bar"] = false;

        BOOST_TEST(o.contain("foo"));
        BOOST_TEST(!o.contain("xyzzy"));
    }

BOOST_AUTO_TEST_SUITE_END() // query

BOOST_AUTO_TEST_SUITE(accessor)

    BOOST_AUTO_TEST_CASE(at)
    {
        json::object o;

        o["foo"] = 1;

        BOOST_TEST(o.at("foo") == 1);
    }

    BOOST_AUTO_TEST_CASE(at_const)
    {
        json::object o;

        o["foo"] = 1;

        auto const oc = o;

        BOOST_TEST(oc.at("foo") == 1);
    }

    BOOST_AUTO_TEST_CASE(brace)
    {
        json::object o;

        o["foo"] = 1;
        BOOST_TEST(o["foo"] == 1);

        o["foo"] = 2;
        BOOST_TEST(o["foo"] == 2);
    }

    BOOST_AUTO_TEST_CASE(brace_const)
    {
        json::object o;

        o["foo"] = 1;
        auto oc = o;
        BOOST_TEST(oc["foo"] == 1);
    }

BOOST_AUTO_TEST_SUITE_END() // accessor

BOOST_AUTO_TEST_SUITE(iterator_)

    BOOST_AUTO_TEST_CASE(begin)
    {
        json::object o;

        o["foo"] = "bar";

        auto it = o.begin();

        BOOST_TEST(it->name == "foo");
        BOOST_TEST(it->value == "bar");
    }

    BOOST_AUTO_TEST_CASE(end)
    {
        json::object o;

        o["foo"] = "bar";

        auto i = o.begin();
        auto e = o.end();

        BOOST_TEST(i != e);
        BOOST_TEST(++i == e);
    }

    BOOST_AUTO_TEST_CASE(begin_const)
    {
        json::object o;

        o["foo"] = "bar";

        auto const& oc = o;

        auto it = oc.begin();

        BOOST_TEST(it->name == "foo");
        BOOST_TEST(it->value == "bar");
    }

    BOOST_AUTO_TEST_CASE(end_const)
    {
        json::object o;

        o["foo"] = "bar";

        auto const& oc = o;

        auto i = oc.begin();
        auto e = oc.end();

        BOOST_TEST(i != e);
        BOOST_TEST(++i == e);
    }

BOOST_AUTO_TEST_SUITE_END() // iterator_

BOOST_AUTO_TEST_SUITE(lookup)

    BOOST_AUTO_TEST_CASE(find)
    {
        json::object o;

        o["foo"] = 1;
        o["bar"] = false;

        auto it1 = o.find("foo");

        BOOST_TEST(it1 == o.begin());

        auto it2 = o.find("xyzzy");

        BOOST_TEST(it2 == o.end());
    }

    BOOST_AUTO_TEST_CASE(find_const)
    {
        json::object o;

        o["foo"] = 1;
        o["bar"] = false;

        auto const& oc = o;

        auto it1 = oc.find("foo");

        BOOST_TEST(it1 == oc.begin());

        auto it2 = oc.find("xyzzy");

        BOOST_TEST(it2 == oc.end());
    }

BOOST_AUTO_TEST_SUITE_END() // lookup

BOOST_AUTO_TEST_SUITE(modifier)

    BOOST_AUTO_TEST_CASE(clear)
    {
        json::object o;

        o["foo"] = 1;
        o.clear();

        BOOST_TEST(o.empty());
        BOOST_TEST(o.capacity() > 0);
    }

    BOOST_AUTO_TEST_CASE(reserve)
    {
        json::object o;

        o.reserve(100);

        BOOST_TEST(o.empty());
        BOOST_TEST(o.capacity() == 100);
    }

    BOOST_AUTO_TEST_CASE(erase_one)
    {
        json::object o;

        o["one"] = 1;
        o["two"] = 2;
        o["three"] = 3;

        auto i = o.begin() + 1;

        o.erase(i);

        BOOST_TEST(o.size() == 2);
        BOOST_TEST(o.find("two") == o.end());
    }

    BOOST_AUTO_TEST_CASE(erase_range)
    {
        json::object o;

        o["one"] = 1;
        o["two"] = 2;
        o["three"] = 3;
        o["four"] = 4;

        auto i1 = o.begin() + 1;
        auto i2 = o.begin() + 3;

        o.erase(i1, i2);

        BOOST_TEST(o.size() == 2);
        BOOST_TEST(o.find("one") != o.end());
        BOOST_TEST(o.find("two") == o.end());
        BOOST_TEST(o.find("three") == o.end());
        BOOST_TEST(o.find("four") != o.end());
    }

    BOOST_AUTO_TEST_CASE(erase_by_key)
    {
        json::object o;

        o["one"] = 1;
        o["two"] = 2;
        o["three"] = 3;

        BOOST_TEST(!o.erase("four"));

        BOOST_TEST(o.erase("two"));
        BOOST_TEST(o.size() == 2);
        BOOST_TEST(o.find("two") == o.end());
    }

BOOST_AUTO_TEST_SUITE_END() // modifier

BOOST_AUTO_TEST_SUITE_END() // object

BOOST_AUTO_TEST_SUITE(object_iterator)

BOOST_AUTO_TEST_SUITE(constructor)

    BOOST_AUTO_TEST_CASE(default_)
    {
        json::object o;
        json::object::iterator i;

        BOOST_TEST(i == o.end());
    }

    BOOST_AUTO_TEST_CASE(copy)
    {
        json::object o;

        o["foo"] = 1;
        o["bar"] = 2;

        auto i1 = o.begin();
        auto i2 = i1;

        BOOST_TEST(i1 == i2);
    }

BOOST_AUTO_TEST_SUITE_END() // constructor

BOOST_AUTO_TEST_SUITE(accessor)

    BOOST_AUTO_TEST_CASE(dereference)
    {
        json::object o;
        o["foo"] = 1;

        auto i = o.begin();
        auto& member = *i;

        BOOST_TEST(member.name == "foo");
        BOOST_TEST(member.value == 1);
    }

    BOOST_AUTO_TEST_CASE(pointer)
    {
        json::object o;
        o["foo"] = 1;

        auto i = o.begin();

        BOOST_TEST(i->name == "foo");
        BOOST_TEST(i->value == 1);
    }

    BOOST_AUTO_TEST_CASE(subscript)
    {
        json::object o;
        o["foo"] = 1;
        o["bar"] = 2;

        auto i = o.begin();

        BOOST_TEST(&i[0] == &*(o.begin() + 0));
        BOOST_TEST(&i[1] == &*(o.begin() + 1));
    }

BOOST_AUTO_TEST_SUITE_END() // accessor

BOOST_AUTO_TEST_SUITE(modifier)

    BOOST_AUTO_TEST_CASE(increment)
    {
        json::object o;
        o["foo"] = 1;
        o["bar"] = 2;

        auto i = o.begin();

        BOOST_TEST(i->name == "foo");
        ++i;
        BOOST_TEST(i->name == "bar");
    }

    BOOST_AUTO_TEST_CASE(decrement)
    {
        json::object o;
        o["foo"] = 1;
        o["bar"] = 2;

        auto i = o.begin() + 1;

        BOOST_TEST(i->name == "bar");
        --i;
        BOOST_TEST(i->name == "foo");
    }

    BOOST_AUTO_TEST_CASE(increment_post)
    {
        json::object o;
        o["foo"] = 1;
        o["bar"] = 2;

        auto i = o.begin();

        BOOST_TEST(i->name == "foo");
        BOOST_TEST((i++)->name == "foo");
        BOOST_TEST(i->name == "bar");
    }

    BOOST_AUTO_TEST_CASE(decrement_post)
    {
        json::object o;
        o["foo"] = 1;
        o["bar"] = 2;

        auto i = o.begin() + 1;

        BOOST_TEST(i->name == "bar");
        BOOST_TEST((i--)->name == "bar");
        BOOST_TEST(i->name == "foo");
    }

BOOST_AUTO_TEST_SUITE_END() // modifier

BOOST_AUTO_TEST_SUITE(operator_)

    BOOST_AUTO_TEST_CASE(increment_n)
    {
        json::object o;
        o["foo"] = 1;
        o["bar"] = 2;
        o["xyzzy"] = 3;

        auto i = o.begin();

        BOOST_TEST(i->name == "foo");
        i += 2;
        BOOST_TEST(i->name == "xyzzy");
    }

    BOOST_AUTO_TEST_CASE(decrement_n)
    {
        json::object o;
        o["foo"] = 1;
        o["bar"] = 2;
        o["xyzzy"] = 3;

        auto i = o.begin() + 2;

        BOOST_TEST(i->name == "xyzzy");
        i -= 2;
        BOOST_TEST(i->name == "foo");
    }

    BOOST_AUTO_TEST_CASE(diff)
    {
        json::object o;
        o["foo"] = 1;
        o["bar"] = 2;
        o["xyzzy"] = 3;

        BOOST_TEST(o.end() - o.begin() == 3);
    }

BOOST_AUTO_TEST_SUITE_END() // operator_

BOOST_AUTO_TEST_SUITE(comparator)

    BOOST_AUTO_TEST_CASE(equal)
    {
        json::object o;
        o["foo"] = 1;

        auto i1 = o.begin() + 1;
        auto i2 = o.end();

        BOOST_TEST(i1 == i2);
    }

    BOOST_AUTO_TEST_CASE(not_equal)
    {
        json::object o;
        o["foo"] = 1;

        auto i1 = o.begin();
        auto i2 = o.end();

        BOOST_TEST(i1 != i2);
    }

    BOOST_AUTO_TEST_CASE(less_than)
    {
        json::object o;
        o["foo"] = 1;

        auto i1 = o.begin();
        auto i2 = o.end();

        BOOST_TEST(i1 < i2);
    }

    BOOST_AUTO_TEST_CASE(grater_than)
    {
        json::object o;
        o["foo"] = 1;

        auto i1 = o.end();
        auto i2 = o.begin();

        BOOST_TEST(i1 > i2);
    }

    BOOST_AUTO_TEST_CASE(less_or_equal)
    {
        json::object o;
        o["foo"] = 1;

        auto i1 = o.begin();
        auto i2 = o.end();
        auto i3 = o.end();

        BOOST_TEST(i1 <= i2);
        BOOST_TEST(i2 <= i3);
        BOOST_TEST(i3 <= i2);
    }

    BOOST_AUTO_TEST_CASE(grater_or_equal)
    {
        json::object o;
        o["foo"] = 1;

        auto i1 = o.end();
        auto i2 = o.begin();
        auto i3 = o.begin();

        BOOST_TEST(i1 >= i2);
        BOOST_TEST(i2 >= i3);
        BOOST_TEST(i3 >= i2);
    }

BOOST_AUTO_TEST_SUITE_END() // comparator

BOOST_AUTO_TEST_SUITE_END() // object_iterator

BOOST_AUTO_TEST_SUITE(object_const_iterator)

BOOST_AUTO_TEST_SUITE(constructor)

    BOOST_AUTO_TEST_CASE(default_)
    {
        json::object const o;
        json::object::const_iterator i;

        BOOST_TEST(i == o.end());
    }

    BOOST_AUTO_TEST_CASE(copy)
    {
        json::object o;

        o["foo"] = 1;

        auto const& oc = o;

        auto i1 = oc.begin();
        auto i2 = i1;

        BOOST_TEST(i1 == i2);
    }

    BOOST_AUTO_TEST_CASE(conversion)
    {
        json::object o;

        o["foo"] = 1;

        json::object::iterator i1 = o.begin();
        json::object::const_iterator i2 = i1;

        BOOST_TEST(i1 == i2);
    }

BOOST_AUTO_TEST_SUITE_END() // constructor

BOOST_AUTO_TEST_SUITE(accessor)

    BOOST_AUTO_TEST_CASE(dereference)
    {
        json::object o;
        o["foo"] = 1;

        auto const& oc = o;

        auto i = oc.begin();
        auto& member = *i;

        static_assert(std::is_same_v<decltype(member), json::object::member const&>);
        BOOST_TEST(member.name == "foo");
        BOOST_TEST(member.value == 1);
    }

    BOOST_AUTO_TEST_CASE(pointer)
    {
        json::object o;
        o["foo"] = 1;

        auto const& oc = o;

        auto i = oc.begin();

        BOOST_TEST(i->name == "foo");
        BOOST_TEST(i->value == 1);
    }

    BOOST_AUTO_TEST_CASE(subscript)
    {
        json::object o;
        o["foo"] = 1;
        o["bar"] = 2;

        auto const& oc = o;

        auto i = oc.begin();

        BOOST_TEST(&i[0] == &*(oc.begin() + 0));
        BOOST_TEST(&i[1] == &*(oc.begin() + 1));
    }

BOOST_AUTO_TEST_SUITE_END() // accessor

BOOST_AUTO_TEST_SUITE(modifier)

    BOOST_AUTO_TEST_CASE(increment)
    {
        json::object o;
        o["foo"] = 1;
        o["bar"] = 2;

        auto const& oc = o;

        auto i = oc.begin();

        BOOST_TEST(i->name == "foo");
        ++i;
        BOOST_TEST(i->name == "bar");
    }

    BOOST_AUTO_TEST_CASE(decrement)
    {
        json::object o;
        o["foo"] = 1;
        o["bar"] = 2;

        auto const& oc = o;

        auto i = oc.begin() + 1;

        BOOST_TEST(i->name == "bar");
        --i;
        BOOST_TEST(i->name == "foo");
    }

    BOOST_AUTO_TEST_CASE(increment_post)
    {
        json::object o;
        o["foo"] = 1;
        o["bar"] = 2;

        auto const& oc = o;

        auto i = oc.begin();

        BOOST_TEST(i->name == "foo");
        BOOST_TEST((i++)->name == "foo");
        BOOST_TEST(i->name == "bar");
    }

    BOOST_AUTO_TEST_CASE(decrement_post)
    {
        json::object o;
        o["foo"] = 1;
        o["bar"] = 2;

        auto const& oc = o;

        auto i = oc.begin() + 1;

        BOOST_TEST(i->name == "bar");
        BOOST_TEST((i--)->name == "bar");
        BOOST_TEST(i->name == "foo");
    }

BOOST_AUTO_TEST_SUITE_END() // modifier

BOOST_AUTO_TEST_SUITE(operator_)

    BOOST_AUTO_TEST_CASE(increment_n)
    {
        json::object o;
        o["foo"] = 1;
        o["bar"] = 2;
        o["xyzzy"] = 3;

        auto const& oc = o;

        auto i = oc.begin();

        BOOST_TEST(i->name == "foo");
        i += 2;
        BOOST_TEST(i->name == "xyzzy");
    }

    BOOST_AUTO_TEST_CASE(decrement_n)
    {
        json::object o;
        o["foo"] = 1;
        o["bar"] = 2;
        o["xyzzy"] = 3;

        auto const& oc = o;

        auto i = oc.begin() + 2;

        BOOST_TEST(i->name == "xyzzy");
        i -= 2;
        BOOST_TEST(i->name == "foo");
    }

    BOOST_AUTO_TEST_CASE(diff)
    {
        json::object o;
        o["foo"] = 1;
        o["bar"] = 2;
        o["xyzzy"] = 3;

        auto const& oc = o;

        BOOST_TEST(oc.end() - oc.begin() == 3);
    }

BOOST_AUTO_TEST_SUITE_END() // operator_

BOOST_AUTO_TEST_SUITE(comparator)

    BOOST_AUTO_TEST_CASE(equal)
    {
        json::object o;
        o["foo"] = 1;

        auto const& oc = o;

        auto i1 = oc.begin() + 1;
        auto i2 = oc.end();

        BOOST_TEST(i1 == i2);
    }

    BOOST_AUTO_TEST_CASE(not_equal)
    {
        json::object o;
        o["foo"] = 1;

        auto const& oc = o;

        auto i1 = oc.begin();
        auto i2 = oc.end();

        BOOST_TEST(i1 != i2);
    }

    BOOST_AUTO_TEST_CASE(less_than)
    {
        json::object o;
        o["foo"] = 1;

        auto const& oc = o;

        auto i1 = oc.begin();
        auto i2 = oc.end();

        BOOST_TEST(i1 < i2);
    }

    BOOST_AUTO_TEST_CASE(grater_than)
    {
        json::object o;
        o["foo"] = 1;

        auto const& oc = o;

        auto i1 = oc.end();
        auto i2 = oc.begin();

        BOOST_TEST(i1 > i2);
    }

    BOOST_AUTO_TEST_CASE(less_or_equal)
    {
        json::object o;
        o["foo"] = 1;

        auto const& oc = o;

        auto i1 = oc.begin();
        auto i2 = oc.end();
        auto i3 = oc.end();

        BOOST_TEST(i1 <= i2);
        BOOST_TEST(i2 <= i3);
        BOOST_TEST(i3 <= i2);
    }

    BOOST_AUTO_TEST_CASE(grater_or_equal)
    {
        json::object o;
        o["foo"] = 1;

        auto const& oc = o;

        auto i1 = oc.end();
        auto i2 = oc.begin();
        auto i3 = oc.begin();

        BOOST_TEST(i1 >= i2);
        BOOST_TEST(i2 >= i3);
        BOOST_TEST(i3 >= i2);
    }

BOOST_AUTO_TEST_SUITE_END() // comparator

BOOST_AUTO_TEST_SUITE_END() // object_iterator

} // namespace json::testing
