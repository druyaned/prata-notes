#include "ch16_string_class_n_standard_template_library.hpp"

using namespace std;

static void intellectual_pointers();
static void practice_with_vector();
static void permutations();
static void practice_with_stl();
static void number1();
static void number2();
static void number4();
static void number5();
static void number7();
static void number8();
static void number9();
static void number10();

int ch16_string_class_n_standard_template_library()
{
    print_run_chapter_message(16);
    intellectual_pointers();
    practice_with_vector();
    permutations();
    practice_with_stl();
    number1();
    number2();
    number4();
    number5();
    number7();
    number8();
    number9();
    number10();
    return EXIT_SUCCESS;
}

// intellectual_pointers
void intellectual_pointers()
{
    cout << "\nIntellectual pointers\n";
    double ver = 3.6;
    Ptr<double> p1;
    *p1 = 5.2 + ver;
    cout << "*p1 = " << *p1 << '\n';
    const int L = 40;
    struct st
    {
        char name[L];
        int res;
    };
    Ptr<st> p2;
    (*p2).res = 2;
    strcpy(p2->name, "Gringo");
    cout << "*p2:\n";
    cout << " Name: " << (*p2).name << "\n Result: " << p2->res << '\n';
    // reference counting in shared_ptr
    shared_ptr<int> p3(new int(2)), p4;
    p4 = p3;
    cout << "shared_ptr:\n";
    cout << " *p3 = " << *p3  << ", *p4 = " << *p4 << '\n';
    *p3 += 11;
    cout << "After changes (*p3 += 11):\n";
    cout << " *p3 = " << *p3  << ", *p4 = " << *p4 << '\n';
    cout << "unique_ptr (not always) doesn't allowed operator=.\n";
    // uniqu_ptr 'owns' memory
}

// practice_with_vector
bool operator<(Person_ch16 const& p1, Person_ch16 const& p2)
{
    if (p1.result < p2.result)
        return true;
    return false;
}
void show_pers(Person_ch16& p)
{
    cout << " Name: " << p.name << ", result: " << p.result << '\n';
}
string& ToLower(string& s)
{
    for (string::iterator it = s.begin(); it != s.end(); ++it)
        if (*it >= 'A' && *it <= 'Z')
            *it = *it - 'A' + 'a';
    return s;
}
ostream& operator<<(ostream& os, Person_ch16 const& p)
{
    cout << ' ' << p.name << ", " << p.result;
    return os;
}
void practice_with_vector()
{
    cout << "\nPractice with vector\n";
    const int S = 5;
    vector<double> zp;
    vector<double>::iterator pd = zp.begin();
    double arr[S] = {19, 54, 3, 48, 13};
    // adding elements
    zp.insert(pd, arr, arr + S);
    cout << "vector<double> zp:\n";
    for (double x : zp)
        cout << x << ' ';
    cout << '\n';
    // adding element to the end of vector
    zp.push_back(4.3);
    sort(zp.begin(), zp.end());
    // erasing elements
    zp.erase(zp.begin() + 2, zp.end() - 1);
    cout << "After push_backing, sorting and erasing:\n";
    copy(zp.begin(), zp.end(), ostream_iterator<double, char>(cout, " "));
    cout << '\n';
    const char Names[S][40] =
    {
        "Gringo Bingo", "Lotos Muchachos", "Pablo Piskoni",
        "Bartoly Persik", "Jorik Ratatu"
    };
    vector<Person_ch16> per(S);
    for (int i = 0; i < S; ++i)
    {
        per[i].name = Names[i];
        per[i].result = int(arr[i]);
    }
    sort(per.begin(), per.end());
    cout << "Persons, sorted by result:\n";
    // show_pers is a functor hear
    for_each(per.begin(), per.end(), show_pers);
    cout << "Again with ostream_iterator:\n";
    copy(per.begin(), per.end(), ostream_iterator<Person_ch16, char>(cout, "\n"));
}

// permutations
void permutations()
{
    cout << "\nPermutations\n";
    string word = "Vilo";
    cout << "Word: " << word << endl;
    cout << "Permutations (in alphabet order):\n";
    sort(word.begin(), word.end());
    cout << "Permutations (in alphabet order):\n1: " << word << '\n';
    for (int i = 2; i < 1000 && next_permutation(word.begin(), word.end()); ++i)
        cout << i << ": " << word << '\n';
    cout << "End.\n";
}

