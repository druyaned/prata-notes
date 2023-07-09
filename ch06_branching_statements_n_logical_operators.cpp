#include "ch06_branching_statements_n_logical_operators.hpp"
#include "Utils.hpp"
#include <iostream>
#include <string>
#include <cstring> // strcpy(a1, a2); strcat(a1, a2);
#include <cstdlib> // rand(), max(), min()
#include <ctime> // rand(): srand(int(time(NULL)));
#include <vector>
#include <array>
#include <iomanip> // setw()
#include <fstream> // file IO (inout-output)
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

using namespace std;

struct patron {string name; double donation;};
const char OUT_FILE[] = "ch06_of.txt";
const char IO_FILE[] = "ch06_io.txt";

void practice_with_cctype(void);
void tercio_operatur(void);
void practice_with_switch(void);
void practice_with_goto(void);
void practise_with_fstream(void);
static void ex1(void);
static void ex3(void);
static void ex5(void);
static void ex6(void);
static void ex7(void);
static void ex8(void);
void show_patrons(patron *patrons, const int &n_patrons);

int ch06_branching_statements_n_logical_operators()
{
    clock_t cpu_start = clock();
    print_run_chapter_message(6);
    practice_with_cctype();
    tercio_operatur();
    practice_with_switch();
    practice_with_goto();
    practise_with_fstream();
    ex1();
    ex3();
    ex5();
    ex6();
    ex7();
    ex8();
    clock_t cpu_end = clock();
    double cpu_time = double(cpu_end - cpu_start) / CLOCKS_PER_SEC;
    cout << "CPU time used: " << cpu_time << " second(s).\n";
    return EXIT_SUCCESS;
}

void practice_with_cctype(void)
{
    cout << "\nPractice with cctype\n";
    cout << "Enter text for analysis ('@' is the last character to be read).\n";
    char ch = '\0';
    size_t whitespace = 0;
    size_t digits = 0;
    size_t letters = 0;
    size_t punct = 0;
    size_t others = 0;
    cin.get(ch);    // получение первого символа
    while (ch != '@')   // проверка на признак окончания ввода
    {
        if(isalpha(ch))         // буквенный символ?
            ++letters;
        else if(isspace(ch))    // пробельный символ?
            ++whitespace;
        else if(isdigit(ch))    // десятичная цифра?
            ++digits;
        else if(ispunct(ch))    // знак препинания?
            ++punct;
        else
            ++others;
        cin.get(ch);    // получение следующего символа
    }
    eat_line();
    cout
         << "letters:      " << letters << endl
         << "whitespace:   " << whitespace << endl
         << "digits:       " << digits << endl
         << "punctuations: " << punct << endl
         << "others:       " << others << endl;
}

void tercio_operatur(void)
{
    cout << "\nTercio operatur\n";
    cout << "Enter the 1st number: ";
    int num1 = input_int();
    cout << "Enter the 2nd number: ";
    int num2 = input_int();
    int max_num = num1 < num2 ? num2 : num1;
    cout << "Max of them is: " << max_num << endl;
}

void practice_with_switch(void)
{
    cout << "\nPractice with\n";
    enum {red, orange, yellow, green, blue, violet, indigo};
    cout << "Enter color code (0-6). To finish enter '-1': ";
    int color = input_int();
    while (color != -1)
    {
        switch (color)
        {
            case red: cout << "red. Try again:\n"; break;
            case orange: cout << "orange. Try again:\n"; break;
            case yellow: cout << "yellow. Try again:\n"; break;
            case green: cout << "green. Try again:\n"; break;
            case blue: cout << "blue. Try again:\n"; break;
            case violet: cout << "violet. Try again:\n"; break;
            case indigo: cout << "indigo. Try again:\n"; break;
            default: cout << "No color for this number.\n";
        }
        cout << "Enter color code (0-6). To finish enter '-1': ";
        color = input_int();
    }
}

void practice_with_goto(void)
{
    cout << "\nPractice with goto\n";
he: cout << "Yea!\n";
    cout << "If you want to see it again, enter an empty line: ";
    char ch = cin.get();
    if (ch == '\n')
        goto he;
    eat_line();
    cout << "Ok. Buy.\n";
}

