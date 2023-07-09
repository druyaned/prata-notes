//  Created by druyaned on 19.06.2023.
//  g++ -std=c++14 *.cpp; ./a.out;
#include "Utils.hpp"
#include "ch01_getting_started.hpp"
#include "ch02_setting_out.hpp"
#include "ch03_dealing_with_data.hpp"
#include "ch04_compound_types.hpp"
#include "ch05_loops_n_relational_expressions.hpp"
#include "ch06_branching_statements_n_logical_operators.hpp"
#include "ch07_functions_cpp_programming_modules.hpp"
#include "ch08_adventures_in_functions.hpp"
#include "ch09_memory_models_n_namespaces.hpp"
#include "ch10_objects_n_classes.hpp"
#include "ch11_working_with_classes.hpp"
#include "ch12_classes_n_dynamic_memory_allocation.hpp"
#include "ch13_class_inheritance.hpp"
#include "ch14_reusing_code.hpp"
#include "ch15_friends_exceptions_n_more.hpp"
#include "ch16_string_class_n_standard_template_library.hpp"
#include "ch17_io_n_files.hpp"
#include "ch18_visiting_with_new_standard.hpp"
#include "Tests.hpp"

bool DEBUG_MODE = false; // TODO: debug

int main(int argc, const char *argv[])
{
    using namespace std;
    if (argc == 2) // argv[0] == "./a.out"
    {
        if (strcmp(argv[1], "test") == 0)
            return run_tests();
        else if (strcmp(argv[1], "debug") == 0) // TODO: debug
        {
            DEBUG_MODE = true;
            return run_tests();
        }
        else
        {
            cerr << "Bad command line argument (must be 'test' or 'debug').\n";
            return EXIT_FAILURE;
        }
    }
    int (*chapters[N_CHAPTERS]) (void) =
    {
        ch01_getting_started,
        ch02_setting_out,
        ch03_dealing_with_data,
        ch04_compound_types,
        ch05_loops_n_relational_expressions,
        ch06_branching_statements_n_logical_operators,
        ch07_functions_cpp_programming_modules,
        ch08_adventures_in_functions,
        ch09_memory_models_n_namespaces,
        ch10_objects_n_classes,
        ch11_working_with_classes,
        ch12_classes_n_dynamic_memory_allocation,
        ch13_class_inheritance,
        ch14_reusing_code,
        ch15_friends_exceptions_n_more,
        ch16_string_class_n_standard_template_library,
        ch17_io_n_files,
        ch18_visiting_with_new_standard
    };
    cout << "Contents:\n";
    for (size_t i = 0, ch_num = 1; ch_num <= N_CHAPTERS; ++ch_num, ++i)
        printf("%2zu: %s\n", ch_num, CHAPTER_NAMES[i]);
    try
    {
        cout << "A chapter to run: ";
        int ch_num = input_int();
        while (N_CHAPTERS < ch_num || ch_num < 1)
        {
            cout << "Choose a number from 1 to " << N_CHAPTERS << ". A chapter to run: ";
            ch_num = input_int();
        }
        return chapters[ch_num - 1]();
    }
    catch (ios_base::failure& fail_exc)
    {
        cerr << fail_exc.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
