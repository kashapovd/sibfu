/**
 * @file rbook.h
 * @brief Заголовчный файл класса rbook.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef RBOOK_H
#define RBOOK_H

#include <QVector>

#include "room.h"
#include "book.h"

/**
 * @brief Класс контейнер комнат.
 * Наследуется от класса book.
 * Добавляет необходимый функционал для доступа к контейнеру комнат.
 */
class rbook : public book<room>
{
public:
    /// Конструктор по умолчанию
    rbook() {}

    /**
    * @brief Производит заселение проживающего в комнату.
    * @param rn Номер комнаты.
    * @param h Указатель на данные проживающего.
    */
    void checkin(uint rn, habitant *h);
    /**
    * @brief Производит выселение проживающего из комнаты.
    * @param rn Номер комнаты.
    * @param sid Номер студенческого билета выселяемого.
    */
    void checkout(uint rn, uint sid);

    /// Возвращает сумму заполненных мест во всех комнатах.
    uint fullness() const;
    /// Устанавливает количество комнат в контейнере равным @p cap.
    void setCapacity(uint &cap);
    /// Статический метод, возвращающий указатель на созданный
    /// объект класса rbook с загруженны контейнером.
    static rbook *getRbook();
    /// Возвращает указатель на объект проживающего с
    /// номером студенческого билета, равным @p sid
    const habitant *getHabitantBySid(uint &sid) const;
    /// Возвращает список доступных для заселения комнат.
    QStringList availRooms() const;
    /// Возвращает список доступных для заселения комнат, исключая @p.
    QStringList availRooms(uint &exludeRoomNumber) const;
    /// Возвращает логическое значание, которое отражает доступно ли
    /// заселение в общежитие.
    bool availableForCheckin() const;
    /// Генерирует файл данных контейнера.
    void touchFile(uint &dormCap, uint &roomCap);
};

#endif // RBOOK_H
