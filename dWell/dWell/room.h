/**
 * @file room.h
 * @brief Заголовчный файл класса room.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef ROOM_H
#define ROOM_H

#include "bookentry.h"
#include "habitant.h"

#include <QString>

/**
 * @brief Класс комнаты.
 * Наследуется от класса bookEntry.
 * Содержит контейнер проживающих в комнате.
 */
class room : public bookEntry
{
public:
    /// Конструктор по умолчанию
    room() {}

    /**
    * @brief Производит заселение проживающего в комнату.
    * @param h Указатель на данные проживающего.
    */
    void checkin(habitant h);
    /**
    * @brief Производит выселение проживающего из комнаты.
    * @param sid Номер студенческого билета выселяемого.
    */
    bool checkout(uint sid);
    /// Возвращает номер комнаты проживавющего.
    uint number() const;
    /// Возвращает количество мест в комнате.
    uint capacity() const;
    /// Возвращает количество занятых мест.
    uint size() const;
    /// Возвращает количество свободных мест.
    uint freeSlots() const;
    /**
     * @brief Оператор [].
     * @param idx Индекс читаемого проживающего.
     * @return Константная ссылка на читаемого проживающего.
     */
    const habitant &operator[](uint idx) const;
    /// Устанавливает количество мест в комнате равным @p n.
    void setCapacity(uint &n);
    /// Устанавливает номер комнаты равным @p n.
    void setNumber(uint &n);
    /// Освобождает все места в комнате.
    void clear();
    /// Возвращает логическое значение, которое отражает пуста ли комната.
    bool isEmpty() const;
    /// Возвращает логическое значение, которое отражает доступна
    /// ли комната для заселения.
    bool availableForCheckin() const;
    /// Возвращает итератор на проживающего с номером студ. билета @p sid.
    QVector<habitant>::iterator findBySid(uint sid);

private:
    /// Поле номера комнаты.
    uint mNumber;
    /// Контейнер проживающих.
    QVector<habitant> mHabitants;

protected:
    /**
     * @brief Определение базового метода записи комнаты в поток
     * @param ost Ссылка на поток.
     */
    void write(QDataStream &ost) const override;
    /**
     * @brief Определение базового метода считывания комнаты из потока
     * @param ist Ссылка на поток.
     */
    void read(QDataStream &ist) override;
};

#endif // ROOM_H
