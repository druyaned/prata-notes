#include "ch08_adventures_in_functions.hpp"
#include "Utils.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
typedef unsigned long ul;

using namespace std;

const char IO_FILE[] = "ch08_io.txt";

struct NameNumber {Line name; int number;};
struct CandyBar {Line name; double weight; int calories;};
struct SomeString {char *str; size_t n;};
struct Debt {char name[FF_SIZE]; double amount;}; // задолженность

void string_links(void);
void inheritance(void); // наследование + аргумент по умолчанию
void overload(void); // перегрузка функций
void practice_with_template(void); // мой_шаблон

static void ex1(void);
static void ex2(void);
static void ex3(void);
static void ex4(void);
static void ex5(void);
static void ex6(void);
static void ex7(void);

int ch08_adventures_in_functions()
{
    print_run_chapter_message(8);
    string_links();
    inheritance();
    overload();
    practice_with_template();
    ex1();
    ex2();
    ex3();
    ex4();
    ex5();
    ex6();
    ex7();
    return EXIT_SUCCESS;
}

const string &both(string &main_s, const string &adding_s)
{
    main_s = adding_s + main_s + adding_s;
    return main_s;
}
void string_links(void)
{
    cout << "\nString links\n";
    string str = "PUPS";
    cout << "Main string: " << str << "; address: " << &str << endl;
    string result = both(str, "***");
    // тут литерал не соответствует типу формального параметра,
    // но возможно приведение типа => "***" сохраняется во
    // временную строку (временная переменная)
    cout << "The string was enhanced.\n";
    cout << "Result:      " << result << "; address: " << &result << endl;
    cout << "Main string: " << str << "; address: " << &str << endl;
}

inline void add_to_file(ostream &fout, const char *str = "Default string.")
{
    fout << str;
}
void inheritance(void)
{
    cout << "\nInheritance\n";
    ofstream fout;
    fout.open(IO_FILE);
    if (!fout.is_open())
    {
        cout << "Couldn't open file '" << IO_FILE << "'\n";
        return;
    }
    add_to_file(fout, "Some text. ");
    add_to_file(fout);
    add_to_file(fout, "\n");
    // fstream - производный класс от ostream =>
    // => можно юзать cout. Это пример наследования.
    add_to_file(cout, "The file has been written.\n");
    fout.close();
}

void my_swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
bool my_swap(double &a, double &b)
{
    double temp = a;
    a = b;
    b = temp;
    return true;
}
void overload(void)
{
    cout << "\nOverload\n";
    int a = 7, b = 11;
    double x = 12.54, y = 324.231;
    cout << "a = " << a << "; b = " << b << endl;
    my_swap(a, b);
    cout << "After my_swap:\n";
    cout << "a = " << a << "; b = " << b << endl;
    cout << "Now another veriables.\n";
    cout << "x = " << x << "; y = " << y << endl;
    my_swap(x, y);
    cout << "x = " << x << "; y = " << y << endl;
}

template<typename any_name> void my_swap(any_name &a, any_name &b) // шаблон
{
    any_name c = a;
    a = b;
    b = c;
}
template <> void my_swap<NameNumber>(NameNumber &a, NameNumber &b) // явная специализация
{
    int temp_num = a.number;
    a.number = b.number;
    b.number = temp_num;
    Line temp = a.name;
    a.name = b.name;
    b.name = temp;
}
void practice_with_template(void) // note: template can be overloaded
{
    cout << "\nPractice with template\n";
    float x = 11, y = 22;
    cout << "x = " << x << "; y = " << y << endl;
    my_swap(x, y);
    cout << "After my_swap:\n";
    cout << "x = " << x << "; y = " << y << endl;
    NameNumber namNum1 = {"Hellos", 27}, namNum2 = {"Kakos", 72};
    cout << "namNum1: {" << namNum1.name << ", " << namNum1.number << "}\n";
    cout << "namNum2: {" << namNum2.name << ", " << namNum2.number << "}\n";
    my_swap(namNum1, namNum2);
    cout << "After my_swap:\n";
    cout << "namNum1: {" << namNum1.name << ", " << namNum1.number << "}\n";
    cout << "namNum2: {" << namNum2.name << ", " << namNum2.number << "}\n";
    char ch1 = 'x', ch2 = 'y';
    cout << "ch1 = '" << ch1 << "'; ch2 = '" << ch2 << "'\n";
    my_swap<char>(ch1, ch2);
    cout << "After my_swap:\n";
    cout << "ch1 = '" << ch1 << "'; ch2 = '" << ch2 << "'\n";
}

