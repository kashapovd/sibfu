/**
 * @file lottery.cpp
 * @brief Файл реализации класса lottery
 * @author Кашапов Ярослав
 * @date 2020
 */
#include <lottery.hpp>

#include <QRandomGenerator>

lottery::lottery(){}

/**
 * @brief Метод, имитирующий лотерею
 * @return Наименование приза
 */
const QString lottery::kick_the_bucket()
{
    // используем генератор случайных чисел операционной системы
    QRandomGenerator *rand = QRandomGenerator::system();
    // generateDouble() вернёт [0, 1)
    // 0.5 - шанс выигрыша. всего 20 билетов
    // n = 9 - последняя цифра в зачётке, поэтому
    // шанс равен (9+1)/20
    if (rand->generateDouble() < 0.5) {
        // bounded() вернёт [0, n)
        return prizes[rand->bounded(n)];
    }
    return tr("a mere nothing");
}
