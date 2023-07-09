#ifndef ch12_classes_n_dynamic_memory_allocation_hpp
#define ch12_classes_n_dynamic_memory_allocation_hpp
#include "Utils.hpp"

int ch12_classes_n_dynamic_memory_allocation();

// Str
class String
{
private:
    char *str;
    int l;
    static int num;
    static const int inlim = 81;
public:
    String();                   // default constructer
    String(const char *);
    String(const String &);     // copier-constructer
    ~String();
    int L() {return l;};
    String & operator=(const String &);
    char & operator[](int i) {return str[i];};
    const char & operator[](int i) const {return str[i];};
    bool operator<(const String &) const;
    bool operator>(const String &) const;
    bool operator==(const String &) const;
    friend std::ostream & operator<<(std::ostream &, const String &);
    friend std::istream & operator>>(std::istream &, String &);
    static int number() {return num;};
};

// que
class Customer_ch12
{
private:
    long arrive;
    short processtime;
public:
    Customer_ch12(void) : arrive(0), processtime(0) {};
    ~Customer_ch12(void) {}
    void SetCust(long);
    long when(void) {return arrive;}
    short ptime(void) {return processtime;}
};
class Queue
{
    struct Node
    {
        Customer_ch12 item;
        Node *next;
    };
private:
    int amount;
    const int MaxAmount;
    Node *front;
    Node *rear;
    Queue(const Queue &) : MaxAmount(0) {} // these 2 lines exist
    Queue & operator=(const Queue &) {return *this;} // to eliminate the possibility of errors
public:
    Queue(int mq = 10);
    ~Queue(void);
    bool isempty(void) const {return amount == 0;}
    bool isfull(void) const{return amount == MaxAmount;}
    int amountQ(void) {return amount;}
    bool enQueue(const Customer_ch12 &);
    bool deQueue(Customer_ch12 &);
};
inline bool NewCust(double a) {return (rand() * a / RAND_MAX < 1.0);}

// number1
class Cow
{
    char name[20];
    char *hobby;
    double weight;
    static int num;
public:
    Cow();
    Cow(const char *nm, const char *ho, double wt);
    Cow(const Cow &c);
    ~Cow();
    Cow & operator=(const Cow & c);
    void ShowCow() const;    // отображение всех данных Cow
};

// number2
class StringS
{
private:
    char *str;
    int l;
    static int num;
    static const int CinSiz;
public:
    StringS(void);
    StringS(const char *);
    StringS(const StringS &);
    ~StringS();
    int L(void) const {return l;}
    StringS & operator=(const StringS &);
    StringS & operator=(const char *);
    bool operator<(const StringS &) const;
    bool operator>(const StringS &) const;
    bool operator==(const StringS &) const;
    char & operator[](int i) {return str[i];}
    const char & operator[](int i) const {return str[i];}
    StringS operator+(const StringS &) const;
    StringS resiz(int);
    StringS strlow();
    StringS strup();
    friend std::ostream & operator<<(std::ostream &, const StringS &);
    friend std::istream & operator>>(std::istream &, StringS &);
};

// number3
typedef char Mytype;
class Line_ch12
{
    struct node
    {
        Mytype c;
        node *next;
        node *previous;
    };
private:
    const int lim = 1000;
    int num;
    node *front;
    node *rear;
    Line_ch12(const Line_ch12 &) {}
    Line_ch12 & operator=(const Line_ch12 &) {return *this;}
public:
    Line_ch12(void);
    ~Line_ch12(void);
    int N(void) const {return num;}
    inline bool isfull(void) const {return num == lim;}
    inline bool isempty(void) const {return num == 0;}
    bool addFront(const Mytype &);
    bool addRear(const Mytype &);
    bool delFront(const Mytype &);
    bool delRear(const Mytype &);
    inline const Mytype & Front(void) const {return front->c;}
    inline const Mytype & Rear(void) const {return rear->c;}
    friend std::ostream & operator<<(std::ostream&, Line_ch12 const&);
};

// number4
typedef long type4;
class Stack_ch12
{
private:
    enum {M = 100};
    type4 *st;
    int num;
    int top;
public:
    Stack_ch12(int n = 10);
    Stack_ch12(const Stack_ch12 &);
    ~Stack_ch12(void);
    inline bool isempty(void) const {return top == 0;}
    inline bool isfull(void) const {return top == num;}
    bool add(const type4 &);
    bool take(type4 &);
    Stack_ch12 & operator=(const Stack_ch12 &);
    void Show(void) const;
};


#endif /* ch12_classes_n_dynamic_memory_allocation_hpp */
