#include "ch13_class_inheritance.hpp"
#include <cmath>

using namespace std;

static void inheritanceA_Higgins();
static void brss();
static void abk();
static void number1();
static void number3();
static void number4();

int ch13_class_inheritance()
{
    print_run_chapter_message(13);
    inheritanceA_Higgins();
    brss();
    abk();
    number1();
    number3();
    number4();
    return EXIT_SUCCESS;
}

format SetFormat()
{
    return cout.setf(ios_base::fixed, ios_base::floatfield);
}
void restore(format f, streamsize s)
{
    cout.setf(f, ios_base::floatfield);
    cout.precision(s);
}

void inheritanceA_Higgins()
{
    cout << "\nInheritance A. Higgins\n";
    format fst = SetFormat();
    streamsize sts = cout.precision(2);
    cout << 1.32453234 << '\n'; // showing the effect of SetFormat()
    RatingP rp(413270, "Alex Higgins", true);
    SnookerP *tp(&rp);
    cout << "Player #1:\n";
    tp->Name();
    cout << ", ";
    rp.Rat();
    if (rp.isTable())
        cout << " - has a table.";
    else
        cout << " - hasn't a table.";
    cout << '\n';
    restore(fst, sts);
    cout << 1.32453234 << '\n'; // showing the effect of restore()
}

// brss
bool Brass::Deposit(double d)
{
    if (d < 0.0)
        return false;
    balance += d;
    return true;
}
bool Brass::Withdraw(double w)
{
    if (w < 0.0 || w > balance)
        return false;
    balance -= w;
    return true;
}
void Brass::ViewAcnt() const
{
    cout << "  Name:           " << name << endl;
    cout << "  Account number: " << AccountNumber << endl;
    cout << "  Balance:        " << balance << endl;
}
BrassPlus::BrassPlus(const string &s, size_t an, double b,
                     double ml, double r) : Brass(s, an, b)
{
    MaxLoan = ml;
    owe = 0.0;
    rate = r;
}
BrassPlus::BrassPlus(const Brass &br, double ml, double r) : Brass(br)
{
    MaxLoan = ml;
    owe = 0.0;
    rate = r;
}
bool BrassPlus::Withdraw(double w)
{
    double bl = Balance();
    if (w < 0.0)
        return false;
    else if (w <= bl)
        Brass::Withdraw(w);
    else if (w < bl + MaxLoan - owe)
    {
        double advance = w - bl;
        owe += advance * rate;
        Brass::Deposit(advance);
        Brass::Withdraw(w);
    }
    else
        return false;
    return true;
}
void BrassPlus::ViewAcnt() const
{
    Brass::ViewAcnt();
    cout << " Maximum Loan: " << MaxLoan
    << "\n Owe: " << owe
    << "\n Rate: " << rate * 100 << "%\n";
}
void brss()
{
    cout << "\nBrass\n";
    const int S = 2;
    Brass *br[S];
    string nm;
    size_t an;
    double b, ml, r, dep, w;
    cout << "Tere are " << S << " bank accounts.\n";
    for (int i = 0; i < S; ++i)
    {
        cout << "Acoount #" << i+1 << endl;
        cout << " Enter the name: ";
        Line line = Line(cin);
        nm = line.str();
        cout << " Enter account number: ";
        an = input_size();
        cout << " Enter the balance (2.3): ";
        b = input_double();
        cout << " 1) Brass; 2) BrassPlus; 3) BrassPlus default: ";
        input_line(line);
        while (line != "1" && line != "2" && line != "3")
        {
            cout << " 1) Brass; 2) BrassPlus; 3) BrassPlus default: ";
            input_line(line);
        }
        if (line == "1")
            br[i] = new Brass(nm, an, b);
        else if (line == "2")
        {
            cout << " Enter maximum loan (2.3): ";
            ml = input_double();
            cout << " Enter account rate in decimal fraction (2.3): ";
            r = input_double();
            br[i] = new BrassPlus(nm, an, b, ml, r);
        }
        else
            br[i] = new BrassPlus(nm, an, b);
    }
    for (int i = 0; i < S; ++i)
    {
        cout << "Enter account #" << i + 1 << " deposit (2.3): ";
        dep = input_double();
        if (!br[i]->Deposit(dep))
            cout << "Deposit cancled.\n";
        cout << "Enter account #" << i + 1 << " withdraw (2.3): ";
        w = input_double();
        if (!br[i]->Withdraw(w))
            cout << "Withdraw cancled.\n";
    }
    for (int i = 0; i < S; ++i)
    {
        cout << "Account #" << i + 1 << ":\n";
        br[i]->ViewAcnt();
    }
    for (int i = 0; i < S; ++i)
        delete br[i];
}

