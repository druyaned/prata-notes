#include "Tests.hpp"
#include "Utils.hpp"
#include <regex>

typedef unsigned long long ull;
using namespace std;

//-PROTOTYPES---------------------------------------------------------------------------------------

void test_parse_double();
void test_parse_int();
void test_parse_size();

//-MAIN---------------------------------------------------------------------------------------------

int run_tests()
{
    test_parse_double();
    test_parse_int();
    test_parse_size();
    return EXIT_SUCCESS;
}

//-TEST-PARSERS-------------------------------------------------------------------------------------

void test_parse_double()
{
    cout << "\nTest 'parse_double'\n";
    const char pattern[] = "[-+]?(0|([1-9][0-9]*))\\.[0-9]+(e[-+][1-9][0-9]*)?";
    cout << "Pattern: " << pattern << endl;
    cout << "DBL_NON_EXP_DIG: " << DBL_NON_EXP_DIG << endl;
    cout << "DBL_EXP_DIG:     " << DBL_EXP_DIG << endl;
    regex re(pattern);
    const char NUMS[][FF_SIZE] =
    {
        // e.g. -12.034e+56
        "0.0", "-1.0", "+0.2", "30.0", "-0.04", "+50.06",
        "23.04e+5", "-23.04e-5", "+23.04e+5", "-23.04e-5",
        "0.00e+1", "-200.030e-20", "+0.2e+34", "30.0e-56",
        "-9999999999999.9e-99", "+9999999999999.9e+99",
        "----------------",
        "", "--0.0", "++0.0", "-+0.0", "+-0.0",
        ".1", "-.02", "+.003",
        "a.0", "-a0.1", "+a03.0",
        "00.0", "-01.0", "+020.0",
        "1a.0", "-2a3.0", "+45a0.0",
        "0", "-12", "+345678",
        "0.", "-12.", "+345678.",
        "0.a", "12.a01", "345678.a234",
        "0.1e--", "0.1e++", "0.1e-+", "0.1e+-",
        "0.1e", "0.1e-", "0.1e+",
        "0.1ea", "0.1e-a", "0.1e+a",
        "0.1e0", "0.1e-01", "0.1e+02",
        "0.1e1a", "0.1e-2a", "0.1e+3a",
        "1234567890123.45e123", "-1234567890123.45e+123", "+1234567890123.45e-123"
    };
    const int N = sizeof(NUMS) / sizeof(NUMS[0]);
    for (int i = 0; i < N; ++i)
    {
        char num[FF_SIZE] = "'";
        strcat(num, NUMS[i]);
        strcat(num, "'");
        const char *regex_res = regex_match(NUMS[i], re) ? "true" : "false";
        double val;
        const char *parse_res = parse_double(NUMS[i], val) ? "true" : "false";
        char fmt[FF_SIZE] = "num: %";
        char width[FF_SIZE];
        sprintf(width, "%zu", DBL_NON_EXP_DIG + DBL_EXP_DIG + 6); // [-+] [.] [e] [-+] [']x2
        strcat(fmt, width);
        if (strcmp(parse_res, "true") == 0)
        {
            strcat(fmt, "s; val: %");
            char prec[FF_SIZE];
            sprintf(prec, ".%u", 15); // precision = 15
            strcat(fmt, prec);
            strcat(fmt, "e; [regex='%s' parse='%s']\n");
            printf(fmt, num, val, regex_res, parse_res);
        }
        else
        {
            strcat(fmt, "s; [regex='%s' parse='%s']\n");
            printf(fmt, num, regex_res, parse_res);
        }
    }
}

