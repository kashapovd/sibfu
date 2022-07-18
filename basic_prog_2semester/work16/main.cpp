// Кашапов Ярослав, 12 вариант, 100%

#include <iostream>     // std::cout,cin
#include <fstream>      // std::istream,ostream
#include <vector>       // std::vector
#include <string>       // std::string
#include <cstring>      // strlen
#include <algorithm>    // std::sort

#define DB_PATH_TXT "/home/yaroslav/practical works/basic_prog/FILES/work16_txt"
#define DB_PATH_BIN "/home/yaroslav/practical works/basic_prog/FILES/work16_bin"
#define DB_PATH_SORTBIN "/home/yaroslav/practical works/basic_prog/FILES/work16_sortbin"

struct userRights {
    char name[15];
    char login[15];
    char password[11];
    enum role { ADMIN,
                MODERATOR,
                REGULAR_USER
              } role : 8;
} _userRights;

int num_structs;

userRights *loadTxt(std::istream &);
userRights *loadBin(std::istream &);
userRights *sortRole(userRights *);
void saveBin(const userRights *, std::ostream &);
void printData(const userRights *, std::ostream &);
bool cmpByRole(const userRights &struct1, const userRights &struct2);
bool cmpByName(const userRights &struct1, const userRights &struct2);

int main()
{
    userRights *database;
    std::fstream db_txt;
    std::fstream db_bin;
    std::ofstream db_sortbin;

    db_txt.open(DB_PATH_TXT, std::ios::in);
    db_bin.open(DB_PATH_BIN, std::ios::binary | std::ios::out | std::ios::in | std::ios::trunc);
    db_sortbin.open(DB_PATH_SORTBIN, std::ios::binary | std::ios::trunc);
    if (!db_bin.is_open() || !db_txt.is_open() || !db_sortbin.is_open()) {
        std::cerr << "Problem with a files. Stopping..\n";
        return 1;
    }

    database = loadTxt(db_txt);
    std::cout << "Read after loading data from work16_txt...\n";
    printData(database, db_txt);

    saveBin(database, db_bin);

    database = loadBin(db_bin);
    std::cout << "Read after loading data from work16_bin...\n";
    printData(database, db_txt);

    database = sortRole(database);
    std::cout << "Read after sorting data...\n";
    printData(database, db_txt);

    saveBin(database, db_sortbin);

    db_txt.close();
    db_bin.close();
    db_sortbin.close();

    database = nullptr;
    return 0;
}

void saveBin(const userRights *data, std::ostream &ost)
{
    for (int i = 0; i < num_structs; i++)
        ost.write((char *)& *(data+i), sizeof (userRights));
}

userRights *loadBin(std::istream &ist)
{
    std::vector<userRights> db;
    for (int i = 0; i < num_structs; i++)
    {
        db.push_back(userRights());
        ist.seekg(i*sizeof (userRights));
        ist.read((char *)&(db[i]), sizeof (userRights));

    }
    return db.data();
}

void printData(const userRights *data, std::ostream &ost)
{
    for (int k = 0; k < 62; k++) std::cout << '+';
    std::cout << "\nname" << "\t\t" << "login" << "\t\t" << "password" << "\t" << "role" << "\n";
    for (int k = 0; k < 62; k++) std::cout << '+';
    std::cout << "\n";

    for (int i = 0; i < num_structs; i++)
    {
        std::cout << (data+i)->name << ((strlen((data+i)->name) >= 8) ? "\t" : "\t\t");
        std::cout << (data+i)->login << ((strlen((data+i)->login) >= 8) ? "\t" : "\t\t");
        std::cout << (data+i)->password << "\t";

        switch((data+i) -> role) {
            case 0: std::cout << "admin\n";
                break;
            case 1: std::cout << "moderator\n";
                break;
            case 2: std::cout << "regular user\n";
                break;
        }
    }
    for (int k = 0; k < 62; k++) std::cout << '=';
    std::cout << std::endl << std::endl;
}

userRights *loadTxt(std::istream &ist)
{
    std::vector<userRights> db;

    std::string _role;
    for (int i = 0; !ist.eof(); i++)
    {
        db.push_back(userRights());
        ist >> db[i].name >> db[i].login >> db[i].password;
        ist >> _role;
        if (_role == "admin")
            db[i].role = userRights::ADMIN;
        else if (_role == "moderator")
            db[i].role = userRights::MODERATOR;
        else if (_role == "\"regular") {
            db[i].role = userRights::REGULAR_USER;
            ist >> _role;
        }
    }
    num_structs = db.size() - 1;

    return db.data();
}

userRights *sortRole(userRights *data)
{
    std::sort(data, data + num_structs, cmpByRole);
    //std::sort(data, data + num_structs, cmpByName);
    return data;
}

bool cmpByName(const userRights &struct1, const userRights &struct2)
{
    return static_cast<std::string>(struct1.name) < static_cast<std::string>(struct2.name);
}

bool cmpByRole(const userRights &struct1, const userRights &struct2)
{
    return struct1.role > struct2.role;
}