// abk
void abk()
{
    cout << "\nAbase\n";
    Abase *ab;
    Stud s("Joe", 2376440, 10.0);
    Wor w("Jack", 1901691, 3790.39);
    ab = &s;
    ab->show();
    w.show();
    s.ResetAR(9.93);
    s.ResetTN(3006440);
    cout << "After thr last class work:\n";
    ab->show();
}

// number1
Cd::Cd()
{
    performers[0] = '\0';
    label[0] = '\0';
    selections = 0;
    playtime = 0.0;
}
Cd::Cd(const char *perf, const char *lab, int sel, double playt)
{
    int l = int(strlen(perf));
    l = S > l ? l : S - 1;
    strncpy(performers, perf, l);
    performers[l] = '\0';
    l = int(strlen(lab));
    l = S > l ? l : S;
    strncpy(label, lab, l);
    label[l] = '\0';
    selections = sel;
    playtime = playt;
}
Cd::Cd(const Cd &cd)
{
    strcpy(performers, cd.performers);
    performers[strlen(performers)] = '\0';
    strcpy(label, cd.label);
    label[strlen(label)] = '\0';
    selections = cd.selections;
    playtime = cd.playtime;
}
void Cd::show() const
{
    cout << "Performers: " << performers
    << "\n Label: " << label
    << "\n Selections: " << selections
    << "\n Playtime: " << playtime << '\n';
}
const Cd & Cd::reset(const char *perf, const char *lab, int sel, double playt)
{
    int l = int(strlen(perf));
    l = S > l ? l : S - 1;
    strncpy(performers, perf, l);
    performers[l] = '\0';
    l = int(strlen(lab));
    l = S > l ? l : S;
    strncpy(label, lab, l);
    label[l] = '\0';
    selections = sel;
    playtime = playt;
    return *this;
}
Cd & Cd::operator=(const Cd &cd)
{
    strcpy(performers, cd.performers);
    performers[strlen(performers)] = '\0';
    strcpy(label, cd.label);
    label[strlen(label)] = '\0';
    selections = cd.selections;
    playtime = cd.playtime;
    return *this;
}
Classic::Classic() : Cd()
{
    primary[0] = '\0';
}
Classic::Classic(const char *perf, const char *lab, const char *prim, int sel, double playt)
: Cd(perf, lab, sel, playt)
{
    int l = int(strlen(prim));
    l = S > l ? l : S - 1;
    strncpy(primary, prim, l);
    primary[l] = '\0';
}
Classic::Classic(const Classic &cl) : Cd(cl)
{
    strcpy(primary, cl.primary);
    primary[strlen(primary)] = '\0';
}
void Classic::show() const
{
    Cd::show();
    cout << " Primary: " << primary << '\n';
}
const Classic & Classic::reset(const char *perf, const char *lab, const char *prim, int sel, double playt)
{
    Cd::reset(perf, lab, sel, playt);
    int l = int(strlen(prim));
    l = S > l ? l : S - 1;
    strncpy(primary, prim, l);
    primary[l] = '\0';
    return *this;
}
Classic & Classic::operator=(const Classic &cl)
{
    strcpy(performers, cl.performers);
    performers[strlen(performers)] = '\0';
    strcpy(label, cl.label);
    label[strlen(label)] = '\0';
    selections = cl.selections;
    playtime = cl.playtime;
    strcpy(primary, cl.primary);
    return *this;
}
void number1()
{
    cout << "\nNumber 1\n";
    Cd c1("Beatles", "Capitol", 14, 35.5);
    Classic c2 = Classic("Piano Sonata in В flat, Fantasia in C",
                         "Alfred Brendel", "Philips", 2, 57.17);
    Cd *pc1 = &c1, *pc2 = &c2;
    Cd &p1 = c1, &p2 = c2;
    cout << "Using objects directly:\n";
    c1.show();
    c2.show();
    cout << "Using pointers:\n";
    pc1->show();
    pc2->show();
    cout << "Using references:\n";
    p1.show();
    p2.show();
    c2.reset("Bach", "Johann Sebastian Bach", "Toccata And Fugue", 2, 83.59);
    cout << "c2 after reseting (using reference):\n";
    p2.show();
    c1 = c2;
    cout << "c1 = c2 => Now c1 (using pointer):\n";
    pc1->show();
}