void ex1_print(const char *str, const size_t &n = 0)
{
    static size_t calls = 0; // amount of function calls
    ++calls;
    if (n == 0)
    {
        for (size_t i = 0; i < calls; ++i)
            cout << i + 1 << ": '" << str << "'\n";
        return;
    }
    for (size_t i = 0; i < n; ++i)
        cout << i + 1 << ": '" << str << "'\n";
}
void ex1(void)
{
    cout << "\nExercise 1\n";
    const char *str = "It's just a string.";
    cout << "Function call #1 'ex1_print(str);'\n";
    ex1_print(str);
    cout << "Function call #2 'ex1_print(str, 5);'\n";
    ex1_print(str, 5);
    cout << "Function call #3 'ex1_print(str);'\n";
    ex1_print(str);
}

void ex2_setting(CandyBar &, Line const& name, double weight = 80, int calories = 3072);
void ex2_setting(CandyBar &candy_bar, Line const& name, double weight, int calories)
{
    candy_bar.name = name;
    candy_bar.weight = weight;
    candy_bar.calories = calories;
}
inline void ex2_setting(CandyBar &);
void ex2_setting(CandyBar &candy_bar)
{
    candy_bar.name = "no_name";
    candy_bar.weight = 80;
    candy_bar.calories = 3072;
}
void ex2_show(const CandyBar &candy_bar)
{
    cout
        << "Name:     " << candy_bar.name << endl
        << "Weight:   " << candy_bar.weight << endl
        << "Calories: " << candy_bar.calories << endl;
}
void ex2(void)
{
    cout << "\nExercise 2\n";
    CandyBar candy_bar1{}, candy_bar2{};
    cout << "Enter name of manufacturer: ";
    Line name = Line(cin);
    cout << "Enter the weight of Candies (2.3): ";
    double weight = input_double();
    cout << "Enter the calories: ";
    int calories = input_int();
    ex2_setting(candy_bar1, name, weight, calories);
    ex2_setting(candy_bar2);
    cout << "Candy bar #1:\n";
    ex2_show(candy_bar1);
    cout << "Candy bar #2:\n";
    ex2_show(candy_bar2);
}

void ex3_remake(string &s)
{
    for (int i = 0; s[i]; ++i)
    {
        if (islower(s[i]))
            s[i] = 'A' + (s[i] - 'a');
    }
    cout << s << endl;
}
void ex3(void)
{
    cout << "\nExercise 3\n";
    string s;
    cout << "Enter a string (q to quite): ";
    getline(cin, s);
    while (s != "q")
    {
        ex3_remake(s);
        cout << "Enter a string (q to quite): ";
        getline(cin, s);
    }
}

void ex4_set(SomeString &, char []);
void ex4_set(SomeString &s, char str[])
{
    s.n = strlen(str);
    char *p = new char[s.n + 1];
    strcpy(p, str);
    s.str = p;
}
inline void ex4_show(const SomeString &, int quantity = 1);
void ex4_show(const SomeString &s, int n)
{
    cout << "DISPLAY THE STRING " << n << " TIMES:\n";
    for (int i = 0; i < n; ++i)
        cout << s.str << endl;
}
inline void ex4_show(const char [], int quantity = 1);
void ex4_show(const char c[], int n)
{
    cout << "DISPLAY THE STRING " << n << " TIMES:\n";
    for (int i = 0; i < n; ++i)
        cout << c << endl;
}
void ex4(void)
{
    cout << "\nExercise 4\n";
    SomeString a;
    char t[] = "Reality isn't what it used to be.";
    ex4_set(a, t);
    ex4_show(a);
    ex4_show(a, 3);
    t[0] = 'D';
    t[1] = 'u';
    ex4_show(t);
    ex4_show(t, 2);
    delete [] a.str;
}

