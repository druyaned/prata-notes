#include "ch05_loops_n_relational_expressions.hpp"
#include "Utils.hpp"
#include <string>
#include <cstring>  // strcpy(a1, a2); strcat(a1, a2);
#include <vector>
#include <array>
#include <iomanip>  // setw()
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

using namespace std;

static void expressions(void);
void compare_char_n_string(void);
void time_of_work(void);
void two_dimensional_array(void);
void practice_with_clock(void);
static void ex1(void);
static void ex2(void);
static void ex3(void);
static void ex4(void);
static void ex5(void);
static void ex6(void);
static void ex7(void);
static void ex8(void);
static void ex9(void);
static void ex10(void);

int ch05_loops_n_relational_expressions()
{
    print_run_chapter_message(5);
    expressions();
    compare_char_n_string();
    time_of_work();
    two_dimensional_array();
    practice_with_clock();
    ex1();
    ex2();
    ex3();
    ex4();
    ex5();
    ex6();
    ex7();
    ex8();
    ex9();
    ex10();
    return EXIT_SUCCESS;
}

static void expressions(void)
{
    cout << "\nExpressions:\n";
    // Выражение C++ — это значение или комбинация значений и операций,
    // и каждое выражение C++ имеет свое значение.
    int x;
    cout << "The expression (x = 100) has the value " << (x = 100) << endl;
    cout << "(x < 3): " << (x < 3) << endl;
    cout << "(x > 3): " << (x > 3) << endl;
    cout.setf(ios_base::boolalpha); // 0 -> false; 1, 2.2, ... -> true
    cout << "After cout.setf(ios_base::boolalpha)\n"
        << "(x < 3): " << (x < 3) << endl
        << "(x > 3): " << (x > 3) << endl;
    // increment and decrement
    int a = 5;
    int b = ++a;    // b = 6; a = 6;
    cout << "b = ++a => b = " << b << "; a = " << a << endl;
    a = 5;
    b = a++;        // b = 5; a = 6;
    cout << "b = a++ => b = " << b << "; a = " << a << '\n';
    int m[3] = {54, 142, 297};
    cout << "int m[3]:\n";
    for (int i = 0; i < 3; ++i)
        cout << m[i] << " ";
    cout << endl;
    int a1;
    int a2 = ((void)(a1 = 45), 65); // (void) to solve possible misuse
    // firstly a1 = 45; expression result (a1 = 45, 65) is 65 => a2 = 65;
    cout << "'int a2 = ((void)(a1 = 45), 65);' a1=" << a1 << " a2=" << a2 << endl;
}

void compare_char_n_string(void)
{
    cout << "\nCompare char & string:\n";
    const int siz = 50, pix = 4;
    char c1[siz] = "hellos, kakos", c2[siz] = "geldos, makos";
    cout << "We have 2 srings:\n\"" << c1 << "\" and\n\"" << c2 << "\".\n";
    cout << "The difference between each element is:\n";
    for (int i = 0; c1[i] != '\0' && c2[i] != '\0'; ++i)
        cout << c1[i] << setw(pix);
    cout << endl << setw(-pix);
    for (int i = 0; c1[i] != '\0' && c2[i] != '\0'; ++i)
        cout << c2[i] << setw(pix);
    cout << endl << setw(-pix);
    for (int i = 0; c1[i] != '\0' && c2[i] != '\0'; ++i)
        cout << c1[i] - c2[i] << setw(pix);
    cout << "\nNow let's look at the work of strcmp(c1, c2):\n";
    for (int i = 0; c1[i] != '\0' && c2[i] != '\0'; ++i)
    {
        cout << strcmp(c1, c2) << setw(pix);
        if (c1[i] != c2[i])
            c2[i] = c1[i];
    }
    cout << endl;
    cout << "Compare std::string:\n";
    string s = "?hiteSnake";
    cout << "string s = \"" << s << "\".\nStart searching for the missing element:\n";
    for (char c = 'A'; s != "WhiteSnake" && c <= 'Z'; c++)
    {
        cout << s << endl;
        s[0] = c;
    }
    cout << "The result of the search is: \"" << s << "\".\n";
    cout << "Cycle based on the range:\n";
    int a[3] = {10, 24, 3};
    cout << "a:\n";
    for (int i = 0; i < 3; i++)
        cout << a[i] << setw(pix);
    cout << endl << setw(-pix);
    cout << "for (int &x : a) {x += 3;} :\n";
    for (int &x : a)
    {
        x += 3;
        cout << x << setw(pix);
    }
    cout << setw(-pix) << endl;
}