// number3
baseDMA::baseDMA(const char *lab, int rat)
{
    int l = int(strlen(lab));
    label = new char[l + 1];
    strcpy(label, lab);
    label[l] = '\0';
    rating = rat;
}
baseDMA::baseDMA(const baseDMA &bd)
{
    int l = int(strlen(bd.label));
    label = new char[l + 1];
    strcpy(label, bd.label);
    label[l] = '\0';
    rating = bd.rating;
}
baseDMA::~baseDMA()
{
    delete [] label;
}
baseDMA & baseDMA::operator=(const baseDMA &rs)
{
    if (this == &rs)
        return *this;
    delete [] label;
    int l = int(strlen(rs.label));
    label = new char[l + 1];
    strcpy(label, rs.label);
    label[l] = '\0';
    rating = rs.rating;
    return *this;
}
lacksDMA::lacksDMA(const char *lab, const char *col, int rat) : baseDMA(lab, rat)
{
    int l = int(strlen(col));
    l = S > l ? l : S - 1;
    strncpy(color, col, l);
    color[l] = '\0';
}
lacksDMA::lacksDMA(const lacksDMA &ld) : baseDMA(ld)
{
    int l = int(strlen(ld.color));
    strcpy(color, ld.color);
    color[l] = '\0';
}
void lacksDMA::show() const
{
    cout << "Label: " << label
    << "\n Rating: " << rating
    << "\n Color: " << color << '\n';
}

hasDMA::hasDMA(const char *lab, const char *st, int rat) : baseDMA(lab, rat)
{
    int l = int(strlen(st));
    style = new char[l + 1];
    strcpy(style, st);
    style[l] = '\0';
}
hasDMA::hasDMA(const hasDMA &hd) : baseDMA(hd)
{
    int l = int(strlen(hd.style));
    style = new char[l + 1];
    strcpy(style, hd.style);
    style[l] = '\0';
}
hasDMA::~hasDMA()
{
    delete [] style;
}
hasDMA & hasDMA::operator=(const hasDMA &hd)
{
    if (this == &hd)
        return *this;
    baseDMA::operator=(hd);
    delete [] style;
    int l = int(strlen(hd.style));
    style = new char[l + 1];
    strcpy(style, hd.style);
    style[l] = '\0';
    return *this;
}
void hasDMA::show() const
{
    cout << "Label: " << label
    << "\n Rating: " << rating
    << "\n Style: " << style << '\n';
}
void number3()
{
    cout << "\nExercise 3\n";
    const int S = 2;
    baseDMA *bd[S];
    int rat;
    for (int i = 0; i < S; ++i)
    {
        cout << "Enter the label: ";
        Line label = Line(cin);
        cout << "Enter the rating: ";
        rat = input_int();
        cout << "Eneter '1' for color and '2' for style: ";
        Line line = Line(cin);
        while (line != "1" && line != "2")
        {
            cout << "Eneter '1' for color and '2' for style: ";
            input_line(line);
        }
        if (line == "1")
        {
            cout << "Enter the color: ";
            Line color = Line(cin);
            bd[i] = new lacksDMA(label.str(), color.str(), rat);
        }
        else
        {
            cout << "Enter th style: ";
            Line style = Line(cin);
            bd[i] = new hasDMA(label.str(), style.str(), rat);
        }
    }
    cout << "Look:\n";
    for (int i = 0; i < S; ++i)
        bd[i]->show();
    for (int i = 0; i < S; ++i)
        delete bd[i];
    cout << "Buy!\n";
}

