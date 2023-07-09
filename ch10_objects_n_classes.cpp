#include "ch10_objects_n_classes.hpp"
#include "Utils.hpp"
#include <cstring>

using namespace std;

static void ex0();
static void ex1();
static void ex3();
static void ex4();
static void ex5();
static void ex6();
static void ex7();
static void ex8();

int ch10_objects_n_classes()
{
    print_run_chapter_message(10);
    ex0();
    ex1();
    ex3();
    ex4();
    ex5();
    ex6();
    ex7();
    ex8();
    return EXIT_SUCCESS;
}

// exercise 0
void ex0()
{
    cout << "\nExercise 0\n";
    Person pers{};
  //*pers.p_age() = 15; // invalid because of 'const*' in the declaration
    pers.r_age() = 15;
    cout << "name():   " << pers.name() << endl;
    cout << "age():    " << pers.age() << endl;
    cout << "p_name(): " << pers.p_name() << endl;
    cout << "p_age():  " << pers.p_age() << endl;
    cout << "r_name(): " << pers.r_name() << endl;
    cout << "r_age():  " << pers.r_age() << endl;
    char buf[FF_SIZE]{};
    cout << "as_c_str(): " << pers.as_c_str(buf, FF_SIZE) << endl;
}

// exercise 1
BankAccount::BankAccount(co_ch *name, co_ch *number, co_db balance)
{
    strcpy(m_name, name);
    strcpy(m_number, number);
    m_balance = balance;
}
void BankAccount::show()
{
    cout << "  Name:   '" << m_name << "'\n";
    cout << "  Number: [" << m_number << "]\n";
    cout << "  Balance: " << m_balance << endl;
}
void ex1()
{
    cout << "\nExercise 1\n";
    BankAccount acc1, acc2("Nick", "12345678", 12430.2);
    cout << "Account 1:\n";
    acc1.show();
    cout << "Account 2:\n";
    acc2.show();
    cout << "Add to 2nd 100.\n";
    acc2.add(100.0);
    cout << "Take 23.1 from 2nd.\n";
    acc2.take(23.1);
}

// exercise 3
GolfPlayer_ex10::GolfPlayer_ex10(co_ch *name, const int &handicap)
{
    strcpy(m_name, name);
    m_handicap = handicap;
}
void GolfPlayer_ex10::fill_golf()
{
    cout << "Enter name of golf player: ";
    Line name = Line(cin);
    while (name.empty())
    {
        cout << "Enter name of golf player: ";
        input_line(name);
    }
    strncpy(m_name, name.str(), name.len() + 1);
    cout << "Enter handicap: ";
    m_handicap = input_int();
}
void GolfPlayer_ex10::show()
{
    cout << "  Name:     " << m_name << endl;
    cout << "  Handicap: " << m_handicap << endl;
}
void ex3()
{
    cout << "\nExercise 3\n";
    GolfPlayer_ex10 players[] =
    {
        {},
        {"Ronnie O'Salivan", 123},
        {"Nick Furie"}
    };
    const size_t N = sizeof(players) / sizeof(GolfPlayer_ex10);
    for (size_t i = 0; i < N; ++i)
    {
        cout << "Player #" << i + 1 << "\n";
        players[i].show();
    }
    players[2].set_handicap(128);
    cout << "The handicap of player #3 is reset.\n";
    cout << "Enter player #1:\n";
    players[0].fill_golf();
    for (size_t i = 0; i < N; ++i)
    {
        cout << "Player #" << i + 1 << "\n";
        players[i].show();
    }
}