void time_of_work(void)
{
    cout << "\nTime of work:\n";
    ld t = clock(); // processor time since program's execution
    cout << "Program was working " << t / CLOCKS_PER_SEC << " second(s).\n";
}

void two_dimensional_array(void)
{
    cout << "\nTwo dimensional array:\n";
    const int N_CITIES = 3, N_YEARS = 4;
    const char *cities[N_CITIES] = {"Minsk", "Piter", "Kiev"};
    const int temperatures[N_YEARS][N_CITIES] =
    {
        {23, 19, 21},
        {22, 16, 23},
        {20, 18, 24},
        {21, 17, 22}
    };
    cout << "Midle temperatures for years 1990, 2000, 2008, 2015:\n";
    for (int c = 0; c < N_CITIES; ++c)
    {
        cout << cities[c] << ":\t";
        for (int t = 0; t < N_YEARS; ++t)
            cout << ' ' << temperatures[t][c];
        cout << endl;
    }
}

void practice_with_clock(void)
{
    cout << "\nPractice with clock:\n";
    cout << "Enter seconds to wait (2): ";
    size_t sec = input_size();
    cout << "Now wait for " << sec << " second(s)...\n";
    sec *= CLOCKS_PER_SEC;
    while (sec - clock() > 0);
    cout << "Well done!\n";
}

static void ex1(void)
{
    cout << "\nExercise 1:\n";
    cout << "Enter the 1st number: ";
    int num1 = input_int();
    cout << "Enter the 2nd number: ";
    int num2 = input_int();
    if (num2 < num1)
        swap(num1, num2);
    int sum_ath_seq = ( (num1 + num2) * (num2 - num1 + 1) ) / 2;
    printf("The sum of the arithmetic sequence [%d...%d]: %d\n", num1, num2, sum_ath_seq);
    int sum_loop = 0;
    for (int i = num1; i <= num2; ++i)
        sum_loop += i;
    printf("This sum by looping: %d\n", sum_loop);
}

static void ex2(void)
{
    cout << "\nExercise 2:\n";
    const int ARR_SIZE = 101;
    array<long double, ARR_SIZE> factorials;
    factorials[1] = factorials[0] = 1;
    for (int i = 2; i < ARR_SIZE; ++i)
        factorials[i] = i * factorials[i-1];
    for (int i = 0; i < ARR_SIZE; ++i)
        cout << i << "! = " << factorials[i] << endl;
}

static void ex3(void)
{
    cout << "\nExercise 3:\n";
    cout << "Hello. My name is Jo. If you enter some numbers\n"
        "I will show you the sum of them.\n"
        "Let's try! Enter some numbers (0 to stop).\n";
    int number = 1;
    ll sum = 0;
    while (number != 0)
    {
        cout << "Enter a number: ";
        number = input_int();
        sum += number;
        cout << "sum: " << sum << endl;
    }
    cout << endl;
}

static void ex4(void)
{
    cout << "\nExercise 4:\n";
    int dafna = 110, years = 1;
    double kleo = 105;
    while (kleo < dafna)
    {
        dafna += 10;
        kleo += (kleo * 0.05);
        ++years;
    }
    cout << "Dafna: " << dafna << endl;
    cout << "Kleo: " << kleo << endl;
    cout << "Years = " << years << endl;
}

static void ex5(void)
{
    cout << "\nExercise 5:\n";
    const int MONTHS = 3;
    char month[MONTHS][FF_SIZE] = {"January", "February", "March",};
    int books_in_month[MONTHS];
    ll sum = 0;
    cout << "Number of books, which were sold in first 3 months:\n";
    for (int i = 0; i < MONTHS; ++i)
    {
        char prompt[FF_SIZE];
        strcpy(prompt, month[i]);
        strcat(prompt, ": ");
        cout << prompt;
        books_in_month[i] = input_int();
        sum += books_in_month[i];
    }
    cout << "Sum of books for the year: " << sum << endl;
}

