#include "ch12_classes_n_dynamic_memory_allocation.hpp"
#include <cstring>

using namespace std;

static void my_string_practice(void);
static void queue_practice(void);
static void number1(void);
static void number2(void);
static void number3(void);
static void number4(void);
static void number6(void);

int ch12_classes_n_dynamic_memory_allocation()
{
    print_run_chapter_message(12);
    my_string_practice();
    queue_practice();
    number1();
    number2();
    number3();
    number4();
    number6();
    return EXIT_SUCCESS;
}

// my_string_practice
int String::num = 0;
String::String()
{
    ++num;
    l = 0;
    str = new char[1];
    str[0] = '\0';
    cout << "[Default constructer was called. " << num << " left]\n";
}
String::String(const char *s)
{
    ++num;
    l = int(strlen(s));
    str = new char[l + 1];
    strcpy(str, s);
    cout << "[Simple constructer for: " << str << ". " << num << " left]\n";
}
String::String(const String &s)
{
    ++num;
    l = s.l;
    str = new char[l + 1];
    strcpy(str, s.str);
    cout << "[Copier-constructer for: " << str << ". " << num << " left]\n";
}
String::~String()
{
    --num;
    cout << "[Destructer for: " << str << ". " << num << " left]\n";
    delete [] str;
}
String & String::operator=(const String &s)
{
    cout << "[operator= was called]\n";
    if (this == &s)
        return *this;
    delete [] str;
    l = s.l;
    str = new char[l + 1];
    strcpy(str, s.str);
    return *this;
}
bool String::operator<(const String &s) const
{
    int lm = l < s.l ? l : s.l;
    for (int i = 0; i < lm; ++i)
    {
        if (str[i] < s.str[i])
            return true;
        else if (str[i] > s.str[i])
            return false;
    }
    if (l > lm)
        return false;
    else
        return true;
}
bool String::operator>(const String &s) const
{
    int lm = l < s.l ? l : s.l;
    for (int i = 0; i < lm; ++i)
    {
        if (str[i] > s.str[i])
            return true;
        if (str[i] < s.str[i])
            return false;
    }
    if (l > lm)
        return true;
    else
        return false;
}
bool String::operator==(const String &s) const
{
    if (l != s.l)
        return false;
    for (int i = 0; i < l; ++i)
        if (str[i] != s.str[i])
            return false;
    return true;
}
ostream & operator<<(ostream& sout, String const& s)
{
    sout << s.str;
    return sout;
}
istream & operator>>(istream& sin, String& s)
{
    char buf[String::inlim]{};
    sin.getline(buf, String::inlim);
    if (sin.fail())
    {
        char message[FF_SIZE]{};
        sprintf(message, "String::String fails (String::inlim=%d)", String::inlim);
        throw std::ios_base::failure(message);
    }
    // insert contents
    for (s.l = 0; buf[s.l] != '\0' && s.l < String::inlim; ++s.l);
    delete [] s.str;
    s.str = new char[s.l + 1];
    strncpy(s.str, buf, s.l);
    s.str[s.l] = '\0';
    return sin;
}
void my_string_practice(void)
{
    cout << "\nMy string practice\n";
    const int S = 7;
    String s[S] = {"Hellos, Kakos!", "Hellos, Bambinos!"};
    s[2] = "Hellos, Gambrinos!";
    for (int i = 0; i < 3; ++i)
        cout << i+1 << ": " << s[i] << '\n';
    cout << "Now enter from " << 4 << " to " << S << " strings [nothing to quit]:\n";
    int amount = 3;
    for (; amount < S; ++amount)
    {
        cout << amount + 1 << ": ";
        Line line = Line(cin);
        if (line.empty())
            break;
        s[amount] = line.str();
    }
    int shortest = 0, first = 0;
    for (int i = 0; i < amount; ++i)
    {
        shortest = s[i].L() < s[shortest].L() ? i : shortest;
        first = s[i] < s[first] ? i : first;
    }
    cout << "The first string alphabeticly:\n " << s[first] << '\n';
    cout << "The shortest string is:\n " << s[shortest] << '\n';
    int a = 5;
    double arr[20] = {};
    String *p1, *p2;
    p1 = new (&a) String("Hellos, Muchachos!"); // new with placing
    p2 = new (arr) String("Hellos, Gringos!");
    cout << "*p1: " << *p1 << '\n';
    cout << "*p2: " << *p2 << '\n';
    p2->~String(); // very important to follow the sequence
    p1->~String();
}

