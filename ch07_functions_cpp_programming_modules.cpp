#include "ch07_functions_cpp_programming_modules.hpp"
#include "Utils.hpp"
#include <iostream>
#include <cmath>
#include <array>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

using namespace std;

struct box
{
    char maker[FF_SIZE];
    double height;
    double width;
    double length;
    double volume;
};
struct student
{
    Line fullname;
    Line hobby;
    int ooplevel;
};

const char Season[4][8] = {"Spring", "Summer", "Fall", "Winter"};

static void ex1(void);
static void ex2(void);
static void ex3(void);
static void ex4(void);
static void ex5(void);
static void ex6(void);
static void ex7(void);
static void ex9(void);
static void ex10(void);

int ch07_functions_cpp_programming_modules()
{
    print_run_chapter_message(7);
    ex1();
    ex2();
    ex3();
    ex4();
    ex5();
    ex6();
    ex7();
    ex9();
    ex10();
    return EXIT_SUCCESS;
}

double ex1_avg(void)
{
    cout << "Enter the 1st number != 0: ";
    int num1 = input_int();
    cout << "Enter the 2nd number != 0: ";
    int num2 = input_int();
    if (num1 != 0 && num2 != 0)
        return 2 * double(num1) / (num1 + num2) * num2;
    else
        return 0;
}
void ex1(void)
{
    cout << "\nExercise 1\n";
    double average = ex1_avg();
    while (average == 0)
        average = ex1_avg();
    cout << "Harmonic mean of the numbers: " << average << endl;
}

void ex2_arr_enter(int* arr, const int& N)
{
    cout << "Enter " << N << " numbers.\n";
    for (size_t i = 0; i < N; ++i)
    {
        cout << "arr[" << i << "]: ";
        arr[i] = input_int();
    }
}

void ex2(void)
{
    cout << "\nExercise 2\n";
    const size_t N = 4;
    int arr[N];
    ex2_arr_enter(arr, N);
    double average = 0;
    cout << "The array is:\n";
    for (size_t i = 0; i < N; ++i)
    {
        cout << ' ' << *(arr + i);
        average += arr[i];
    }
    cout << endl;
    average /= N;
    cout << "The average of elements: " << average << endl;
}

void ex3_calc_volume(box *b)
{
    b->volume = (*b).height * b->length * b->width;
}

void ex3_print(box b)
{
    cout << "Box:"
        << "\n  Maker: " << b.maker
        << "\n  Height: " << b.height
        << "\n  Width: " << b.width
        << "\n  Length: " << b.length
        << "\n  Volume: " << b.volume << endl;
}

void ex3(void)
{
    cout << "\nExercise 3\n";
    box b = {"Petya", 14.3, 16.72, 12.19};
    ex3_calc_volume(&b);
    ex3_print(b);
}

ld ex4_probability(int max, int n, int megaR)
{
    ld R = 1;
    for (int i = 0; i < n; ++i)
        R *= double(max - i) / (n - i);
    R *= megaR;
    return R;
}

void ex4(void)
{
    cout << "\nExercise 4\n";
    int max = 47, amount = 5, megaR = 27;
    cout << "Lottery: numbers from 1-" << max
        << ";\namount: " << amount << ";\nmega R: " << megaR << endl;
    cout << "Chance to win is 1 from " << ex4_probability(max, amount, megaR) << ".\n";
}

ld ex5_factorial(size_t max_base, size_t cur_base = 1)
{
    if (cur_base < max_base)
        return ld(cur_base) * ex5_factorial(max_base, cur_base + 1);
    return ld(cur_base);
}
void ex5(void)
{
    cout << "\nExercise 5\n";
    size_t base{};
    ld factorial{};
    cout << "Enter a number (e.g. 4, 'q' to stop): ";
    Line line = Line(cin);
    while (line != "q")
    {
        if (!parse_size(line, base))
        {
            cout << "Enter a number (e.g. 4, 'q' to stop): ";
            input_line(line);
            continue;
        }
        factorial = ex5_factorial(base);
        cout << "factorial: " << factorial << endl;
        cout << "Enter a number (e.g. 4, 'q' to stop): ";
        input_line(line);
    }
}

