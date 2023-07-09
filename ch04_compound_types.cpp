#include "ch04_compound_types.hpp"
#include "Utils.hpp"
#include <string>
#include <cstring>  // strcpy(a1, a2); strcat(a1, a2);
#include <vector>
#include <array>
#include <iomanip>
typedef long long ll;   // better than '#define ll long long'

using namespace std;

void array_initialization(void);
void practice_with_string(void);
void getline_n_get(void);
void practice_with_struct(void);
void practice_with_pointer(void);
void get_to_vector(void);
static void ex1(void);
static void ex2(void);
static void ex3(void);
static void ex5(void);
static void ex6(void);
static void ex7(void);
static void ex8(void);
static void ex9(void);
static void ex10(void);

int ch04_compound_types()
{
    print_run_chapter_message(4);
    array_initialization();
    practice_with_string();
    getline_n_get();
    practice_with_struct();
    practice_with_pointer();
    get_to_vector();
    ex1();
    ex2();
    ex3();
    ex5();
    ex6();
    ex7();
    ex8();
    ex9();
    ex10();
    return EXIT_SUCCESS;
}

void array_initialization(void)
{
    cout << "\nArray initialization:\n";
    const int SIZE1 = 5;
    int arr1[SIZE1] { 5, 2 }; // 3rd, 4th and 5th elements get 0
    cout << "Initialization #1: int arr1[" << SIZE1 << "] { 5, 2 };\n";
    cout << "arr1:";
    for (int i = 0; i < SIZE1; i++)
        cout << ' ' << arr1[i];
    cout << endl;
    int arr2[] { 5, 3, 2 };  // compiler counts the size
    cout << "Initialization #2: int arr2[] { 5, 3, 2 };\n";
    const int SIZE2 = sizeof(arr2) / sizeof(arr2[0]);
    cout << "arr2:";
    for (int i = 0; i < SIZE2; i++)
        cout << ' ' << arr2[i];
    cout << endl;
    cout << "There are " << SIZE2 << " element(s) in the arr2\n";
}

void practice_with_string(void)
{
    cout << "\nPractice with string:\n";
    cout << "The last element of string in C style is always '\\0'\n";
    cout << "char ch_arr1[6] = {'P', 'u', 'p', 'o', 'k', '\\0'};\n";
    char ch_arr1[6] = {'P', 'u', 'p', 'o', 'k', '\0'};
    cout << "'cout << ch_arr1;': " << ch_arr1 << endl;
    char ch_arr2[] = "Hellos, my dear! Nice.";  // 22 + '\0' = 23 elements
    cout << "char ch_arr2[] = \"Hellos, my dear! Nice.\";\n";
    cout << "ch_arr2: '" << ch_arr2 << "'\n";
    const int SIZE2 = sizeof(ch_arr2) / sizeof(ch_arr2[0]);
    cout << "There are " << SIZE2 << " element(s) in the ch_arr2\n";
    cout << "strlen(ch_arr2)=" << strlen(ch_arr2) << endl;    // lenght of ch_arr2
    string str = "Hellos, my dear! Nice.";
    cout << "std::string str=\"Hellos, my dear! Nice.\";\n";
    cout << "str.length=" << str.length() << endl;
    char ch_arr3[] = "Hellos"   // concatenation of string literals
        ", my dear! Nice.";
    const int SIZE3 = sizeof(ch_arr3) / sizeof(ch_arr3[0]);
    cout << "ch_arr3 was initialized with a concatenation of string literals\n";
    cout << "There are " << SIZE3 << " element(s) there\n";;
    char ch_arr4[FF_SIZE] = "Yo! ";
    cout << "char ch_arr4[FF_SIZE]=\"Yo! \";\n";
    strcat(ch_arr4, ch_arr1);
    cout << "strcat(ch_arr4, ch_arr1);\n";
    cout << "ch_arr4: '" << ch_arr4 << "'\n";
    strcpy(ch_arr4, ch_arr2);
    cout << "strcpy(ch_arr4, ch_arr2);\n";
    cout << "Now ch_arr4: '" << ch_arr4 << "'\n";
}

