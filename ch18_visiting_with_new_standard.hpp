#ifndef ch18_visiting_with_new_standard_hpp
#define ch18_visiting_with_new_standard_hpp
#include "Utils.hpp"
#include <cstdio>
#include <algorithm>
#include <set>
#include <array>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <functional> // function

using namespace std;

int ch18_visiting_with_new_standard();

// already
template <class T1, class T2>
auto Multiplic(T1 &a, T2 &b) -> decltype(a * b)
{
    return a * b;
}

template <class T>
using array12 = array<T, 12>;

// rval
class Field
{
private:
    int n;
    char *s;
    static int ct;
public:
    Field();
    explicit Field(int, char = '.');
    Field(int, char *);
    Field(const Field &);           // standart copier
    Field(Field &&);                // copier with carry
    ~Field();
    void Set(int, char);
    Field operator+(const Field &) const;
    Field & operator=(const Field &);
    Field & operator=(Field &&);    // && - it means, that rvalue is received
    void Show() const;
};

// defaulted_deleted_methods
class Cl1
{
private:
    double a, b;
public:
    Cl1() = default;            // the compiler generates this method
    Cl1(const Cl1 &) = delete;  // this method is prohibited for using
    Cl1(Cl1 &&) = default;
    Cl1(double _a, double _b) : a(_a), b(_b) {}
    
    void Set(double _a, double _b) {a = _a; b = _b;}
    void Set(bool _a, bool _b) {a = (double) _a; b = (double) _b;}
    void Set(int, int) = delete;    // this method is prohibited for using
    void Show() const {cout << "a = " << a << ", b = " << b << '\n';}
    Cl1 operator+(const Cl1 &c) const {return Cl1(a + c.a, b + c.b);}
};

class Cl2 : public Cl1
{
private:
    int c;
public:
    Cl2() = default;
    Cl2(double _a, double _b, int _c) : Cl1(_a, _b), c(_c) {}
    
    void Show() const       // this method blocks all versions Cl1::Show for user
    {Cl1::Show(); cout << " c = " << c << '\n';}
};

class Cl3 : public Cl1
{
private:
    int c;
public:
    using Cl1::Set;         // provides all versions of Cl1::Set for user
    void Set(double _a, double _b, int _c) {Cl1::Set(_a, _b); c = _c;}
    void ShowAll() const {Show(); cout << " c = " << c << '\n';}
};

// lambda
bool f3(int &);
bool f13(int &);

// fun_adapter
double dub(double);
double square(double);

template <class T, class F>
T use_f(T a, F f)
{
    static int ct = 0;
    ++ct;
    cout << " use_f ct = " << ct << ", &ct = " << &ct << '\n';
    return f(a);
}

class Fmult
{
private:
    double a_;
public:
    explicit Fmult(double a) : a_(a) {}
    double operator()(double a) {return a_ * a;}
};

class Fplus
{
private:
    double a_;
public:
    explicit Fplus(double a) : a_(a) {}
    double operator()(double a) {return a_ + a;}
};

// packets_of_parameters
// packets allow to use variable number of arguments

template<typename T>            // overloading for 1 argument
void show_list(const T &a)
{
    cout << a << '\n';
}

template<typename T, typename ... Args>            // template's packet of arguments: Args
void show_list(const T &a, const Args &... packet) // function's packet of arguments: pocket
{
    cout << a;
    show_list(packet...); // unpacking with the help of recursion
}

#endif /* ch18_visiting_with_new_standard_hpp */
