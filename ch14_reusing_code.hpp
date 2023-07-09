#ifndef ch14_reusing_code_hpp
#define ch14_reusing_code_hpp
#include "Utils.hpp"
#include <cstdio>
#include <valarray>
#include <iomanip>

using namespace std;

int ch14_reusing_code();

// worky
class Worker_ch14 // ABC = abstract base class
{
private:
    Line m_name;
    int m_id;
protected:
    virtual void Get();
    virtual void Data() const;
public:
    Worker_ch14() : m_name("none"), m_id(0) {}
    Worker_ch14(Line const& name, int id);
    virtual ~Worker_ch14() = 0; // pure virtual function
    virtual void Set() = 0; // an object of the class can't be made
    virtual void Show() const = 0; // but the function can be defined
};
class Waiter_ch14 : virtual public Worker_ch14
{
private:
    int m_panache;
protected:
    virtual void Get();
    virtual void Data() const;
public:
    Waiter_ch14() : Worker_ch14(), m_panache(0) {};
    Waiter_ch14(Line const& name, int id, int panache)
        : Worker_ch14(name, id), m_panache(panache) {}
    Waiter_ch14(Worker_ch14 const& worker, int panache = 0)
        : Worker_ch14(worker), m_panache(panache) {}
    virtual ~Waiter_ch14() {}
    virtual void Set();
    virtual void Show() const;
};
class Singer_ch14 : public virtual Worker_ch14
{
public:
    enum {other, alto, contralto, soprano, bass, baritone, tenor};
    enum {Vtypes = 7};
private:
    static Line const types[Vtypes];
    int m_voice;
protected:
    virtual void Get();
    virtual void Data() const;
public:
    Singer_ch14() : Worker_ch14(), m_voice(0) {}
    Singer_ch14(Line const& name, int id, int voice)
        : Worker_ch14(name, id), m_voice(voice) {}
    Singer_ch14(Worker_ch14 const& worker, int voice = other)
        : Worker_ch14(worker), m_voice(voice) {}
    virtual ~Singer_ch14() {}
    virtual void Set();
    virtual void Show() const;
};
class SingingWaiter_ch14 : public Waiter_ch14, public Singer_ch14
{
protected:
    void Get();
    void Data() const;
public:
    SingingWaiter_ch14() : Worker_ch14(), Waiter_ch14(), Singer_ch14() {}
    SingingWaiter_ch14(Line const& name, int id, int panache, int voice)
        : Worker_ch14(name, id), Waiter_ch14(name, id, panache), Singer_ch14(name, id, voice) {}
    SingingWaiter_ch14(const Waiter_ch14 &waiter, int voice = other)
        : Worker_ch14(waiter), Waiter_ch14(waiter), Singer_ch14(waiter, voice) {}
    SingingWaiter_ch14(const Singer_ch14 &singer, int panache = 0)
        : Worker_ch14(singer), Waiter_ch14(singer, panache), Singer_ch14(singer) {}
    void Set();
    void Show() const;
};

// tmplt
template <typename Type>
class Stack_ch14
{
private:
    static size_t const AMOUNT_MAX = 0x7;
    Type m_elements[AMOUNT_MAX];
    size_t m_amount;
public:
    Stack_ch14() : m_amount(0) {}
    Stack_ch14(Stack_ch14 const&);
    Stack_ch14 & operator=(Stack_ch14 const&);
    bool isempty() const {return m_amount == 0;}
    bool isfull() const {return m_amount == AMOUNT_MAX;}
    bool push(const Type&);
    bool pop(Type&);
    void show() const;
};
template <typename Type>
Stack_ch14<Type>::Stack_ch14(Stack_ch14 const& stack)
{
    m_amount = stack.m_amount;
    for (int i = 0; i < m_amount; ++i)
        m_elements[i] = stack.m_elements[i];
}
template <typename Type>
Stack_ch14<Type> & Stack_ch14<Type>::operator=(const Stack_ch14 &stack)
{
    if (this == &stack)
        return *this;
    m_amount = stack.m_amount;
    for (int i = 0; i < m_amount; ++i)
        m_elements[i] = stack.m_elements[i];
    return *this;
}
template <typename Type>
bool Stack_ch14<Type>::push(Type const& element)
{
    if (isfull())
        return false;
    m_elements[m_amount++] = element;
    return true;
}
template <typename Type>
bool Stack_ch14<Type>::pop(Type& element)
{
    if (isempty())
        return false;
    element = m_elements[--m_amount];
    return true;
}
template <typename Type>
void Stack_ch14<Type>::show() const
{
    cout.fill('0');
    for (size_t i = m_amount - 1;; --i)
    {
        cout << setw(2) << i + 1 << ": " << m_elements[i] << endl;
        if (i == 0)
            break;
    }
    cout << setfill(' ');
}

