#include "Utils.hpp"
#include <cfloat>
#include <cmath>

extern bool DEBUG_MODE; // TODO: debug

using namespace std;

//-Line---------------------------------------------------------------------------------------------

// constructors
Line::Line()
{
    m_len = 0;
    m_str = new char[m_len + 1]{};
}
Line::Line(char const* str)
{
    for (m_len = 0; str[m_len] != '\0' && m_len < LEN_MAX; ++m_len);
    m_str = new char[m_len + 1]{};
    strncpy(m_str, str, m_len);
    m_str[m_len] = '\0';
}
Line::Line(Line const& line)
{
    m_len = line.m_len;
    m_str = new char[m_len + 1]{};
    strncpy(m_str, line.m_str, m_len);
    m_str[m_len] = '\0';
}
Line::Line(std::istream& sin)
{
    char buf[Line::CNT_MAX]{};
    sin.getline(buf, Line::CNT_MAX);
    if (sin.fail())
    {
        char message[FF_SIZE]{};
        sprintf(message, "Line::Line fails (Line::CNT_MAX=%zu)", Line::CNT_MAX);
        throw std::ios_base::failure(message);
    }
    // insert contents
    for (m_len = 0; buf[m_len] != '\0' && m_len < LEN_MAX; ++m_len);
    m_str = new char[m_len + 1]{};
    strncpy(m_str, buf, m_len);
    m_str[m_len] = '\0';
}
// setters
Line& Line::operator=(char const* str)
{
    for (m_len = 0; str[m_len] != '\0' && m_len < LEN_MAX; ++m_len);
    delete[] m_str;
    m_str = new char[m_len + 1]{};
    strncpy(m_str, str, m_len);
    m_str[m_len] = '\0';
    return *this;
}
Line& Line::operator=(Line const& line)
{
    m_len = line.m_len;
    delete[] m_str;
    m_str = new char[m_len + 1]{};
    strncpy(m_str, line.m_str, m_len);
    m_str[m_len] = '\0';
    return *this;
}
// functions
Line Line::operator+(char const* str) const
{
    size_t str_len = 0;
    for (; str[str_len] != '\0' && str_len < LEN_MAX; ++str_len);
    if (LEN_MAX < str_len + m_len) // works good only if ( 4 <= sizeof(size_t) )
    {
        char message[FF_SIZE]{};
        sprintf(message, "Line::operator+ fails (Line::CNT_MAX=%zu)", Line::CNT_MAX);
        throw std::ios_base::failure(message);
    }
    char buf[CNT_MAX]{};
    size_t const buf_size = str_len + m_len + 1;
    strncpy(buf, m_str, buf_size);
    strncat(buf, str, str_len + 1);
    return Line(buf);
}
Line Line::operator+(Line const& line) const
{
    if (LEN_MAX < line.m_len + m_len)
    {
        char message[FF_SIZE]{};
        sprintf(message, "Line::operator+ fails (Line::CNT_MAX=%zu)", Line::CNT_MAX);
        throw std::ios_base::failure(message);
    }
    char buf[CNT_MAX]{};
    size_t const buf_size = line.m_len + m_len + 1;
    strncpy(buf, m_str, buf_size);
    strncat(buf, line.m_str, line.m_len + 1);
    return Line(buf);
}
static char const* make_double_format()
{
    static char format[FF_SIZE]{};
    sprintf(format, "%%.%zue", DBL_NON_EXP_DIG);
    return format;
}
static char const* double_format = make_double_format();
Line Line::operator+(double const& num) const
{
    char num_str[FF_SIZE]{};
    sprintf(num_str, double_format, num);
    size_t num_len = strlen(num_str);
    if (LEN_MAX < num_len + m_len)
    {
        char message[FF_SIZE]{};
        sprintf(message, "Line::operator+ fails (Line::CNT_MAX=%zu)", Line::CNT_MAX);
        throw std::ios_base::failure(message);
    }
    char buf[CNT_MAX]{};
    strncpy(buf, m_str, m_len + 1);
    strncat(buf, num_str, num_len + 1);
    return Line(buf);
}
Line Line::operator+(int const& num) const
{
    char num_str[FF_SIZE]{};
    sprintf(num_str, "%d", num);
    size_t num_len = strlen(num_str);
    if (LEN_MAX < num_len + m_len)
    {
        char message[FF_SIZE]{};
        sprintf(message, "Line::operator+ fails (Line::CNT_MAX=%zu)", Line::CNT_MAX);
        throw std::ios_base::failure(message);
    }
    char buf[CNT_MAX]{};
    strncpy(buf, m_str, m_len + 1);
    strncat(buf, num_str, num_len + 1);
    return Line(buf);
}
Line Line::operator+(size_t const& num) const
{
    char num_str[FF_SIZE]{};
    sprintf(num_str, "%zu", num);
    size_t num_len = strlen(num_str);
    if (LEN_MAX < num_len + m_len)
    {
        char message[FF_SIZE]{};
        sprintf(message, "Line::operator+ fails (Line::CNT_MAX=%zu)", Line::CNT_MAX);
        throw std::ios_base::failure(message);
    }
    char buf[CNT_MAX]{};
    strncpy(buf, m_str, m_len + 1);
    strncat(buf, num_str, num_len + 1);
    return Line(buf);
}
// friends
ostream& operator<<(ostream& sout, Line const& line)
{
    sout << line.m_str;
    return sout;
}

