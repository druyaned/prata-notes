#ifndef ch11_working_with_classes_hpp
#define ch11_working_with_classes_hpp
#include "Utils.hpp"

using std::ostream;
using std::istream;

int ch11_working_with_classes();

// vect + number1_3
class Vector
{
public:
    enum Mode {RECT, POL};
private:
    Mode M;
    double x, y, magnitude, angle;
    void set_rect(void);
    void set_pol(void);
public:
    // can be: explicit Vector(), if there can be one argument
    Vector(double a1 = 0.0, double a2 = 0.0, Mode m = RECT);
    ~Vector(void) {};
    void reset(double a1 = 0.0, double a2 = 0.0, Mode m = RECT);
    inline double MagVal(void) {return magnitude;};
    void rect_mode(void) {M = RECT;};
    void pol_mode(void) {M = POL;};
    Vector operator+(const Vector &) const;
    Vector operator-(const Vector &) const;
    Vector operator-(void) const; // for example: -v1
    Vector operator*(double) const;
    friend Vector operator*(double, const Vector &);
    friend ostream & operator<<(ostream &, const Vector &);
    operator double(void); // функция преобразования
    explicit operator int(void); // explicit => только явное преобразование
};

// number2_7
class ComplNum
{
public:
    enum Mode {ALG, TRIG, EXPN};
private:
    Mode M;
    double x, y, r, u;
    void set_xy(void);
    void set_ru(void);
public:
    ComplNum(double xr = 0.0, double yu = 0.0, Mode m = ALG);
    ~ComplNum(void) {};
    void reset(double xr = 0.0, double yu = 0.0, Mode m = ALG);
    ComplNum & SetMode(Mode m = ALG);
    ComplNum operator+(const ComplNum &) const;
    ComplNum operator-(const ComplNum &) const;
    ComplNum operator-(void) const;
    ComplNum operator*(const ComplNum &) const;
    ComplNum operator/(const ComplNum &) const;
    ComplNum operator~(void) const;
    friend ostream & operator<<(ostream &, const ComplNum &);
    friend istream & operator>>(istream &, ComplNum &);
    operator double(void) {return r;};
};

// number4
class Time
{
private:
    int hour;
    int minuts;
    long FullMin;
public:
    explicit Time(long m = 0);
    Time(int h, int m);
    ~Time(void) {};
    void reset(long m = 0);
    void reset(int h, int m);
    Time operator+(const Time &) const;
    Time operator-(const Time &) const;
    Time operator+(int) const;
    Time operator-(int) const;
    friend Time operator+(int, const Time &);
    friend Time operator-(int, const Time &);
    friend ostream & operator<<(ostream &, const Time &);
    explicit operator long();
};

// number5_6
class Stonewt
{
public:
    enum Mode {LBS, STN};
private:
    enum {Lbs_stn = 14}; // фунтов на стоун
    Mode M; // режим LBS or STN
    int stone; // полных стоунов
    double pds_left; // дробное число фунтов
    double pounds; // общий вес в фунтах
public:
    Stonewt(double lbs = 0, Mode m = LBS);
    Stonewt(int stn, double lbs, Mode m = STN);
    ~Stonewt() {};
    void reset(double lbs = 0, Mode m = LBS);
    void reset(int stn, double lbs, Mode m = STN);
    void LbsMode(void);
    void StnMode(void);
    Stonewt operator+(const Stonewt &) const;
    Stonewt operator-(const Stonewt &) const;
    Stonewt operator*(double) const;
    bool operator<(const Stonewt &) const;
    bool operator>(const Stonewt &) const;
    bool operator==(const Stonewt &) const;
    friend Stonewt operator*(double, const Stonewt &);
    friend ostream & operator<<(ostream &, const Stonewt &);
    explicit operator double() {return pounds;};
};

#endif /* ch11_working_with_classes_hpp */
