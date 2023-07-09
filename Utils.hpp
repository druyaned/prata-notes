#ifndef Utils_hpp
#define Utils_hpp
#include <iostream>
#include <cstdlib> // srand, rand, max, min
#include <ctime> // time
#include <cfloat>

//-CONSTANTS----------------------------------------------------------------------------------------

/** Number of chapters. */
const size_t N_CHAPTERS = 18;

/** Fixed size: 0xffff = 65535; as an example can be used in inputting. */
const size_t F4_SIZE = 0xffff;

/** Fixed size: 0xff = 255; as an example can be used in inputting. */
const size_t FF_SIZE = 0xff;

/** Names of the chapters of the Prata's book. */
static char const* CHAPTER_NAMES[N_CHAPTERS] =
{
    "Getting Started with C++",
    "Setting Out to C++",
    "Dealing with Data",
    "Compound Types",
    "Loops and Relational Expressions",
    "Branching Statements and Logical Operators",
    "Functions: C++’s Programming Modules",
    "Adventures in Functions",
    "Memory Models and Namespaces",
    "Objects and Classes",
    "Working with Classes",
    "Classes and Dynamic Memory Allocation",
    "Class Inheritance",
    "Reusing Code in C++",
    "Friends, Exceptions, and More",
    "The string Class and the Standard Template Library",
    "Input, Output, and Files",
    "Visiting with the New C++ Standard"
};

//-LINE---------------------------------------------------------------------------------------------

/** Provides a simple wrap for the char* type with dynamic memory allocation. */
class Line
{
public:
    static size_t const CNT_MAX = F4_SIZE;
    static size_t const LEN_MAX = CNT_MAX - 1;
private:
    size_t m_len;
    char* m_str;
public:
    // constructors & destructor
    Line();
    Line(char const* str);
    Line(Line const& line);
    Line(std::istream& sin);
    ~Line() {delete[] m_str;}
    // setters
    Line& operator=(char const* str);
    Line& operator=(Line const& line);
    // getters
    char const& operator[](size_t const& ind) const {return m_str[ind];}
    char const* str() const {return m_str;}
    size_t const& len() const {return m_len;}
    // conditional functions
    bool empty() const {return m_len == 0;}
    bool operator==(char const* str) const {return strcmp(m_str, str) == 0;}
    bool operator==(Line const& line) const {return strcmp(m_str, line.m_str) == 0;}
    bool operator!=(char const* str) const {return strcmp(m_str, str);}
    bool operator!=(Line const& line) const {return strcmp(m_str, line.m_str);}
    bool operator<(char const* str) const {return strcmp(m_str, str) < 0;}
    bool operator<(Line const& line) const {return strcmp(m_str, line.m_str) < 0;}
    bool operator<=(char const* str) const {return strcmp(m_str, str) <= 0;}
    bool operator<=(Line const& line) const {return strcmp(m_str, line.m_str) <= 0;}
    // functions
    Line operator+(char const* str) const;
    Line operator+(Line const& line) const;
    Line operator+(double const& num) const;
    Line operator+(int const& num) const;
    Line operator+(size_t const& num) const;
    // friends
    friend std::ostream& operator<<(std::ostream& sout, Line const& line);
    friend std::istream& input_line(Line& line, std::istream& sin = std::cin)
    {
        char buf[Line::CNT_MAX]{};
        sin.getline(buf, Line::CNT_MAX);
        if (sin.fail())
        {
            char message[FF_SIZE]{};
            sprintf(message, "input_line fails (Line::CNT_MAX=%zu)", Line::CNT_MAX);
            throw std::ios_base::failure(message);
        }
        // aliases
        char*& str = line.m_str;
        size_t& len = line.m_len;
        // insert contents
        for (len = 0; buf[len] != '\0' && len < Line::LEN_MAX; ++len);
        delete[] str;
        str = new char[len + 1]{};
        strncpy(str, buf, len);
        str[len] = '\0';
        return sin;
    }
};

//-DIGITS-N-TENS------------------------------------------------------------------------------------

/**
 *  Counts the number of digits of exponent part
 *  of a maximum decimal double value for the parse_double.
 *  The result is less by 1 than the number of digits of the DBL_MAX_10_EXP.
 *  @return the number of digits of exponent part of a maximum decimal double value
 */
static constexpr size_t make_dbl_exp_dig()
{
    size_t length = 0;
    for (size_t val = DBL_MAX_10_EXP; 0 < val; val /= 10, ++length);
    return length - 1; // the result is less than the origin by 1
}

/**
 *  Counts the number of digits of a maximum decimal int value for the parse_int.
 *  The result is less by 1 than the number of digits of the INT_MAX.
 *  @return the number of digits of a maximum decimal int value for the parse_int
 */
static constexpr size_t make_int_max_dig()
{
    size_t length = 0;
    for (int val = INT_MAX; 0 < val; val /= 10, ++length);
    return length - 1; // the result is less than the origin by 1
}

/**
 *  Counts the number of digits of a maximum decimal size_t value for the parse_size.
 *  The result is less by 1 than the number of digits of the SIZE_MAX.
 *  @return the number of digits of a maximum decimal size_t value for the parse_size
 */
static constexpr size_t make_size_max_dig()
{
    size_t length = 0;
    for (size_t val = SIZE_MAX; 0 < val; val /= 10, ++length);
    return length - 1; // the result is less than the origin by 1
}

