#include "ch18_visiting_with_new_standard.hpp"

using namespace std;

static void already();
static void rval();
static void defaulted_deleted_methods();
static void lambda();
static void fun_adater();
static void packets_of_parameters();

int ch18_visiting_with_new_standard()
{
    print_run_chapter_message(18);
    already();
    rval();
    defaulted_deleted_methods();
    lambda();
    fun_adater();
    packets_of_parameters();
    return EXIT_SUCCESS;
}

// rval
int Field::ct = 0;

Field::Field() : n(0)
{
    cout << ++ct << "[default]\n";
    
    s = new char[1];
    s[0] = '\0';
}
Field::Field(int _n, char c) : n(_n)
{
    cout << ++ct << "[simple]\n";
    
    s = new char[n];
    memset(s, c, n);
}
Field::Field(int _n, char *_s) : n(_n)
{
    cout << ++ct << "[simple*]\n";
    
    s = new char[n];
    memcpy(s, _s, n);
}
Field::Field(const Field &f) : n(f.n)
{
    cout << ++ct << "[copier]\n";
    
    s = new char[n];
    memcpy(s, f.s, n);
}
Field::Field(Field &&f) : n(f.n)
{
    cout << ++ct << "[carry-copier]\n";
    s = f.s;
    f.s = nullptr;
    f.n = 0;
}
Field::~Field()
{
    cout << --ct << "[destructor]\n";
    
    delete [] s;
}

void Field::Set(int _n, char c)
{
    cout << "[Set]\n";
    n = _n;
    
    delete [] s;
    s = new char[n];
    memset(s, c, n);
}
Field Field::operator+(const Field &f) const
{
    cout << "[operator+]\n";
    
    char *_s = new char[n + f.n];
    memcpy(_s, s, n);
    memcpy(_s + n, f.s, f.n);
    
    return Field(n + f.n, _s);
}
Field & Field::operator=(const Field &f)
{
    cout << "[operator=]\n";
    
    if (&f == this)
        return *this;
    
    delete [] s;
    n = f.n;
    s = new char[n];
    memcpy(s, f.s, n);
    
    return *this;
}
Field & Field::operator=(Field &&f)
{
    cout << "[carry-operator=]\n";
    
    delete [] s;
    n = f.n;
    s = f.s;
    f.s = nullptr;
    f.n = 0;
    return *this;
}
void Field::Show() const
{
    for (int i = 0; i < n; ++i)
        cout << s[i];
    cout << ", n = " << n << '\n';
}

// lambda
bool f3(int &a) {return a % 3 == 0;}
bool f13(int &a) {return a % 13 == 0;}

// fun_adater
double dub(double a) {return 2 * a;}
double square(double a) {return a * a;}

//-FUNCTIONS----------------------------------------------------------------------------------------

void already()
{
    cout << "\nAlready\n";
    // auto
    std::set< std::pair<int, int> > st;
    st.insert(make_pair(3, 2));
    cout << " Help of auto:\n";
    for (auto it = st.begin(); it != st.end(); ++it)
        cout << it->first << ' ' << it->second << '\n';
    // decltype and "tailing return"
    int a1 = 3;
    double a2 = 4.1;
    cout << " Look at the header.\n";
    cout << "a1 = " << a1 << ", a2 = " << a2 << '\n';
    cout << "multiplic(a1, a2) = " << Multiplic(a1, a2) << "\n";
    // "using =" makes aliases (псевдонимы)
    cout << " array12 - is an alias declared in header.\na3:\n";
    array12<int> a3;
    for (int i = 0; i < 12; ++i)
        a3[i] = 12 - i;
    sort(a3.begin(), a3.end());
    for (int i = 0; i < 12; ++i)
        cout << ' ' << a3[i];
    cout << endl;
    // added noexcept
}

void rval()
{
    cout << "\nRval\n";
    // "&& rvalue" is for avoiding unnecessary actions
    // c++98 objects:   rvalue -> temporary -> new
    // c++11 objects:   rvalue -> new
    const int S = 4;
    const char C[S] = {'.', '?', ':', '_'};
    const int A[S] = {3, 2, 3, 2};
    Field f[S];
    for (int i = 0; i < S; ++i)
        f[i].Set(A[i], C[i]);
    cout << " f[" << S - 1 << "] = f[0] + f[1];\n";
    f[S-1] = f[0] + f[1];
    cout << " Field temp = f[0] + f[1]:\n";
    Field temp = f[0] + f[1]; // in this statement the compiler takes control
    cout << '\n';
    cout << "temp:\n";
    temp.Show();
    cout << "f:\n";
    for (int i = 0; i < S; ++i)
    {
        cout << " f[" << i << "]: ";
        f[i].Show();
    }
}

void defaulted_deleted_methods()
{
    cout << "\nDefaulted deleted methods\n";
    Cl1 a1(3.4, 5.17), a2(43.62, 20.9);
    cout << "a1: ";
    a1.Show();
    cout << "a2: ";
    a2.Show();
    cout << " [copier] was deleted, so [carry-copier] for a3:\n";
    Cl1 a3(a1 + a2), a4;
    a3.Show();
    cout << "a4: ";
    a4.Show();
    a3.Set(3.0, 5.0); // Set(int, int) = delete; => can't use "a3.Set(3, 5);"
    cout << " Now a3:\n";
    a3.Show();
    // expamples with directive using
    Cl2 a5(0.0, 0.0, 3);
    a5.Set(1.1, 2.2);
    cout << " expamples with directive using\na5:\n";
    a5.Show();
    Cl3 a6;
    a6.Set(0.0, 0.0, 3);
    a6.Set(true, true);     // if there was no "using", all Cl1::Set would be blocked
    cout << "a6:\n";
    a6.Show();
    cout << "Ou. Sorry\na6:\n";
    a6.ShowAll();
}