void ex6_fill_array(int *arr, const int &N)
{
    cout << "Enter " << N << " number(s):\n";
    for (size_t i = 0; i < N; ++i)
    {
        cout << "arr[" << i << "]: ";
        arr[i] = input_int();
    }
}
void ex6_show_array(const int *arr, const size_t &N)
{
    cout << "The array:\n";
    for (int i = 0; i < N; ++i)
        cout << ' ' << arr[i];
    cout << endl;
}
void ex6_reverse_array(int *arr, const size_t &N)
{
    for (size_t i = 0, opposite_i = N - 1; i < opposite_i; ++i, --opposite_i)
    {
        int temp = arr[i];
        arr[i] = arr[opposite_i];
        arr[opposite_i] = temp;
    }
}
void ex6(void)
{
    cout << "\nExercise 6\n";
    const size_t N = 3;
    int arr[N]{};
    ex6_fill_array(arr, N);
    cout << "The array:\n";
    ex6_show_array(arr, N);
    cout << "Reversing the array:\n";
    ex6_reverse_array(arr, N);
    cout << "Now the array:\n";
    ex6_show_array(arr, N);
}

void ex7_fill_array(int *begin, int *end) // begin inclusive, end exclusive
{
    cout << "Enter " << end - begin << " number(s):\n";
    size_t ind = 0;
    for (int *iter = begin; iter != end; ++iter)
    {
        cout << "*iterator for arr[" << ind << "]: ";
        *iter = input_int();
    }
}
void ex7_show_array(int *begin, int *end) // begin inclusive, end exclusive
{
    for (int *iter = begin; iter != end; ++iter)
        cout << ' ' << *iter;
    cout << endl;
}
void ex7(void)
{
    cout << "\nExercise 7\n";
    const size_t N = 3;
    int arr[N]{};
    ex7_fill_array(arr, arr + N);
    cout << "The array:\n";
    ex7_show_array(arr, arr + N);
    cout << "Address of the first element: " << arr << endl;
    cout << "Address of the last  element: " << arr + N << endl;
}

size_t ex9_new_students(student *students, const size_t &N)
{
    // 1st binding student
    cout << "Input of the first student.\n";
    cout << "  Fullname: ";
    input_line(students[0].fullname);
    while (students[0].fullname.empty())
    {
        cout << "  Fullname: ";
        input_line(students[0].fullname);
    }
    cout << "  Hobby: ";
    input_line(students[0].hobby);
    while (students[0].hobby.empty())
    {
        cout << "  Hobby: ";
        input_line(students[0].hobby);
    }
    cout << "  OOP level [-5, +5]: ";
    students[0].ooplevel = input_int();
    while (5 < students[0].ooplevel || students[0].ooplevel < -5)
    {
        cout << "  OOP level [-5, +5]: ";
        students[0].ooplevel = input_int();
    }
    // next students
    size_t n_students = 1;
    for (; n_students < N; ++n_students)
    {
        student &stu = students[n_students];
        cout << "Input of the student #" << n_students + 1 << endl;
        cout << "  Fullname (empty line to stop): ";
        input_line(stu.fullname);
        if (stu.fullname.empty())
            return n_students;
        cout << "  Hobby (empty line to stop): ";
        input_line(stu.hobby);
        if (stu.hobby.empty())
            return n_students;
        cout << "  OOP level [-5, +5]: ";
        stu.ooplevel = input_int();
        while (5 < stu.ooplevel || stu.ooplevel < -5)
        {
            cout << "  OOP level [-5, +5]: ";
            stu.ooplevel = input_int();
        }
    }
    return n_students;
}
void ex9_show_students(student *students, const size_t &N)
{
    for (size_t i = 0; i < N; ++i)
    {
        cout << "Student #" << i + 1 << endl;
        cout << "  Fullname:  " << students[i].fullname << endl;
        cout << "  Hobby:     " << students[i].hobby << endl;
        cout << "  OOP level: " << students[i].ooplevel << endl;
    }
}
void ex9(void)
{
    cout << "\nExercise 9\n";
    student students[FF_SIZE];
    const size_t N = ex9_new_students(students, FF_SIZE);
    ex9_show_students(students, N);
}

typedef double (*calc_alias)(double, double, double (*)(double, double));
double add(double x, double y)
{
    return x + y;
}
double module_minus(double x, double y)
{
    return x < y ? y - x : x - y;
}
double calculate(double x, double y, double (*calc)(double, double))
{
    return calc(x, y);
}
void ex10(void)
{
    cout << "\nExercise 10\n";
    double (*calc_functions[2])(double, double);
    calc_functions[0] = add;
    calc_functions[1] = module_minus;
    calc_alias calc = calculate;
    double x{}, y{};
    Line line = "continue";
    while (line != "q")
    {
        cout << "Enter the 1st number (e.g. 2.0): ";
        x = input_double();
        cout << "Enter the 2nd number (e.g. 3.0): ";
        y = input_double();
        cout << x << " + " << y << " = " << calculate(x, y, calc_functions[0]) << endl;
        cout << '|' << x << " - " << y << "| = " << calc(x, y, module_minus) << endl;
        cout << "'q' to stop, otherwise continue: ";
        input_line(line);
    }
}
