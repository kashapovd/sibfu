/**
 * @file dormitory.h
 * @brief Заголовчный файл класса dormitory.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef DORMITORY_H
#define DORMITORY_H

#include <cstdint>
#include <QString>
#include <QDataStream>

/**
 * @brief Класс, предоставляющий сведения об общежитии.
 */
class dormitory
{
public:
    /// Конструктор по умолчанию.
    dormitory() {}
    /**
     * @brief Дополнительный конструктор.
     * @param name Наименование общежития.
     * @param roomCapacity Количество мест в одной комнате.
     * @param dormCapacity Количество комнат в общежитии.
     */
    dormitory(QString &name, uint &roomCapacity, uint &dormCapacity);
    /// Возвращает наименование комнаты
    const QString name();
    /// Возвращает емкость одной комнаты
    uint roomCapacity();
    /// Возвращает количество комнат в общежитии.
    uint capacity();
    /// Статический метод, возвращающий указатель на созданный
    /// объект класса dormitory с загруженными данными
    static dormitory *getDormCfg();

private:
    /// Количество мест в комнате.
    uint mRoomCapacity;
    /// Количество комнат в общежитии.
    uint mDormCapacity;
    /// Наименование общежития.
    QString mDormName;

    void load(QDataStream &ost);
    void save(QDataStream &ist);
    void loadFromFile(const QString &filename);
    void saveToFile(const QString &filename);
};

#endif // DORMITORY_H