void lambda()
{
    cout << "\nLambda\n";
    const int S1 = 100, S2 = S1 * 100, S3 = S2 * 100;
    seed_rand();
    vector<int> numbers(S1);
    generate(numbers.begin(), numbers.end(), rand);
    long ct3 = count_if(numbers.begin(), numbers.end(), f3),
    ct13 = count_if(numbers.begin(), numbers.end(), f13);
    cout << " Sample size: " << S1 << endl;
    cout << "Count of numbers divisible by 3:  " << ct3  << endl;
    cout << "Count of numbers divisible by 13: " << ct13 << endl;
    class f_mod
    {
    private:
        int m;
    public:
        f_mod(int a) : m(a) {}
        bool operator()(int x) {return x % m == 0;}
    };
    numbers.resize(S2);
    generate(numbers.begin(), numbers.end(), rand);
    ct3 = count_if(numbers.begin(), numbers.end(), f_mod(3));
    ct13 = count_if(numbers.begin(), numbers.end(), f_mod(13));
    cout << " Sample size: " << S2 << endl;
    cout << "Count of numbers divisible by 3:  " << ct3  << endl;
    cout << "Count of numbers divisible by 13: " << ct13 << endl;
    // lambda 1st variant
    numbers.resize(S3);
    generate(numbers.begin(), numbers.end(), rand);
    // lambda-expression like unnamed funtcion: [](type arg, ..) {body; ...}
    ct3 = count_if(numbers.begin(), numbers.end(),
                   [](int x) {return x % 3 == 0;});
    ct13 = count_if(numbers.begin(), numbers.end(),
                    [](int x) {return x % 13 == 0;});
    cout << "[lambda1]\n";
    cout << " Sample size: " << S3 << endl;
    cout << "Count of numbers divisible by 3:  " << ct3  << endl;
    cout << "Count of numbers divisible by 13: " << ct13 << endl;
    // lambda 2nd variant
    /*
     1)
     [&var1, var2](type arg, ..) {body; ...}
     var1, var2 - automatic variable in the area of visibility
     var1 - catched, var2 - catched only value
     2)
     [&, var1](type arg, ..) {body; ...}
     [&] => are catched all automatic, but only value of var1
     3)
     [=, &var1](type arg, ..) {body; ...}
     [=] => are catched all values, but var1 "total" catched
     */
    ct3 = ct13 = 0;
    for_each(numbers.begin(), numbers.end(),
             [&ct3, &ct13](int x) {ct3 += x % 3 == 0; ct13 += x % 13 == 0;});
    cout << "[lambda2]\n";
    cout << " Sample size: " << S3 << endl;
    cout << "Count of numbers divisible by 3:  " << ct3  << endl;
    cout << "Count of numbers divisible by 13: " << ct13 << endl;
}

void fun_adater()
{
    cout << "\nFun adapter\n";
    // bad variant
    double a = 2.2;
    cout << "Functional pointer square:\n";
    cout << ' ' << use_f(a, square) << endl;
    cout << "Functional pointer dub:\n";
    cout << ' ' << use_f(a, dub) << endl;
    cout << "Functional object Fmult:\n";
    cout << ' ' << use_f(a, Fmult(a)) << endl;
    cout << "Functional object Fplus:\n";
    cout << ' ' << use_f(a, Fplus(a)) << endl;
    cout << "Lambda expression 1:\n";
    cout << ' ' << use_f(a, [](const double &x) {return x * x;} ) << endl;
    cout << "Lambda expression 2:\n";
    cout << ' ' << use_f(a, [](const double &x) {return x + x;} ) << endl;
    cout << "There are many classes from template use_f,\n"
        "because of different types in 2nd argiment.\n"
        "Class function helps to solve this problem.\n";
    cout << "Try:\n";
    typedef function<double(double)> fdd; // all of them have the same signature
    cout << "Functional pointer square:\n";
    cout << ' ' << use_f(a, fdd(square)) << endl;
    cout << "Functional pointer dub:\n";
    cout << ' ' << use_f(a, fdd(dub)) << endl;
    cout << "Functional object Fmult:\n";
    cout << ' ' << use_f(a, fdd(Fmult(a))) << endl;
    cout << "Functional object Fplus:\n";
    cout << ' ' << use_f(a, fdd(Fplus(a))) << endl;
    fdd lam1 = [](const double &x) {return x * x;},
    lam2 = [](const double &x) {return x + x;};
    cout << "Lambda expression 1:\n";
    cout << ' ' << use_f(a, lam1) << endl;
    cout << "Lambda expression 2:\n";
    cout << ' ' << use_f(a, lam2) << endl;
    cout << "Good.\n";
}

void packets_of_parameters()
{
    cout << "\nPackets of parameters\n";
    cout << "Packets allow to use variable number of arguments\n";
    cout << "Sended to tamplate function arguments:\n" << showpoint;
    streamsize pr = cout.precision(2);
    string str = "d is very g";
    show_list('E', str, (float) 0.0, 'd');
    cout.unsetf(ios_base::showpoint);
    cout.precision(pr);
    cout << endl;
}
