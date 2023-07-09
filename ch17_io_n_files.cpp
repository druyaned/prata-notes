#include "ch17_io_n_files.hpp"

using namespace std;

static int const W = 16;
char const
*FILE_IN = "ch17_in.txt",
*FILE_OUT = "ch17_out.txt",
*FILE_EX6 = "ch17_ex6_in.txt";

static void cout_decor();
static void about_cin();
static void abitmore_cin();
static void binar_files();
static void number6();

int ch17_io_n_files()
{
    print_run_chapter_message(17);
    cout_decor();
    about_cin();
    abitmore_cin();
    binar_files();
    number6();
    return EXIT_SUCCESS;
}

// cout_decor
void cout_decor()
{
    ios_base::fmtflags dflt_flags = cout.flags();
    cout << "\nCout decor\n";
    int num1 = 1685024583;
    cout << "#1: Practice with '(char *)&'\n";
    cout << '(' << num1 << ")_10 = (01100100 01101111 01101111 01000111)_2 -> ";
    cout.write((char *)& num1, sizeof(int)) << endl;
    cout << "d: 100 = 01100100" << endl;
    cout << "o: 111 = 01101111" << endl;
    cout << "o: 111 = 01101111" << endl;
    cout << "G: 71  = 01000111" << endl;
    cout.fill('_');
    cout << "#2: Practice with 'cout.fill'\n";
    for (int i = 1; i <= 100; i *= 10)
        cout << setw(W) << i << '*' << i << '=' << i * i << endl;
    cout.fill(' ');
    cout << "#3: Practice with 'wcout'\n";
    wchar_t bob[] = L"Bob";
    wcout << "wchar_t bob[]: '" << bob << "'\n";
    cout << "#4: Practice with 'cout.precision'\n";
    streamsize dflt_prec = cout.precision(4); // dflt_prec - default precision
    float num2 = (float) 5 / 3, num3 = 47.9251738f, num4 = 2.3f;
    cout << "Precision 4\n";
    cout << "num2 = " << num2 << ", num3 = " << num3 << ", num4 = " << num4 << endl;
    cout.precision(dflt_prec);
    cout << "Default precision\n";
    cout << "num2 = " << num2 << ", num3 = " << num3 << ", num4 = " << num4 << endl;
    cout << "#5: Practice with 'cout.setf'\n";
    cout.setf(ios_base::hex, ios_base::basefield);
    cout.setf(ios_base::scientific, ios_base::floatfield);
    cout.setf(ios_base::showbase | ios_base::boolalpha | ios_base::showpoint);
    num1 = 48 * 67;
    bool cmp_res = (num1 == 3216) ? true : false;
    cout << "Is 48 * 67 == 3216 ? Answer is " << cmp_res << endl;
    cout << "17 as a hexadecimal number: " << 17 << endl;
    cout << "'cout << 1.23': " << 1.23 << endl;
    cout.flags(dflt_flags);
}

// about_cin
void about_cin()
{
    ios_base::fmtflags dflt_flags = cout.flags();
    cout << "\nAbout cin\n";
    cout << right << setw(W) << "BIT" << setw(W) << "VALUE" << setw(W) << '\n';
    cout.fill('_');
    cout.setf(ios_base::hex, ios_base::basefield);
    cout.setf(ios_base::showbase);
    cout << setw(W) << "goodbit" << setw(W) << ios_base::goodbit << endl;
    cout << setw(W) << "badbit" << setw(W) << ios_base::badbit << endl;
    cout << setw(W) << "eofbit" << setw(W) << ios_base::eofbit << endl;
    cout << setw(W) << "failbit" << setw(W) << ios_base::failbit << endl;
    cout.fill(' ');
    ios_base::iostate stat = cin.rdstate();
    cout << "Stream status: " << stat << endl;
    int num;
    cout << "Enter a character: ";
    cin >> num;
    while (!cin.fail())
    {
        cout << "Not number, a character: ";
        cin >> num;
    }
    stat = cin.rdstate();
    cout << "Nice! Now failbit is setted.\n";
    cout << "Stream status: " << stat << "\n";
    cout << "Clearing the 'cin'...\n";
    cin.clear();
    cout << "Successfully cleared\n";
    while (cin && cin.get() != '\n'); // eat_line
    cout << "Method clear(goodbit) sets goodbit and cleaning bad-, eof- and failbit.\n";
    cout << "setstate(goodbit) only sets goodbit.\n";
    // exceptions
    ifstream fin(FILE_IN);
    if (!fin.is_open())
    {
        ofstream fout(FILE_IN);
        if (!fout.is_open())
        {
            cerr << "can't open the file '" << FILE_IN << "'\n";
            cout.flags(dflt_flags);
            return;
        }
        fout.close();
        fin.open(FILE_IN);
    }
    const int N_NUMS = 7;
    int nums[N_NUMS]{};
    ios_base::iostate exception_mask = ios_base::badbit | ios_base::eofbit | ios_base::failbit;
    fin.exceptions(exception_mask);
    cout << "Trying to read " << N_NUMS << " number(s) from the '" << FILE_IN << "...\n";
    try
    {
        for (size_t i = 0; fin && i < N_NUMS; ++i)
        {
            fin >> nums[i];
        }
        cout << "Read numbers:";
        for (size_t i = 0; i < N_NUMS; ++i)
            cout << ' ' << nums[i];
        cout << endl;
    }
    catch (ios_base::failure& exc)
    {
        cout << "The exception 'ios_base::failure' is caught!\n";
        cout << exc.what() << '\n';
    }
    cout << "fin_stat: " << fin.rdstate() << endl;
    fin.close();
    cout.flags(dflt_flags);
}