// queue_practice
void Customer_ch12::SetCust(long ar)
{
    arrive = ar;
    processtime = rand() % 3 + 1;
}
Queue::Queue(int mq) : MaxAmount(mq) // initialization for constant and reference data
{
    front = rear = nullptr; // nullptr - zero pointer
    amount = 0;
}
Queue::~Queue(void)
{
    Node *temp;
    while (front != nullptr)
    {
        temp = front;
        front = front->next;
        delete temp;
    }
}
bool Queue::enQueue(const Customer_ch12 &c)
{
    if (isfull())
        return false;
    Node *add = new Node;
    add->item = c;
    add->next = nullptr;
    amount++;
    if (front == nullptr)
        front = add;
    else
        rear->next = add;
    rear = add;
    return true;
}
bool Queue::deQueue(Customer_ch12 &c)
{
    if (isempty())
        return false;
    amount--;
    c = front->item;
    Node *temp = front;
    front = front->next;
    if (amount == 0)
        rear = nullptr;
    delete temp;
    return true;
}
void queue_practice()
{
    cout << "\nQueue practice\n";
    srand(int(time(0)));
    int MaxSize, hours;
    double cust_h;
    long MaxTime = 0, fails = 0, customers = 0, LineWait = 0, LenLine = 0, served = 0;
    short WaitTime = 0;
    cout << "Enter maximum size of queue: ";
    MaxSize = input_int();
    cout << "Enter the number of simulation hours: ";
    hours = input_int();
    MaxTime = hours * 60;
    cout << "Enter the average number of customers per hour (2.3): ";
    cust_h = input_double();
    cust_h = 60 / cust_h;
    Queue line(MaxSize);
    Customer_ch12 cust;
    for (long t = 0; t <= MaxTime; ++t)
    {
        if (NewCust(cust_h))
        {
            if (line.isfull())
                fails++;
            else
            {
                customers++;
                cust.SetCust(t);
                line.enQueue(cust);
            }
        }
        if (WaitTime <= 0 && !line.isempty())
        {
            line.deQueue(cust);
            WaitTime = cust.ptime();
            LineWait += t - cust.when();
            served++;
        }
        if (WaitTime > 0)
            WaitTime--;
        LenLine += line.amountQ();
    }
    if (customers > 0)
    {
        cout << "fails = " << fails << "\ncustomers = " << customers
        << "\nLineWait = " << double(LineWait) / served
        << "\nLenLine = " << double(LenLine) / MaxTime
        << "\nserved = " << served << '\n';
    }
    else
        cout << "No customers.\n";
    cout << "Buy!\n";
}

// number1
int Cow::num = 0;
Cow::Cow()
{
    num++;
    name[0] = '\0';
    hobby = new char[1];
    hobby[0] = '\0';
    weight = 0.0;
}
Cow::Cow(const char *nm, const char *ho, double wt)
{
    num++;
    strcpy(name, nm);
    int l = int(strlen(ho));
    hobby = new char[l + 1];
    strcpy(hobby, ho);
    weight = wt;
}
Cow::Cow(const Cow &c)
{
    num++;
    strcpy(name, c.name);
    int l = int(strlen(c.hobby));
    hobby = new char[l + 1];
    strcpy(hobby, c.hobby);
    weight = c.weight;
}
Cow::~Cow()
{
    num--;
    cout << "[destructer" << num << "]\n";
    delete [] hobby;
}
Cow & Cow::operator=(const Cow & c)
{
    if (this == &c)
        return *this;
    strcpy(name, c.name);
    delete [] hobby;
    int l = int(strlen(c.hobby));
    hobby = new char[l + 1];
    strcpy(hobby, c.hobby);
    weight = c.weight;
    return *this;
}
void Cow::ShowCow() const
{
    cout << "name: " << name << ", "
    << "hobby: " << hobby << ", "
    << "weight: " << weight << '\n';
}
void number1(void)
{
    cout << "\nExercise 1\n";
    Cow c1("Dusya", "Smiling", 109), c2, c3;
    c2 = c1;
    c3 = Cow("Lapochka", "Go Banana", 103); // after constructer, will call destructer
    c1.ShowCow();
    c2.ShowCow();
    c3.ShowCow();
}

