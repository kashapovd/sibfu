/**
 * @file rbook.cpp
 * @brief Файл реализации класса rbook.
 * @author Кашапов Ярослав
 * @date 2021
 */

#include "rbook.h"
#include "config.h"

#include <QFile>
#include <QDataStream>

bool rbook::availableForCheckin() const {return !availRooms().empty();}

uint rbook::fullness() const
{
    uint count=0;
    for (const auto &room : mEntries)
        count += room.size();
    return count;
}

void rbook::touchFile(uint &dormCap, uint &roomCap)
{
    for (uint i=0; i < dormCap; i++)
    {
        room *r = new room;
        r->setCapacity(roomCap);
        uint n = i+1;
        r->setNumber(n);
        mEntries.push_back(*r);
    }
    saveToFile(config::fileRooms);
}

QStringList rbook::availRooms() const
{
    QStringList rooms;
    for (const auto &room : qAsConst(mEntries))
    {
        if (room.availableForCheckin())
            rooms << QString("%1").arg(room.number());
    }
    return rooms;
}

QStringList rbook::availRooms(uint &exludeRoomNumber) const
{
    QStringList rooms;
    for (const auto &room : qAsConst(mEntries))
    {
        if (room.number() == exludeRoomNumber)
            continue;
        if (room.availableForCheckin())
            rooms << QString("%1").arg(room.number());
    }
    return rooms;
}

void rbook::setCapacity(uint &cap)
{
    mEntries.reserve(cap);
}

rbook *rbook::getRbook()
{
    rbook *rb = new rbook;
    rb->loadFromFile(config::fileRooms);
    return rb;
}

void rbook::checkin(uint roomNumber, habitant *h)
{
    mEntries[roomNumber-1].checkin(*h);
    saveToFile(config::fileRooms);
    //emit dataChanged();
}

void rbook::checkout(uint roomNumber, uint sid)
{
    //if (mEntries[roomNumber-1].checkout(sid))
    //emit dataChanged();
    mEntries[roomNumber-1].checkout(sid);
    saveToFile(config::fileRooms);
}

const habitant *rbook::getHabitantBySid(uint &sid) const
{
    for(const auto &it : qAsConst(mEntries))
    {
        for (uint i = 0; i < it.size(); i++)
            if (it[i].studentID() == sid)
                return &it[i];
    }
    return nullptr;
}
