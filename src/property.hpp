#include <iosfwd>
#include <type_traits>

namespace py_property {
template <typename T, typename Get, typename, typename That>
class property_helper;

template <typename T, typename Get, typename That>
class property_helper<T, Get, void, That> {
protected:
    That& that;
    Get getter;

public:
    inline constexpr
    property_helper(const Get& getter_, That& that_)
    :   that(that_)
    ,   getter(getter_)
    {}

    inline constexpr
    operator T() const {
        return (that.*getter)();
    }

private:
    property_helper(const property_helper&) = delete;
    property_helper& operator=(const property_helper&) = delete;
};

template <typename T, typename Get, typename Set, typename That>
inline constexpr
auto operator*(const property_helper<T, Get, Set, That>& ph) -> decltype(*(T)ph) {
    return *(T)ph;
}

template <typename T, typename Get, typename Set, typename That>
class property_helper : public property_helper<T, Get, void, That> {
    Set setter;

public:
    inline constexpr
    property_helper(const Get& getter_, const Set& setter_, That& that_)
    :   property_helper<T, Get, void, That>(getter_, that_)
    ,   setter(setter_)
    {}

    inline
    property_helper<T, Get, Set, That>& operator=(const T& other) {
        (this->that.*setter)(other);
        return *this;
    }

#define py_property_helper_decl_friend_opeq_(op)                       \
    template <typename TT, typename UU,                                \
              typename GGet, typename SSet, typename TThat>            \
    friend                                                             \
    property_helper<TT, GGet, SSet, TThat>& operator op                \
        (property_helper<TT, GGet, SSet, TThat>& ph, const UU& other)

    py_property_helper_decl_friend_opeq_(+=);
    py_property_helper_decl_friend_opeq_(-=);
    py_property_helper_decl_friend_opeq_(*=);
    py_property_helper_decl_friend_opeq_(/=);
    py_property_helper_decl_friend_opeq_(%=);
    py_property_helper_decl_friend_opeq_(&=);
    py_property_helper_decl_friend_opeq_(|=);
    py_property_helper_decl_friend_opeq_(^=);
    py_property_helper_decl_friend_opeq_(>>=);
    py_property_helper_decl_friend_opeq_(<<=);
#undef property_helper_delc_friend_opeq_
};

#define py_property_helper_decl_opeq_(op)                                     \
template <typename T, typename U, typename Get, typename Set, typename That>  \
property_helper<T, Get, Set, That>& operator op                               \
    (property_helper<T, Get, Set, That>& ph, const U& other) {                \
    T t((ph.that.*(ph.getter))());                                            \
    return ph = (t op other);                                                 \
}

py_property_helper_decl_opeq_(+=)
py_property_helper_decl_opeq_(-=)
py_property_helper_decl_opeq_(*=)
py_property_helper_decl_opeq_(/=)
py_property_helper_decl_opeq_(%=)
py_property_helper_decl_opeq_(&=)
py_property_helper_decl_opeq_(|=)
py_property_helper_decl_opeq_(^=)
py_property_helper_decl_opeq_(>>=)
py_property_helper_decl_opeq_(<<=)
#undef property_helper_delc_opeq_

template <typename T, typename Get, typename Set, typename That>
bool operator==(const property_helper<T, Get, Set, That>& lhs, const T& rhs) {
    return ((T)lhs) == rhs;
}

template <typename T, typename Get, typename Set, typename That,
          typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(
        std::basic_ostream<CharT, Traits>& out,
        const property_helper<T, Get, Set, That>& rhs
        ) {
    return out << (T)rhs;
}

template <typename T, typename Get, typename Set, typename That,
          typename CharT, typename Traits>
std::basic_istream<CharT, Traits>& operator>>(
        std::basic_ostream<CharT, Traits>& out,
        property_helper<T, Get, Set, That>& rhs
        ) {
    T t; out >> t;
    rhs = t;
    return out;
}

#define make_property(Type, name, getter, setter, That)                      \
  py_property::property_helper<Type, decltype(&That::getter),                \
                        decltype(&That::setter), That>                       \
  name{&That::getter, &That::setter, *this}

#define make_const_property(Type, name, getter, That)                        \
  py_property::property_helper<Type, decltype(&That::getter), void, That>    \
  name{&That::getter, *this}

#if 0
// if we had http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2713
// we could write
// class Foo {
//     auto bar = make_property(int, getter, setter, Foo);
// };
#define make_property(Type, getter, setter, That)                      \
    property_helper<Type, decltype(&That::getter),                     \
                          decltype(&That::setter), That>               \
    (&That::getter, &That::setter, *this)

// and if we had decltype(*this) in this context
// we could write
// class Foo {
//     auto bar = make_property(int, getter, setter);
// };
#define make_property(Type, getter, setter)                                   \
    property_helper<Type, decltype(&decltype(*this)::getter),                 \
                          decltype(&decltype(*this)::setter), decltype(*this)>\
    (&ecltype(*this)::getter, &ecltype(*this)::setter, *this)
#endif

} // namespace py_property

