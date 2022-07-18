/**
 * @file config.h
 * @brief Файл конфигурации.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <QtGlobal>
#include <QString>

namespace config
{
    /**
     * @brief Название приложения.
     * @note QT_TRANSLATE_NOOP() используется, чтобы строки отображались в файле
     * строк для перевода на другие языки в контексте Config.
     */
    const char applicationName[] = QT_TRANSLATE_NOOP("Config", "dWell");
    /// Версия приложения.
    const char applicationVersion[] = "20210104";
    /// название файла, в котором записаны пользователи.
    const QString fileUsers = "users.dwl";
    /// название файла, в котором записаны комнаты общежития.
    const QString fileRooms = "rooms.dwl";
    /// название файла, в котором записаны сведения об общежитии.
    const QString dormConf = "dorm.dwl";
}

#endif // CONFIG_H
