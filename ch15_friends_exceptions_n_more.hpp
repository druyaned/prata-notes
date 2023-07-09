#ifndef ch15_friends_exceptions_n_more_hpp
#define ch15_friends_exceptions_n_more_hpp
#include "Utils.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <exception>
#include <stdexcept>
#include <cmath>

int ch15_friends_exceptions_n_more();

using namespace std;

string to_binar(int);

// number1
class Remote;
class Tv
{
public:
    friend class Remote;
    enum {Off, On};
    enum {MaxVol = 40, MaxChan = 50, MaxTracks = 20};
    enum {antenna, cable};
    enum {tv, dvd};
private:
    int state;
    int volume;
    int channel;
    int track;
    int mode;
    int input;
public:
    Tv() : state(Off), volume(5), channel(1),
    track(1), mode(cable), input(tv) {}
    void power() {state ^= 1;}
    bool vol_up();
    bool vol_down();
    bool next_tv();
    bool prev_tv();
    bool vary_mode();
    bool vary_input();
    bool show() const;
    bool vary_remmode(Remote &r);
};
class Remote
{
public:
    friend class Tv;
    enum {Norm, Inter};
private:
    int mode;
public:
    Remote() : mode(Norm) {}
    void power_tv(Tv &t) {t.state ^= 1;}
    inline bool vol_up(Tv &t) {return t.vol_up();}
    inline bool vol_down(Tv &t) {return t.vol_down();}
    inline bool next_rem(Tv &t) {return t.next_tv();}
    inline bool prev_rem(Tv &t) {return t.prev_tv();}
    inline bool vary_mode(Tv &t) {return t.vary_mode();}
    inline bool vary_input(Tv &t) {return t.vary_input();}
    inline bool show_tv(Tv &t) const {return t.show();}
    bool set_chan(Tv &, int) const;
    void show_mode() const;
};
inline void on_off(bool b)
{
    if (!b)
        cout << "Tv is turned off.\n";
}

// number2
class bad_hmean : public logic_error
{
private:
    double a;
    double b;
public:
    bad_hmean(double aa, double bb, const string &s = "Bad call hmean()")
        : logic_error(s), a(aa), b(bb) {}
    void messg() const;
};
class bad_gmean : public logic_error
{
private:
    double a;
    double b;
public:
    bad_gmean(double aa, double bb, const string &s = "Bad call gmean()")
    : a(aa), b(bb), logic_error(s) {}
    void messg() const;
};
double hmean(double, double);
double gmean(double, double);

// number3
class bad_attempt : public logic_error
{
protected:
    double a;
    double b;
public:
    bad_attempt(double aa, double bb, const string &s)
        : a(aa), b(bb), logic_error(s) {}
    virtual ~bad_attempt() {}
    virtual void messg() const = 0;
};
class hmean_bad : public bad_attempt
{
public:
    hmean_bad(double aa, double bb, const string &s = "Bad call hmean1()")
    : bad_attempt(aa, bb, s) {}
    void messg() const;
};
class gmean_bad : public bad_attempt
{
public:
    gmean_bad(double aa, double bb, const string &s = "Bad call gmean1()")
        : bad_attempt(aa, bb, s) {}
    void messg() const;
};
double hmean1(double, double);
double gmean1(double, double);
//number4
class Sales
{
public:
    enum {M = 12};
private:
    int per_month[M];
    int year;
public:
    class bad_ind : public logic_error
    {
    private:
        int bi;
    public:
        bad_ind(int i, const string &s = "Bad index in object Sales") : logic_error(s), bi(i) {}
        int val_bi() const {return bi;}
        virtual void messg() const;
        virtual ~bad_ind() {}
    };
    Sales(int *p_m, int y);
    virtual ~Sales() {}
    virtual int & operator[](int);
    virtual int operator[](int) const;
    virtual void show() const;
};
class LabelSales : private Sales
{
private:
    string label;
public:
    class lbad_ind : public bad_ind
    {
    public:
        lbad_ind(int i, const string &s = "Bad index in object LabelSales") : bad_ind(i, s) {}
        void messg() const;
    };
    LabelSales(int *p_m, int y, const string &lb) : Sales(p_m, y), label(lb) {}
    int & operator[](int);
    int operator[](int) const;
    void show() const;
};

#endif /* ch15_friends_exceptions_n_more_hpp */
