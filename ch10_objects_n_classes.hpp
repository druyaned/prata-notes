#ifndef ch10_objects_n_classes_hpp
#define ch10_objects_n_classes_hpp

#include "Utils.hpp"
#include <string>
typedef const char co_ch;
typedef const double co_db;
typedef const std::string co_st;

int ch10_objects_n_classes();

// exercise 0
class Person
{
private:
    char const* m_name;
    size_t m_age;
public:
    // constructor & destructor
    Person()
    {
        m_name = "name";
        m_age = 0;
    }
    ~Person() {}
    // getters
    char const* name() const {return m_name;}
    size_t age() const {return m_age;}
    // getter-pointers
    char const* const* p_name() const {return &m_name;}
    size_t const* p_age() const {return &m_age;}
    // getter- and setter-references
    char const* & r_name() {return m_name;}
    size_t & r_age() {return m_age;}
    // c_srt
    char const* as_c_str(char* buf, size_t const& BUF_SIZE) const
    {
        sprintf(buf, "[name=%s, age=%zu]", m_name, m_age);
        return buf;
    }
};

// exercise 1
class BankAccount
{
private: // 'm_' - it's an arrangement to identify member variables
    char m_name[FF_SIZE];
    char m_number[FF_SIZE];
    double m_balance;
public: // 'm_name' can't be used as a parameter
    BankAccount(co_ch *name = "no_name", co_ch *number = "none", co_db balance = 0.0);
    void show();
    inline void add(co_db to_balance) {m_balance += to_balance;}
    inline void take(co_db from_balance) {m_balance -= from_balance;}
    inline const double& balance() const {return m_balance;}
    // 'const double&' - constant (only rvalue) return type; 'const;' - constant this
};

// exercise 3
class GolfPlayer_ex10
{
private:
    char m_name[FF_SIZE];
    int m_handicap; // handicap - measure of skill
public:
    GolfPlayer_ex10(co_ch *name = "no_name", const int &handicap = 0);
    void fill_golf();
    inline void set_handicap(const int &handicap) {m_handicap = handicap;}
    void show();
};

// exercise 4
namespace SALES_ex10
{
const size_t QUARTERS = 4;
class Sales
{
private:
    double m_values[QUARTERS]{};
    size_t m_n_values = 0;
    double m_average = 0.0;
    double m_max = 0.0;
    double m_min = 0.0;
public:
    Sales();
    Sales(co_db *values, const size_t &N);
    ~Sales();
    void show();
};
}

// exercise 5
struct Customer
{
    char name[FF_SIZE];
    double payment;
};
class Stack
{
    static const size_t MAX_N_CUSTOMERS = 7;
private:
    Customer m_customers[MAX_N_CUSTOMERS];
    size_t m_n_customers; // index
public:
    Stack() {m_n_customers = 0;}
    inline bool is_empty() {return m_n_customers == 0;}
    inline bool is_full() {return m_n_customers == MAX_N_CUSTOMERS;}
    bool push(const Customer &customer);
    bool pull(Customer &customer);
};

// exercise 6
class Move
{
private:
    double m_x;
    double m_y;
public:
    Move(double const& x = 0.0, double const& y = 0.0);
    Move& add(const Move &move);
    void reset(const double &x = 0, const double &y = 0);
    void show() const;
    char const* as_c_str(char* buf, size_t const& BUF_SIZE) const;
};

// exercise 7
class Plorg
{
private:
    enum {LEN = 20};
    char m_name[LEN];
    size_t m_index;
public:
    Plorg(co_ch *name = "Plorg", const size_t &ind = 50);
    char const* name() {return m_name;}
    size_t index() {return m_index;}
    Plorg& set_name(co_ch *name);
    Plorg& set_index(const size_t &ind);
};

// exercise 8
template<class T> class List
{
    static const size_t MAX_SIZE = 0xffff;
    static const size_t DEFAULT_CAPACITY = 0x10;
private:
    T *arr;
    size_t m_capacity;
    size_t m_size;
public:
    List();
    ~List();
    inline size_t capacity() const {return m_capacity;}
    inline size_t size() const {return m_size;}
    inline const T& operator[](const size_t &ind) const {return *(arr + ind);}
    bool add(const T &elem);
    bool remove(const size_t &ind);
    const char* as_c_str() const;
};

#endif /* ch10_objects_n_classes_hpp */