// exercise 4
SALES_ex10::Sales::Sales()
{
    for (size_t i = 0; i < QUARTERS; ++i)
        m_values[i] = 0;
    m_min = m_max = m_average = 0.0;
}
SALES_ex10::Sales::Sales(co_db *values, const size_t &N)
{
    if (N == 0)
    {
        m_n_values = 1;
        m_values[0] = m_average = m_max = m_min = 0.0;
        return;
    }
    m_n_values = QUARTERS < N ? QUARTERS : N;
    double sum = m_values[0] = values[0];
    m_max = values[0];
    m_min = values[0];
    for (size_t i = 1; i < m_n_values; ++i)
    {
        m_values[i] = values[i];
        sum += values[i];
        if (m_max < values[i])
            m_max = values[i];
        if (values[i] < m_min)
            m_min = values[i];
    }
    m_average = sum / m_n_values;
}
SALES_ex10::Sales::~Sales()
{
    cout << "In 'SALES::Sales::~Sales()'\n";
}
void SALES_ex10::Sales::show()
{
    cout << "  Values:";
    for (size_t i = 0; i < m_n_values; ++i)
        cout << ' ' << m_values[i];
    cout << endl;
    cout << "  Average: " << m_average << endl;
    cout << "  Max:     " << m_max << endl;
    cout << "  Min:     " << m_min << endl;
}
void ex4()
{
    cout << "\nExercise 4\n";
    using namespace SALES_ex10;
    double sales_values1[] = {1.2, 3.432, 423.98543, 289.43195};
    const size_t N1 = sizeof(sales_values1) / sizeof(double);
    double sales_values2[] = {2.1, 28.572, 289.5973};
    const size_t N2 = sizeof(sales_values2) / sizeof(double);
    Sales sales1 = Sales(sales_values1, N1);
    Sales sales2 = Sales(sales_values2, N2);
    Sales sales3 = Sales();
    cout << "Sales #1\n";
    sales1.show();
    cout << "Sales #2\n";
    sales2.show();
    cout << "Sales #3\n";
    sales3.show();
}

// exercise 5
bool Stack::push(const Customer &customer)
{
    if (m_n_customers == MAX_N_CUSTOMERS)
        return false;
    m_customers[m_n_customers++] = customer;
    return true;
}
bool Stack::pull(Customer &customer)
{
    if (m_n_customers == 0)
        return false;
    Customer &pulled = m_customers[--m_n_customers];
    strcpy(customer.name, pulled.name);
    customer.payment = pulled.payment;
    return true;
}
void show_customer(const Customer &customer)
{
    cout << "  Name:    " << customer.name << endl;
    cout << "  Payment: " << customer.payment << endl;
}
void ex5()
{
    cout << "\nExercise 5\n";
    Customer customers[]
    {
        {"Nicholas Joseph Fury", 11232.67},
        {"Jack Sparow", 13734.29},
        {"Don Quixote", 12876.85}
    };
    const size_t N = sizeof(customers) / sizeof(Customer);
    Stack stack{};
    cout << "Pushing customers into the stack\n";
    for (size_t i = 0; i < N; ++i)
    {
        cout << "Customer #" << i + 1 << endl;
        show_customer(customers[i]);
        if (!stack.push(customers[i]))
        {
            cout << "Oops! The stack is full\n";
            break;
        }
    }
    cout << "Customers menu: a) push; b) pull; q) quit: ";
    Line line = Line(cin);
    while (line != "q")
    {
        if (line == "a")
        {
            if (stack.is_full())
            {
                cout << "Oops! The stack is full\n";
                cout << "Customers menu: a) push; b) pull; q) quit: ";
                input_line(line);
                continue;
            }
            cout << "Pushing a new customer\n";
            Customer customer{};
            cout << "Name:    ";
            Line buf = Line(cin);
            strncpy(customer.name, buf.str(), buf.len() + 1);
            cout << "Payment (2.3): ";
            customer.payment = input_double();
            stack.push(customer);
        }
        else if (line == "b")
        {
            if (stack.is_empty())
            {
                cout << "Oops! The stack is empty\n";
                cout << "Customers menu: a) push; b) pull; q) quit: ";
                input_line(line);
                continue;
            }
            cout << "Pulling a customer from the top\n";
            Customer customer{};
            stack.pull(customer);
            cout << "Pulled customer\n";
            show_customer(customer);
        }
        cout << "Customers menu: a) push; b) pull; q) quit: ";
        input_line(line);
    }
}

// exercise 6
Move::Move(double const& x, double const& y)
{
    m_x = x;
    m_y = y;
}
Move& Move::add(Move const& move)
{
    m_x += move.m_x;
    m_y += move.m_y;
    return *this;
}
void Move::reset(const double &x, const double &y)
{
    m_x = x;
    m_y = y;
}
void Move::show() const
{
    cout << "  (x=" << m_x << ", y=" << m_y << ")\n";
}
char const* Move::as_c_str(char* buf, size_t const& BUF_SIZE) const
{
    sprintf(buf, "(x=%.3e, y=%.3e)", m_x, m_y);
    return (char const*)buf;
}
inline void show_moves(Move *moves, const size_t &N)
{
    char buf[FF_SIZE]{};
    for (size_t i = 0; i < N; ++i)
        cout << "  Move #" << i + 1 << ": " << moves[i].as_c_str(buf, FF_SIZE) << endl;
}
void ex6()
{
    cout << "\nExercise 6\n";
    const size_t N = 3;
    Move moves[N] {Move(), Move(), Move()};
    double x = 1.23, y = 2.34;
    for (size_t i = 0; i < N; ++i)
    {
        moves[i].reset(x, y);
        if (i % 2 != 0)
        {
            x += 1.0;
            y += 0.5;
        }
        else
        {
            x += 0.5;
            y += 1.0;
        }
    }
    cout << "Moves\n";
    show_moves(moves, N);
    moves[0].add(moves[1]).add(moves[2]);
    moves[1].add(moves[2]);
    cout << "Some move additions were made";
    cout << "Moves\n";
    show_moves(moves, N);
}