// number2
int StringS::num = 0;
const int StringS::CinSiz = 10000;
StringS::StringS(void)
{
    cout << "[default" << ++num << "]\n";
    l = 1;
    str = new char[1];
    str[0] = '\0';
}
StringS::StringS(const char *s)
{
    cout << "[simple" << ++num << "]\n";
    l = int(strlen(s));
    str = new char[l + 1];
    strcpy(str, s);
}
StringS::StringS(const StringS &s)
{
    cout << "[copier" << ++num << "]\n";
    l = s.l;
    str = new char[l + 1];
    strcpy(str, s.str);
}
StringS::~StringS()
{
    cout << "[destructer" << --num << "]\n";
    delete [] str;
}
StringS & StringS::operator=(const StringS &s)
{
    cout << "[oper=]\n";
    if (this == &s)
        return *this;
    delete [] str;
    l = s.l;
    str = new char[l + 1];
    strcpy(str, s.str);
    return *this;
}
StringS & StringS::operator=(const char *s)
{
    cout << "[oper=]\n";
    delete [] str;
    l = int(strlen(s));
    str = new char[l + 1];
    strcpy(str, s);
    return *this;
}
bool StringS::operator<(const StringS &s) const
{
    int lm = l < s.l ? l : s.l;
    for (int i = 0 ; i < lm; ++i)
    {
        if (str[i] < s.str[i])
            return true;
        if (str[i] > s.str[i])
            return false;
    }
    if (l < s.l)
        return true;
    else
        return false;
}
bool StringS::operator>(const StringS &s) const
{
    int lm = l < s.l ? l : s.l;
    for (int i = 0 ; i < lm; ++i)
    {
        if (str[i] > s.str[i])
            return true;
        if (str[i] < s.str[i])
            return false;
    }
    if (l > s.l)
        return true;
    else
        return false;
    return true;
}
bool StringS::operator==(const StringS &s) const
{
    int lm = l < s.l ? l : s.l;
    for (int i = 0 ; i < lm; ++i)
        if (str[i] != s.str[i])
            return false;
    if (l == s.l)
        return true;
    else
        return false;
}
StringS StringS::operator+(const StringS &s) const
{
    StringS st;
    delete [] st.str;
    st.l = l + s.l;
    st.str = new char[st.l + 1];
    strcpy(st.str, str);
    strcat(st.str, s.str);
    return st;
}
StringS StringS::resiz(int siz)
{
    char *s = new char[l + 1];
    strcpy(s, str);
    delete[] str;
    l = siz;
    str = new char[l + 1];
    strncpy(str, s, l + 1);
    str[l] = '\0';
    delete[] s;
    return *this;
}
StringS StringS::strlow()
{
    for (int i = 0; str[i]; ++i)
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 'a' - 'A';
    return *this;
}
StringS StringS::strup()
{
    for (int i = 0; str[i]; ++i)
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] += 'A' - 'a';
    return *this;
}
ostream & operator<<(ostream& sout, const StringS &s)
{
    sout << s.str;
    return sout;
}
istream & operator>>(istream& sin, StringS &s)
{
    sin.get(s.str, StringS::CinSiz).get();
    return sin;
}
void number2(void)
{
    cout << "\nExercise 2\n";
    const int S = 6;
    StringS s[S]
    {
        "Hellos, Gringos!",
        "Hellos, Bambinos!",
        "Hellos, Muchachos!"
    };
    cout << "Enter some to " << S << " string(s) (nothing to quit):\n";
    int amount = 3;
    for (; amount < S; ++amount)
    {
        cout << amount + 1 << ": ";
        Line line = Line(cin);
        if (line.empty())
            break;
        s[amount] = line.str();
    }
    cout << "Strings:\n";
    for (int i = 0; i < amount; ++i)
        cout << i+1 << ": " << s[i] << '\n';
    int a = 2;
    StringS *p = new (&a) StringS("Bingo-Gringo");
    s[2] = s[0] + " " + *p;
    cout << "s3: " << s[2] << '\n';
    p->~StringS();
    if (s[0] < s[1])
        cout << "s1 < s2.\n";
    else
        cout << "s1 >= s2.\n";
    cout << "s1.strlow() = " << s[0].strlow() << '\n';
    cout << "s1.strup() = " << s[0].strup() << '\n';
    cout << "s1.resiz(5) = " << s[0].resiz(5) << '\n';
}

