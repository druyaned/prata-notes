#ifndef ch16_string_class_n_standard_template_library_hpp
#define ch16_string_class_n_standard_template_library_hpp
#include "Utils.hpp"
#include <string>
#include <cstring>
#include <memory> // shared_ptr<>, uniqu_ptr<>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iterator> // ostream_iterator<int, char> out_iter(cout, " ")

using namespace std;

int ch16_string_class_n_standard_template_library();

// intellectual_pointers (f.e. nessesary with exceptions)
template <class T> class Ptr
{
private:
    T* m_ptr;
    T* operator=(T* ptr) {m_ptr = ptr; return m_ptr;}
public:
    Ptr() : m_ptr(new T) {}
    ~Ptr() {cout << "[destructer]\n"; delete m_ptr;}
    inline T& operator*() {return *m_ptr;}
    T* operator->() {return m_ptr;}
};

// practice_with_vector
struct Person_ch16
{
    Line name;
    int result;
};
bool operator<(Person_ch16 const&, Person_ch16 const&);
ostream& operator<<(ostream&, Person_ch16 const&);
void show_pers(Person_ch16&);
string& ToLower(string&);

// number1
bool is_palindrome(string const&);
bool is_palindrome(char const*);

// number5
template <class T>
int reduce(T ar[], int n)
{
    sort(ar, ar + n);
    return int(unique(ar, ar + n) - ar);
}

// number7
vector<int> Lotto(int max_number, int amount);

// number8
void show_elem(int);

// number10
struct Book
{
    string name;
    int rating;
    double price;
};
bool by_price(Book const&, Book const&);
bool by_name(Book const&, Book const&);
bool by_rating(Book const&, Book const&);
void show_book(Book&);

#endif /* ch16_string_class_n_standard_template_library_hpp */
