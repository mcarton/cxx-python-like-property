// error: invalid initialization of reference of type ‘int&’
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
    int& cp = t.cst;
}

