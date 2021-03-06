cxx-python-like-property
========================

This an useless project to show that we can have [python-like properties](http://docs.python.org/3/library/functions.html#property) in C++ (this requires C++11, clang 3.1 and g++ 4.7.2 compile it fine).

For example this python code:

    class C:
        def __init__(self):
            self._x = 0
    
        def getx(self):
            return self._x
    
        def setx(self, value):
            if value > 0:
                self._x = value
    
        def delx(self):
            del self._x
    
        x = property(getx, setx)

Is equivalent to this C++ code:

    class C {
        int m_x = 0;
    
    public:
        int get_x() const {
            return m_x;
        }
    
        void set_x(int value) {
            if(value > 0) {
                m_x = value;
            }
        }
    
        make_property(int, x, get_x, set_x, C);
    };

And then you can use `x` as if it was a public `int` member of the class C, but you will use transparently `get_x` and `set_x`.

    C c;
    std::cout << c.x << std::endl; // this prints "0"
    c.x = 42;
    std::cout << c.x << std::endl; // this prints "42"
    c.x = -12;
    std::cout << c.x << std::endl; // this prints "42"