// number3
Line_ch12::Line_ch12(void)
{
    front = rear = nullptr;
    num = 0;
}
Line_ch12::~Line_ch12(void)
{
    node *temp;
    while (front != nullptr)
    {
        temp = front;
        front = front->next;
        delete temp;
    }
}
bool Line_ch12::addFront(const Mytype & ch)
{
    if (isfull())
        return false;
    ++num;
    node *temp = new node;
    temp->c = ch;
    temp->next = front;
    temp->previous = nullptr;
    if (rear == nullptr)
        rear = temp;
    else
        front->previous = temp;
    front = temp;
    return true;
}
bool Line_ch12::addRear(const Mytype & ch)
{
    if (isfull())
        return false;
    ++num;
    node *temp = new node;
    temp->c = ch;
    temp->next = nullptr;
    temp->previous = rear;
    if (front == nullptr)
        front = temp;
    else
        rear->next = temp;
    rear = temp;
    return true;
}
bool Line_ch12::delFront(const Mytype & ch)
{
    if (front == nullptr)
        return false;
    --num;
    node *temp = front;
    front = front->next;
    delete temp;
    return true;
}
bool Line_ch12::delRear(const Mytype & ch)
{
    if (rear == nullptr)
        return false;
    --num;
    node *temp = rear;
    rear = rear->previous;
    delete temp;
    return true;
}
ostream & operator<<(ostream &os, const Line_ch12 &b)
{
    Line_ch12::node *temp = b.front;
    if (b.isempty())
    {
        os << "Line is empty.";
        return os;
    }
    while (temp->next != nullptr)
    {
        os << temp->c;
        temp = temp->next;
    }
    os << temp->c;
    return os;
}
void number3(void)
{ // http://codeforces.com/problemset/problem/638/B
    cout << "\nExercise 3 (watch the code)\n";
    const int N = 12;
    char const* input_lines[N] =
    {
        "dc", "ab", "bdc", "a", "m", "qp", "xm", "ma", "wy", "nkw", "o", "qpo"
    };
    cout << "n: " << N << endl;
    cout << "input lines:\n";
    for (size_t i = 0; i < N; ++i)
        cout << " '" << input_lines[i] << "'";
    cout << endl;
    const int S = 100, A = 26;
    char a[S][A + 1] {};
    for (int i = 0; i < N; ++i)
        strcpy(a[i], input_lines[i]);
    int letters = 0;
    bool al[A + 1] {};
    for (int i = 0; i < N; ++i)
        for (int j = 0; a[i][j] != '\0'; ++j)
            if (!al[a[i][j] - 'a'])
            {
                al[a[i][j] - 'a'] = true;
                ++letters;
            }
    Line_ch12 l[S];
    int li = 0;
    l[0].addFront(a[0][0]);
    letters--;
    al[a[0][0] - 'a'] = false;
    bool f = true, r = true;
    while (letters != 0)
    {
        // front
        f = true;
        for (int i = 0; i < N && f; ++i)
        {
            for (int j = 0; a[i][j] != '\0'; ++j)
            {
                if (a[i][j] == l[li].Front() && j > 0)
                {
                    l[li].addFront(a[i][j-1]);
                    al[a[i][j-1] - 'a'] = false;
                    --letters;
                    f = false;
                    break;
                }
            }
        }
        // rear
        r = true;
        for (int i = 0; i < N && r; ++i)
        {
            for (int j = 0; a[i][j] != '\0'; ++j)
            {
                if (a[i][j] == l[li].Rear() && a[i][j+1] != '\0')
                {
                    l[li].addRear(a[i][j+1]);
                    al[a[i][j+1] - 'a'] = false;
                    --letters;
                    r = false;
                    break;
                }
            }
        }
        if (f && r)
        {
            ++li;
            for (int i = 0; i < A; ++i)
                if (al[i])
                {
                    --letters;
                    al[i] = false;
                    l[li].addFront(char(i + 'a'));
                    break;
                }
        }
    }
    for (int i = 0; i <= li; ++i)
        cout << l[i];
    cout << '\n';
}

