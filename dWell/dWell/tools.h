/**
 * @file tools.h
 * @brief Заголовчный файл класса tools.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef TOOLS_H
#define TOOLS_H

#include <QString>
#include <QDialog>

#include "ubook.h"

/**
 * @brief Класс вспомогательных инструментов.
 */
class tools
{
public:
    /// Конструктор.
    tools() {}
    /// Преобразовывает тип пользователя в строку с названием типа.
    static QString userTypeToStr(const user::utype &);
    /// Производит начальную инициализацию системы
    static void initSystem(QWidget *);
    /// Возвращает указатель на интерфейс пользователя с типом @p type
    static QDialog *getUserInterface(QWidget *, const user::utype &type);
};

#endif // TOOLS_H
