#include "ch14_reusing_code.hpp"
#include <ctime>
#include <cstring>

using namespace std;

static void worky();
static void tmplt();
static void frindly_templ_fun();
static void number1();
static void number2();
static void number3();
static void number4();
static void number5();

int ch14_reusing_code()
{
    print_run_chapter_message(14);
    worky();
    tmplt();
    frindly_templ_fun();
    number1();
    number2();
    number3();
    number4();
    number5();
    return EXIT_SUCCESS;
}

// worky
Worker_ch14::~Worker_ch14() {}
void Worker_ch14::Get()
{
    cout << "Enter the name: ";
    input_line(m_name);
    cout << "Enter worker's ID (2): ";
    m_id = input_int();
}
void Worker_ch14::Data() const
{
    cout << "Name='" << m_name << "'\n ID=" << m_id << endl;
}
void Waiter_ch14::Get()
{
    cout << "Enter the panache (2): ";
    m_panache = input_int();
}
void Waiter_ch14::Data() const
{
    cout << " Panache: " << m_panache << endl;
}
void Waiter_ch14::Set()
{
    Worker_ch14::Get();
    Get();
}
void Waiter_ch14::Show() const
{
    Worker_ch14::Data();
    Data();
}
Line const Singer_ch14::types[Singer_ch14::Vtypes] {"other", "alto",
    "contralto", "soprano", "bass", "baritone", "tenor"};
void Singer_ch14::Get()
{
    cout << "Enter the vocal range: ";
    m_voice = input_int();
}
void Singer_ch14::Data() const
{
    cout << " Vocal range: " << types[m_voice] << endl;
}
void Singer_ch14::Set()
{
    Worker_ch14::Get();
    Get();
}
void Singer_ch14::Show() const
{
    Worker_ch14::Data();
    Data();
}
void SingingWaiter_ch14::Get()
{
    Waiter_ch14::Get();
    Singer_ch14::Get();
}
void SingingWaiter_ch14::Data() const
{
    Waiter_ch14::Data();
    Singer_ch14::Data();
}
void SingingWaiter_ch14::Set()
{
    Worker_ch14::Get();
    Get();
}
void SingingWaiter_ch14::Show() const
{
    Worker_ch14::Data();
    Data();
}
void worky()
{
    cout << "\nWorky\n";
    const int S = 3;
    Waiter_ch14 w;
    Singer_ch14 s;
    SingingWaiter_ch14 sw;
    Worker_ch14 *wk[S] {&w, &s, &sw};
    w.Show();
    s.Show();
    sw.Show();
    cout << "With pointers:\n";
    for (int i = 0; i < S; ++i)
        wk[i]->Show();
}

// tmplt
void tmplt()
{
    cout << "\nTmplt: practice with the Stack\n";
    const int SIZE = 3;
    Stack_ch14<Line> stack;
    Line lines[SIZE];
    cout << "Enter " << SIZE << " line(s)\n";
    for (int i = 0; i < SIZE; ++i)
    {
        cout << i + 1 << ": ";
        input_line(lines[i]);
        stack.push(lines[i]);
    }
    cout << "Stack:\n";
    stack.show();
    Line deleted_line{};
    stack.pop(deleted_line);
    cout << '\'' << deleted_line << "' was deleted.\n";
}

// frindly_templ_fun - связанные шаблонные друзья
void show1(const Friendly<int> &f)
{
    cout << " v1: " << f.m_a << ", " << f.m_b << endl;
}
void show1(const Friendly<double> &f)
{
    cout << " v1: " << f.m_a << ", " << f.m_b << endl;
}
void frindly_templ_fun()
{
    cout << "\nFrindly template functions\n";
    Friendly<int> fint(2, 5);
    Friendly<double> fdouble(2.2, 5.5);
    cout << "For 'int' Friendly element:\n";
    show1(fint);
    show2(fint);
    show3(fint);
    cout << "For 'double' Friendly element:\n";
    show1(fdouble);
    show2(fdouble);
    show3(fdouble);
}