void test_parse_int()
{
    cout << "\nTest 'parse_int'\n";
    const char pattern[] = "[-+]?(0|([1-9][0-9]*))";
    cout << "Pattern: " << pattern << endl;
    cout << "INT_MAX_DIG: " << INT_MAX_DIG << endl;
    regex re(pattern);
    const char NUMS[][FF_SIZE] =
    {
        "0", "-0", "+0", "-1", "+20", "12345",
        "-123456789", "999999999", "-999999999", "+999999999",
        "----------------",
        "", "--0", "++0", "-+0", "+-0",
        "-", "+",
        "a", "-a0", "+a03",
        "00", "-01", "+020",
        "1a", "-2a3", "+45a0",
        "0.", "-12.", "+345678.",
        "0.a", "0--", "0++", "0-+", "0+-",
        "0-", "0+",
        "0-a", "0+a",
        "0-01", "0+02",
        "0-2a", "0+3a",
        "1000000000", "-1000000000", "+1000000000",
        "1234567890", "-1234567890", "+1234567890"
    };
    const int N = sizeof(NUMS) / sizeof(NUMS[0]);
    for (int i = 0; i < N; ++i)
    {
        char num[FF_SIZE] = "'";
        strcat(num, NUMS[i]);
        strcat(num, "'");
        const char *regex_res = regex_match(NUMS[i], re) ? "true" : "false";
        int val = 0;
        const char *parse_res = parse_int(NUMS[i], val) ? "true" : "false";
        char fmt[FF_SIZE] = "num: %";
        char width[FF_SIZE];
        sprintf(width, "%zu", INT_MAX_DIG + 3); // [-+] [']x2
        strcat(fmt, width);
        if (strcmp(parse_res, "true") == 0)
        {
            strcat(fmt, "s; val: %d; [regex='%s' parse='%s']\n");
            printf(fmt, num, val, regex_res, parse_res);
        }
        else
        {
            strcat(fmt, "s; [regex='%s' parse='%s']\n");
            printf(fmt, num, regex_res, parse_res);
        }
    }
}

void test_parse_size()
{
    cout << "\nTest 'parse_size'\n";
    const char pattern[] = "[+]?(0|([1-9][0-9]*))";
    cout << "Pattern: " << pattern << endl;
    cout << "SIZE_MAX_DIG: " << SIZE_MAX_DIG << endl;
    regex re(pattern);
    const char NUMS[][FF_SIZE] =
    {
        "0", "+0", "1", "+20", "12345",
        "1234567890123456789", "9999999999999999999", "+9999999999999999999",
        "----------------",
        "", "--0", "++0", "-+0", "+-0", "-", "+",
        "a", "-a0", "+a03",
        "00", "-01", "+020",
        "1a", "-2a3", "+45a0",
        "0.", "-12.", "+345678.",
        "0.a", "0--", "0++", "0-+", "0+-",
        "0-", "0+",
        "0-a", "0+a",
        "0-01", "0+02",
        "0-2a", "0+3a",
        "10000000000000000000", "-10000000000000000000", "+10000000000000000000",
        "12345678901234567890", "-12345678901234567890", "+12345678901234567890"
    };
    const int N = sizeof(NUMS) / sizeof(NUMS[0]);
    for (int i = 0; i < N; ++i)
    {
        char num[FF_SIZE] = "'";
        strcat(num, NUMS[i]);
        strcat(num, "'");
        const char *regex_res = regex_match(NUMS[i], re) ? "true" : "false";
        size_t val = 0;
        const char *parse_res = parse_size(NUMS[i], val) ? "true" : "false";
        char fmt[FF_SIZE] = "num: %";
        char width[FF_SIZE];
        sprintf(width, "%zu", SIZE_MAX_DIG + 3); // [-+] [']x2
        strcat(fmt, width);
        if (strcmp(parse_res, "true") == 0)
        {
            strcat(fmt, "s; val: %zu; [regex='%s' parse='%s']\n");
            printf(fmt, num, val, regex_res, parse_res);
        }
        else
        {
            strcat(fmt, "s; [regex='%s' parse='%s']\n");
            printf(fmt, num, regex_res, parse_res);
        }
    }
}
