#include "ch11_working_with_classes.hpp"
#include <cmath>
#include <fstream>
#include <cstdlib> // rand() srand()
#include <ctime> // time()
#include "Utils.hpp"

using std::cin;
using std::cout;
using std::endl;

static char const* IO_FILE = "ch11_io.txt";

static void vect(void);
static void number1_3(void);
static void number2_7(void);
static void number4(void);
static void number5_6(void);

int ch11_working_with_classes()
{
    print_run_chapter_message(11);
    vect();
    number1_3();
    number2_7();
    number4();
    number5_6();
    return EXIT_SUCCESS;
}

// vect + number1_3
double const DEG_RAD = 45.0 / atan(1.0);
void Vector::set_rect(void)
{
    x = magnitude * cos(angle);
    y = magnitude * sin(angle);
}
void Vector::set_pol(void)
{
    magnitude = sqrt(x*x + y*y);
    angle = 0.0;
    if (x == 0.0)
    {
        if (y > 0.0)
            angle = M_PI / 2.0;
        else if (y < 0.0)
            angle = -M_PI / 2.0;
    }
    else
        angle = atan(y / x);
}
Vector::Vector(double a1, double a2, Mode m)
{
    M = m;
    if (m == RECT)
    {
        x = a1;
        y = a2;
        set_pol();
    }
    else if (m == POL)
    {
        magnitude = a1;
        angle = a2 / DEG_RAD;
        set_rect();
    }
    else
    {
        std::cout << "Unknown mode, vector = 0.\n";
        x = y = magnitude = angle = 0.0;
    }
}
void Vector::reset(double a1, double a2, Mode m)
{
    M = m;
    if (m == RECT)
    {
        x = a1;
        y = a2;
        set_pol();
    }
    else if (m == POL)
    {
        magnitude = a1;
        angle = a2 / DEG_RAD;
        set_rect();
    }
}
Vector Vector::operator+(const Vector &vect) const
{
    return Vector(x + vect.x, y + vect.y);
}
Vector Vector::operator-(const Vector &vect) const
{
    return Vector(x - vect.x, y - vect.y);
}
Vector Vector::operator-(void) const
{
    return Vector(-x, -y);
}
Vector Vector::operator*(double coef) const
{
    Vector v;
    if (M == RECT)
    {
        v.reset(x * coef, y * coef, M);
        v.set_pol();
    }
    else if (M == POL)
    {
        v.reset(magnitude * coef, angle, M);
        v.set_rect();
    }
    return v;
}
Vector operator*(double coef, const Vector &vect)
{
    return vect * coef;
}
ostream & operator<<(ostream& sout, const Vector &vect)
{
    if (vect.M == Vector::RECT)
        sout << "(x,y): (" << vect.x << ", " << vect.y << ')';
    else if (vect.M == Vector::POL)
        sout << "(m,a): (" << vect.magnitude << ", " << vect.angle * DEG_RAD << ')';
    else
        sout << "Unkown mode.";
    return sout;
}
Vector::operator double()
{
    return x;
}
Vector::operator int()
{
    return x + 0.5;
}
void vect()
{
    cout << "\nVect\n";
    Vector v1(12.3, 17.491), v2 = Vector(0.0, -2.3, Vector::RECT), v3;
    v2.pol_mode();
    cout << "v1:\n" << v1 << "\nv2:\n" << v2 << '\n';
    v2.reset((double) 1, double(45), Vector::POL);
    v2.rect_mode();
    v1 = 2; // v1 = double(2); - automatical CONSTRUCTOR'S conversation
    cout << "v1 and v2 were reseted.\nv1:\n" << v1 << "\nv2:\n" << v2 << '\n';
    double a = v2;      // conversion function
    cout << "a = v2 = " << a << '\n';
    v3 = 2.0 * (v1 - v2);
    // int(v3) - explicit conversion
    cout << "v3 = 2.0 * (v1 - v2) :\n" << v3 << "\nRounded x: " << int(v3) << '\n';
}
void number1_3(void)
{
    cout << "\nNumber 1-3\n";
    std::ofstream f(IO_FILE);
    double dist = 100.0, step = 20.0;
    cout << "The file was reseted.\n";
    f << "Step: " << step << ", distance: " << dist << '\n';
    Vector vNow, v;
    int i = 0;
    seed_rand();
    while (vNow.MagVal() < dist)
    {
        double direction = double(rand() % 360);
        v.reset(step, direction, Vector::POL);
        vNow = vNow + v;
        f << ++i << ") " << vNow << '\n';
    }
    f
    << "After " << i << " steps, the subject has the following location:\n"
    << vNow << '\n';
    vNow.pol_mode();
    f << "or:\n" << vNow << '\n' << "Average outward step: " << vNow.MagVal() / double(i);
    cout << "The file '" << IO_FILE << "' was written\n";
    f.close();
}

