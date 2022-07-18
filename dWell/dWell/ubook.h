/**
 * @file ubook.h
 * @brief Заголовчный файл класса ubook.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef UBOOK_H
#define UBOOK_H

#include "book.h"
#include "user.h"

#include <QVector>

/**
 * @brief Класс контейнер пользователей.
 * Наследуется от класса book.
 * Добавляет необходимый функционал для доступа к контейнеру book.
 */
class ubook : public book<user>
{
public:
    /// Конструктор по умолчанию
    ubook() {}

    /**
     * @brief Ищет пользователя с указанным именем и паролем.
     * @param name Имя пользователя.
     * @param passwd Пароль пользователя.
     * @return Тип пользователя.
     */
    user::utype findUser(const QString &name, const QString &passwd) const;
    /**
     * @brief Ищет пользователя с указанным именем.
     * @param name Имя пользователя.
     * @return Тип пользователя.
     */
    user::utype findUserByName(const QString &name) const;

    /// Создаёт в контейнере запись о пользователе @p user
    bool insert(user &user);
    /// Извлекает из контейнера запись о пользователе, который соответствует позиции @p idx
    bool remove(const uint &idx);
    /// Статический метод, возвращающий указатель на созданный
    /// объект класса ubook с загруженны контейнером.
    static ubook *getUbook();
    /// Генерирует файл данных контейнера.
    void touchFile();
};

#endif // UBOOK_H