// abitmore_cin
void abitmore_cin()
{
    cout << "\nA bit more cin\n";
    // writing some data
    ofstream fout(FILE_IN);
    if (!fout.is_open())
    {
        cerr << "can't open the file '" << FILE_IN << "'\n";
        return;
    }
    fout << "That's a great string!\n";
    fout << "And this string is a great too!#\n";
    fout << "It should be you've guessed that this line is also great!\n";
    fout.close();
    ifstream fin(FILE_IN);
    if (!fin.is_open())
    {
        cerr << "can't open the file '" << FILE_IN << "'\n";
        return;
    }
    cout << "Reading until '#'...\n";
    char ch;
    int line_num = 1;
    cout << setw(2) << line_num << ": ";
    while (fin.get(ch))
    {
        if (ch == '#')
        {
            fin.putback(ch);     // return the character to the file
            cout << endl << "'#' is found. The reading is stopped.\n";
            break;
        }
        else if (ch == '\n')
        {
            cout << endl << setw(2) << ++line_num << ": ";
        }
        else
            cout << ch;
    }
    if (!fin)
        cout << "'fin' failed!\n";
    cout << "So let's continue until '!'...\n";
    while (fin && fin.peek() != '!')   // just look the following character
    {
        ch = (char)fin.get();
        if (ch == '\n')
        {
            cout << endl << setw(2) << ++line_num << ": ";
        }
        else
            cout << ch;
    }
    cout << endl;
    fin.close();
}

