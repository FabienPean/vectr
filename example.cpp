#include "vectr.h"
#include <vector>
#include <iostream>
struct X {
    static inline int n = 0;
    int x;
    X(int i) : x(i) { std::cout << "constructed-default" << std::endl; ++n; }
    X() { std::cout << "constructed-default" << std::endl; ++n; }
    X(X&& y) { std::cout << "constructed-move" << std::endl; x = y.x; ++n; }
    X& operator=(X&& y) { std::cout << "assign-move" << std::endl; x = y.x; ++n; return *this; }
    X(const X& y) { std::cout << "constructed-copy" << std::endl; x = y.x; ++n; }
    X& operator=(const X& y) { std::cout << "assign-copy" << std::endl; x = y.x; ++n; return *this; }
    ~X() { std::cout << "destroyed" << std::endl; --n; }
    operator int& () { return x; }
    operator const int& () const { return x; }
};
auto test(vectr::vecter&& vin) {
    vectr::vecter v;
    v = std::move(vin);
    assert(v.vector<X>(0) == 42);
}
auto test(vectr::vecter& vin) {
    vectr::vecter v(vin);
    assert(v.vector<X>(0) == 42);
}
int main() {
    {
        auto vd = vectr::vecter::create<X>();
        vd.vector<X>().push_back(42);
        assert(vd.vector<X>(0).x == 42);
        vd.vector<X>().push_back(3);
        assert(vd.vector<X>(0).x == 42);
        assert(vd.vector<X>(1) == 3);
        test(vd);
        test(std::move(vd));
        vd.vector<X>().push_back(23);
        assert(vd.vector<X>(0) == 23);
        vd.vector<X>().push_back(2);
        assert(vd.vector<X>(0) == 23);
        assert(vd.vector<X>(1) == 2);
    }
    {
        vectr::vecter va = vectr::vecter();
        va = vectr::vecter::create<X>();
        va.vector<X>().push_back(42);
        assert(X::n == 1);
    }
    assert(X::n == 0);

    auto vx = vectr::vecter::create<X>();
    vx.vector<X>().emplace_back(42);
    vx.vector<X>().emplace_back(404);
    auto&& x = vx.vector<X>().pop_back();
    assert(x.x == 404);
    vx.resize(6);
    assert(vx.capacity() == 8);


    return vx.vector<X>().size();
}