// frindly_templ_fun - связанные шаблонные друзья
template <typename T> void show2(T const&);
template <typename T> class Friendly
{
private:
    T m_a;
    T m_b;
public:
    Friendly(T a, T b) : m_a(a), m_b(b) {}
    // нешаблонные друзья
    friend void show1(Friendly<T> const&);
    // связанные шаблонные друзья
    friend void show2< Friendly<T> >(Friendly<T> const&);
    // == friend void show2<>(Friendly<T> const&);
    // не связанные шаблонные друзья
    template <typename C> friend void show3(C const&);
};
template <class D> void show2(D const& d)
{
    cout << " v2: " << d.m_a << ", " << d.m_b << endl;
}
template <class C> void show3(const C &c)
{
    cout << " v3: " << c.m_a << ", " << c.m_b << endl;
}

// number1
template <class T1, class T2> class Pair
{
private:
    T1 m_fst;
    T2 m_snd;
public:
    Pair() : m_fst(0), m_snd(0) {}
    Pair(T1 const& fst, T2 const& snd) : m_fst(fst), m_snd(snd) {}
    T1& first() {return m_fst;}
    T1 const& first() const {return m_fst;}
    T2& second() {return m_snd;}
    T2 const& second() const {return m_snd;}
};
typedef valarray<int> Vint;
typedef Pair<Vint, Vint> PairVint;
class Wine
{
private:
    Line const m_label;
    int m_amount;
    PairVint m_years_bottles;
public:
    Wine(Line const& label, int amount)
        : m_label(label), m_amount(amount), m_years_bottles(PairVint()) {}
    Wine(Line const& label, int amount, Vint const& years, Vint const& bottles)
        : m_label(label), m_amount(amount), m_years_bottles(PairVint(years, bottles)) {}
    Line const& Label() const {return m_label;};
    int Sum() const {return m_years_bottles.second().sum();}
    void Get();
    void Show() const;
};

// number2
class Wine2 : private PairVint
{
private:
    string label;
    int years;
public:
    Wine2(const string &l, int y)
    : PairVint(), label(l), years(y) {}
    Wine2(const string &l, int y, const Vint & yr, const Vint & bot)
    : PairVint(yr, bot), label(l), years(y) {}
    int Sum() const {return second().sum();}
    void Get();
    void Show() const;
};

// number3
template <class T> class QueueTP
{
public:
    struct Node
    {
        T elem;
        Node *next;
        Node *previous;
    };
private:
    int amount;
    Node *front;
    Node *rear;
    QueueTP(const QueueTP &q) {}
    QueueTP & operator=(const QueueTP &q) {return *this;}
public:
    QueueTP() : front(nullptr), rear(nullptr), amount(0) {}
    ~QueueTP();
    void AddFront(const T &);
    void AddRear(const T &);
    bool DelFront(T &);
    bool DelRear(T &);
    bool Show() const;
};
template <class T>
QueueTP<T>::~QueueTP()
{
    Node *temp;
    for (int i = 0; i < amount; ++i)
    {
        temp = front;
        front = front->next;
        delete temp;
    }
}
template <class T>
void QueueTP<T>::AddFront(const T &t)
{
    Node *temp = new Node;
    temp->elem = t;
    temp->previous = nullptr;
    if (amount++ == 0)
    {
        temp->next = nullptr;
        rear = temp;
    }
    else
    {
        temp->next = front;
        front->previous = temp;
    }
    front = temp;
}
template <class T>
void QueueTP<T>::AddRear(const T &t)
{
    Node *temp = new Node;
    temp->elem = t;
    temp->next = nullptr;
    if (amount++ == 0)
    {
        temp->previous = nullptr;
        front = temp;
    }
    else
    {
        temp->previous = rear;
        rear->next = temp;
    }
    rear = temp;
}
template <class T>
bool QueueTP<T>::DelFront(T &t)
{
    if (amount == 0)
        return false;
    t = front->elem;
    Node *temp = front;
    front = front->next;
    front->previous = nullptr;
    delete temp;
    --amount;
    return true;
}
template <class T>
bool QueueTP<T>::DelRear(T &t)
{
    if (amount == 0)
        return false;
    t = rear->elem;
    Node *temp = rear;
    rear = rear->previous;
    rear->next = nullptr;
    delete temp;
    --amount;
    return true;
}
template <class T>
bool QueueTP<T>::Show() const
{
    if (amount == 0)
        return false;
    Node *temp = front;
    cout << '\t';
    for (int i = 0; i < amount; ++i)
    {
        cout << temp->elem << ' ';
        temp = temp->next;
    }
    cout << '\n';
    return true;
}

