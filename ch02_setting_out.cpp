#include "ch02_setting_out.hpp"
#include "Utils.hpp"
#include <climits>
#include <chrono>
#include <ctime>
#define some_variable 12    /* the message will be sent to a preprocessor
                             to find and change in the source file
                             all separate concurrences with SV to 12 */

using namespace std;

void bit_byte_n_num_sys();
void styles_of_programming();
void code_execution_phases();
void whitespace_characters();
// exercises
static void ex1_show_name();
static void ex2_furlong_to_yard();
static void ex4_age_in_months();
static void ex5_celsius_to_fahrenheit();
static void ex6_light_to_astronomical();

int ch02_setting_out()
{
    print_run_chapter_message(2);
    bit_byte_n_num_sys();
    styles_of_programming();
    code_execution_phases();
    whitespace_characters();
    ex2_furlong_to_yard();
    ex4_age_in_months();
    ex5_celsius_to_fahrenheit();
    ex6_light_to_astronomical();
    return EXIT_SUCCESS;
}

void bit_byte_n_num_sys()
{
    cout << "\nBits, bytes and number systems:\n"
        "There are " << CHAR_BIT << " bits in the type 'char'.\n";
    // bit - fundamental unit of memory (0 or 1)
    cout << "In bytes: sizeof(char)=" << sizeof(char)
        << "; sizeof(int)=" << sizeof(int) << endl;
    // 1 byte - minimum set of adjacent bits
    // which is sufficient to include a basic set of implementation symbols
    // 1 kb = 1024 bytes; 1 mb = 1024 kb
    cout << "Let's see some tricks with numbers:\n";
    cout << "  42 = " << 42 << endl;
    cout << " 042 = " << 042 << endl;
    cout << "0x42 = " << 0x42 << endl;
    cout << "0xf + 1 = " << 0xf + 1 << endl;
}

void styles_of_programming()
{
    cout << "\nStyles of programming:\n"
        "- Procedural (Процедурный)\n"
        "- Structural (Структурный)\n"
        "- Top-down (Нисходящее)\n"
        "- Object-oriented (Объектно-ориентированное)\n";
}

void code_execution_phases()
{
    cout << "\nCode execution phases:\n"
        "- Source code\n"
        "- Compiler\n"
        "- Object code\n"
        "- Composer (startup code and libraries)\n"
        "- Executable code\n";
}

void whitespace_characters()
{
    cout << "\nWhitespace characters:\n"
        "- Space\n"
        "- Tabulation\n"
        "- Carriage return\n"
        "Lexeme - indivisible part of string\n";
}

inline unsigned long furlong_to_yard(const unsigned &furlong)
{
    return (unsigned long)(220ul * furlong);   // 1 f = 220 y
}

void ex2_furlong_to_yard()
{
    cout << "\nExercise 2: furlong to yard\n";
    cout << "Distance in furlong: ";
    unsigned furlong { 14 };  // unsigned = unsigned int; {} - universal type of initialisation
    unsigned long yard = furlong_to_yard(furlong);
    cout << furlong << " furlong(s) = " << yard << " yard(s)\n";
}

void ex4_age_in_months()
{
    cout << "\nExercise 4: age in months\n";
    using chrono::system_clock;
    unsigned age = 16;
    cout << "Age in years: " << age << endl;
    unsigned birth_month = 8;
    cout << "The number of birth month (from 1 to 12): " << birth_month << endl;
    time_t current_time = system_clock::to_time_t(system_clock::now());
    tm *dt = localtime(&current_time);
    unsigned current_month = dt->tm_mon + 1;
    cout << "Current month: " << current_month << endl;
    unsigned age_in_months = age * 12 +
        (birth_month <= current_month ?
         current_month - birth_month :
         12 - birth_month + current_month);
    cout << "Age in months: " << age_in_months << endl;
}

inline double celsius_to_fahrenheit(const int &celsius)
{
    return 1.8 * celsius + 32;
}

void ex5_celsius_to_fahrenheit()
{
    cout << "\nExercise 5: celsius to fahrenheit\n";
    const int N = 3;
    const int celsius[N] = { 20, 0, -20 };
    for (int i = 0; i < N; ++i)
    {
        cout << celsius[i] << " degrees Celsius is "
            << celsius_to_fahrenheit(celsius[i]) << " degrees Fahrenheit\n";
    }
}

inline double light_to_astronomical(const double &light_years)
{
    return 63240.0 * light_years; // 1 light year(s) = 63240 astronomical unit(s)
}

void ex6_light_to_astronomical()
{
    cout << "\nExercise 6: light years to astronomical units\n";
    const int N = 2;
    const double light_years[N] = { 12, 123456789 };
    for (int i = 0; i < N; ++i)
    {
        cout << light_years[i] << " light year(s) = "
            << light_to_astronomical(light_years[i]) << " astronomical unit(s)\n";
    }
}