// number4
Stack_ch12::Stack_ch12(int n)
{
    if (n <= M && n > 0)
        num = n;
    else
        num = M;
    st = new type4[num];
    top = 0;
}
Stack_ch12::Stack_ch12(const Stack_ch12 &s)
{
    num = s.num;
    st = new type4[num];
    top = s.top;
    for (int i = 0; i < s.top; ++i)
        st[i] = s.st[i];
}
Stack_ch12::~Stack_ch12(void)
{
    delete [] st;
}
bool Stack_ch12::add(const type4 &t)
{
    if (top >= num)
        return false;
    st[top++] = t;
    return true;
}
bool Stack_ch12::take(type4 &t)
{
    if (top < 1)
        return false;
    t = st[--top];
    return true;
}
Stack_ch12 & Stack_ch12::operator=(const Stack_ch12 &s)
{
    if (this == &s)
        return *this;
    num = s.num;
    delete [] st;
    st = new type4[num];
    top = s.top;
    for (int i = 0; i < s.top; ++i)
        st[i] = s.st[i];
    return *this;
}
void Stack_ch12::Show(void) const
{
    if (top < 1)
        cout << "Stack_ch12 is emppty.";
    for (int i = 0; i < top; ++i)
        cout << st[i] << ' ';
    cout << '\n';
}
void number4(void)
{
    cout << "\nExercise 4\n";
    const int S = 4;
    Stack_ch12 s[S] =
    {
        Stack_ch12(5),
        Stack_ch12(20)
    };
    srand(int(time(0)));
    for (int i = 0; i < S; ++i)
        while (!s[i].isfull())
            s[i].add(type4(rand() % 99 + 1));
    for (int i = 0; i < S; ++i)
    {
        cout << "Stack #" << i+1 << ":\n";
        s[i].Show();
    }
    type4 t;
    if (s[S-1].take(t))
    {
        cout << t << " was taken from Stack#" << S << ":\n";
        s[S-1].Show();
    }
    cout << "Stack #2 = Stack #1. Stack #2:\n";
    (s[1] = s[0]).Show();
    cout << "Buy!\n";
}

// number6
void number6(void)
{
    cout << "\nExercise 6\n";
    int M = 5;
    cout << "Maximum size of queues: " << M << '\n';
    Queue q1(M), q2(M);
    long T = 100, served = 0, fails = 0, customers = 0;
    double WaitT = 0.0, len = 0.0;
    short w1 = 0, w2 = 0;
    cout << "Hours: " << T << '\n';
    T *= 60;
    double cust_h = 60;
    cout << "Customers per hour: " << cust_h << '\n';
    cust_h = 60 / cust_h;
    Customer_ch12 cst;
    srand(int(time(0)));
    for (long m = 0; m < T; ++m)
    {
        if (NewCust(cust_h))
        {
            cst.SetCust(m);
            ++customers;
            if (!q1.isfull() && !q2.isfull())
            {
                if (q1.amountQ() < q2.amountQ())
                    q1.enQueue(cst);
                else
                    q2.enQueue(cst);
            }
            else if (!q1.isfull())
                q1.enQueue(cst);
            else if (!q2.isfull())
                q2.enQueue(cst);
            else
            {
                --customers;
                fails++;
            }
        }
        if (w1 <= 0 && !q1.isempty())
        {
            q1.deQueue(cst);
            WaitT += m - cst.when();
            w1 = cst.ptime();
            ++served;
        }
        if (w2 <= 0 && !q2.isempty())
        {
            q2.deQueue(cst);
            WaitT += m - cst.when();
            w2 = cst.ptime();
            ++served;
        }
        --w1;
        --w2;
        len += q1.amountQ() + q2.amountQ();
    }
    WaitT /= customers;
    len /= customers;
    if (customers != 0)
    {
        cout << "In 2 queues:\nAverage waiting time: " << WaitT
        << "\nAverage length: " << len
        << "\nCustomers: " << customers
        << "\nFails: " << fails
        << "\nServed: " << served;
    }
    else
        cout << "Really?! No customers.";
    cout << "\nBuy!\n";
}