//-PARSERS------------------------------------------------------------------------------------------

bool parse_double(Line const& line, double& val)
{
    // regex: "[-+]?(0|([1-9][0-9]*))\\.[0-9]+(e[-+][1-9][0-9]*)?"
    // e.g. -12.034e+56
    // #1 define the length
    size_t const& len = line.len();
    if (len == 0)
        return false;
    if (DEBUG_MODE) // TODO: debug
        printf("[#1 len=%zu]\n", len);
    // #2 integer part [-+]?(0|([1-9][0-9]*))
    size_t start_int = 0; // start index of integer part
    size_t n_int = 0; // number of digits of integer part
    size_t ind = 0; // current line index
    if (line[ind] == '-' || line[ind] == '+') // [-+]?
    {
        if (len == ++ind)
            return false;
    }
    start_int = ind;
    if (line[ind] == '0') // 0
    {
        if (DBL_NON_EXP_DIG < ++n_int)
            return false;
        if (len == ++ind) // 0 skip
            return false;
    }
    else if ('1' <= line[ind] && line[ind] <= '9') // [1-9][0-9]*
    {
        if (DBL_NON_EXP_DIG < ++n_int)
            return false;
        if (len == ++ind) // [1-9] skip
            return false;
        while (line[ind] != '.')
        {
            if ('9' < line[ind] || line[ind] < '0' || DBL_NON_EXP_DIG < ++n_int)
                return false;
            if (len == ++ind) // [0-9] skip
                return false;
        }
    }
    else
        return false;
    if (DEBUG_MODE) // TODO: debug
        printf("[#2 i1=%zu in=%zu]\n", start_int, n_int);
    // #3 fractional part \\.[0-9]+
    size_t start_fct = 0; // start index of fractional part
    size_t n_fct = 0; // number of digits of fractional part
    if (line[ind] != '.')
        return false;
    if (len == ++ind) // skip '.'
        return false;
    start_fct = ind;
    do {
        if ('9' < line[ind] || line[ind] < '0' || DBL_NON_EXP_DIG < ++n_fct + n_int)
            return false;
        if (len == ++ind) // [0-9] skip
            break;
    } while (line[ind] != 'e');
    if (DEBUG_MODE) // TODO: debug
        printf("[#3 f1=%zu fn=%zu]\n", start_fct, n_fct);
    // #4 exponent part (e[-+][1-9][0-9]*)?
    bool has_exp_prt = false; // has exponent part
    size_t start_exp = 0; // start index of exponent part
    size_t n_exp = 0; // number of digits of exponent part
    if (len != ind)
    { // note: order of evaluation is unspecified
        if (line[ind] == 'e')
        {
            has_exp_prt = true;
            if (len == ++ind) // e skip
                return false;
            if (line[ind] != '-' && line[ind] != '+')
                return false;
            if (len == ++ind) // [-+] skip
                return false;
            start_exp = ind;
            if ('9' < line[ind] || line[ind] < '1' || DBL_EXP_DIG < ++n_exp)
                return false;
            while (++ind < len) // [1-9] skip; [0-9] skip
            {
                if ('9' < line[ind] || line[ind] < '0' || DBL_EXP_DIG < ++n_exp)
                    return false;
            }
        }
        else
            return false;
    }
    if (DEBUG_MODE) // TODO: debug
        printf("[#4 e1=%zu en=%zu]\n", start_exp, n_exp);
    // #5 make value
    size_t val_int = 0; // integer part
    size_t val_fct = 0; // fractional part
    for (size_t i = start_int, i_ten = n_int - 1; i < start_int + n_int; ++i, --i_ten)
        val_int += (line[i] - '0') * TENS[i_ten]; // make integer part
    for (size_t i = start_fct, i_ten = n_fct - 1; i < start_fct + n_fct; ++i, --i_ten)
        val_fct += (line[i] - '0') * TENS[i_ten]; // make fractional part
    val = (line[0] == '-') ? // combine integer and fractional parts
        -double(val_int) - double(val_fct) / TENS[n_fct] :
        +double(val_int) + double(val_fct) / TENS[n_fct];
    if (has_exp_prt)
    {
        size_t val_exp = 0; // exponent part
        for (size_t i = start_exp, i_ten = n_exp - 1; i < start_exp + n_exp; ++i, --i_ten)
            val_exp += (line[i] - '0') * TENS[i_ten]; // make exponent part
        val *= (line[start_exp - 1] == '-') ? // combine exponent part
            pow(10.0, -double(val_exp)) :
            pow(10.0, double(val_exp));
    }
    return true;
}