// number1
void Wine::Get()
{
    Vint years(m_amount), bottles(m_amount);
    cout << "Enter " << m_amount << " year(s) for '" << m_label << "' wine harvest:\n";
    for (size_t i = 0; i < m_amount; ++i)
    {
        cout << '#' << i + 1 << endl;
        cout << " year (1978): ";
        years[i] = input_int();
        cout << " bottles (17): ";
        bottles[i] = input_int();
    }
    m_years_bottles.first() = years;
    m_years_bottles.second() = bottles;
}
void Wine::Show() const
{
    cout << "Wine: " << m_label  << endl;
    cout << setw(7) << "[Yaer]" << ' ' << setw(10) << "[Bottles]" << endl;
    for (size_t i = 0; i < m_amount; ++i)
    {
        cout << setw(7) << m_years_bottles.first()[i] << ' '
            << setw(10) << m_years_bottles.second()[i] << endl;
    }
    cout << " Total amount of bottles: " << Sum() << endl;
}
void number1()
{
    cout << "\nExercise 1\n";
    cout << "Enter label: ";
    Line label = Line(cin);
    cout << "Enter amount of wine harvest years: ";
    int amount = input_int();
    Wine w1(label.str(), amount);
    w1.Get();
    w1.Show();
}

// number2
void Wine2::Get()
{
    Vint yr(years), bot(years);
    cout << "Enter " << label << " data for " << years << " year(s):\n";
    for (int i = 0; i < years; ++i)
    {
        cout << i + 1 << ")\tyear: ";
        yr[i] = input_int();
        cout << "\tbottles: ";
        bot[i] = input_int();
    }
    first() = yr;
    second() = bot;
}
void Wine2::Show() const
{
    cout << "Wine: " << label << "\n\t[Yaer]\t[Bottles]\n";
    for (int i = 0; i < years; ++i)
        cout << '\t' << first()[i] << '\t' << second()[i] << endl;
    cout << " Total amount of bottles: " << Sum() << '\n';
}
void number2()
{
    cout << "\nExercise 2\n";
    int years;
    cout << "Enter label: ";
    Line label = Line(cin);
    cout << "Enter years: ";
    years = input_int();
    Wine2 w1(label.str(), years);
    w1.Get();
    w1.Show();
}

// number3
void number3()
{
    cout << "\nExercise 3\n";
    QueueTP<char *> q1;
    const int L = 50;
    char s[3][L];
    strcpy(s[0], "Hellos");
    q1.AddFront(s[0]);
    strcpy(s[1], "Gringo!");
    q1.AddRear(s[1]);
    cout << "Queue:\n";
    if (!q1.Show())
        cout << "\tis empty.\n";
    char *p;
    q1.DelFront(p);
    cout << '\'' << p << "\' was deleted.\n";
    strcpy(s[2], "Bingo");
    q1.AddFront(s[2]);
    cout << "Some element was added to front.\n"
    "Now Queue:\n";
    q1.Show();
    q1.DelRear(p);
    cout << '\'' << p << "\' was deleted.\n";
}

