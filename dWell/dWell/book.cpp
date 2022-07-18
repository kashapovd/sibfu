/**
 * @file book.cpp
 * @brief Файл реализации класса book.
 * @author Кашапов Ярослав
 * @date 2021
 */

#include "book.h"
#include "config.h"
#include "user.h"
#include "room.h"

#include <QFile>
#include <QString>

template <typename entry>
void book<entry>::saveToFile(const QString &filename) const
{
    QFile bookfile(filename);
    bookfile.open(QIODevice::WriteOnly);
    QDataStream ost(&bookfile);
    write(ost);
    bookfile.close();
}

template <typename entry>
void book<entry>::loadFromFile(const QString &filename)
{
    QFile bookfile(filename);
    if (!bookfile.open(QIODevice::ReadOnly))
        throw std::runtime_error((QString("open(): ") +
                                  bookfile.errorString())
                                 .toStdString());
    QDataStream ist(&bookfile);
    read(ist);
    bookfile.close();
}

/**
 * Возвращает ссылку на элемент с индексом @a idx. Слово @c const после
 * списка параметров означает, что это константная версия метода,
 * она не может изменять данные класса. Результат также имеет квалификатор
 * @c const, т. е. по этой ссылке элемент нельзя изменить.
 *
 * Можно было бы определить метод, позволяющий изменить заметку. Его объявление
 * выглядело бы так:
 * @code
 * Note &operator[](uint idx);
 * @endcode
 * В данном случае делать этого нельзя, поскольку возвращённая ссылка на элемент
 * неподконтрольна данному классу и он не имеет возможности узнать,
 * было ли изменение и когда это произошло, а значит не может
 * уведомить присоединённые виды о том, что данные изменились.
 */
template <typename entry>
const entry &book<entry>::operator[](uint idx) const
{
    return mEntries[idx];
}

template <typename entry>
uint book<entry>::size() const
{
    return mEntries.size();
}

/**
 * @brief Переопределение наследуемого метода writeReadableItem::write
 */
template <typename entry>
void book<entry>::write(QDataStream &ost) const
{
    ost << mEntries.size();
    for (const auto &e : mEntries)
    {
        ost << e;
        if (ost.status() == QDataStream::WriteFailed)
            throw std::runtime_error(QString("Write to the stream failed").toStdString());
    }
}

/**
 * @brief Переопределение наследуемого метода writeReadableItem::read
 */
template <typename entry>
void book<entry>::read(QDataStream &ist)
{
    mEntries.clear();
    uint size;
    ist >> size;
    for(uint i=0; i < size; i++)
    {
        entry e;
        ist >> e;
        if (ist.status() == QDataStream::ReadCorruptData)
            throw std::runtime_error(QString("Corrupt data were read from the stream").toStdString());
        else
            mEntries.push_back(e);
    }
}

/**
 * @brief Так как класс шаблонный, то, по требованиям c++,
 * необходимо его реализовать либо в заголовочном файле, либо
 * явно указать, какие типы возможны.
 */
template class book<user>;
template class book<room>;
