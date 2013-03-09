cxx-python-like-property
========================

This an useless project to show that we can have (python-like properties)[http://docs.python.org/3/library/functions.html#property] in C++[^cxx11].

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

[^cxx11]: This requires C++11, clang 3.1 and g++ 4.7.2 compile it fine.
