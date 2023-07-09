#include "ch03_dealing_with_data.hpp"
#include "Utils.hpp"
#include <climits>
#include <cfloat> // constants that show information about floating-point numbers
typedef long long ll; // better than '#define ll long long'

void suffixes();
void simbols(void);
void sam_lara(void);
void size_of(void);
void int_lit(void);
void floating_numbers();
static void ex1_convert_inches(void);
static void ex2_height_n_weight(void);
static void ex3_latitude(void);
static void ex4_convert_seconds(void);
static void ex5_population(void);
static void ex6_fuel_consumption(void);
static void ex7_convert_fuel_consumption(void);

int ch03_dealing_with_data()
{
    print_run_chapter_message(3);
    suffixes();
    simbols();
    sam_lara();
    size_of();
    int_lit();
    floating_numbers();
    ex1_convert_inches();
    ex2_height_n_weight();
    ex3_latitude();
    ex4_convert_seconds();
    ex5_population();
    ex6_fuel_consumption();
    ex7_convert_fuel_consumption();
    return EXIT_SUCCESS;
}

void suffixes()
{
    using namespace std;
    cout << "\nSuffixes:\n";
    cout << "112L == 112l - long\n"
        "112lu == 112LU == 112Lu - unsigned long\n"
        "112ull == 112ULL - unsigned long long\n"
        "112ll == 112LL - long long\n"
        "1.2f - float\n"
        "1.2L - long double\n"
        "\\u222B == ∫ - универсальные символьные имена\n";
}

void simbols()
{
    std::cout << "\nSimbols:\n";
    using namespace std;
    char e = '\x45', d = e - 1; // E <=> 69 = 0x45;
                                // в памяти хранится код 69 сответствующий символу Е
    cout << "'\\xa''\\x45''\\40''\\x44':"
        << '\xa' << e << '\40' << d << '\n';    // \x20 == \40 - space; 040 = 0x20 = 32
    char ch_a = 'a', ch_b = 'b', ch_z = 'z';
    printf("Code of 'a' = %d, 'b' = %d, 'z' = %d\n", ch_a, ch_b, ch_z);
    wchar_t la = L'A';
    std::wcout << "Usage of 'wcout' for L'A': "
        << la << "; size of wcahr_t: " << sizeof(wchar_t) << '\n';
    std::cout << "-15 in unsigned long long: " << -15ULL
        << "; \"g\\u00E2teau\": \"g\u00E2teau\"";
    // \" - управляющая последовательность; \u + 00E2 => сюрприз
    std::cout.put('.').put('\n');   // пример функции-члена, где '.' - операция членства
}

void sam_lara()
{
    std::cout << "\nSam and Lara:\n";
    using std::cout;
    using std::endl;
    short sam = SHRT_MAX;
    unsigned short lara = sam;
    cout << "Sam has " << sam << "₽ (SHRT_MAX, type: short) "
        "and Lara has " << lara << "₽ (SHRT_MAX, type: unsigned short).\n";
    cout << "Add 1₽ to each account.\n";
    sam = sam + 1;
    lara = lara + 1;
    cout << "Now Sam has " << sam << "₽ and Lara has " << lara << "₽. Poor Sam!\n";
    cout << "Reset both to zero.\n";
    sam = lara = 0;
    cout << "Sam has " << sam << "₽ and Lara has " << lara << "₽.\n";
    cout << "Take 1₽ from each account." << endl;
    sam = sam - 1;
    lara = lara - 1;
    cout << "Sam has " << sam << "₽ and Lara has " << lara << "₽. Lucky Lara!\n";
}

void size_of(void)
{
    std::cout << "\nSize of:\n";
    using std::cout;
    using std::endl;
    cout << "Bits in char: " << CHAR_BIT << endl
        << "Min char: " << CHAR_MIN << endl
        << "Max char: " << CHAR_MAX << endl
        << "Bytes in int: " << sizeof(int) << endl
        << "Bytes in long long: " << sizeof(long long) << endl
        << "Max  ll: " << LLONG_MAX << endl
        << "Max ull: " << ULLONG_MAX << endl;
    int a = 1;
    cout << "int a = " << a << "; sizeof(a) = " << sizeof(a) << endl;
    cout << "sizeof((ll)(a)): " << sizeof((ll)(a)) << endl;
    cout << "sizeof(static_cast<ll>(a)): " << sizeof(static_cast<ll>(a)) << endl;
    cout << "sizeof(9ULL): " << sizeof(9ULL) << " byte(s)\n";
    cout << "sizeof(\"\u00f6\"): " << sizeof("\u00f6") << endl;
    cout << "sizeof(\"a\"): " << sizeof("a") << endl;
    cout << "sizeof(\'a\'): " << sizeof('a') << endl;
    cout << "sizeof(u'п'): " << sizeof(u'п') << " (char16_t)" << endl;  // char16_t
    cout << "sizeof(U'п'): " << sizeof(U'п') << " (char32_t)" << endl;  // char32_t
    cout << "sizeof(L'п'): " << sizeof(L'п') << " (wchar_t)" << endl;   // wchar_t
}

