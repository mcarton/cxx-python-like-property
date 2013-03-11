#include "../src/python_like_property.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <boost/utility.hpp>
struct Noncopyable : boost::noncopyable {
    int value = 0;
};

class Test_Noncopyable {
public:
    Noncopyable m_mut;
    Noncopyable m_cst;

public:
    Test_Noncopyable() : m_mut(), m_cst() {}

    const Noncopyable& get_mut() const {
        return m_mut;
    }

    void set_mut(const Noncopyable&) {
        m_mut.value = 1;
    }

    const Noncopyable& get_cst() const {
        return m_cst;
    }

    make_property(const Noncopyable&, mut, get_mut, set_mut, Test_Noncopyable);
    make_const_property(const Noncopyable&, cst, get_cst, Test_Noncopyable);
};

struct Fixture_Noncopyable {
    Test_Noncopyable test;
};

void f(const Noncopyable&) {
}

BOOST_FIXTURE_TEST_SUITE(test_uncopyable, Fixture_Noncopyable)

BOOST_AUTO_TEST_CASE( test_mut ) {
    BOOST_CHECK_EQUAL(test.m_mut.value, 0);
    BOOST_CHECK_EQUAL(static_cast<const Noncopyable&>(test.mut).value, 0);
    f(test.mut);

    test.mut = Noncopyable(); // this look weird but is ok because of set_mut
    BOOST_CHECK_EQUAL(test.m_mut.value, 1);
    BOOST_CHECK_EQUAL(static_cast<const Noncopyable&>(test.mut).value, 1);
}

BOOST_AUTO_TEST_CASE( test_cst ) {
    BOOST_CHECK_EQUAL(test.m_cst.value, 0);
    BOOST_CHECK_EQUAL(static_cast<const Noncopyable&>(test.cst).value, 0);
    f(test.cst);
}

BOOST_AUTO_TEST_SUITE_END()