// binar_files
void show_planet_header()
{
    cout << setw(W) << "NAME" << ' '
        << setw(W) << "PERIHELION (km)" << ' '
        << setw(W) << "G (m/sec^2)" << endl;
}
void show_planet(Planet planet)
{
    cout << setw(W) << planet.name << ' '
        << setw(W) << planet.perihelion << ' '
        << setw(W) << planet.g << endl;
}
void show_file_planets(istream& fin, Planet const* planets, size_t const N_PLANETS)
{
    cout << "Contents of the file '" << FILE_OUT << "'\n";
    show_planet_header();
    cout.fill('_');
    for (int i = 0; i < N_PLANETS; ++i)
    {
        Planet planet;
        fin.read((char *) &planet, sizeof(Planet));
        show_planet(planet);
    }
    cout.fill(' ');
}
void binar_files()
{
    cout << "\nBinar files\n";
    cout.setf(ios_base::right, ios_base::adjustfield);
    typedef unsigned long long ull;
    size_t const N_PLANETS = 4;
    Planet planets[N_PLANETS];
    char const* names[N_PLANETS] = {"Earth", "Jupiter", "Mercury", "Neptune"};
    ull const perihelions[N_PLANETS] = {147098290, 740573600, 46001009, 4452940833};
    double const gs[N_PLANETS] = {9.81, 24.79, 3.7, 11.15};
    for (size_t i = 0; i < N_PLANETS; ++i)
    {
        strcpy(planets[i].name, names[i]);
        planets[i].perihelion = perihelions[i];
        planets[i].g = gs[i];
    }
    // 1st writing the file
    ofstream fout(FILE_OUT, ios_base::out | ios_base::trunc | ios_base::binary);
    if (!fout.is_open())
    {
        cerr << "can't open the file '" << FILE_OUT << "'\n";
        return;
    }
    cout << "#1: Starting writing the planets into '" << FILE_OUT << "'...\n";
    for (size_t i = 0; i < N_PLANETS - 1; ++i)
        fout.write((char *)& planets[i], sizeof(Planet));
    cout << "The data has been written\n";
    fout.close();
    // 1st reading the file
    ifstream fin;
    fin.open(FILE_OUT, ios_base::in | ios_base::binary);
    if (!fin.is_open())
    {
        cerr << "can't open the file '" << FILE_OUT << "'\n";
        return;
    }
    show_file_planets(fin, planets, N_PLANETS - 1);
    fin.clear();
    fin.close();
    // 2nd writing the file
    fout.open(FILE_OUT, ios_base::out | ios_base::app | ios_base::binary);
    if (!fout.is_open())
    {
        cerr << "can't open the file '" << FILE_OUT << "'\n";
        return;
    }
    cout << "#2: Appending the file...\n";
    fout.write((char*)&planets[N_PLANETS - 1], sizeof(Planet));
    cout << "Successfully appended\n";
    fout.close();
    // 2nd reading the file
    fin.open(FILE_OUT, ios_base::in | ios_base::binary);
    if (!fin.is_open())
    {
        cerr << "can't open the file " << FILE_OUT << endl;
        return;
    }
    show_file_planets(fin, planets, N_PLANETS);
    cout.fill(' ');
    cout << flush; // clean the buffer
    fin.close();
    // random access
    fstream fio(FILE_OUT, ios_base::in | ios_base::out | ios_base::binary);
    if (!fio.is_open())
    {
        cerr << "can't open the file '" << FILE_OUT << "'\n";
        return;
    }
    const int START_POS = 2; // third planet
    streampos pos = START_POS * sizeof(Planet);
    fio.seekg(pos); // seekg - for istream buffer
    Planet planet;
    cout << "#3: Reading the third planet from the file...\n";
    fio.read((char *)& planet, sizeof(Planet));
    cout << "Read planet\n";
    show_planet_header();
    show_planet(planet);
    fio.seekp(pos, ios_base::beg); // seekp - for ostream buffer
    cout << "#4: Writing the third planet in the file...\n";
    fio.write((char *)& planet, sizeof(Planet));
    cout << "Successfully written\n";
    cout.unsetf(ios_base::adjustfield);
}