void practise_with_fstream(void)
{
    cout << "\nPractise with fstream\n";
    ofstream fout(OUT_FILE);
    fstream f{IO_FILE, fstream::in | fstream::out | fstream::trunc};
    if (!fout.is_open())
    {
        cout << "Couldn't open file '" << OUT_FILE << "'\n";
        fout.close();
        return;
    }
    if (!f.is_open())
    {
        cout << "Couldn't open file '" << IO_FILE << "'\n";
        fout.close();
        return;
    }
    struct car
    {
        char model[FF_SIZE];
        size_t price;
        int year;
    };
    const char MODELS[][FF_SIZE] = {"Audi", "Mercedes", "Lada", "Москвич", "Geely"};
    const size_t N_CARS = sizeof(MODELS) / sizeof(MODELS[0]);
    seed_rand();
    // write data
    f << "Number of cars:\n";
    f << N_CARS << endl;
    size_t prices[N_CARS]{};
    f << "Prices:\n";
    for (size_t i = 0; i < N_CARS; ++i)
    {
        prices[i] = 0xffff + rand() % 0xffff;
        f << prices[i] << endl;
    }
    int years[N_CARS];
    f << "Years:\n";
    for (size_t i = 0; i < N_CARS; ++i)
    {
        years[i] = 2020 + rand() % 4;
        f << years[i] << endl;
    }
    // read data
    size_t line_ind = 1;
    f.seekg(0, ios_base::beg); // sets input position
    size_t n = 0;
    char buf[FF_SIZE]{};
    while (f.get() != '\n'); // N_CARS message
    ++line_ind;
    f.getline(buf, FF_SIZE); // N_CARS
    if (!parse_size(buf, n))
    {
        cout << "Unsuccessful size parsing; file='" << IO_FILE
            << "', line='" << line_ind << "'\n";
        return;
    }
    ++line_ind;
    while (f.get() != '\n'); // Prices message
    ++line_ind;
    size_t read_prices[N_CARS]{};
    for (size_t i = 0; i < N_CARS; ++i, ++line_ind)
    {
        f.getline(buf, FF_SIZE);
        if (!parse_size(buf, read_prices[i]))
        {
            cout << "Unsuccessful size parsing; file='" << IO_FILE
                << "', line='" << line_ind << "'\n";
            return;
        }
    }
    while (f.get() != '\n'); // Years message
    ++line_ind;
    int read_years[N_CARS]{};
    for (size_t i = 0; i < N_CARS; ++i, ++line_ind)
    {
        f.getline(buf, FF_SIZE);
        if (!parse_int(buf, read_years[i]))
        {
            cout << "Unsuccessful int parsing; file='" << IO_FILE
                << "', line='" << line_ind << "'\n";
            return;
        }
    }
    // write cars
    car *cars = new car[N_CARS];
    fout << "There are some cars:\n";
    for (size_t i = 0; i < N_CARS; ++i)
    {
        fout << "Car #" << setfill('0') << setw(2) << i + 1 << ":\n";
        fout << "  Model: " << MODELS[rand() % N_CARS] << endl;
        fout << "  Price: " << read_prices[i] << endl;
        fout << "  Year: " << read_years[i] << endl;
    }
    cout << "File '" << OUT_FILE << "' is written.\n";
    fout.close();
    f.close();
    delete []cars;
}

void ex1(void)
{
    cout << "\nExercise 1\n";
    cout << "Enter something. Input is terminated after the charter @.\n";
    char ch = cin.get();
    while (ch != '@')
    {
        if (!isdigit(ch))
        {
            if (isupper(ch))
                cout << char(ch - 'A' + 'a');
            else if (islower(ch))
                cout << char(ch - 'a' + 'A');
            else
                cout << ch;
        }
        ch = cin.get();
    }
    eat_line();
}