void getline_n_get(void)
{
    cout << "\n'getline' & 'get':\n";
    char line[FF_SIZE];
    // getline
    cout << "Usage of 'cin.getline(line, FF_SIZE);'\n";
    cout << "'cin.getline' exctracts the delimiter ('\\n')\n";
    cout << "Enter something: ";
    cin.getline(line, FF_SIZE);
    cout << "Entered: '" << line << "'. It was great!\n";
    // get
    cout << "Usage of 'cin.get(line, FF_SIZE);'\n";
    cout << "'cin.get' does NOT exctract the delimiter ('\\n')\n";
    cout << "Enter something: ";
    cin.get(line, FF_SIZE);
    if (cin.fail())
    {
        cout << "The 'cin' failed! Clearing the 'cin'...\n";
        cin.clear();
    }
    cout << "So the '\\n' is still in the input queue...\n";
    cout << "Using 'cin.get()' to exctract the delimiter...\n";
    while (cin && cin.get() != '\n');
    cout << "Entered: '" << line << "'. It was also great!\n";
    // variable
    cout << "Usage of 'cin >> int_variable;' (watch the source code)\n";
    int v;
    cout << "Enter veriable 'v': ";
    cin >> v;   // reads until the 1st whitespace, which also remains in the input queue
    while (!cin)
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "An integer is required: ";
        cin >> v;
    }   // now cin is good
    while (cin.get() != '\n');
    cout << "v=" << v << ". That was pretty good!\n";
}

void practice_with_struct(void)
{
    cout << "\nPractice with struct:\n";
    struct BasketPlayer
    {
        string name;
        short pts_per_season;
        float salary{};
    };
    BasketPlayer players[]
    {
        { "Petya", 277 },
        { "Vova", 319 },
        { "Borya", 299 },
        { "Grisha", 358 },
        { "Garik", 401 }
    };
    const int N1 = sizeof(players) / sizeof(players[0]);
    cout << "sizeof(players)=" << sizeof(players) << " byte(s)\n";
    for (int i = 0; i < N1; ++i)
    {
        printf("sizeof(players[%d])=%zu byte(s)\n", i, sizeof(players[i]));
        if (players[i].pts_per_season > 300)
            players[i].salary = 600;
        else
            players[i].salary = players[i].pts_per_season * 1.7;
    }
    printf("Basketball players (struct):\n"
           "%15s|%15s|%15s\n", "Name", "PTS per season", "Salary");
    for (int i = 0; i < N1; i++)
    {
        printf("%15s|%15hd|%15.2f\n",
               players[i].name.c_str(), players[i].pts_per_season, players[i].salary);
    }
    cout << "UNION: memory is allocated only for a largest element\n";
    cout << "So the stored data can be interpreted as each variable\n";
    cout << "Let's look at the double64_cast\n";
    union double64_cast
    {
        double value;
        struct
        {
            size_t mantissa : 52; // DBL_MANT_DIG - 1
            unsigned int exponent : 11; // sizeof(double) * 8 - DBL_MANT_DIG
            unsigned int sign : 1;
        } parts;
    };
    cout << "sizeof(double64_cast): " << sizeof(double64_cast) << endl;
    double64_cast cast_var = {.value = 122.5625};
    printf("cast_var.value: %a = %.4f\n", cast_var.value, cast_var.value);
    size_t mnt = cast_var.parts.mantissa;
    unsigned int exp = cast_var.parts.exponent, sgn = cast_var.parts.sign;
    printf("cast_var.parts.mantissa: %#zx = %zu\n", mnt, mnt);
    printf("cast_var.parts.exponent: %#x = %u\n", exp, exp);
    printf("    cast_var.parts.sign: %u\n", sgn);
    enum spectrum // перечисление
    {
        red, orange, yellow = 5, green, blue, violet, indigo = 102, ultraviolet
    };
    cout << "enum spectrum { red, orange, yellow = 5, "
        "green, blue, violet, indigo = 102, ultraviolet }\n";
    cout << "values: red=" << red << " orange=" << orange << " yellow=" << yellow
        << " green=" << green << " blue=" << blue << " violet=" << violet
        << " indigo=" << indigo << " ultraviolet=" << ultraviolet << endl;
    spectrum color = ultraviolet;
    cout << "spectrum color = ultraviolet;\n";
    cout << "color=" << color << "; can be cast to the short type\n";
    cout << "Range 'r' of spectrum 's': ( max[s] == (ultraviolet = 103) ) => r = 128 = 2^7\n";
}

