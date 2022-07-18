/**
 * @file lottery.hpp
 * @brief Заголовочный файл класса lottery.
 * @author Кашапов Ярослав
 * @date 2020
 */
#ifndef LOTTERY_HPP
#define LOTTERY_HPP

#include <QString>
#include <QObject> // tr()

/**
 * @brief Класс лотереи.
 *
 * Отвечает за иммитацию лотереи. 10 выигрышных билетов из 20
 */
class lottery : QObject
{
    Q_OBJECT

public:
    /// Конструктор по умолчанию
    lottery();
    /// Возвращает наименование приза, полученного в результате лотереи
    const QString kick_the_bucket();

private:

    /// Последняя цифра номера зачётной книжки + 1
    static const int n = 10;
    /// список призов
    const QString prizes[n] =
    {
        tr("Notepad"),
        tr("Chinese Arduino Nano"),
        tr("USB flash drive 64GB"),
        tr("Original Arduino Uno"),
        tr("RaspberryPi 4 8GB"),
        tr("Librem 5"),
        tr("Ultabook with 10-gen i7"),
        tr("Metcal soldering station"),
        tr("Brand new RTX 3080Ti"),
        tr("Pass to IKIT")
    };
};

#endif // LOTTERY_HPP