void ex3(void)
{
    cout << "\nExercise 3\n";
    cout << "a) joke; b) truth; c) number; d) letter\n: ";
    Line line = Line(cin);
    while (true)
    {
        if (line.len() == 1)
        {
            if ( ('a' <= line[0] && line[0] <= 'd') || ('A' <= line[0] && line[0] <= 'D') )
                break;
        }
        cout << "a) joke; b) truth; c) number; d) letter\n: ";
        input_line(line);
    }
    switch (line[0])
    {
        case 'a':
        case 'A': cout << "a) joke: diaphanous door in a refrigerator\n"; break;
        case 'b':
        case 'B': cout << "b) truth: 2 + 2 = 4\n"; break;
        case 'c':
        case 'C': cout << "c) number: " << 5 << endl; break;
        case 'd':
        case 'D': cout << "d) letter: " << 'E' << endl; break;
        default: cout << "Bad choice.\n";
    }
}

void ex5(void)
{
    cout << "\nExercise 5\n";
    cout << "Enter an income (e.g. 5050), -1 to stop: ";
    int income = input_int();
    double tex = 0.0;
    while (income != -1)
    {
        if (income < 5000)
            tex = 0.0;
        else if (income < 15000)
            tex = (income - 5000) * 0.1;
        else if (income < 35000)
            tex = 1000 + (income - 15000) * 0.15;
        else
            tex = 4000 + (income - 35000) * 0.2;
        cout << "Tax = " << tex << endl;
        cout << "Enter an income (e.g. 5050), -1 to stop: ";
        income = input_int();
    }
    cout << "It's was good!\n";
}

void ex6(void)
{
    cout << "\nExercise 6\n";
    cout << "Enter the number of patrons (2): ";
    size_t n = input_size();
    patron *patrons = new patron[n];
    patron *grand_patrons = new patron[n];
    size_t n_grand_patrons = 0, n_patrons = 0;
    cout << "Now enter name and donation for each maecenas:\n";
    for (size_t i = 0; i < n; ++i)
    {
        patron p{"", 0.0};
        cout << "#" << i + 1 << endl;
        cout << "  Name: ";
        Line line = Line(cin);
        p.name = line.str();
        while (1000.0 < p.donation || p.donation < 1.0)
        {
            cout << "  Donation ([1.0, 1000.0]: ";
            p.donation = input_double();
        }
        if (p.donation <= 512.0)
            patrons[n_patrons++] = p;
        else
            grand_patrons[n_grand_patrons++] = p;
    }
    if (0 < n_grand_patrons)
    {
        cout << "Grand Patrons:\n";
        for (size_t i = 0; i < n_grand_patrons; ++i)
        {
            cout << '#' << i + 1 << ": name: " << grand_patrons[i].name
                << "; donation: " << grand_patrons[i].donation << endl;
        }
    }
    else
        cout << "No Grand Patrons\n";
    if (0 < n_patrons)
    {
        cout << "Patrons:\n";
        for (size_t i = 0; i < n_patrons; ++i)
        {
            cout << '#' << i + 1 << ": name: " << patrons[i].name
                << "; donation: " << patrons[i].donation << endl;
        }
    }
    else
        cout << "No Patrons\n";
    delete []grand_patrons;
    delete []patrons;
}

void ex7(void)
{
    cout << "\nExercise 7\n";
    cout << "Enter words ('q' to quit):\n";
    size_t vowels = 0, consonants = 0, other = 0;
    string s;
    cin >> s;
    while (s != "q")
    {
        if (isalpha(s[0]))
        {
            switch (s[0])
            {
                case 'a': case 'A': case 'e': case 'E': case 'i':
                case 'I': case 'o': case 'O': case 'u': case 'U':
                case 'y': case 'Y': ++vowels; break;
                default: ++consonants;
            }
        }
        else
            ++other;
        cin >> s;
    }
    cout
        << vowels << " word(s) beginning with vowel(s).\n"
        << consonants << " word(s) beginning with consonant(s).\n"
        << other << " other(s).\n";
}

void ex8(void)
{
    cout << "\nExercise 8\n";
    ifstream fin(IO_FILE);
    char ch;
    int n = 0;
    while (fin.get(ch)) // while (fin), i.e. until the EOF
        ++n;
    cout << "Number of charters in file '" << IO_FILE << "' is: " << n << endl;
    fin.close();
}

void show_patrons(const patron *patrons, const int &n_patrons)
{
    for (size_t i = 0; i < n_patrons; ++i)
    {
        cout << '#' << i + 1 << endl;
        cout << "  Name:     " << patrons[i].name << endl;
        cout << "  Donation: " << patrons[i].donation << endl;
    }
}
