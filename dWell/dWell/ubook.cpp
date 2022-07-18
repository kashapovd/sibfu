/**
 * @file ubook.cpp
 * @brief Файл реализации класса ubook.
 * @author Кашапов Ярослав
 * @date 2021
 */

#include "ubook.h"
#include "config.h"

#include <QFile>
#include <algorithm>

user::utype ubook::findUser(const QString &name, const QString &passwd) const
{
    auto f = std::find_if(mEntries.begin(),
                      mEntries.end(),
         [&](const user &u) {return u.name() == name
                && u.passwd() == passwd;});

    if (f != mEntries.end()) return f->type();
    return user::utype::UNKNOWN;
}

user::utype ubook::findUserByName(const QString &name) const
{
    auto f = std::find_if(mEntries.begin(),
                      mEntries.end(),
         [&](const user &u) {return u.name() == name;});

    if (f != mEntries.end()) return f->type();
    return user::utype::UNKNOWN;
}

bool ubook::insert(user &user)
{
    if (findUser(user.name(), user.passwd()) == user::UNKNOWN)
    {
        mEntries.push_back(std::move(user));
        saveToFile(config::fileUsers);
        return true;
    }
    return false;
}

bool ubook::remove(const uint &idx)
{
    if (idx <= uint(mEntries.size()))
    {
        mEntries.erase(std::next(mEntries.begin(), idx));
        saveToFile(config::fileUsers);
        return true;
    }
    return false;
}

ubook *ubook::getUbook()
{
    ubook *u = new ubook;
    u->loadFromFile(config::fileUsers);
    return u;
}

void ubook::touchFile()
{
    saveToFile(config::fileUsers);
}
