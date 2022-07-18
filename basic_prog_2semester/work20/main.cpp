// Кашапов Ярослав, 12 вариант, 100%

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <algorithm>

#define DB_PATH_TXT "/home/yaroslav/practical works/programming/FILES/work20_txt"
#define DB_PATH_BIN "/home/yaroslav/practical works/programming/FILES/work20_bin"

class Item {

    std::string sname;
    std::string login;
    std::string passw;
    enum roles {ADMIN,MODERATOR,REGULAR_USER} role;

public:
    Item() {};
    bool eld_txt(std::istream &ist) {
        std::string _role;
        ist >> sname >> login >> passw;
        ist >> _role;
        if (_role == "admin")
            role = ADMIN;
        else if (_role == "moderator")
            role = MODERATOR;
        else {
            role = REGULAR_USER;
            ist >> _role;
        }
        return sname.length() > 0 &&
               login.length() > 0 &&
               passw.length() > 0;;
    }

    bool eld_bin(std::istream &ist) {

        struct payload {
            char _sname[16];
            char _login[16];
            char _passw[11];
            roles _role;
        } attr;

        ist.read(reinterpret_cast<char *>(&attr),sizeof (attr));
        sname = attr._sname;
        login = attr._login;
        passw = attr._passw;
        role  = attr._role;
        return sname.length() > 0 &&
               login.length() > 0 &&
               passw.length() > 0;;
    }

    void esv_bin(std::ostream &ost) const {

        struct payload {
            char _sname[16] = "";
            char _login[16] = "";
            char _passw[11] = "";
            roles _role;
        } attr;
        strcpy(attr._sname, sname.data());
        strcpy(attr._login, login.data());
        strcpy(attr._passw, passw.data());
        attr._role = role;
        ost.write(reinterpret_cast<char *>(&attr), sizeof (attr));
    }

    uint8_t getRole() {return role;};

    static void print_table_head(std::ostream &ost) {
        ost << "\n";
        for (int k = 0; k < 56; k++) std::cout << '+';
        ost << std::left << std::setw(15) << "\nname" << std::setw(15) << "login" << std::setw(15) << "password" << std::setw(15) << "role" << std::endl;
        for (int k = 0; k < 56; k++) std::cout << '+';
            ost << "\n";
    }

    void print_table_row(std::ostream &ost) const {
        ost << std::left << std::setw(14) << sname
            << std::setw(15) << login << std::setw(15)
            << passw << std::setw(15);
        switch (role) {
        case ADMIN:
            ost << std::setw(15) << "admin";
            break;
        case MODERATOR:
            ost << std::setw(15) << "moderator";
            break;
        case REGULAR_USER:
            ost << std::setw(15) << "regular_user";
            break;
        }
        ost << "\n";
    }
};

using Database = std::vector<Item>;
std::size_t print_table(const Database &, std::ostream &);
std::size_t load_txt(Database &, std::istream &);
std::size_t load_bin(Database &, std::istream &);
std::size_t save_bin(const Database &, std::ostream &);
void sortByRole(Database &);
bool cmpByRole(Item &, Item &);

int main() {

    Database database;
    std::ifstream db_txt;
    std::fstream db_bin;

    char mode[1];

    while (strcmp(mode, "1") != 0 and strcmp(mode, "2") != 0) {

        std::cout <<("1. load from txt, print it and save to bin\n"
                     "2. load from bin and print\n"
                     "Choose a mode: ");
        std::cin >> mode;
    }
    if (strcmp(mode, "1") == 0) {
        db_txt.open(DB_PATH_TXT, std::ios::in);
        db_bin.open(DB_PATH_BIN, std::ios::binary | std::ios::out | std::ios::trunc);
        if (!db_bin.is_open() || !db_txt.is_open()) {
            std::cerr << "Problems with the files. Stopping..\n";
            return 1;
        }
        std::cout << "Was loaded " << (unsigned)load_txt(database, db_txt) << " entries\n";
        print_table(database, std::cout);
        sortByRole(database);
        print_table(database, std::cout); // printing after sorting
        save_bin(database, db_bin);
    }
    else {
        db_bin.open(DB_PATH_BIN, std::ios::binary | std::ios::in);
        if (!db_bin.is_open()) {
            std::cerr << "Problems with the bin file. Stopping..\n";
            return 1;
        }
        load_bin(database, db_bin);
        print_table(database, std::cout);
    }

    db_txt.close();
    db_bin.close();
    return 0;
}

std::size_t load_txt(Database &db, std::istream &ist) {
    uint i = 0;
    while(!ist.eof() && ist.good()) {
        Item *entry = new Item();
        if (entry->eld_txt(ist)) {
            db.push_back(*entry);
            i++;
        }
    }
    return i;
}

std::size_t save_bin(const Database &db, std::ostream &ost) {
    uint count = 0;
    for (const Item &i : db) {
        i.esv_bin(ost);
        count++;
    }
    return count;
}

std::size_t load_bin(Database &db, std::istream &ist) {
    uint i = 0;
    while(!ist.eof() && ist.good()) {
        Item *entry = new Item();
        if (entry->eld_bin(ist)) {
            db.push_back(*entry);
            i++;
        }
    }
    return i;
}

std::size_t print_table(const Database &db, std::ostream &ost) {
    uint i=0;
    db.at(i).print_table_head(ost);
    for (i=0; i < db.size(); i++) {
        db.at(i).print_table_row(ost);
    }
    ost << std::endl;
    return i;
}

void sortByRole(Database &db)
{
    std::sort(db.begin(), db.end(), cmpByRole);
}

bool cmpByRole(Item &member1, Item &member2) {
        return member1.getRole() > member2.getRole();
}
