#include <iostream>

class Base {
protected:
    int dat;
    double a[5] = {10, 1, 7, 1, 9};
public:
    Base() : dat(1) {}
    Base(int d) : dat(d) {}
};

class D1 : protected Base {
protected:
    int d1;
public:
    D1() : d1(1) {}
    D1(int d, int dt) : Base(dt), d1(d) {}
};

class D2 : protected Base {
protected:
    double d2;
public:
    D2() : d2(1) {}
    D2(int d, double dt) : Base(d), d2(dt) {}
};

class D3 : protected D1 {
protected:
    float d3;
public:
    D3() : d3(1.0f) {}
    D3(int a, int b, float c) : D1(a, b), d3(c) {}
};

class D4 : protected D2 {
protected:
    char d4;
public:
    D4() : d4('A') {}
    D4(int a, double b, char c) : D2(a, b), d4(c) {}
};

class R : protected D3, protected D4 {
protected:
    double dt;
public:
    R() : dt(1.0) {}
    R(int a, int b, float c, int d, double e, char f)
        : D3(a, b, c), D4(d, e, f), dt(2.0) {}
    void showDat() {
        std::cout << "Non-virtual: dat is ambiguous due to multiple Base copies.\n";
    }
};

class BaseV {
protected:
    int dat;
    double a[5] = {10, 1, 7, 1, 9};
public:
    BaseV() : dat(1) {}
    BaseV(int d) : dat(d) {}
};

class D1V : virtual protected BaseV {
protected:
    int d1;
public:
    D1V() : d1(1) {}
    D1V(int d, int dt) : BaseV(dt), d1(d) {}
};

class D2V : virtual protected BaseV {
protected:
    double d2;
public:
    D2V() : d2(1) {}
    D2V(int d, double dt) : BaseV(d), d2(dt) {}
};

class D3V : protected D1V {
protected:
    float d3;
public:
    D3V() : d3(1.0f) {}
    D3V(int a, int b, float c) : D1V(a, b), d3(c) {}
};

class D4V : protected D2V {
protected:
    char d4;
public:
    D4V() : d4('A') {}
    D4V(int a, double b, char c) : D2V(a, b), d4(c) {}
};

class RV : protected D3V, protected D4V, virtual protected BaseV {
protected:
    double dt;
public:
    RV() : dt(1.0) {}
    RV(int a, int b, float c, int d, double e, char f, int g)
        : D3V(a, b, c), D4V(d, e, f), BaseV(g), dt(2.0) {}
    void showDat() {
        std::cout << "Virtual: dat = " << dat << "\n";
    }
};

int main() {
    R obj1;
    R obj2(1, 2, 3.0f, 4, 5.0, 'B');

    RV obj3;
    RV obj4(1, 2, 3.0f, 4, 5.0, 'B', 6);

    std::cout << "Non-virtual inheritance:\n";
    std::cout << "Size of Base: " << sizeof(Base) << "\n";
    std::cout << "Size of D1: " << sizeof(D1) << "\n";
    std::cout << "Size of D2: " << sizeof(D2) << "\n";
    std::cout << "Size of D3: " << sizeof(D3) << "\n";
    std::cout << "Size of D4: " << sizeof(D4) << "\n";
    std::cout << "Size of R: " << sizeof(R) << "\n";
    std::cout << "Size of obj1 (R): " << sizeof(obj1) << "\n";
    std::cout << "Size of obj2 (R): " << sizeof(obj2) << "\n";

    std::cout << "\nVirtual inheritance:\n";
    std::cout << "Size of BaseV: " << sizeof(BaseV) << "\n";
    std::cout << "Size of D1V: " << sizeof(D1V) << "\n";
    std::cout << "Size of D2V: " << sizeof(D2V) << "\n";
    std::cout << "Size of D3V: " << sizeof(D3V) << "\n";
    std::cout << "Size of D4V: " << sizeof(D4V) << "\n";
    std::cout << "Size of RV: " << sizeof(RV) << "\n";
    std::cout << "Size of obj3 (RV): " << sizeof(obj3) << "\n";
    std::cout << "Size of obj4 (RV): " << sizeof(obj4) << "\n";

    obj2.showDat();
    obj4.showDat();

    return 0;
}