/**
 *  Fills a simple array of tens: tens[0] = 1, tens[1] = 10, tens[2] = 100, etc.
 *  @return a simple array of tens: tens[0] = 1, tens[1] = 10, tens[2] = 100, etc.
 */
static size_t const* fill_tens(size_t const& SIZE_MAX_DIG)
{
    static size_t tens[FF_SIZE]{};
    for (size_t i = 0, ten = 1; i < SIZE_MAX_DIG; ++i, ten *= 10)
        tens[i] = ten;
    return tens;
}

/**
 *  Number of digits of integer and fractional parts of a
 *  maximum decimal double value for the parsing.
 */
const size_t DBL_NON_EXP_DIG = DBL_DIG - 1;

/**
 *  Number of digits of exponent part of a
 *  maximum decimal double value for the parsing.
 */
const size_t DBL_EXP_DIG = make_dbl_exp_dig();

/** Number of digits of a maximum decimal int value for the parsing. */
const size_t INT_MAX_DIG = make_int_max_dig();

/** Number of digits of a decimal maximum size_t value for the parsing. */
const size_t SIZE_MAX_DIG = make_size_max_dig();

/**
 *  TENS[2] == (10 to the power of 2);
 *  maximum power = (SIZE_MAX_DIG - 1).
 */
static size_t const* TENS = fill_tens(SIZE_MAX_DIG);


//-INLINE-FUNCTIONS---------------------------------------------------------------------------------

/**
 *  Simple executes the code "while (sin && sin.get() != '\n');".
 *  @param  sin the object of the input stream to eat a line there.
 */
inline void eat_line(std::istream& sin = std::cin)
{
    while (sin && sin.get() != '\n');
}

/**
 *  Prints the message into the standard output of the beginning of a chapter.
 *  @param  ch_num the number of the chapter
 *  @param  sout the object of the output stream to print the message there.
 */
inline void print_run_chapter_message(const int& ch_num, std::ostream& sout = std::cout)
{
    sout << "\nRunning chapter " << ch_num << ": "
        << CHAPTER_NAMES[ch_num - 1] << std::endl;
}

/**
 *  Seeds the pseudo-random number generator used by std::rand()
 *  with the value of "std::time(nullptr) % UINT_MAX".
 */
inline void seed_rand()
{
    std::srand(std::time(nullptr) % UINT_MAX);
}

//-PARSERS------------------------------------------------------------------------------------------

/**
 *  Parses the line to fill the val.
 *  The line must corresponds the conditions:
 *  (1) to match the regular expression
 *  "[-+]?(0|([1-9][0-9]*))\\.[0-9]+(e[-+][1-9][0-9]*)?" (e.g. -12.034e+56);
 *  (2) 3 <= line.len <= DBL_MAX_LEN, where DBL_MAX_LEN is a definition
 *  of length of decimal notation of maximum allowed double value.
 *  This function is necessary because
 *  there is no complete satisfaction with the sscanf work.
 *  @param  line to be parsed
 *  @param  val to be filled
 *  @return false if the conditions are not met so the val remains intact,
 *          otherwise true with filling the val by the parsed value
 */
bool parse_double(Line const& line, double& val);

/**
 *  Parses the line to fill the val.
 *  The line must corresponds the conditions:
 *  (1) to match the regular expression "[-+]?(0|([1-9][0-9]*))";
 *  (2) 1 <= line.len <= INT_MAX_DIG, where INT_MAX_DIG is a definition
 *  of length of decimal notation of maximum allowed int value.
 *  This function is necessary because
 *  there is no complete satisfaction with the sscanf work.
 *  @param  line to be parsed
 *  @param  val to be filled
 *  @return false if the conditions are not met so the val remains intact,
 *          otherwise true with filling the val by the parsed value
 */
bool parse_int(Line const& line, int& val);

/**
 *  Parses the line to fill the val.
 *  The line must corresponds the conditions:
 *  (1) to match the regular expression "[+]?(0|([1-9][0-9]*))";
 *  (2) 1 <= line.len <= SIZE_MAX_DIG, where SIZE_MAX_DIG is a definition
 *  of the length of the decimal notation of the maximum allowed size_t value.
 *  This function is necessary because
 *  there is no complete satisfaction with the sscanf work.
 *  @param  line to be parsed
 *  @param  val to be filled
 *  @return false if the conditions are not met so the val remains intact,
 *          otherwise true with filling the val by the parsed value
 */
bool parse_size(Line const& line, size_t& val);

//-INPUT-FUNCTIONS----------------------------------------------------------------------------------

/**
 *  Reads a double value from the input stream.
 *  @param  sin input stream to read from
 *  @throw  ios_base::failure if the parse_double returns false
 *  @return parsed double value
 */
double input_double(std::istream& sin = std::cin);

/**
 *  Reads an int value from the input stream.
 *  @param  sin input stream to read from
 *  @throw  ios_base::failure if the parse_int returns false
 *  @return parsed int value
 */
int input_int(std::istream& sin = std::cin);

/**
 *  Reads a size_t value from the input stream.
 *  @param  sin input stream to read from
 *  @throw  ios_base::failure if the parse_size returns false
 *  @return parsed size_t value
 */
size_t input_size(std::istream& sin = std::cin);

#endif /* Utils_hpp */