// practice_with_stl
void practice_with_stl()
{
    cout << "\nPractice with stl\n";
    typedef pair<const string, int> Pair;
    typedef map<string, int> Map;
    typedef set<string> Set;
    Map m;
    const int S = 8;
    const char Names[S][40] =
    {
        "Gory Holmik", "Gringo Bingo", "Lotos Muchachos",
        "Pablo Piskoni", "Gringo Bingo", "Kamony Persik",
        "Gory Holmik", "Gringo Bingo"
    };
    vector<string> name(S);
    Set s;
    for (int i = 0; i < S; ++i)
        name[i] = Names[i];
    // insert_iterator allow to use functions, changing object's memory
    transform(name.begin(), name.end(), insert_iterator<Set>(s, s.begin()), ToLower);
    for (Set::iterator it = s.begin(); it != s.end(); ++it)
        m.insert( Pair(*it, (int) count(name.begin(), name.end(), *it)) );
    cout << "Persons and their counts in alphabetic order:\n";
    for (Map::iterator it = m.begin(); it != m.end(); ++it)
        cout << ' ' << (*it).first << ", " << (*it).second << '\n';
}

// number1
bool is_palindrome(string const& st)
{
    string s;
    long l0 = st.length();
    for (int i = 0; i < l0; ++i)
        if (isalpha(st[i]))
            s += tolower(st[i]);
    long l = s.length(), lh = l / 2;
    --l;
    for (long i = 0; i < lh; ++i)
        if (s[i] != s[l - i])
            return false;
    return true;
}
bool is_palindrome(char const* st)
{
    string s;
    long l0 = strlen(st);
    for (int i = 0; i < l0; ++i)
        if (isalpha(st[i]))
            s += tolower(st[i]);
    long l = s.length(), lh = l / 2;
    --l;
    for (long i = 0; i < lh; ++i)
        if (s[i] != s[l - i])
            return false;
    return true;
}
vector<int> Lotto(int max_number, int amount)
{
    set<int> st;
    set<int>::iterator it;
    for (int i = max_number; i > 0; --i)
        st.insert(i);
    vector<int> a;
    for (int i = 0, ind; i < amount; ++i)
    {
        ind = rand() % (max_number - i);
        it = st.lower_bound(ind);
        a.push_back(*it);
        st.erase(it);
    }
    sort(a.begin(), a.end());
    return a;
}
void number1()
{
    cout << "\nExercise 1\n";
    cout << "Enter a word (q to quite): ";
    Line line = Line(cin);
    while (line != "q")
    {
        if (is_palindrome(line.str()))
            cout << " \'" << line << "\' is a polindrome.\n";
        else
            cout << " \'" << line << "\' is not a polindrome.\n";
        cout << "Enter another word (q to quite): ";
        input_line(line);
    }
}

// number2
void number2()
{
    cout << "\nExercise 2\n";
    cout << "Enter a some words (q to quite): ";
    Line line = Line(cin);
    while (line != "q")
    {
        if (is_palindrome(line.str()))
            cout << " \'" << line << "\' is a polindrome.\n";
        else
            cout << " \'" << line << "\' is not a polindrome.\n";
        cout << "Enter another some words (q to quite): ";
        input_line(line);
    }
}

// number4
void number4()
{
    cout << "\nExercise 4\n";
    const int S = 8;
    long a[S] = {6, 2, 5, 4, 2, 6, 12, 2};
    cout << "Array:\n";
    for (int i = 0; i < S; ++i)
        cout << ' ' << a[i];
    cout << '\n';
    int new_S = reduce(a, S);
    cout << "Array after reduce():\n";
    for (int i = 0; i < new_S; ++i)
        cout << ' ' << a[i];
    cout << '\n';
}

// number5
void number5()
{
    cout << "\nExercise 5\n";
    const int S = 8;
    long a[S] = {6, 2, 5, 4, 2, 6, 12, 2};
    cout << "Array:\n";
    for (int i = 0; i < S; ++i)
        cout << ' ' << a[i];
    cout << '\n';
    int new_S = reduce(a, S);
    cout << "Array after reduce():\n";
    for (int i = 0; i < new_S; ++i)
        cout << ' ' << a[i];
    cout << '\n';
    
    string s[8] =
    {
        "Gringo Bingo", "Lotos Muchachos", "Gory Holmik",
        "Pablo Piskoni", "Gringo Bingo", "Kamony Persik",
        "Gory Holmik", "Gringo Bingo"
    };
    cout << "\nArray of sentences:\n";
    for (int i = 0; i < 8; ++i)
        cout << i+1 << ": " << s[i] << '\n';
    cout << "\nArray of sentences after reduce():\n";
    new_S = reduce(s, 8);
    for (int i = 0; i < new_S; ++i)
        cout << i+1 << ": " << s[i] << '\n';
}

// number 7
void number7()
{
    cout << "\nExercise 7\n";
    seed_rand();
    vector<int> a(Lotto(50, 4));
    cout << "Ticket with numbers:";
    for (int i = 0; i < 4; ++i)
        cout << ' ' << a[i];
    cout << ", wins!\n";
}