// number2_7
void ComplNum::set_xy(void)
{
    x = r * cos(u);
    y = r * sin(u);
}
void ComplNum::set_ru(void)
{
    r = sqrt(x*x + y*y);
    u = 0.0;
    if (x == 0.0)
    {
        if (y > 0.0)
            u = M_PI / 2;
        else if (y < 0.0)
            u = -M_PI / 2;
    }
    else
        u = atan(y / x);
}
ComplNum::ComplNum(double xr, double yu, Mode m)
{
    M = m;
    if (m == ALG)
    {
        x = xr;
        y = yu;
        set_ru();
    }
    else
    {
        r = xr;
        u = yu / DEG_RAD;
        set_xy();
    }
}
void ComplNum::reset(double xr, double yu, Mode m)
{
    M = m;
    if (m == ALG)
    {
        x = xr;
        y = yu;
        set_ru();
    }
    else
    {
        r = xr;
        u = yu / DEG_RAD;
        set_xy();
    }
}
ComplNum & ComplNum::SetMode(Mode m)
{
    M = m;
    return *this;
}
ComplNum ComplNum::operator+(const ComplNum &z) const
{
    return ComplNum(x + z.x, y + z.y);
}
ComplNum ComplNum::operator-(const ComplNum &z) const
{
    return ComplNum(x - z.x, y - z.y);
}
ComplNum ComplNum::operator-(void) const
{
    return ComplNum(-x, -y);
}
ComplNum ComplNum::operator*(const ComplNum &z) const
{
    return ComplNum(r * z.r, (u + z.u) * DEG_RAD, EXPN);
}
ComplNum ComplNum::operator/(const ComplNum &z) const
{
    return ComplNum(r / z.r, (u - z.u) * DEG_RAD, EXPN);
}
ComplNum ComplNum::operator~(void) const
{
    return ComplNum(x, -y);
}
ostream & operator<<(ostream& sout, const ComplNum &z)
{
    if (z.M == ComplNum::ALG)
    {
        if (z.y < 0)
            sout << z.x << " - " << -z.y << "•i";
        else
            sout << z.x << " + " << z.y << "•i";
    }
    else if (z.M == ComplNum::TRIG)
    {
        sout << z.r << "(cos(" << int(z.u * DEG_RAD) <<
            "º) + i•sin(" << int(z.u * DEG_RAD) << "º))";
    }
    else
        sout << z.r << "•exp[" << int(z.u * DEG_RAD) << "º]";
    return sout;
}
std::istream & operator>>(std::istream &sin, ComplNum &z)
{
    double ax{}, ay{};
    cout << "x (2.3): ";
    ax = input_double(sin);
    cout << "y (2.3): ";
    ay = input_double(sin);
    z.reset(ax, ay, ComplNum::ALG);
    return sin;
}
void number2_7(void)
{
    cout << "\nNumber 2-7\n";
    ComplNum z1, z2(2.1, 2.03), z3;
    z1.reset(2.3, 45.1, ComplNum::EXPN);
    cout << "z1 = " << z1.SetMode() << " = " << z1.SetMode(ComplNum::EXPN)
    << "\nz2 = " << z2 << " = " << z2.SetMode(ComplNum::EXPN) << '\n';
    z3 = z1 / z2;
    cout << "z1 / z2 = " << z3 << " = " << z3.SetMode(ComplNum::ALG) << '\n';
    z3 = z1 * z2;
    cout << "z1 * z2 = " << z3 << " = " << z3.SetMode(ComplNum::ALG) << '\n'
    << "-z1 - z2 = " << -z1 - z2 << '\n';
    cout << "Enter z3:\n";
    cin >> z3;
    cout << "~z3 = " << ~z3 << " = " << (~z3).SetMode(ComplNum::TRIG) << '\n';
}

