/**
 * @file bookentry.h
 * @brief Заголовчный файл класса bookEntry.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef BOOKENTRY_H
#define BOOKENTRY_H

#include "writereadableitem.h"

#include <QDataStream>

/**
 * @brief Класс шаблонного элемента контейнера системы.
 * Наследуется от класса writeReadableItem, определяя операторы >> и <<
 * над методами writeReadableItem::write и writeReadableItem::read.
 */
class bookEntry : public writeReadableItem
{
public:
    /// Конструктор класса по умолчанию
    bookEntry() {}
    /**
     * @brief Дружественное определение оператора <<.
     * @param ost поток, в который происходит запись.
     * @param e элемент, записываемый в поток.
     */
    friend QDataStream &operator<< (QDataStream &ost, const bookEntry &e);
    /**
     * @brief Дружественное определение оператора >>.
     * @param ost поток, из которого происходит чтение.
     * @param e элемент, считываемый из потока.
     */
    friend QDataStream &operator>> (QDataStream &ist, bookEntry &e);
};

/// Реализация оператора <<
inline QDataStream &operator<< (QDataStream &ost, const bookEntry &e)
{
    e.write(ost);
    return ost;
}

/// Реализация оператора >>
inline QDataStream &operator>> (QDataStream &ist, bookEntry &e)
{
    e.read(ist);
    return ist;
}

#endif // BOOKENTRY_H