// number8
void show_elem(int a)
{
    cout << ' ' << a;
}
void number8()
{
    cout << "\nExercise 8\n";
    set<string> name1, name2, name3;
    set<string>::iterator it;
    const int S1 = 5, S2 = 6;
    const string names1[S1] =
    {
        "Gringo Bingo", "Lotos Muchachos", "Pablo Piskoni",
        "Bartoly Persik", "Jorik Ratatu"
    };
    const string names2[S2] =
    {
        "Gory Holmik", "Gringo Bingo", "Lotos Muchachos",
        "Pablo Piskoni", "Kamony Persik", "Evanescence"
    };
    for (int i = 0; i < S1; ++i)
        name1.insert(names1[i]);
    for (int i = 0; i < S2; ++i)
        name2.insert(names2[i]);
    cout << "Mat's guests:\n";
    it = name1.begin();
    for (int i = 1; it != name1.end(); ++it, ++i)
    {
        cout << ' ' << i << ": " << *it << '\n';
        name3.insert(*it);
    }
    cout << "Pat's guests:\n";
    it = name2.begin();
    for (int i = 1; it != name2.end(); ++it, ++i)
    {
        cout << ' ' << i << ": " << *it << '\n';
        name3.insert(*it);
    }
    cout << "Common guests:\n";
    it = name3.begin();
    for (int i = 1; it != name3.end(); ++it, ++i)
        cout << ' ' << i << ": " << *it << '\n';
}

// number9
void number9()
{
    cout << "\nExercise 9\n";
    const int S = 2000000;
    vector<int> v0;
    seed_rand();
    for (int i = 0; i < S; ++i)
        v0.push_back((int) rand() % S);
    vector<int> v1(v0);
    list<int> li(v0.begin(), v0.end());
    list<int>::iterator it;
    clock_t fst, lst;
    //
    fst = clock();
    li.sort();
    lst = clock();
    cout << "sort li:\n " << (long double) (lst - fst) / CLOCKS_PER_SEC << " second(s)\n";
    //
    fst = clock();
    sort(v1.begin(), v1.end());
    lst = clock();
    cout << "sort v1:\n " << (long double) (lst - fst) / CLOCKS_PER_SEC << " second(s)\n";
    //
    fst = clock();
    copy(v0.begin(), v0.end(), li.begin());
    lst = clock();
    cout << "copy v0 to li:\n " << (long double) (lst - fst) / CLOCKS_PER_SEC << " second(s)\n";
    //  0.089124 second(s) - copy()
    fst = clock();
    copy(li.begin(), li.end(), v1.begin());
    sort(v1.begin(), v1.end());
    copy(v1.begin(), v1.end(), li.begin());
    lst = clock();
    cout << "copy li to v1, sort v1, copy v1 to li:\n " << (long double) (lst - fst) / CLOCKS_PER_SEC << " second(s)\n";
}

// number10
bool by_price(Book const& b1, Book const& b2)
{
    if (b1.price < b2.price)
        return true;
    else if (b1.price == b2.price && b1.rating < b2.rating)
        return true;
    return false;
}
bool by_name(Book const& b1, Book const& b2)
{
    if (b1.name < b2.name)
        return true;
    return false;
}
bool by_rating(Book const& b1, Book const& b2)
{
    if (b1.rating > b2.rating)
        return true;
    else if (b1.rating == b2.rating && b1.price < b2.price)
        return true;
    return false;
}
void show_book(Book& b)
{
    cout << ' ' << b.name << ", " << b.price << "$, " << b.rating << "%\n";
}
void number10()
{
    cout << "\nExercise 10\n";
    const int S = 5;
    Book b[S];
    const char Name[S][31] =
    {
        "Lotos Muchachos", "Pablo Piskoni",
        "Gory Holmik", "Kamony Persik", "Gringo Bingo"
    };
    const int Rating[S] = {93, 71, 89, 71, 91};
    const double Price[S] = {112.45, 103.99, 183.57, 99.99, 125.0};
    for (int i = 0; i < S; ++i)
    {
        b[i].name = Name[i];
        b[i].rating = Rating[i];
        b[i].price = Price[i];
    }
    cout << "Books:\n";
    for_each(b, b + S, show_book);
    cout << "Sort by a) price, b) rating, c) name, q) quit; choice: ";
    Line line = Line(cin);
    while (line != "q")
    {
        if (line == "a")
        {
            sort(b, b + S, by_price);
            cout << "Books sorted by price:\n";
            for_each(b, b + S, show_book);
        }
        else if (line == "b")
        {
            sort(b, b + S, by_rating);
            cout << "Books sorted by rating:\n";
            for_each(b, b + S, show_book);
        }
        else if (line == "c")
        {
            sort(b, b + S, by_name);
            cout << "Books sorted by name:\n";
            for_each(b, b + S, show_book);
        }
        else
            cout << "Wrong enter.\n";
        cout << "Sort by a) price, b) rating, c) name, q) quit; choice: ";
        input_line(line);
    }
    cout << "Buy!\n";
}
