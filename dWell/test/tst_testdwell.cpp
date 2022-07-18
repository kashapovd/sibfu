#include <QtTest>
#include <QDateTime>
#include <QTemporaryFile>

#include "../dWell/user.h"
#include "../dWell/ubook.h"
#include "../dWell/room.h"
#include "../dWell/habitant.h"

Q_DECLARE_METATYPE(user);
Q_DECLARE_METATYPE(user::utype)
Q_DECLARE_METATYPE(ubook);
Q_DECLARE_METATYPE(room);
Q_DECLARE_METATYPE(habitant);

class testDWell : public QObject
{
    Q_OBJECT

private slots:
    //user class tests
    void getUserName();
    void getUserPassword();
    void getUserType();
    void setUserData();
    void writeAndReadUserFromFile();

    //ubook class tests
    void insertUsers();
    void removeUsers();

    //room class tests
    void setRoomCapacity();
    void roomCheckin();
    void roomWiping();

};

void testDWell::getUserName()
{
    QString n = "admin";
    user u0(n, "P@ssw0rd", user::ADMIN);
    QVERIFY(u0.name() == n);
}

void testDWell::getUserPassword()
{
    QString p = "P@ssw0rd";
    user u("student", p, user::STUDENT);
    QVERIFY(u.passwd() == p);
}

void testDWell::getUserType()
{
    user::utype t = user::ADMIN;
    user ua("admin", "P@ssw0rd", t);
    QVERIFY(ua.type() == t);
    t = user::STUDENT;
    user us("student", "P@ssw0rd ", t);
    QVERIFY(us.type() == t);
    t = user::COMMANDANT;
    user uc("comm", "P@ssw0rd", t);
    QVERIFY(uc.type() == t);
}

void testDWell::writeAndReadUserFromFile()
{
    QString n = "admin";
    QString p = "P@ssw0rd";
    user::utype t = user::ADMIN;
    QTemporaryFile f("file");
    f.open();
    QDataStream wstr(&f);
    user wu(n, p, t);
    wstr << wu;
    f.close();
    f.open();
    QDataStream rstr(&f);
    user ru;
    rstr >> ru;
    f.close();
    QVERIFY(ru.name() == n && ru.passwd() == p && ru.type() == t);
}

void testDWell::setUserData()
{
    QString n = "admin";
    QString p = "P@ssw0rd";
    user::utype t = user::ADMIN;
    user u(n, p, t);
    QString newn = "anykey";
    QString newp = "pass";
    user::utype newt = user::STUDENT;
    u.setData(newn, newp, newt);
    QVERIFY(u.name() == newn and u.passwd() == newp and u.type() == newt);

    //empty name
    n = "";
    QVERIFY2(u.setData(n, p, t)==false, "failed to set user data with empty name field");
    n = "user";

    //empty password
    p = "";
    QVERIFY2(u.setData(n, p, t)==false, "failed to set user data with empty password field");
    p = "P@ssw0rd";

    //user type is enumeration ADMIN=0, COMMANDANT=1, STUDENT=2 and UNKNOWN=3
    t = user::UNKNOWN;
    QVERIFY2(u.setData(n, p, t)==false, "failed to set user data with UNKNOWN type");
    t = user::utype(-1);
    QVERIFY2(u.setData(n, p, t)==false, "failed to set user data with wrong type");
    t = user::utype(10);
    QVERIFY2(u.setData(n, p, t)==false, "failed to set user data with wrong type");

    n="";
    p="";
    t = user::utype(100);
    QVERIFY2(u.setData(n, p, t)==false, "failed to set wrong data");
}

void testDWell::insertUsers()
{
    user u1("a", "a", user::ADMIN);
    ubook usersbook;
    QVERIFY(usersbook.insert(u1));
    QVERIFY2(usersbook.size()==1, "wrong size");

    QVERIFY2(usersbook[0].name() == "a" && usersbook[0].passwd() == "a" && usersbook[0].type() == user::ADMIN, "error occurred when user pushing in userbook");
    user u2("a", "a", user::ADMIN);
    QVERIFY2(usersbook.insert(u2) == false, "an error occurred while adding a user with a matching name");
    user u3("b", "b", user::COMMANDANT);
    user u4("c", "c", user::STUDENT);
    QVERIFY(usersbook.insert(u3));
    QVERIFY(usersbook.insert(u4));
    QVERIFY2(usersbook.size() == 3, "wrong size");
}