// number4
typedef const char* ccp;
class Person_ch14
{
private:
    char* fname;
    char* lname;
protected:
    void Get();
    void Data() const;
public:
    Person_ch14();
    Person_ch14(ccp f, ccp l);
    Person_ch14(const Person_ch14 &);
    virtual ~Person_ch14();
    Person_ch14 & operator=(const Person_ch14 &);
    virtual void Set();
    virtual void Show() const;
};
class Gunslinger : virtual public Person_ch14
{
private:
    double ptime;
    int notching;
protected:
    void Get();
    void Data() const;
public:
    Gunslinger() : Person_ch14(), ptime(0), notching(0) {}
    Gunslinger(ccp f, ccp l, double tp, int nt)
        : Person_ch14(f, l), ptime(tp), notching(nt) {}
    Gunslinger(const Person_ch14 &p, double tp, int nt)
        : Person_ch14(p), ptime(tp), notching(nt) {}
    virtual ~Gunslinger() {};
    double Draw() const {return ptime;}
    virtual void Set();
    virtual void Show() const;
};
class PokerPlayer : public virtual Person_ch14
{
private:
    short card;
protected:
    void Get();
    void Data() const;
public:
    PokerPlayer() : Person_ch14(), card(0) {}
    PokerPlayer(ccp f, ccp l) : Person_ch14(f, l) {Get();}
    PokerPlayer(const Person_ch14 &p) : Person_ch14(p) {Get();}
    virtual ~PokerPlayer() {};
    short Draw() const {return card;}
    virtual void Set();
    virtual void Show() const;
};
class BadDude : public Gunslinger, public PokerPlayer
{
public:
    BadDude() : Person_ch14(), Gunslinger(), PokerPlayer() {}
    BadDude(ccp f, ccp l, double pt, int nt)
        : Person_ch14(f, l), Gunslinger(f, l, pt, nt), PokerPlayer(f, l) {}
    double Gdraw() const {return Gunslinger::Draw();}
    short Cdraw() const {return PokerPlayer::Draw();}
    void Set();
    void Show() const;
};

// number5
typedef const string CS;
class abstr_emp
{
private:
    string fname;
    string lname;
    string job;
public:
    abstr_emp() : fname("none"), lname("none"), job("none") {}
    abstr_emp(CS &f, CS &l, CS &j)
    : fname(f), lname(l), job(j) {}
    virtual ~abstr_emp() = 0;
    virtual void SetAll();
    virtual void ShowAll() const;
    friend ostream & operator<<(ostream &, const abstr_emp &);
};
class employee : public abstr_emp
{
public:
    employee() : abstr_emp() {}
    employee(CS &f, CS &l, CS &j)
    : abstr_emp(f, l, j) {}
    virtual void SetAll();
    virtual void ShowAll() const;
};
class manager : virtual public abstr_emp
{
protected:
    int inchargeof;
public:
    manager() : abstr_emp(), inchargeof(0) {}
    manager(CS &f, CS &l, CS &j, int inchof)
    : abstr_emp(f, l, j), inchargeof(inchof) {}
    manager(const abstr_emp &ab, int inchof)
    : abstr_emp(ab), inchargeof(inchof) {}
    virtual ~manager() {}
    virtual void SetAll();
    virtual void ShowAll() const;
};
class fink : virtual public abstr_emp
{
protected:
    string reportsto;
public:
    fink() : abstr_emp(), reportsto("none") {}
    fink(CS &f, CS &l, CS &j, CS & rto)
    : abstr_emp(f, l, j), reportsto(rto) {}
    fink(const abstr_emp &ab, const string &rto)
    : abstr_emp(ab), reportsto(rto) {}
    virtual ~fink() {}
    virtual void SetAll();
    virtual void ShowAll() const;
};
class highfink : public manager, public fink
{
public:
    highfink() : manager(), fink() {}
    highfink(CS &f, CS &l, CS &j, int inchof, CS &rto)
    : abstr_emp(f, l, j), manager(f, l, j, inchof), fink(f, l, j, rto) {}
    highfink(const abstr_emp &ae, int inchof, CS &rto)
    : abstr_emp(ae), manager(ae, inchof), fink(ae, rto) {}
    highfink(const manager &mn, CS &rto)
    : abstr_emp(mn), manager(mn), fink(mn, rto) {}
    highfink(const fink &fk, int inchof)
    : abstr_emp(fk), manager(fk, inchof), fink(fk) {}
    void SetAll();
    void ShowAll() const;
};

#endif /* ch14_reusing_code_hpp */