void practice_with_pointer(void)
{
    cout << "\nPractice with pointer (watch the code):\n";
    cout << "Always initialize pointers!\n";
    int a = 23, *pa = &a;   // always initialize pointers
    pa = &a;                // it's already done
    cout << "a=" << a << ", address: &a=" << &a << endl;
    cout << "*pa=" << *pa << ", pa=" << pa << endl;
    ll addr = (long long)(&a);
    cout << hex << addr << dec << endl;
    cout << "Dynamic memory allocation:\n";
    double *p = new double;
    *p = 36.43;
    cout << "*p=" << *p << "; p=" << p << endl;
    cout << "Don't forget to free up the memory!\n";
    delete p;   // delete the memory, wich is pointed by *p
    int n = 7;
    int *arr = new int[n];  // variable size
    seed_rand();
    for (int i = 0; i < n; i++)
    {
        *(arr + i) = rand() % 64;   // *(arr + i) == arr[i]
        // (arr + i) - arithmetic of pointers => access to (i + 1) element
    }
    cout << "arr:";
    for (int i = 0; i < n; i++)
        cout << ' ' << arr[i];
    cout << endl;
    delete[] arr;   // array deletion
    const int N = 3;
    short sa[N];
    cout << "sa:";
    for (int i = 0; i < N; i++)
    {
        sa[i] = rand() % 64;
        cout << ' ' << sa[i];
    }
    cout << endl;
    cout << "&sa=" << &sa << "; sa=" << sa << endl;
    short (*psa)[N] = &sa; // pointer to the array of N elements; psa == &sa; *psa == sa
    cout << "psa=" << psa << "; *psa=" << *psa << endl;
    cout << "(*psa)[2]=" << (*psa)[2] << "; *(*psa + 1)=" << *(*psa + 1) << endl;
    short *sa_alias = sa;
    cout << "*(sa_alias + 1)=" << *(sa_alias + 1) << endl;
    short *(arrp[N]) =      // array of pointers to the short
    {
        sa, sa + 1, sa + 2
    };
    cout << "arrp=" << arrp << "; *arrp=" << *arrp << endl;
    cout << "*arrp[1]=" << *arrp[1] << "; *(*(arrp + 2))=" << *(*(arrp + 2)) << endl;
    cout << "sizeof(*sa)=" << sizeof(*sa) << endl;
    cout << "sizeof(&sa)=" << sizeof(&sa) << "; sizeof(sa)=" << sizeof(sa) << endl;
    cout << "sizeof(psa)=" << sizeof(psa) << "; sizeof(*psa)=" << sizeof(*psa) << endl;
    cout << "sizeof(arrp)=" << sizeof(arrp) << "; sizeof(*arrp)=" << sizeof(*arrp) << endl;
}

void get_to_vector(void)
{
    cout << "\nGet to the vector<>:\n";
    int n = 3;
    vector<int> vect(n);
    vect[2] = 12;
    cout << "vect:";
    for (int i = 0; i < n; ++i)
        cout << ' ' << vect[i];
    cout << endl;
}

static void ex1(void)
{
    cout << "\nExercise 1 (char*):\n";
    cout << "What is your first name? ";
    Line f_name = Line(cin);
    cout << "What is your last name? ";
    Line l_name = Line(cin);
    cout << "What is your age? ";
    size_t age = input_size();
    cout << "Name: " << f_name << ' ' << l_name << "; Age: " << age << endl;
}

