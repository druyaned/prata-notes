#ifndef ch09_memory_models_n_namespaces_hpp
#define ch09_memory_models_n_namespaces_hpp

#include "Utils.hpp"
#include <new>

int ch09_memory_models_n_namespaces();

// exercise 1
struct GolfPlayer {char name[FF_SIZE]; int handicap;}; // handicap - measure of skill
void set_golf_player(GolfPlayer &gp, const char *name, const int &handicap);
bool set_golf_player(GolfPlayer &gp);
void show_golf_player(const GolfPlayer &gp);

// exercise 2
struct Headphone {char name[FF_SIZE]; int price;};
void show_headphone(Headphone &headphone);

// exercise 3
struct Harvest {char field[FF_SIZE]; int tons;};
void fill_harvest(Harvest &harvest, const char *field, const int &tons);
void show_harvest(const Harvest &harvest);

// exercise 4
namespace SALES
{
const size_t QUARTERS = 4; // квартал
struct Sales
{
    double values[QUARTERS]{};
    size_t n_values = 0;
    double average = 0.0;
    double max = 0.0;
    double min = 0.0;
};
const Sales& set_sales(Sales &sales, const double *values, const size_t &VALUES_SIZE);
const Sales& set_sales(Sales &sales); // interactive
void show_sales(const Sales &sales);
}

#endif /* ch09_memory_models_n_namespaces_hpp */
