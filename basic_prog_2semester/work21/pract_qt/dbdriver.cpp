// Кашапов Ярослав, 12 вариант, 100%

#include <vector>
#include <QtAlgorithms>
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QObject>
#include <cstring>

class Item;
class dbdriver;
using Database = std::vector<Item>;

class Item {

    QString sname;
    QString login;
    QString passw;
    enum roles {ADMIN,MODERATOR,REGULAR_USER} role;

public:
    Item() {};
    bool eld_txt(QTextStream &ist) {
        QString _role;
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
               passw.length() > 0;
    }

    bool eld_bin(QDataStream &ist) {

        ist >> sname >> login >> passw >> role;
        return sname.length() > 0 &&
               login.length() > 0 &&
               passw.length() > 0;;
    }

    void esv_bin(QDataStream &ost) const { ost << sname << login << passw << role; }

    uint8_t getRole() {return role;};

    static void print_table_head(QTextStream &ost) {
        ost.setFieldWidth(15);
        ost << Qt::left << "\nname" << "login" << "password" << "role" << Qt::endl;
        ost.setFieldWidth(0);
        ost << "\n";
    }

    void print_table_row(QTextStream &ost) const {
        ost.setFieldWidth(15);
        ost << Qt::left << sname << login << passw ;
        switch (role) {
        case ADMIN:
            ost << "admin";
            break;
        case MODERATOR:
            ost << "moderator";
            break;
        case REGULAR_USER:
            ost << "regular_user";
            break;
        }
        ost.setFieldWidth(0);
        ost << "\n";
    }
};

class dbdriver {

    QString db_path_txt;
    QString db_path_bin;

    static std::size_t print_table(const Database &db, QTextStream &ost) {
        uint count=0;
        Item::print_table_head(ost);
        for (const Item &i : db) {
            i.print_table_row(ost);
            count++;
        }
        ost << Qt::endl;
        return count;
    }

    static std::size_t load_txt(Database &db, QTextStream &ist) {
        uint count = 0;
        while(!ist.atEnd()) {
            Item *entry = new Item();
            if (entry->eld_txt(ist)) {
                db.push_back(*entry);
                count++;
            }
        }
        return count;
    }

    static std::size_t load_bin(Database &db, QDataStream &ist) {
        uint count = 0;
        while(!ist.atEnd()) {
            Item *entry = new Item();
            if (entry->eld_bin(ist)) {
                db.push_back(*entry);
                count++;
            }
        }
        return count;
    }

    static std::size_t save_bin(const Database &db, QDataStream &ost) {
        uint count = 0;
        for (const Item &i : db) {
            i.esv_bin(ost);
            count++;
        }
        return count;
    }

    static void sortByRole(Database &db) {
        qSort(db.begin(), db.end(), cmpByRole);
    }

    static bool cmpByRole(Item &member1, Item &member2) {
        return member1.getRole() > member2.getRole();
    }

public:

    dbdriver(QString txtfile, QString binfile)
    {
        db_path_txt = txtfile;
        db_path_bin = binfile;
    };

    void work(int mode, QTextStream &ost)
    {
        Database database;
        QFile db_txt (db_path_txt);
        QFile db_bin (db_path_bin);

        if (mode == 1) {
            db_txt.open(QIODevice::ReadOnly | QIODevice::Text);
            db_bin.open(QIODevice::WriteOnly | QIODevice::Truncate);
            if(!db_bin.isOpen() && !db_txt.isOpen()) {

                QTextStream cerr(stderr);
                cerr << "Something that appears on the error stream";
                ost << "Something that appears on the error stream";
                return;
            }
            QTextStream _db_txt(&db_txt);
            QDataStream _db_bin(&db_bin);

            ost << QObject::tr("Было загружено ") << (unsigned)load_txt(database, _db_txt) << QObject::tr(" записей\n");
            print_table(database, ost);
            sortByRole(database);
            print_table(database, ost);
            save_bin(database, _db_bin);
        } else {
            db_bin.open(QIODevice::ReadOnly);
            if(!db_bin.isOpen()) {
                QTextStream cerr(stderr);
                cerr << "Something that appears on the error stream";
                ost << "Something that appears on the error stream";
                    return;
            }

            QDataStream _db_bin(&db_bin);

            load_bin(database, _db_bin);
            print_table(database, ost);
        }
        db_txt.close();
        db_bin.close();
    }
};