static void ex2(void)
{
    cout << "\nExercise 2 (string):\n";
    string name, dessert;
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your favorite dessert: ";
    getline(cin,  dessert);
    cout << "I have some delicious " << dessert << " for you, " << name << ".\n";
}

static void ex3(void)
{
    cout << "\nExercise 3 (strcat):\n";
    cout << "Enter your first name: ";
    Line f_name = Line(cin);
    string l_name;
    cout << "Enter your last name: ";
    getline(cin, l_name);
    l_name += "\n";
    char buf[F4_SIZE]{};
    strcpy(buf, f_name.str());
    strcat(buf, " ");
    strcat(buf, l_name.c_str());
    cout << "Here's the information in a single string: " << buf;
}

struct CandyBar
{
    char name[FF_SIZE];
    float weight;
    int calories;
};

static void ex5(void)
{
    cout << "\nExercise 5:\n";
    CandyBar snack { "Mocha Much", 2.3, 350 };
    cout << "Name: " << snack.name << endl
        << "Weight: " << snack.weight << endl
        << "Calories: " << snack.calories << endl;
}

static void ex6(void)
{
    cout << "\nExercise 6:\n";
    CandyBar candies[3]
    {
        { "Hellos-Kakos", 2.4, 374 },
        { "Muchachos", 2.0, 392 },
        { "Goody good", 3.1, 369 }
    };
    for (int i = 0; i < 3; i++)
    {
        cout << i + 1
            << ": Name: " << (*(candies + i)).name << endl
            << "Weight: " << candies[i].weight << endl
            << "Calories: " << (candies + i)->calories << endl;
    }
}

struct Pizza
{
    string company;
    double diameter;
    double weight;
} pizza;

static void ex7(void)
{
    cout << "\nExercise 7:\n";
    Pizza *p = &pizza;
    cout << "Enter name of company: ";
    getline(cin, p->company);
    cout << "Enter diameter of the pizza (2.3): ";
    p->diameter = input_double();
    cout << "Enter weight of pizza (2.3): ";
    (*p).weight = input_double();
    cout << "Company: " << pizza.company << endl;
    cout << "Diameter: " << (*p).diameter << endl;
    cout << "Weight: " << p->weight << endl;
}

static void ex8(void)
{
    cout << "\nExercise 8:\n";
    Pizza *p = new Pizza;
    cout << "Enter diameter of pizza (2.3): ";
    p->diameter = input_double();
    cout << "Enter name of company: ";
    getline(cin, p->company);
    cout << "Enter weight of pizza (2.3): ";
    p->weight = input_double();
    cout << "Company: " << (*p).company << endl;
    cout << "Diameter: " << (*p).diameter << endl;
    cout << "Weight: " << p->weight << endl;
    delete p;
}

static void ex9(void)
{
    cout << "\nExercise 9:\n";
    CandyBar *p = new CandyBar[3];
    p[0] = {"Hellos-Kakos", 2.4, 374};
    *(p + 1) = {"Muchachos", 2.0, 392};
    p[2] = {"Goody good", 3.1, 369};
    for (int i = 0; i < 3; i++)
    {
        cout << i + 1
            << ": Name: " << (*(p + i)).name << endl
            << "Weight: " << p[i].weight << endl
            << "Calories: " << (p + i)->calories << endl;
    }
    delete[] p;
}

static void ex10(void)
{
    cout << "\nExercise 10:\n";
    cout << "Enter the number of runnnings for 100 meters (2): ";
    int n = input_int();
    double *runs = new double[n];
    cout << "Enter " << n << " results in sec of the runnings (9.58):\n";
    for (int i = 0; i < n; i++)
    {
        cout << setfill('0') << setw(2) << i + 1 << ": ";
        runs[i] = input_double();
    }
    cout << "Results:\n";
    double avg = 0.0;
    for (int i = 0; i < n; i++)
    {
        cout << ' ' << runs[i];
        avg += runs[i];
    }
    cout << endl;
    avg /= n;
    cout << "Average: " << avg << endl;
    delete[] runs;
}