// number4
void Person_ch14::Get()
{
    cout << "Enter the first name: ";
    Line fn = Line(cin);
    fname = new char[fn.len() + 1];
    strncpy(fname, fn.str(), fn.len());
    fname[fn.len()] = '\0';
    cout << "Enter the last name: ";
    Line ln = Line(cin);
    lname = new char[ln.len() + 1];
    strncpy(lname, ln.str(), ln.len());
    lname[ln.len()] = '\0';
}
void Person_ch14::Data() const
{
    cout << "\tFirst name: " << fname
    << "\n\tLast name: " << lname << '\n';
}
Person_ch14::Person_ch14()
{
    fname = new char[1];
    fname[0] = '\0';
    lname = new char[1];
    lname[0] = '\0';
}
Person_ch14::Person_ch14(ccp f, ccp l)
{
    int len = int(strlen(f));
    fname = new char[len + 1];
    strcpy(fname, f);
    len = int(strlen(l));
    lname = new char[len + 1];
    strcpy(lname, l);
}
Person_ch14::Person_ch14(const Person_ch14 &p)
{
    int len = int(strlen(p.fname));
    fname = new char[len + 1];
    strcpy(fname, p.fname);
    len = int(strlen(p.lname));
    lname = new char[len + 1];
    strcpy(lname, p.lname);
}
Person_ch14::~Person_ch14()
{
    delete[] fname;
    delete[] lname;
}
Person_ch14 & Person_ch14::operator=(const Person_ch14 &p)
{
    if (&p == this)
        return *this;
    delete [] fname;
    delete [] lname;
    int len = int(strlen(p.fname));
    fname = new char[len + 1];
    strcpy(fname, p.fname);
    len = int(strlen(p.lname));
    lname = new char[len + 1];
    strcpy(lname, p.lname);
    return *this;
}
void Person_ch14::Set()
{
    Get();
}
void Person_ch14::Show() const
{
    Data();
}
void Gunslinger::Get()
{
    cout << "Enter the preparing time of shot (3.4): ";
    ptime = input_double();
    cout << "Enter the notching (3): ";
    notching = input_int();
}
void Gunslinger::Data() const
{
    cout << "\tPreparing time: " << ptime << endl;
    cout << "\tNotching: " << notching << endl;
}
void Gunslinger::Set()
{
    Person_ch14::Get();
    Get();
}
void Gunslinger::Show() const
{
    Person_ch14::Data();
    Data();
}
void PokerPlayer::Get()
{
    srand(int(time(0)));
    card = rand() % 52 + 1;
}
void PokerPlayer::Data() const
{
    cout << "\tCard #" << card << '\n';
}
void PokerPlayer::Set()
{
    Person_ch14::Get();
    Get();
}
void PokerPlayer::Show() const
{
    Person_ch14::Data();
    Data();
}
void BadDude::Set()
{
    Person_ch14::Get();
    Gunslinger::Get();
    PokerPlayer::Get();
}
void BadDude::Show() const
{
    Person_ch14::Data();
    Gunslinger::Data();
    PokerPlayer::Data();
}
void number4()
{
    cout << "\nExercise 4\n";
    PokerPlayer pp("Guru", "Gordan");
    cout << "PokerPlayer [pp]:\n";
    pp.Show();
    Gunslinger g;
    cout << "Setting Gunslinger [g]:\n";
    g.Set();
    cout << "g:\n";
    g.Show();
    BadDude bd;
    cout << "Setting BadDude [db]:\n";
    bd.Set();
    cout << "bd:\n";
    bd.Show();
}

// number5
abstr_emp::~abstr_emp() {}
void abstr_emp::SetAll()
{
    cout << " Enter the first name: ";
    getline(cin, fname);
    cout << " Enter the last name: ";
    getline(cin, lname);
    cout << " Enter the job: ";
    getline(cin, job);
}
void abstr_emp::ShowAll() const
{
    cout << "\t1st name: " << fname
    << "\n\tlast name: " << lname
    << "\n\tjob: " << job << '\n';
}
ostream & operator<<(ostream &os, const abstr_emp &ae)
{
    os << ae.fname << ", " << ae.lname;
    return os;
}
void employee::SetAll()
{
    abstr_emp::SetAll();
}
void employee::ShowAll() const
{
    abstr_emp::ShowAll();
}
void manager::SetAll()
{
    abstr_emp::SetAll();
    cout << " Enter the inchargeof: ";
    inchargeof = input_int();
}
void manager::ShowAll() const
{
    abstr_emp::ShowAll();
    cout << "\tinchargeof: " << inchargeof << '\n';
}
void fink::SetAll()
{
    abstr_emp::SetAll();
    cout << " Enter the reportsto: ";
    getline(cin, reportsto);
}
void fink::ShowAll() const
{
    abstr_emp::ShowAll();
    cout << "\treportsto: " << reportsto << '\n';
}
void highfink::SetAll()
{
    abstr_emp::SetAll();
    cout << " Enter the inchargeof: ";
    inchargeof = input_int();
    cout << " Enter the reportsto: ";
    getline(cin, reportsto);
}
void highfink::ShowAll() const
{
    abstr_emp::ShowAll();
    cout << "\tinchargeof: " << inchargeof
    << "\n\treportsto: " << reportsto << '\n';
}
void number5()
{
    cout << "\nExercise 5\n";
    const int S = 3;
    abstr_emp *ae[S];
    ae[0] = new employee;
    ae[1] = new manager;
    ae[2] = new fink;
    highfink hf;
    for (int i = 0; i < S; ++i)
    {
        cout << i + 1 << "#:\n";
        ae[i]->ShowAll();
    }
    cout << "Highfink:\n";
    hf.ShowAll();
}
