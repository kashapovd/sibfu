/**
 * @file writereadableitem.h
 * @brief Заголовчный файл класса writeReadableItem.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef WRITEREADABLEITEM_H
#define WRITEREADABLEITEM_H

#include <QDataStream>

/**
 * @brief Абстрактный класс обекта, способного
 * записываться и считываться из потока.
 */
class writeReadableItem
{
public:
    /// Конструктор по умолчанию.
    writeReadableItem() {}

protected:
    /// Определение виртуального метода для записи в поток.
    virtual void write(QDataStream &ost) const = 0;
    /// Определение виртуального метода для считывания из потока.
    virtual void read(QDataStream &ist) = 0;
};

#endif // WRITEREADABLEITEM_H