static void ex6(void)
{
    cout << "\nExercise 6:\n";
    int year[] = {2000, 2010, 2015};
    const int MONTHS = 12, YEARS = sizeof(year) / sizeof(int);
    seed_rand();
    int books[MONTHS][3] =
    {
        {rand() % 500 + 1, rand() % 500 + 1, rand() % 500 + 1},
        {rand() % 500 + 1, rand() % 500 + 1, rand() % 500 + 1},
        {rand() % 500 + 1, rand() % 500 + 1, rand() % 500 + 1},
        {rand() % 500 + 1, rand() % 500 + 1, rand() % 500 + 1},
        {rand() % 500 + 1, rand() % 500 + 1, rand() % 500 + 1},
        {rand() % 500 + 1, rand() % 500 + 1, rand() % 500 + 1},
        {rand() % 500 + 1, rand() % 500 + 1, rand() % 500 + 1},
        {rand() % 500 + 1, rand() % 500 + 1, rand() % 500 + 1},
        {rand() % 500 + 1, rand() % 500 + 1, rand() % 500 + 1},
        {rand() % 500 + 1, rand() % 500 + 1, rand() % 500 + 1},
        {rand() % 500 + 1, rand() % 500 + 1, rand() % 500 + 1},
        {rand() % 500 + 1, rand() % 500 + 1, rand() % 500 + 1}
    };
    const int WIDTH = 3;
    cout << "Sold books in each month:\n";
    for (int y = 0; y < YEARS; ++y)
    {
        cout << year[y] << ": ";
        for (int m = 0; m < MONTHS; ++m)
            cout << ' ' << setw(WIDTH) << books[m][y];
        cout << endl;
    }
}

static void ex7(void)
{
    cout << "\nExercise 7:\n";
    struct car
    {
        string manufacturer;
        int year;
    };
    cout << "How many cars placed in the directory (2)? ";
    int amount = input_int();
    car *c = new car[amount];
    for (int i = 0; i < amount; ++i)
    {
        cout << "Car #" << i + 1 << ":\n";
        cout << "Enter manufacturer (Audi): ";
        Line line = Line(cin);
        c[i].manufacturer = line.str();
        cout << "Enter year of release (2023): ";
        c[i].year = input_int();
    }
    cout << "This is your collection:\n";
    for (int i = 0; i < amount; ++i)
        cout << c[i].year << ' ' << c[i].manufacturer << endl;
    delete[] c;
}

static void ex8(void)
{
    cout << "\nExercise 8:\n";
    char word[FF_SIZE];
    int amount = 0;
    cout << "Enter some words ('q' to stop):\n";
    cin >> word;
    while (strcmp(word, "q") != 0)
    {
        ++amount;
        cin >> word;
    }
    eat_line();
    cout << amount << " words were entered.\n";
}

static void ex9(void)
{
    cout << "\nExercise 9:\n";
    string word;
    int amount = 0;
    cout << "Enter some words ('q' to stop):\n";
    cin >> word;
    while (word != "q")
    {
        ++amount;
        cin >> word;
    }
    eat_line();
    cout << amount << " words were entered.\n";
}

static void ex10(void)
{
    cout << "\nExercise 10:\n";
    cout << "Enter number of strings (7): ";
    size_t n = input_size();
    if (n == 0)
    {
        cout << "There could be a tree here...\n";
        return;
    }
    cout << "Fur-tree:\n";
    // 1st line
    for (size_t j = 0; j < n - 1; ++j)
        cout << ' ';
    cout << "^\n"; // 1st caret
    // other lines
    size_t pipe_ind = n - 1;
    for (size_t i = 1; i < n; ++i)
    {
        size_t line_len = n + i;
        size_t n_spaces = n - 1 - i;
        for (size_t j = 0; j < line_len; ++j)
        {
            if (j < n_spaces)
                cout << ' ';
            else if (j == pipe_ind)
                cout << '|';
            else
                cout << '^';
        }
        cout << endl;
    }
}