template <class T> T ex5_max(T *a, const size_t &N)
{
    T m = a[0];
    for (int i = 0; i < N; ++i)
        m = a[i] < m ? m : a[i];
    return m;
}
void ex5(void)
{
    cout << "\nExercise 5\n";
    const size_t N = 5;
    int a1[N] = {5, 354, 357, 183, 95};
    double a2[N] = {15.12, 395.545, 354.453, 283.98, 395.54};
    cout << "The 1st array:\n";
    for (int i = 0; i < 5; ++i)
        cout << ' ' << a1[i];
    cout << endl;
    cout << "Max of them: " << ex5_max(a1, N) << endl;
    cout << "The 2nd array:\n";
    for (int i = 0; i < 5; ++i)
        cout << ' ' << a2[i];
    cout << endl;
    cout << "Max of them: " << ex5_max(a2, N) << endl;
}

template<typename T> const T ex6_max(const T *arr, const size_t &N)
{
    T mx = arr[0];
    for (size_t i = 1; i < N; ++i)
    {
        if (mx < arr[i])
            mx = arr[i];
    }
    return mx;
}
template<> char* const ex6_max<char*>(char* const *strs, const size_t &N)
{
    char* mx = strs[0];
    for (size_t i = 1; i < N; ++i)
    {
        if (strcmp(mx, strs[i]) < 0)
            mx = strs[i];
    }
    return mx;
}
template<typename T> inline void ex6_show_arr(const T *arr, const size_t &N)
{
    for (size_t i = 0; i < N; ++i)
        cout << " '" << arr[i] << '\'';
    cout << endl;
}
void ex6(void)
{
    cout << "\nExercise 6\n";
    const char *strs[] = {"string #1", "string #2", "some other string", "ok"};
    const size_t N = sizeof(strs) / sizeof(char*);
    const double dbls[N] = {1.23e-4, -98.76, 234.565, 100.001};
    const int ints[N] = {1, 2, 3, 4};
    cout << "strs:\n";
    ex6_show_arr(strs, N);
    cout << " max: " << ex6_max(strs, N) << endl;
    cout << "dbls:\n";
    ex6_show_arr(dbls, N);
    cout << " max: " << ex6_max(dbls, N) << endl;
    cout << "ints:\n";
    ex6_show_arr(ints, N);
    cout << " max: " << ex6_max(ints, N) << endl;
}

template <class T> T SumArray(T arr[], const size_t &N)
{
    cout << "SumArray #1 usage\n";
    T sum = 0;
    for (size_t i = 0; i < N; ++i)
    {
        cout << ' ' << arr[i];
        sum += arr[i];
    }
    cout << endl;
    return sum;
}
template <class T> T SumArray(T *p_arr[], const size_t &N)
{
    cout << "SumArray #2 usage\n";
    T sum = 0;
    for (size_t i = 0; i < N; ++i)
    {
        cout << ' ' << *p_arr[i];
        sum += *p_arr[i];
    }
    cout << endl;
    return sum;
}
void ex7(void)
{
    cout << "\nExercise 7\n";
    int numbers[] = {13, 31, 103, 301, 310, 130};
    const size_t N_NUMBERS = sizeof(numbers) / sizeof(int);
    Debt debts[] =
    {
        {"Ima Wolfe", 2400.0},
        {"Ura Foxe", 1300.0},
        {"Iby Stout", 1800.0}
    };
    const size_t N_DEBTS = sizeof(debts) / sizeof(Debt);
    double *p_amounts[N_DEBTS];
    for (size_t i = 0; i < N_DEBTS; ++i)
        p_amounts[i] = &( (debts + i)->amount ); // == &debts[i].amount
    int sum_numbers = SumArray(numbers, N_NUMBERS);
    double sum_amounts = SumArray(p_amounts, N_DEBTS);
    cout << "sum_numbers: " << sum_numbers << endl;
    cout << "sum_amounts: " << sum_amounts << endl;
}
