#include "ch09_memory_models_n_namespaces.hpp"
#include <cfloat>

using namespace std;

static void ex1();
static void ex2();
static void ex3();
static void ex4();

int ch09_memory_models_n_namespaces()
{
    print_run_chapter_message(9);
    ex1();
    ex2();
    ex3();
    ex4();
    return EXIT_SUCCESS;
}

// exercise 1
void set_golf_player(GolfPlayer &gp, const char *name, const int &handicap)
{
    strcpy(gp.name, name);
    gp.handicap = handicap;
}
bool set_golf_player(GolfPlayer &gp)
{
    cout << "Enter name (empty line to quit): ";
    Line line = Line(cin);
    if (line.empty())
        return false;
    strcpy(gp.name, line.str());
    cout << "Enter handicape (3): ";
    gp.handicap = input_int(); // handicap - measure of skill
    return true;
}
void show_golf_player(const GolfPlayer &gp)
{
    cout << "  Name:     " << gp.name << endl;
    cout << "  Handicap: " << gp.handicap << endl;
}
void ex1(void)
{
    cout << "\nExercise 1\n";
    const size_t N = 4;
    GolfPlayer players[N]{};
    set_golf_player(players[0], "Steve Vai", 21);
    cout << "There are " << N << " golf player(s).\n";
    cout << "Player #1\n";
    show_golf_player(players[0]);
    cout << "Enter the remaining ones.\n";
    size_t n = 1;
    for (; n < N; ++n)
    {
        cout << "Player #" << n + 1 << endl;
        if (!set_golf_player(players[n]))
            break;
    }
    for (size_t i = 0; i < n; ++i)
    {
        cout << "Player #" << n + 1 << endl;
        show_golf_player(players[i]);
    }
}

// exercise 2
void show_headphone(Headphone &headphone)
{
    static int total = 0;
    total += headphone.price;
    cout << "  Brand: " << headphone.name << endl;
    cout << "  Price: " << headphone.price << endl;
    cout << "Total: " << total << endl;
}
void ex2(void)
{
    cout << "\nExercise 2\n";
    const int siz = 3;
    Headphone headphones[siz] =
    {
        {"Sony", 32},
        {"Beats", 103},
        {"Sennheiser", 64}
    };
    for (size_t i = 0; i < siz; ++i)
        
    for (int i = 0; i < siz - 1; ++i)
        show_headphone(headphones[i]);
}

// exercise 3
void fill_harvest(Harvest &harvest, const char *field, const int &tons)
{
    strcpy(harvest.field, field);
    harvest.tons = tons;
}
void show_harvest(const Harvest &harvest)
{
    cout << "  Field: " << harvest.field << endl;
    cout << "  Tons:  " << harvest.tons << endl;
}
const size_t N_HARVESTS = 2;
const size_t BUF_SIZE = ( FF_SIZE + sizeof(int) / sizeof(char) ) * N_HARVESTS;
static char buffer[BUF_SIZE]{};
void ex3(void)
{
    cout << "\nExercise 3 (placement new)\n";
    Harvest *harvests = new (&buffer) Harvest[N_HARVESTS];
    fill_harvest(harvests[0], "Ivanushkino", 110);
    fill_harvest(harvests[1], "Pavlovo", 120);
    cout << "Harvests #1\n";
    show_harvest(harvests[0]);
    cout << "Harvests #2\n";
    show_harvest(harvests[1]);
}

// exercise 4
namespace SALES
{
const Sales& set_sales(Sales &sales, const double *values, const size_t &VALUES_SIZE)
{
    if (VALUES_SIZE == 0)
        return sales;
    sales.n_values = QUARTERS < VALUES_SIZE ? QUARTERS : VALUES_SIZE;
    double &mx = sales.max;
    double &mn = sales.min;
    double &avg = sales.average;
    mx = values[0];
    mn = values[0];
    double sum = sales.values[0] = values[0];
    for (size_t i = 1; i < sales.n_values; ++i)
    {
        sales.values[i] = values[i];
        sum += values[i];
        if (mx < values[i])
            mx = values[i];
        if (values[i] < mn)
            mn = values[i];
    }
    avg = sum / sales.n_values;
    return sales;
}
const Sales& set_sales(Sales &sales)
{
    while (4 < sales.n_values || sales.n_values < 1) // by default = 0
    {
        cout << "Enter number of quarters [1, 4]: ";
        sales.n_values = input_size();
    }
    double (&vals)[QUARTERS] = sales.values;
    double &mx = sales.max;
    double &mn = sales.min;
    double &avg = sales.average;
    mx = DBL_MIN;
    mn = DBL_MAX;
    double sum = 0.0;
    for (size_t i = 0; i < sales.n_values; ++i)
    {
        cout << "Quarter #" << i + 1 << ": enter value of sales (1200.0): ";
        vals[i] = input_double();
        sum += vals[i];
        if (mx < vals[i])
            mx = vals[i];
        if (vals[i] < mn)
            mn = vals[i];
    }
    avg = sum / sales.n_values;
    return sales;
}
void show_sales(const Sales &sales)
{
    using std::cout;
    using std::endl;
    cout << "  Sales:";
    for (size_t i = 0; i < sales.n_values; ++i)
        cout << ' ' << sales.values[i];
    cout << endl;
    cout << "  Average: " << sales.average << endl;
    cout << "  Max:     " << sales.max << endl;
    cout << "  Min:     " << sales.min << endl;
}
}
void ex4(void)
{
    cout << "\nExercise 4\n";
    SALES::Sales sales1, sales2;
    double values[] = {1430.0, 970.50, 1028.0};
    const size_t N = sizeof(values) / sizeof(double);
    SALES::set_sales(sales1, values, N);
    cout << "Sales #1\n";
    SALES::show_sales(sales1);
    SALES::set_sales(sales2);
    cout << "Sales #2\n";
    SALES::show_sales(sales2);
}