void testDWell::removeUsers()
{
    user u1("a", "a", user::ADMIN);
    ubook usersbook;
    usersbook.insert(u1);
    QVERIFY(usersbook.size()==1);
    user u2("b", "a", user::ADMIN);
    user u3("c", "b", user::COMMANDANT);
    user u4("s", "c", user::STUDENT);
    usersbook.insert(u2);
    usersbook.insert(u3);
    usersbook.insert(u4);
    QVERIFY(usersbook.size()==4);

    usersbook.remove(0); // 0 - element index
    QVERIFY(usersbook.size()==3);
    usersbook.remove(0);
    usersbook.remove(0);
    usersbook.remove(0);
    QVERIFY(usersbook.size()==0);
}

void testDWell::setRoomCapacity()
{
    room r;
    uint roomCap = 4;
    r.setCapacity(roomCap);
    QVERIFY(r.capacity() == 4);
    roomCap = 100;
    r.setCapacity(roomCap);
    QVERIFY(r.capacity() == 100);
    roomCap = 0;
    r.setCapacity(roomCap);
    QVERIFY(r.capacity() == 100);
    roomCap = -1;
    r.setCapacity(roomCap);
    QVERIFY(r.capacity() == 100);
}

void testDWell::roomCheckin()
{
    room r;
    uint roomNumber = 100;
    uint roomCap = 1;
    r.setCapacity(roomCap);
    r.setNumber(roomNumber);

    QVERIFY(r.isEmpty() == true);

    habitant h1;
    habitant::habitantData hb;
    hb.birthDate = QDate(QDateTime::currentDateTime().date());
    hb.fname = "vasya";
    hb.lname = "ivanov";
    hb.group = "KI19-07b";
    hb.numOfCourse = 1;
    hb.patronymic = "Palych";
    hb.roomNumber = roomNumber;
    hb.studentID = 123;
    h1.setData(&hb);

    r.checkin(h1);
    QVERIFY(r.size() == 1);
    QVERIFY(r.isEmpty()==false);

    habitant h2;
    hb.birthDate = QDate(QDateTime::currentDateTime().date());
    hb.fname = "vasya";
    hb.lname = "ivanosddadsv";
    hb.group = "KI19-07b";
    hb.numOfCourse = 2;
    hb.patronymic = "Palychasdasdasdasdas";
    hb.roomNumber = roomNumber;
    hb.studentID = 124;
    h1.setData(&hb);

    QVERIFY(r.availableForCheckin() == false);
    roomCap = 2;
    r.setCapacity(roomCap);
    r.checkin(h2);
    QVERIFY(r.size() == 2);
    QVERIFY(r.isEmpty()==false);
}

void testDWell::roomWiping()
{
    room r;
    uint roomNumber = 100;
    uint roomCap = 2;
    r.setCapacity(roomCap);
    r.setNumber(roomNumber);

    QVERIFY(r.isEmpty() == true);

    habitant h1;
    habitant::habitantData hb;
    hb.birthDate = QDate(QDateTime::currentDateTime().date());
    hb.fname = "vasya";
    hb.lname = "ivanov";
    hb.group = "KI19-07b";
    hb.numOfCourse = 1;
    hb.patronymic = "Palych";
    hb.roomNumber = roomNumber;
    hb.studentID = 123;
    h1.setData(&hb);

    r.checkin(h1);

    habitant h2;
    hb.birthDate = QDate(QDateTime::currentDateTime().date());
    hb.fname = "vasya";
    hb.lname = "ivanosddadsv";
    hb.group = "KI19-07b";
    hb.numOfCourse = 2;
    hb.patronymic = "Palychasdasdasdasdas";
    hb.roomNumber = roomNumber;
    hb.studentID = 124;
    h1.setData(&hb);

    r.checkin(h2);

    QVERIFY(r.isEmpty()==false);
    r.clear();
    QVERIFY(r.isEmpty());
    QVERIFY(r.size()==0);
    QVERIFY(r.availableForCheckin());
}

QTEST_APPLESS_MAIN(testDWell)
#include "tst_testdwell.moc"
