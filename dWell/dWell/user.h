/**
 * @file user.h
 * @brief Заголовчный файл класса user.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef USER_H
#define USER_H

#include "bookentry.h"

#include <QString>

/**
 * @brief Класс комнаты.
 * Наследуется от класса bookEntry.
 */
class user : public bookEntry
{
public:
    /// Перечислитель, содержащий возможные типы пользователей.
    enum utype {ADMIN, COMMANDANT, STUDENT, UNKNOWN};
    /// Конструктор по умолчанию.
    user() {}
    /**
     * @brief Дополнительный конструктор. Устанавливает
     * соответствующие поля объекта класса user.
     * @param name Имя пользователя
     * @param pass Пароль пользователя.
     * @param type Тип пользователя.
     */
    user(QString name, QString pass, utype type);
    /// Возвращает имя пользователя.
    const QString name() const;
    /// Возвращает пароль пользователя.
    const QString passwd() const;
    /// Возвращает тип пользователя.
    utype type() const;
    /// Устанавливает поля объекта пользователя.
    bool setData(QString &name, QString &pass, utype &type);

private:
    /// Поле имени пользователя.
    QString mName;
    /// Поле пароля пользователя.
    QString mPasswd;
    /// Поле типа пользователя.
    utype mType;

protected:
    void write(QDataStream &ost) const override;
    void read(QDataStream &ist) override;
};

#endif // USER_H
