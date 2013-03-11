#include "../src/python_like_property.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <string>

using std::string;

class Test_string {
public:
    string m_mut;
    string m_mut2;
    string m_cst;
    string m_cst2;

public:
    Test_string() : m_mut(), m_mut2(), m_cst("foo"), m_cst2("bar") {}

    const string& get_mut() const {
        return m_mut;
    }

    void set_mut(const string& v) {
        m_mut = v;
    }

    string get_mut2() const {
        return m_mut2+"baz";
    }

    void set_mut2(const string& v) {
        m_mut2 = v+"quz";
    }

    const string& get_cst() const {
        return m_cst;
    }

    string get_cst2() const {
        return m_cst2+"baz";
    }

    make_property(string, mut, get_mut, set_mut, Test_string);
    make_property(string, mut2, get_mut2, set_mut2, Test_string);
    make_const_property(string, cst, get_cst, Test_string);
    make_const_property(string, cst2, get_cst2, Test_string);
};

struct Fixture_string {
    Test_string test;
};

BOOST_FIXTURE_TEST_SUITE(test_string, Fixture_string)

BOOST_AUTO_TEST_CASE( test_mut ) {
    BOOST_CHECK_EQUAL(test.m_mut, string());
    BOOST_CHECK_EQUAL(test.mut, string());

    test.mut = "foo";
    BOOST_CHECK_EQUAL(test.m_mut, string("foo"));
    BOOST_CHECK_EQUAL(test.mut, string("foo"));

    test.mut += "bar";
    BOOST_CHECK_EQUAL(test.m_mut, string("foobar"));
    BOOST_CHECK_EQUAL(test.mut, string("foobar"));
}

BOOST_AUTO_TEST_CASE( test_cst ) {
    BOOST_CHECK_EQUAL(test.m_cst, string("foo"));
    BOOST_CHECK_EQUAL(test.cst, string("foo"));
}

BOOST_AUTO_TEST_CASE( test_mut2 ) {
    BOOST_CHECK_EQUAL(test.m_mut2, string());
    BOOST_CHECK_EQUAL(test.mut2, string("baz"));

    test.mut2 = "foo";
    BOOST_CHECK_EQUAL(test.m_mut2, string("fooquz"));
    BOOST_CHECK_EQUAL(test.mut2, string("fooquzbaz"));

    test.mut2 += "bar";
    BOOST_CHECK_EQUAL(test.m_mut2, string("fooquzbazbarquz"));
    BOOST_CHECK_EQUAL(test.mut2, string("fooquzbazbarquzbaz"));
}

BOOST_AUTO_TEST_CASE( test_cst2 ) {
    BOOST_CHECK_EQUAL(test.m_cst2, string("bar"));
    BOOST_CHECK_EQUAL(test.cst2, string("barbaz"));
}

BOOST_AUTO_TEST_SUITE_END()


