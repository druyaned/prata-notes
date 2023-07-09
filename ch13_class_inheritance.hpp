#ifndef ch13_class_inheritance_hpp
#define ch13_class_inheritance_hpp
#include "Utils.hpp"
#include <string>
#include <cstring>

using namespace std;
typedef ios_base::fmtflags format;
typedef const char co_ch;

int ch13_class_inheritance();

format SetFormat();
void restore(format, streamsize);
// inheritanceA_Higgins()
class SnookerP
{
private:
    string name;
    bool table;
public:
    SnookerP(const string nm = "none", bool t = false) : name(nm), table(t) {}
    SnookerP(const SnookerP &tp) : name(tp.name), table(tp.table) {}
    void Name() const {cout << "Name: " << name;}
    bool isTable() const {return table;}
};
class RatingP : public SnookerP
{
private:
    unsigned int rat;
public:
    RatingP(int r = 0, const string &nm = "none", bool t = false) : rat(r), SnookerP(nm, t) {}
    RatingP(int r, const SnookerP &tp) : rat(r), SnookerP(tp) {}
    void Rat() const {cout << "Rating: " << rat;}
};
// brss
class Brass
{
private:
    string name;
    size_t AccountNumber;
    double balance;
public:
    Brass(const string &s = "none", size_t an = 0, double b = 0.0)
        : name(s), AccountNumber(an), balance(b) {}
    Brass(const Brass &br)
        : name(br.name), AccountNumber(br.AccountNumber), balance(br.balance) {}
    virtual ~Brass() {};        // BrassPlus bp; Brass &p = bp; delete p; (using ~BrassPlus)
    bool Deposit(double);
    virtual bool Withdraw(double);
    double Balance() const {return balance;}
    virtual void ViewAcnt() const;
};
class BrassPlus : public Brass
{
private:
    double MaxLoan;
    double owe;
    double rate;
public:
    BrassPlus(const string &s = "none", size_t an = 0, double b = 0.0,
              double ml = 500.0, double r = 0.11125);
    BrassPlus(const Brass &, double ml = 500.0, double r = 0.11125);
    ~BrassPlus() {};
    bool Withdraw(double);
    void ViewAcnt() const;
};
// abk
class Abase
{
protected:
    string name;
    size_t TelNum;
public:
    Abase(const string &nm = "none", size_t tn = 0) : name(nm), TelNum(tn) {}
    Abase(const Abase &a) : name(a.name), TelNum(a.TelNum) {}
    virtual ~Abase() {}
    void ResetName(const string &nm = "none") {name = nm;}
    void ResetTN(size_t tn = 0) {TelNum = tn;}
    virtual void show() const = 0;      // clear virtual function
    // there couldn't be any objects with this class
};
class Stud : public Abase
{
private:
    double AvRat;
public:
    Stud(const string &nm = "none", size_t tn = 0, double ar = 0.0) : Abase(nm, tn), AvRat(ar) {}
    Stud(const Abase &a, double ar = 0.0) : Abase(a), AvRat(ar) {}
    ~Stud() {};
    void ResetAR(double ar = 0.0) {AvRat = ar;}
    void show() const
    {
        cout << "  Name:   " << name << endl;
        cout << "  TelNum: " << TelNum << endl;
        cout << "  Average rating: " << AvRat << endl;
    }
};
class Wor : public Abase
{
private:
    double salary;
public:
    Wor(const string &nm = "none", size_t tn = 0, double s = 0.0) : Abase(nm, tn), salary(s) {}
    Wor(const Abase &a, double s = 0.0) : Abase(a), salary(s) {}
    void ResetSal(double s = 0.0) {salary = s;}
    void show() const
    {cout << "Name: " << name << "\n TelNum: " << TelNum << "\n Salary: " << salary << '\n';}
};
// number1
class Cd
{
public:
    enum {S = 50};
protected:
    char performers[S], label[S];
    int selections;
    double playtime;
public:
    Cd();
    Cd(co_ch *perf, co_ch *lab, int sel, double playt);
    Cd(const Cd &);
    virtual ~Cd() {};
    virtual void show() const;
    const Cd & reset(co_ch *perf, co_ch *lab, int sel, double playt);
    Cd & operator=(const Cd &);
};
class Classic : public Cd
{
private:
    char primary[S];
public:
    Classic();
    Classic(co_ch *perf, co_ch *lab, co_ch *prim, int sel, double playt);
    Classic(const Classic &);
    void show() const;
    const Classic & reset(co_ch *perf, co_ch *lab, co_ch *prim, int sel, double playt);
    Classic & operator=(const Classic &);
};
// number3
class baseDMA
{
protected:
    char *label;
    int rating;
public:
    baseDMA(co_ch *l = "null", int r = 0);
    baseDMA(const baseDMA &rs);
    virtual ~baseDMA();
    baseDMA & operator=(const baseDMA &rs);
    virtual void show() const = 0;
};
class lacksDMA : public baseDMA
{
public:
    enum {S = 40};
private:
    char color[S];
public:
    lacksDMA(co_ch *l = "null", co_ch *c = "none", int r = 0);
    lacksDMA(const lacksDMA &);
    void show() const;
};
class hasDMA : public baseDMA
{
private:
    char *style;
public:
    hasDMA(co_ch *l = "null", co_ch *s = "none", int r = 0);
    hasDMA(const hasDMA &);
    ~hasDMA();
    hasDMA & operator=(const hasDMA &);
    void show() const;
};
// number4
class Port
{
public:
    enum {S = 30};
protected:
    char *brand;
    char style[S];
    int bottles;
public:
    Port(co_ch *br = "none", co_ch *st = "none", int bot = 0);
    Port(const Port &);
    virtual ~Port() {delete [] brand;}
    Port & operator=(const Port &);
    Port & operator+=(int);
    Port & operator-=(int);
    virtual void show() const;
    friend ostream & operator<<(ostream &, const Port &);
};
class VintagePort : public Port
{
private:
    char *NickName;
    int years;
public:
    VintagePort();
    VintagePort(co_ch *br, int bot, co_ch *nick, int y);
    VintagePort(const VintagePort &);
    ~VintagePort() {delete [] NickName;}
    VintagePort & operator=(const VintagePort &);
    void show() const;
    friend ostream & operator<<(ostream &, const VintagePort &);
};

#endif /* ch13_class_inheritance_hpp */

