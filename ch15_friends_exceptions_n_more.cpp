#include "ch15_friends_exceptions_n_more.hpp"

using namespace std;

static void show_binar();
static void number1();
static void number2();
static void number3();
static void number4();

int ch15_friends_exceptions_n_more()
{
    print_run_chapter_message(15);
    show_binar();
    number1();
    number2();
    number3();
    number4();
    return EXIT_SUCCESS;
}

// show_binar
string to_binar(int a)
{
    string s;
    int r = 0, ver;
    while ((a >> r) > 1)
        ++r;
    while (r > -1)
    {
        ver = 1;
        ver <<= r;
        if (ver > a)
            s += '0';
        else
        {
            s+= '1';
            a -= ver;
        }
        --r;
    }
    return s;
}
void show_binar()
{
    cout << "\nShow binar\n";
    int a = 923, b = 846;
    string sa = to_binar(a);
    string sb = to_binar(b);
    cout << sa << " = " << a << endl;
    cout << sb << " = " << b << endl;
    cout << "  " << to_binar(a ^ b) << " = a ^ b = " << (a ^ b) << endl;
    cout << to_binar(a & b) << " = a & b = " << (a & b) << endl;
    cout << to_binar(a | b) << " = a | b = " << (a | b) << endl;
}

// number1
bool Tv::vol_up()
{
    if (state == Off) return false;
    if (volume != MaxVol)
        ++volume;
    return true;
}
bool Tv::vol_down()
{
    if (state == Off) return false;
    if (volume != 1)
        --volume;
    return true;
}
bool Tv::next_tv()
{
    if (state == Off) return false;
    if (input == tv)
    {
        if (channel == MaxChan)
            channel = 0;
        ++channel;
    }
    else
    {
        if (track != MaxTracks)
            ++track;
    }
    return true;
}
bool Tv::prev_tv()
{
    if (state == Off) return false;
    if (input == tv)
    {
        if (channel == 1)
            channel = MaxChan;
        --channel;
    }
    else
    {
        if (track != 1)
            --track;
    }
    return true;
}
bool Tv::vary_mode()
{
    if (state == Off) return false;
    mode ^= 1;
    return true;
}
bool Tv::vary_input()
{
    if (state == Off) return false;
    input ^= 1;
    return true;
}
bool Tv::show() const
{
    if (state == Off) return false;
    if (mode == antenna)
        cout << " Mode:\t\tAntenna\n";
    else
        cout << " Mode:\t\tCable\n";
    if (input == tv)
        cout << " Input:\t\tTV\n";
    else
        cout << " Input:\t\tDVD\n";
    cout << " Volume:\t" << volume << endl;
    cout << " Chanal:\t" << channel << endl;
    cout << " Track:\t\t" << track << endl;
    return true;
}
bool Tv::vary_remmode(Remote &r)
{
    if (state == Off) return false;
    r.mode ^= 1;
    return true;
}
bool Remote::set_chan(Tv &t, int num) const
{
    if (t.state == Tv::Off) return false;
    if (num > Tv::MaxChan || num < 1)
        return true;
    t.channel = num;
    return true;
}
void Remote::show_mode() const
{
    if (mode == Norm)
        cout << " Mode: normal\n";
    else
        cout << " Mode: interactive\n";
}
void number1()
{
    cout << "\nExercise 1\n";
    Tv t1, t2;
    t2.power();
    Remote r1;
    r1.power_tv(t1);
    r1.vary_mode(t1);
    on_off(r1.vary_input(t2));
    for (int i = 0; i < 7; ++i)
    {
        r1.prev_rem(t1);
        r1.next_rem(t2);
    }
    on_off(r1.vary_input(t2));
    on_off(r1.vary_input(t1));
    for (int i = 0; i < 3; ++i)
    {
        r1.next_rem(t1);
        r1.prev_rem(t2);
    }
    cout << "Tv1:\n";
    on_off(t1.show());
    cout << "Tv2:\n";
    on_off(t2.show());
    cout << "Enter tv1 channel (43): ";
    int ch = input_int();
    on_off(r1.set_chan(t1, ch));
    on_off(r1.vol_up(t1));
    cout << "Now Tv1:\n";
    on_off(t1.show());
    t1.vary_remmode(r1);
    r1.power_tv(t1);
    r1.power_tv(t2);
    on_off(r1.vary_input(t1));
    on_off(r1.vary_input(t2));
    cout << "Now remote:\n";
    r1.show_mode();
}

