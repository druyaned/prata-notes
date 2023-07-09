#ifndef ch17_io_n_files_hpp
#define ch17_io_n_files_hpp
#include "Utils.hpp"
#include <iostream>
#include <iomanip> // setw(), setprecision()
#include <cmath>
#include <cstdio>
#include <fstream>
#include <cctype>
#include <set>
#include <string>
#include <cstring>
#include <vector>

int ch17_io_n_files();

using namespace std;

// binar_files
struct Planet
{
    char name[FF_SIZE];
    unsigned long long perihelion; // km
    double g; // m/sec^2
};

// number6
// Worker
class Worker
{
private:
    Line m_name;
    int m_id;
protected:
    void setWorker(Line const& name, int id) {m_name = name; m_id = id;}
    Line workerToLine() const {return Line("name=") + m_name + ", id=" + m_id;}
public:
    Worker() : m_name(), m_id(0) {}
    Worker(Line const& name, int id) : m_name(name), m_id(id) {}
    Worker(Worker const& worker) : m_name(worker.m_name), m_id(worker.m_id) {}
    virtual ~Worker() = 0;
    Line const name() const {return m_name.str();}
    int const id() const {return m_id;}
    Worker& operator=(Worker const& worker);
    virtual void set(Line const& name, int id);
    virtual void show() const;
    friend ostream& operator<<(ostream& sout, Worker const& worker);
};
// Waiter
class Waiter : virtual public Worker
{
private:
    int m_rang;
protected:
    void setWaiter(int rang) {m_rang = rang;}
    Line waiterToLine() const {return Line("rang=") + m_rang;}
public:
    Waiter() : Worker(), m_rang(0.0) {}
    Waiter(Line const& name, int id, int rang) : Worker(name, id), m_rang(rang) {}
    ~Waiter() {}
    int const rang() const {return m_rang;}
    virtual void set(Line const& name, int id, int rang);
    virtual void show() const;
};
// Singer
class Singer : public virtual Worker
{
public:
    enum VoiceType {tenor, baritone, bass};
private:
    VoiceType m_voice;
protected:
    void setSinger(VoiceType voice) {m_voice = voice;}
    Line singerToLine() const {return Line("voice=") + int(m_voice);}
public:
    Singer() : Worker(), m_voice(bass) {}
    Singer(Line const& name, int id, VoiceType voice)
        : Worker(name, id), m_voice(voice) {}
    ~Singer() {}
    VoiceType const voice() const {return m_voice;}
    virtual void set(Line const& name, int id, VoiceType voice);
    virtual void show() const;
};
// SingerWaiter
class SingerWaiter : public Singer, public Waiter
{
public:
    SingerWaiter() : Worker(), Waiter(), Singer() {}
    SingerWaiter(Line const& name, int id, int rang, VoiceType voice)
        : Worker(name, id), Waiter(name, id, rang), Singer(name, id, voice) {}
    ~SingerWaiter() {}
    virtual void set(Line const& name, int id, int rang, VoiceType voice);
    virtual void show() const;
};

#endif /* ch17_io_n_files_hpp */
