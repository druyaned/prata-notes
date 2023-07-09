#include "ch01_getting_started.hpp"
#include "Utils.hpp"
#include <fstream>
#include <iostream> // включили файл iostream => результирующий файл - это мой и iostream
#include <cmath>    // math.h - файл C; cmath - файл C++
#include <cstdlib>  // int rand(void) - прототип функции rand
#include <ctime>    // std::time(nullptr)
#include <climits>  // INT_MAX

int ch01_getting_started(void)  /* вместо chapter_01 представлю main.
                                 void в скобках => функция main не принимает аргументов.
                                 Пустые скобки main() означают для компилятора main(void)
                                 void main() - не стандартная запись => может дать сбой */
{
    print_run_chapter_message(1);
    int a = 0, b = 0;   // если не занулять, то забивается что-то
    using std::cout;    // using - директива/оператор/объявление, std - пространство имен
    cout << "Enter a number for variable 'a': ";
    std::cin >> a;      // cout - оператор, объект (инструкция компу)
    if (!std::cin)
    {
        std::cout << "Bad input.\n";    // std::cout - так называется переменная cout
        return EXIT_SUCCESS;
    }
    b = a;
    cout << "Look at the wonders of arithmetic!";
    cout << '\n';       // '\n' по_смыслу== endl. endl - приоретет
    using namespace std;
    for (int i = 1; i <= 3; i++)
    {
        a = b;
        a = a + i;      // endl - манипулятор для cout
        cout <<"a + " << i << " = " << a << endl;
    }
    int c = 0, d = 0;
    c = d = 88;         // f = 88 = d - нельзя так. "=" работает справо налево
    printf("Showing a number using the 'printf' function: " /* конкатенация */ "%d\n", 25);
    double dbl_val = 6.25, res = sqrt(dbl_val);
    cout << "Square root of " << dbl_val << " = " << res << endl;
    seed_rand();
    int random_number, n = 8;
    cout << "Let's look at random numbers.\n";
    for (int i = 0; i < n; ++i)
    {
        random_number = rand();
        cout << "#" << i << ": " << random_number << endl;
    }
    return(0);  /* для функции main() можно её возврат опустить,
                 т. е. не писать return 0. Компилятору все равно. Но стандарт
                 ISO есть стандарт. Тем более для любых других функций
                 такого делать нельзя */
}