// number2
void bad_hmean::messg() const
{
    cout << what() << endl;
    cout << "Numbers (" << a << ", " << b << ") must not be additive.\n";
}
void bad_gmean::messg() const
{
    cout << what() << endl;
    cout << "Numbers (" << a << ", " << b << ") must be positive.\n";
}
double hmean(double a, double b)
{
    if (a == -b)
        throw bad_hmean(a, b);
    return 2.0 * a * b / (a + b);
}
double gmean(double a, double b)
{
    if (a < 0 || b < 0)
        throw bad_gmean(a, b);
    return sqrt(a * b);
}
void number2()
{
    cout << "\nExercise 2\n";
    const int S = 5;
    seed_rand();
    double a, b;
    for (int i = 0; i < S; ++i)
    {
        cout << i+1 << "#:\n";
        if (i == 0)
        {
            a = 5;
            b = -5;
        }
        else
        {
            a = double(rand() % 101 - 50) / 20;
            b = double(rand() % 101 - 50) / 20;
        }
        try
        {
            cout << " Harmonic mean of " << a << ", " << b << " is: " << hmean(a, b) << endl;
            cout << " Geometric mean of " << a << ", " << b << " is: " << gmean(a, b) << endl;
        }
        catch (bad_hmean &bh)
        {
            bh.messg();
        }
        catch (bad_gmean &bg)
        {
            bg.messg();
        }
    }
    cout << "Buy!\n";
}

// number3
void hmean_bad::messg() const
{
    cout << what() << endl;
    cout << "Numbers (" << a << ", " << b << ") must not be additive.\n";
}
void gmean_bad::messg() const
{
    cout << what() << endl;
    cout << "Numbers (" << a << ", " << b << ") must be positive.\n";
}
double hmean1(double a, double b)
{
    if (a == -b)
        throw hmean_bad(a, b);
    return 2.0 * a * b / (a + b);
}
double gmean1(double a, double b)
{
    if (a < 0 || b < 0)
        throw gmean_bad(a, b);
    return sqrt(a * b);
}
void number3()
{
    cout << "\nExercise 3\n";
    const int S = 5;
    seed_rand();
    double a, b;
    for (int i = 0; i < S; ++i)
    {
        cout << i+1 << "#:\n";
        if (i == 0)
        {
            a = 5;
            b = -5;
        }
        else
        {
            a = double(rand() % 101 - 50) / 20;
            b = double(rand() % 101 - 50) / 20;
        }
        try
        {
            cout << " Harmonic mean of " << a << ", " << b << " is: " << hmean1(a, b) << endl;
            cout << " Geometric mean of " << a << ", " << b << " is: " << gmean1(a, b) << endl;
        }
        catch (bad_attempt &ba)
        {
            ba.messg();
        }
    }
    cout << "Buy!\n";
}

// number4
void Sales::bad_ind::messg() const
{
    cout << what() << " (ind = " << bi << ", max_ind = " << M - 1 << ")\n";
}
Sales::Sales(int *p_m, int y)
{
    for (int i = 0; i < M; ++i)
        per_month[i] = p_m[i];
    year = y;
}
int & Sales::operator[](int i)
{
    if (i >= M || i < 0)
        throw bad_ind(i);
    return per_month[i];
}
int Sales::operator[](int i) const
{
    if (i >= M || i < 0)
        throw bad_ind(i);
    return per_month[i];
}
void Sales::show() const
{
    cout << " Sales in " << year << " year:\n";
    for (int i = 0; i < M; ++i)
        cout << per_month[i] << ' ';
    cout << endl;
}
void LabelSales::lbad_ind::messg() const
{
    cout << what() << " (ind = " << val_bi() << ", max_ind = " << M - 1 <<")\n";
}
int & LabelSales::operator[](int i)
{
    if (i >= M || i < 0)
        throw lbad_ind(i);
    return Sales::operator[](i);
}
int LabelSales::operator[](int i) const
{
    if (i >= M || i < 0)
        throw lbad_ind(i);
    return Sales::operator[](i);
}
void LabelSales::show() const
{
    cout << " Label: " << label << endl;
    Sales::show();
}
void number4()
{
    cout << "\nExercise 4\n";
    int pm1[12] = {12, 14, 9, 13, 8, 10, 11, 15, 13, 12, 14, 19};
    int pm2[12] = {8, 10, 11, 15, 13, 12, 14, 19, 12, 14, 9, 13};
    string lab = "Delicious-farm";
    Sales s(pm1, 1998);
    LabelSales ls(pm2, 1999, lab);
    try
    {
        cout << "1#:\n";
        s.show();
        cout << "Enter some index (0 - 11): ";
        int ind = input_int();
        cout << "s[" << ind << "] = " << s[ind] << endl;
        cout << "2#:\n";
        ls.show();
        cout << "Enter some index (0 - 11): ";
        ind = input_int();
        cout << "ls[" << ind << "] = " << ls[ind] << endl;
    }
    catch (Sales::bad_ind &bi)
    {
        if (typeid(bi) == typeid(LabelSales::lbad_ind))
        {
            bi.messg();
            cout << "Buy!\n";
        }
        else
        {
            bi.messg();
            cout << "Good Buy!\n";
        }
    }
}