bool parse_int(Line const& line, int& val)
{
    // #1 define the length
    size_t const& len = line.len();
    if (len == 0)
        return false;
    // #2 regex: [-+]?(0|([1-9][0-9]*))
    size_t start = 0; // start index
    size_t n = 0; // number of digits
    size_t ind = 0; // current buffer index
    if (line[ind] == '-' || line[ind] == '+') // [-+]?
    {
        if (len == ++ind)
            return false;
    }
    start = ind;
    if (line[ind] == '0') // 0
    {
        if (INT_MAX_DIG < ++n)
            return false;
        if (len != ++ind) // 0 skip
            return false;
    }
    else if ('1' <= line[ind] && line[ind] <= '9') // [1-9][0-9]*
    {
        if (INT_MAX_DIG < ++n)
            return false;
        while (++ind < len) // [1-9] skip; [0-9] skip
        {
            if ('9' < line[ind] || line[ind] < '0' || INT_MAX_DIG < ++n)
                return false;
        }
    }
    else
        return false;
    // #3 make value
    size_t abs_val = 0;
    for (size_t i = start, i_ten = n - 1; i < start + n; ++i, --i_ten)
        abs_val += (line[i] - '0') * TENS[i_ten];
    val = line[0] == '-' ? -int(abs_val) : int(abs_val);
    return true;
}

bool parse_size(Line const& line, size_t& val)
{
    // #1 define the length
    size_t const& len = line.len();
    if (len == 0)
        return false;
    // #2 regex: [+]?(0|([1-9][0-9]*))
    size_t start = 0; // start index
    size_t n = 0; // number of digits
    size_t ind = 0; // current buffer index
    if (line[ind] == '+') // [+]?
    {
        if (len == ++ind)
            return false;
    }
    start = ind;
    if (line[ind] == '0') // 0
    {
        if (SIZE_MAX_DIG < ++n)
            return false;
        if (len != ++ind) // 0 skip
            return false;
    }
    else if ('1' <= line[ind] && line[ind] <= '9') // [1-9][0-9]*
    {
        if (SIZE_MAX_DIG < ++n)
            return false;
        while (++ind < len) // [1-9] skip; [0-9] skip
        {
            if ('9' < line[ind] || line[ind] < '0' || SIZE_MAX_DIG < ++n)
                return false;
        }
    }
    else
        return false;
    // #3 make value
    val = 0;
    for (size_t i = start, i_ten = n - 1; i < start + n; ++i, --i_ten)
        val += (line[i] - '0') * TENS[i_ten];
    return true;
}

//-INPUT-FUNCTIONS----------------------------------------------------------------------------------

double input_double(std::istream& sin)
{
    Line line = Line(sin);
    double val = 0.0;
    if (!parse_double(line, val))
        throw ios_base::failure("parse_double fails (e.g. -12.034e+56)");
    return val;
}

int input_int(std::istream& sin)
{
    Line line = Line(sin);
    int val = 0;
    if (!parse_int(line, val))
        throw ios_base::failure("parse_int fails (e.g. -12034)");
    return val;
}

size_t input_size(std::istream& sin)
{
    Line line = Line(sin);
    size_t val = 0;
    if (!parse_size(line, val))
        throw ios_base::failure("parse_size fails (e.g. +12034)");
    return val;
}
