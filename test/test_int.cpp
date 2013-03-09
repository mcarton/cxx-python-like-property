#include "../src/property.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

class Test {
public:
    int m_mut;
    int m_mut2;
    int m_cst;
    int m_cst2;

public:
    Test() : m_mut(0), m_mut2(0), m_cst(0), m_cst2(0) {}

    const int& get_mut() const {
        return m_mut;
    }

    void set_mut(int v) {
        m_mut = v;
    }

    int get_mut2() const {
        return m_mut2+2;
    }

    void set_mut2(int v) {
        m_mut2 = v-3;
    }

    int get_cst() const {
        return m_cst;
    }

    int get_cst2() const {
        return m_cst2+6;
    }

    make_property(int, mut, get_mut, set_mut, Test);
    make_property(int, mut2, get_mut2, set_mut2, Test);
    make_const_property(int, cst, get_cst, Test);
    make_const_property(int, cst2, get_cst2, Test);
};

struct Fixture {
    Test test;
};

void equal(int lhs, int rhs) {
    BOOST_CHECK_EQUAL(lhs, rhs);
}

BOOST_FIXTURE_TEST_SUITE(test_int, Fixture)

BOOST_AUTO_TEST_CASE( test_mut ) {
    BOOST_CHECK_EQUAL(test.m_mut, 0);
    BOOST_CHECK_EQUAL(test.mut, 0);
    equal(test.mut, 0);

    test.mut = 6;
    BOOST_CHECK_EQUAL(test.m_mut, 6);
    BOOST_CHECK_EQUAL(test.mut, 6);

    test.mut *= 7;
    BOOST_CHECK_EQUAL(test.m_mut, 42);
    BOOST_CHECK_EQUAL(test.mut, 42);
}

BOOST_AUTO_TEST_CASE( test_cst ) {
    BOOST_CHECK_EQUAL(test.m_cst, 0);
    BOOST_CHECK_EQUAL(test.cst, 0);
    equal(test.cst, 0);
}

BOOST_AUTO_TEST_CASE( test_mut2 ) {
    BOOST_CHECK_EQUAL(test.m_mut2, 0);
    BOOST_CHECK_EQUAL(test.mut2, 2);
    equal(test.mut2, 2);

    test.mut2 = 6;
    BOOST_CHECK_EQUAL(test.m_mut2, 3);
    BOOST_CHECK_EQUAL(test.mut2, 5);

    test.mut2 *= 7;
    BOOST_CHECK_EQUAL(test.m_mut2, 32);
    BOOST_CHECK_EQUAL(test.mut2, 34);
}

BOOST_AUTO_TEST_CASE( test_cst2 ) {
    BOOST_CHECK_EQUAL(test.m_cst2, 0);
    BOOST_CHECK_EQUAL(test.cst2, 6);
    equal(test.cst2, 6);
}

BOOST_AUTO_TEST_SUITE_END()

