// error: use of deleted function
#include "../src/property.hpp"

class Test {
public:
    int m_cst;

public:
    Test() : m_cst(0) {}

    int get_cst() const {
        return m_cst;
    }

    make_const_property(int, cst, get_cst, Test);
};

void test() {
    Test t;
    auto cp = t.cst;
}