void int_lit()
{
    std::cout << "\nInteger literals:\n";
    using std::endl;
    using std::cout;
    short my_dec = 42, my_hex = 0x42, my_oct = 042;
    cout << "42 in different notations:\n"
        << "decimal 42 = " << my_dec << endl
        << "hexadecimal 0x42 = " << my_hex << endl  // 4*16^1 + 2*16^0 = 66
        << "octal 042 = " << my_oct << endl;    // 4*8^1 + 2*8^0 = 34
    cout << "Big number 1'000'000'000: " << 1'000'000'000 << endl;
}

void floating_numbers()
{
    std::cout << "\nFloating numbers:\n";
    using namespace std;
    cout << "Minimum significant digits in the type float:\t\t" << FLT_DIG << endl;
    cout << "Minimum significant digits in the type double:\t\t" << DBL_DIG << endl;
    cout << "Minimum significant digits in the type long double:\t" << LDBL_DIG << endl;
    cout << "Bits for float's mantissa:\t\t" << FLT_MANT_DIG << endl;
    cout << "Bits for double's mantissa:\t\t" << DBL_MANT_DIG << endl;
    cout << "Bits for long double's mantissa:\t" << LDBL_MANT_DIG << endl;
    cout << "Maximum value of float order:\t\t" << FLT_MAX_10_EXP << endl;
    cout << "Maximum value of double order:\t\t" << DBL_MAX_10_EXP << endl;
    cout << "Maximum value of long double order:\t" << LDBL_MAX_10_EXP << endl;
    cout << "Minimum value of float order:\t\t" << FLT_MIN_10_EXP << endl;
    cout << "Minimum value of double order:\t\t" << DBL_MIN_10_EXP << endl;
    cout << "Minimum value of long double order:\t" << LDBL_MIN_10_EXP << endl;
}

using namespace std;

void ex1_convert_inches(void)
{
    cout << "\nExercise 1: convert inches\n";
    int inches = 74;
    printf("Height = %d inch(es) = %d fееt(foot) %d inch(es)\n",
           inches, inches / 12, inches % 12);
}

void ex2_height_n_weight(void) {
    cout << "\nExercise 2: height and weight\n";
    cout.setf(ios_base::fixed, ios_base::floatfield);   // output with 6 elements after dot
    const unsigned short feet_inches = 12;
    const float inches_meters = 0.0254;
    const double kg_pounds = 2.2;
    unsigned short feet = 6, inches = 7, pounds = 201;
    double kg = double(pounds) / kg_pounds;
    float meter = float(feet * feet_inches + inches) * inches_meters;
    cout << "Height = " << feet << " feet(foot) " << inches << " inch(es)\n";
    cout << "Weight = " << pounds << " pound(s)\n";
    cout << "After conversion:\n";
    cout << "Height = " << meter << " meter(s)\n";
    cout << "Weight = " << kg << " kilogram(s)\n";
    cout << "Body mass index = " << kg / double(meter * meter) << endl;
    // if 'double' is not matching, compiler do it autimaticly
}

void ex3_latitude(void) {
    cout << "\nExercise 3: latitude in degrees, minutes, and seconds\n";
    short degrees = 37, minuts = 51, seconds = 19;
    // 1º = 60 minuts
    cout << "Degrees = " << degrees << ", minuts = " << minuts
        << ", seconds = " << seconds << endl;
    float angle = degrees + float(minuts) / 60 + float(seconds) / 3600;
    cout << "Angle = " << angle << endl;
}

void ex4_convert_seconds(void) {
    cout << "\nExercise 4: convert seconds\n";
    ll sec = 31600000;
    cout << "Seconds = " << sec << " seconds";
    const short sec_min = 60, sec_hour = 3600;
    const int sec_day = 86400;
    ll days = sec / ll(sec_day);
    sec -= days * sec_day;
    short hours = short(sec / (long long)(sec_hour));
    // sec_hour -> ll; than (sec / sec_hour) -> short
    sec -= hours * sec_hour;
    short minuts = sec / sec_min;
    sec -= minuts * sec_min;
    cout << " = " << days << " day(s) " << hours << " hour(s) "
        << minuts << " minut(s) " << sec << " second(s)\n";
}

void ex5_population(void) {
    cout << "\nExercise 5: population (2023)\n";
    ll world = 8039694550, bel = 9440150;
    cout << "World pipulation: " << world << "\nPopulation of Belarus: " << bel
        << "\nThe population of Belarus is " << float(bel) / world * 100
        << "% of the world population.\n";
}

void ex6_fuel_consumption(void) {
    cout << "\nExercise 6: fuel consumption\n";
    short km = 367, liters = 23;
    cout << "Passed kilometers: " << km << "; spent fuel: " << liters << " liters\n";
    double consumption = double(liters) / double(km) * 100.0;
    cout << "Consumption = " << consumption << " liter(s) per 100 km\n";
}

void ex7_convert_fuel_consumption(void) { // 1 km = 0.6214 miles; 1 gallon = 3.875 liters
    cout << "\nExercise 7: convert fuel consumption\n";
    const double gal_lit = 3.875, km_miles = 0.6214;
    short km = 367, liters = 23;
    cout << "Passed kilometers: " << km << "; spent fuel: " << liters << " liters\n";
    double consumption = double(liters) / km * 100.0;
    cout << "Consumption = " << consumption << " liter(s) per 100 km\n";
    consumption = (km * km_miles) / (liters / gal_lit);
    cout << "Consumption in the USA: " << consumption << " miles per gallon\n";
}
