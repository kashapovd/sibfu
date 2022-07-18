/**
 * @file dormitory.cpp
 * @brief Файл реализации класса dormitory.
 * @author Кашапов Ярослав
 * @date 2021
 */

#include "dormitory.h"
#include "config.h"

#include <QFile>

dormitory::dormitory(QString &name, uint &roomCapacity, uint &dormCapacity)
{
    mDormName = name;
    mRoomCapacity = roomCapacity;
    mDormCapacity = dormCapacity;
    saveToFile(config::dormConf);
}

const QString dormitory::name()
{
    return mDormName;
}

uint dormitory::roomCapacity()
{
    return mRoomCapacity;
}

uint dormitory::capacity()
{
    return mDormCapacity;
}

dormitory *dormitory::getDormCfg()
{
    dormitory *d = new dormitory;
    d->loadFromFile(config::dormConf);
    return d;
}

void dormitory::save(QDataStream &ost)
{
    ost << mDormName << mRoomCapacity << mDormCapacity;
    // Если возникла ошибка, запускаем исключительную ситуацию
    if (ost.status() == QDataStream::WriteFailed)
    {
        throw std::runtime_error(QObject::tr("Write to the stream failed").toStdString());
    }
}

void dormitory::saveToFile(const QString &filename)
{
    QFile dormConfFile(filename);
    dormConfFile.open(QIODevice::WriteOnly);
    QDataStream ost(&dormConfFile);
    save(ost);
    dormConfFile.close();
}

void dormitory::loadFromFile(const QString &filename)
{
    QFile dormConfFile(filename);
    // Открываем файл только для чтения
    if (!dormConfFile.open(QIODevice::ReadOnly))
    {
        throw std::runtime_error((QObject::tr("open(): ") + dormConfFile.errorString()).toStdString());
    }
    QDataStream ist(&dormConfFile);
    load(ist);
    dormConfFile.close();
}

void dormitory::load(QDataStream &ist)
{
    while (!ist.atEnd())
    {
        ist >> mDormName >> mRoomCapacity >> mDormCapacity;
        // Если возникла ошибка, запускаем исключительную ситуацию
        if (ist.status() == QDataStream::ReadCorruptData)
        {
            throw std::runtime_error(QObject::tr("Corrupt data were read from the stream").toStdString());
        }
    }
}