// exercise 7
Plorg::Plorg(co_ch *name, const size_t &ind)
{
    strncpy(m_name, name, LEN);
    m_name[LEN - 1] = '\0';
    m_index = ind;
}
Plorg& Plorg::set_name(co_ch *name)
{
    strncpy(m_name, name, LEN);
    m_name[LEN - 1] = '\0';
    return *this;
}
Plorg& Plorg::set_index(const size_t &ind)
{
    m_index = ind;
    return *this;
}
void ex7()
{
    cout << "\nExercise 7\n";
    Plorg plorg1 {Plorg()}, plorg2 {Plorg("Plorg2")}, plorg3 {Plorg("Plorg3", 3)};
    plorg1.set_name("Long name, very very very very very");
    plorg1.set_index(1);
    plorg2.set_index(2);
    cout << "Plorg #1\n";
    cout << "  Name:  '" << plorg1.name() << "'\n";
    cout << "  Index:  " << plorg1.index() << endl;
    cout << "Plorg #2\n";
    cout << "  Name:  '" << plorg2.name() << "'\n";
    cout << "  Index:  " << plorg2.index() << endl;
    cout << "Plorg #3\n";
    cout << "  Name:  '" << plorg3.name() << "'\n";
    cout << "  Index:  " << plorg3.index() << endl;
}

// exercise 8
template<class T> List<T>::List()
{
    arr = new T[DEFAULT_CAPACITY];
    m_capacity = DEFAULT_CAPACITY;
    m_size = 0;
}
template<class T> List<T>::~List()
{
    delete[] arr;
}
template<class T> bool List<T>::add(const T &elem)
{
    if (m_size == MAX_SIZE)
        return false;
    if (m_size == m_capacity)
    {
        m_capacity <<= 1;
        T *old_arr = arr;
        arr = new T[m_capacity];
        for (T *i = arr, *o_i = old_arr; o_i != old_arr + m_size; ++o_i, ++i)
            *i = *o_i;
        delete[] old_arr;
    }
    arr[m_size++] = elem;
    return true;
}
template<class T> bool List<T>::remove(const size_t &ind)
{
    if (m_size == 0)
        return false;
    for (size_t i = ind; i < m_size; ++i)
        arr[i] = arr[i + 1];
    --m_size;
    return true;
}
template<class T> const char* List<T>::as_c_str() const
{
    char buf[F4_SIZE]{};
    sprintf(buf, "[capacity=%zu, size=%zu]", m_capacity, m_size);
    const char *str = buf;
    return str;
}
template<> const char* List<int>::as_c_str() const
{
    char buf[F4_SIZE]{};
    sprintf(buf, "[capacity=%zu, size=%zu, arr={", m_capacity, m_size);
    if (0 < m_size)
    {
        char buf2[FF_SIZE]{};
        sprintf(buf2, "%d", arr[0]);
        strcat(buf, buf2);
        for (size_t i = 1; i < m_size; ++i)
        {
            sprintf(buf2, ", %d", arr[i]);
            strcat(buf, buf2);
        }
    }
    strcat(buf, "}]");
    const char *str = buf;
    return str;
}

// exercise 8
void ex8()
{
    cout << "\nExercise 8\n";
    List<int> list = List<int>();
    cout << list.as_c_str() << endl;
    int cnt = -8;
    for (size_t i = 0; i < 17; ++i, ++cnt)
    {
        list.add(cnt);
        cout << list.as_c_str() << endl;
    }
    seed_rand();
    for (size_t i = 0; i < 9; ++i)
    {
        size_t ind_to_remove = rand() % list.size();
        list.remove(ind_to_remove);
        cout << list.as_c_str() << endl;
    }
}