// number6
// Worker
Worker::~Worker() {}
Worker& Worker::operator=(Worker const& worker)
{
    m_name = worker.m_name;
    m_id = worker.m_id;
    return *this;
}
void Worker::set(Line const& name, int id)
{
    setWorker(name, id);
}
void Worker::show() const
{
    cout << '[' << workerToLine() << "]\n";
}
ostream& operator<<(ostream& sout, Worker const& worker)
{
    sout << worker.workerToLine();
    return sout;
}
// Waiter
void Waiter::set(Line const& name, int id, int rang)
{
    setWorker(name, id);
    m_rang = rang;
}
void Waiter::show() const
{
    cout << '[' << workerToLine() << ", " << waiterToLine() << "]\n";
}
// Singer
void Singer::set(Line const& name, int id, VoiceType voice)
{
    setWorker(name, id);
    m_voice = voice;
}
void Singer::show() const
{
    cout << '[' << workerToLine() << ", " << singerToLine() << "]\n";
}
// SingerWaiter
void SingerWaiter::set(Line const& name, int id, int rang, VoiceType voice)
{
    setWorker(name, id);
    setWaiter(rang);
    setSinger(voice);
}
void SingerWaiter::show() const
{
    cout << '[' << workerToLine()
        << ", " << waiterToLine()
        << ", " << singerToLine() << "]\n";
}
void show_workers(Worker* const* workers, size_t const N_WORKERS)
{
    for (size_t i = 0; i < N_WORKERS; ++i)
    {
        cout << '#' << i + 1 << ": ";
        if (workers[i] == nullptr)
            cout << "nullptr\n";
        else
            workers[i]->show();
    }
}
void write_worker(ofstream& fout, Worker* worker)
{
    size_t const len = worker->name().len();
    fout.write((char*)& len, sizeof(size_t));
    char const* name = worker->name().str();
    fout.write(name, len + 1);
    int const id = worker->id();
    fout.write((char*)& id, sizeof(int));
    Waiter* waiter = dynamic_cast<Waiter*>(worker);
    Singer* singer = dynamic_cast<Singer*>(worker);
    SingerWaiter* sinWai = dynamic_cast<SingerWaiter*>(worker);
    if (sinWai != nullptr)
    {
        int type = 3; // type == 3 for the SingerWaiter
        fout.write((char*)& type, sizeof(int));
        int const rang = sinWai->rang();
        fout.write((char*)& rang, sizeof(int));
        int const voice = sinWai->voice();
        fout.write((char*)& voice, sizeof(int));
    }
    else if (singer != nullptr)
    {
        int type = 2; // type == 2 for the Singer
        fout.write((char*)& type, sizeof(int));
        int const voice = singer->voice();
        fout.write((char*)& voice, sizeof(int));
    }
    else if (waiter != nullptr)
    {
        int type = 1; // type == 1 for the Waiter
        fout.write((char*)& type, sizeof(int));
        int const rang = waiter->rang();
        fout.write((char*)& rang, sizeof(int));
    }
}
Worker* read_new_worker(ifstream& fin) // without validations
{
    char buf[FF_SIZE]{};
    size_t len = 0;
    fin.read((char*)& len, sizeof(size_t));
    char name[Line::CNT_MAX]{};
    fin.read((char*)& name, len + 1);
    int id = 0;
    fin.read((char*)& id, sizeof(int));
    int type = 0;
    fin.read((char*)& type, sizeof(int));
    if (type == 3) // SingerWaiter
    {
        int rang = 0;
        fin.read((char*)& rang, sizeof(int));
        int voice = 0;
        fin.read((char*)& voice, sizeof(int));
        parse_int(buf, voice);
        return new SingerWaiter(name, id, rang, (Singer::VoiceType)voice);
    }
    else if (type == 2) // Singer
    {
        int voice = 0;
        fin.read((char*)& voice, sizeof(int));
        return new Singer(name, id, (Singer::VoiceType)voice);
    }
    else if (type == 1) // Waiter
    {
        int rang = 0;
        fin.read((char*)& rang, sizeof(int));
        return new Waiter(name, id, rang);
    }
    return nullptr;
}
void number6()
{
    cout << "\nExercise 6\n";
    // writing the data
    ofstream fout(FILE_EX6, ios_base::out | ios_base::trunc | ios_base::binary);
    if (!fout.is_open())
    {
        cerr << "can't open the file '" << FILE_EX6 << "'\n";
        return;
    }
    const size_t N_WORKERS = 3;
    char const* names[N_WORKERS] = {"Waiter Potter", "Singer Solo", "SinWai Sanchez"};
    int const ids[N_WORKERS] = {1, 2, 3};
    int const rangs[N_WORKERS] = {5, 6, 7};
    Singer::VoiceType const voices[N_WORKERS] =
    {
        Singer::VoiceType::tenor,
        Singer::VoiceType::baritone,
        Singer::VoiceType::bass
    };
    Waiter waiter = Waiter(names[0], ids[0], rangs[0]);
    Singer singer = Singer(names[1], ids[1], voices[1]);
    SingerWaiter sinWai = SingerWaiter(names[2], ids[2], rangs[2], voices[2]);
    Worker* workers[N_WORKERS] = {&waiter, &singer, &sinWai};
    cout << "Workers\n";
    show_workers(workers, N_WORKERS);
    // writing the data
    cout << "Writing them into the file '" << FILE_EX6 << "'...\n";
    for (size_t i = 0; i < N_WORKERS; ++i)
        write_worker(fout, workers[i]);
    cout << "Writing is completed\n";
    fout.close();
    // reading the data
    ifstream fin(FILE_EX6, ios_base::in | ios_base::binary);
    if (!fin.is_open())
    {
        cerr << "can't open the file '" << FILE_EX6 << "'\n";
        return;
    }
    cout << "Reading the data from the file...\n";
    Worker* read_workers[N_WORKERS];
    for (size_t i = 0; fin && i < N_WORKERS; ++i)
        read_workers[i] = read_new_worker(fin);
    cout << "Read workers\n";
    show_workers(read_workers, N_WORKERS);
    for (size_t i = 0; i < N_WORKERS; ++i)
    {
        if (read_workers[i] != nullptr)
            delete read_workers[i];
    }
    fin.close();
}