// number4
Time::Time(long m)
{
    FullMin = m;
    hour = int(FullMin / long(60));
    minuts = int(FullMin % long(60));
}
Time::Time(int h, int m)
{
    hour = h;
    minuts = m;
    FullMin = h * 60 + m;
}
void Time::reset(long m)
{
    FullMin = m;
    hour = int(FullMin / long(60));
    minuts = int(FullMin % long(60));
}
void Time::reset(int h, int m)
{
    hour = h;
    minuts = m;
    FullMin = h * 60 + m;
}
Time Time::operator+(const Time &t) const
{
    return Time(FullMin + t.FullMin);
}
Time Time::operator-(const Time &t) const
{
    if (FullMin < t.FullMin)
        return Time();
    return Time(FullMin - t.FullMin);
}
Time Time::operator+(int m) const
{
    return Time(FullMin + m);
}
Time Time::operator-(int m) const
{
    if (FullMin < m)
        return Time();
    return Time(FullMin - m);
}
Time operator+(int m, const Time &t)
{
    return Time(m + t.FullMin);
}
Time operator-(int m, const Time &t)
{
    if (t.FullMin > m)
        return Time();
    return Time(m - t.FullMin);
}
ostream & operator<<(ostream& sout, const Time &t)
{
    sout << t.hour << " hour(s) " << t.minuts << " minute(s)";
    return sout;
}
Time::operator long()
{
    return FullMin;
}
void number4(void)
{
    cout << "\nNumber 4\n";
    Time t1 = Time(937), t2(23, 24);
    cout
    << "t1 = " << t1 << " = " << long(t1) << " minute(s)\n"
    << "t2 = " << t2 << " = " << long(t2) << " minute(s)\n"
    << "t1 - t2 = " << t1 - t2 << '\n'
    << "t2 - t1 - 78 = " << t2 - t1 - 78 << " = " << long(t2 - t1 - 78) << " minute(s)\n"
    << "t1 + t2 = " << t1 + t2 << '\n'
    << "23 - t2 = " << 23 - t2 << '\n'
    << "2 + t2 - 23 = " << 2 + t2 - 23 << '\n';
    Time t3 = (t2.operator-(t1)).operator-(78);
    cout << "t3 = " << t3 << " = " << long(t3) << " minute(s)\n";
}

// number5_6
Stonewt::Stonewt(double lbs, Mode m)
{
    M = m;
    pounds = lbs;
    stone = int(lbs) / Lbs_stn;
    pds_left = lbs - int(lbs) + int(lbs) % Lbs_stn;
}
Stonewt::Stonewt(int stn, double lbs, Mode m)
{
    M = m;
    stone = stn;
    pds_left = lbs;
    pounds = stn * Lbs_stn + lbs;
}
void Stonewt::reset(double lbs, Mode m)
{
    M = m;
    pounds = lbs;
    stone = int(lbs) / Lbs_stn;
    pds_left = lbs - int(lbs) + int(lbs) % Lbs_stn;
}
void Stonewt::reset(int stn, double lbs, Mode m)
{
    M = m;
    stone = stn;
    pds_left = lbs;
    pounds = stn * Lbs_stn + lbs;
}
void Stonewt::LbsMode(void)
{
    M = LBS;
}
void Stonewt::StnMode(void)
{
    M = STN;
}
Stonewt Stonewt::operator+(const Stonewt &s) const
{
    return Stonewt(pounds + s.pounds, LBS);
}
Stonewt Stonewt::operator-(const Stonewt &s) const
{
    if (pounds < s.pounds)
        return Stonewt();
    return Stonewt(pounds - s.pounds, LBS);
}
Stonewt Stonewt::operator*(double a) const
{
    return Stonewt(pounds * a, LBS);
}
bool Stonewt::operator<(const Stonewt &s) const
{
    if (pounds < s.pounds)
        return true;
    return false;
}
bool Stonewt::operator>(const Stonewt &s) const
{
    if (pounds > s.pounds)
        return true;
    return false;
}
bool Stonewt::operator==(const Stonewt &s) const
{
    if (pounds == s.pounds)
        return true;
    return false;
}
Stonewt operator*(double a, const Stonewt &s)
{
    return Stonewt(s.pounds * a, Stonewt::LBS);
}
ostream & operator<<(ostream& sout, const Stonewt &s)
{
    if (s.M == Stonewt::STN)
        sout << s.stone << " stone(s) " << s.pds_left << " pound(s)";
    else
        sout << s.pounds << " pound(s)";
    return sout;
}
void number5_6(void)
{
    cout << "\nNumber 5-6\n";
    Stonewt s1 = Stonewt(345.7), s2 = {23, 12.7};
    cout << "s1 = " << s1 << '\n'
        << "s2 = " << s2 << " = " << double(s2) << " pound(s)" << '\n'
        << "9•s1 + s2 = " << 9 * s1 + s2 << '\n';
    s1.StnMode();
    cout << "s1 = " << s1 << "\n\n";
    const int S = 6;
    Stonewt s[S] =
    {
        Stonewt(327.18),
        Stonewt(24, 2.385, Stonewt::LBS),
    };
    srand(int(time(0)));
    for (int i = 0; i < S - 2; ++i)
        s[i+2].reset(double(rand() % 20 + 320) + double(rand() % 100) / 100, Stonewt::LBS);
    Stonewt maxi, mini;
    maxi = mini = s[0];
    for (int i = 0; i < S; ++i)
    {
        maxi = s[i] > maxi ? s[i] : maxi;
        mini = s[i] < mini ? s[i] : mini;
    }
    for (int i = 0; i < S; ++i)
        cout << "s[" << i << "] = " << s[i] << '\n';
    cout << "Max = " << maxi << ", Min = " << mini << '\n';
}
