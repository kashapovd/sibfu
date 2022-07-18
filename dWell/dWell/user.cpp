/**
 * @file user.cpp
 * @brief Файл реализации класса user.
 * @author Кашапов Ярослав
 * @date 2021
 */

#include "user.h"

user::user(QString name, QString passwd, utype type) : mName(name), mPasswd(passwd), mType(type) {}

const QString user::name() const
{
    return mName;
}

const QString user::passwd() const
{
    return mPasswd;
}

user::utype user::type() const
{
    return mType;
}

bool user::setData(QString &name, QString &passwd, utype &type)
{
    name = name.trimmed();
    passwd = passwd.trimmed();
    if (!name.isEmpty() and !passwd.isEmpty() and
            (type == user::ADMIN or type == user::COMMANDANT or type == user::STUDENT))
    {
        mName = name;
        mPasswd = passwd;
        mType = type;
        return true;
    }
    return false;
}

void user::write(QDataStream &ost) const
{
    ost << mName << mPasswd << mType;
}

void user::read(QDataStream &ist)
{
    ist >> mName >> mPasswd >> mType;
}