// number4
Port::Port(co_ch *br, co_ch *st, int bot)
{
    int l = int(strlen(br));
    brand = new char[l + 1];
    strcpy(brand, br);
    l = int(strlen(st));
    l = S > l ? l : S - 1;
    strncpy(style, st, l);
    style[l] = '\0';
    bottles = bot;
}
Port::Port(const Port &p)
{
    int l = int(strlen(p.brand));
    brand = new char[l + 1];
    strcpy(brand, p.brand);
    l = int(strlen(p.style));
    strncpy(style, p.style, l);
    style[l] = '\0';
    bottles = p.bottles;
}
Port & Port::operator=(const Port &p)
{
    if (this == &p)
        return *this;
    int l = int(strlen(p.brand));
    delete [] brand;
    brand = new char[l + 1];
    strcpy(brand, p.brand);
    l = int(strlen(p.style));
    strncpy(style, p.style, l);
    style[l] = '\0';
    bottles = p.bottles;
    return *this;
}
Port & Port::operator+=(int bot)
{
    bottles += bot;
    return *this;
}
Port & Port::operator-=(int bot)
{
    if (bot > bottles)
        bottles = 0;
    else
        bottles -= bot;
    return *this;
}
void Port::show() const
{
    cout << "Brand: " << brand
    << "\n Kind: " << style
    << "\n Bottle(s): " << bottles << '\n';
}
ostream & operator<<(ostream &os, const Port &p)
{
    os << p.brand << ", " << p.style << ", " << p.bottles;
    return os;
}
VintagePort::VintagePort() : Port("none", "vintage")
{
    NickName = new char[5];
    strcpy(NickName, "none");
    NickName[4] = '\0';
    years = 0;
}
VintagePort::VintagePort(co_ch *br, int bot, co_ch *nick, int y) : Port(br, "vintage", bot)
{
    int l = int(strlen(nick));
    NickName = new char[l + 1];
    strcpy(NickName, nick);
    years = y;
}
VintagePort::VintagePort(const VintagePort &vp) : Port(vp)
{
    int l = int(strlen(vp.NickName));
    NickName = new char[l + 1];
    strcpy(NickName, vp.NickName);
    years = vp.years;
}
VintagePort & VintagePort::operator=(const VintagePort &vp)
{
    if (this == &vp)
        return *this;
    Port::operator=(vp);
    int l = int(strlen(vp.NickName));
    delete NickName;
    NickName = new char[l + 1];
    strcpy(NickName, vp.NickName);
    years = vp.years;
    return *this;
}
void VintagePort::show() const
{
    Port::show();
    cout << " NickName: " << NickName
    << "\n Year: " << years << '\n';
}
ostream & operator<<(ostream &os, const VintagePort &vp)
{
    os << (const Port &) vp;
    os << ", " << vp.NickName << ", " << vp.years;
    return os;
}
void number4()
{
    cout << "\nExercise 4\n";
    VintagePort vp1;
    Port &p = vp1;
    p += 2;
    p.show();
}
