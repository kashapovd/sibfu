/**
 * @file habitant.h
 * @brief Заголовчный файл класса habitant.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef HABITANT_H
#define HABITANT_H

#include <QString>
#include <QDate>
#include <QDataStream>

/**
 * @brief Класс проживающего.
 */
class habitant
{
public:
    /**
     * @brief Cтруктура, хранящая информацию о проживающем.
     * Используется для перемещения этой информации внутри программы.
     */
    struct habitantData
    {
        QString fname;
        QString lname;
        QString patronymic;
        QDate birthDate;
        uint studentID;
        uint numOfCourse;
        QString group;
        uint roomNumber;
    };

    /// Конструктор класса.
    habitant() {}
    /**
     * @brief Дополнительный конструктор.
     * @param hd Указатель на структуру данных.
     */
    habitant(habitantData *hd);
    /// Устанавливает поля данных, равным полям в структуре @p.
    bool setData(habitantData *hd);
    /// Возвращает указатель на данные проживающего.
    habitantData *getData() const;

    /// Возвращает имя проживающего.
    const QString fname() const;
    /// Возвращает фамилию проживающего.
    const QString lname() const;
    /// Возвращает отчество проживающего.
    const QString patronymic() const;
    /// Возвращает дату рождения проживающего.
    const QDate birthDate() const;
    /// Возвращает номер студенческого билета проживающего.
    uint studentID() const;
    /// Возвращает номер курса обучения проживающего.
    uint numOfCourse() const;
    /// Возвращает наименование группы, в которой обучается проживащий.
    QString group() const;
    /// Возвращает номер комнаты проживающего.
    uint roomNumber() const;

private:
    /// Поле имени.
    QString mFname;
    /// Поле фамилии.
    QString mLname;
    /// Поле отчества.
    QString mPatronymic;
    /// Поле даты рождения.
    QDate mBirthDate;
    /// Поле номера студенческого билета.
    uint mStudentID;
    /// Поле номера курса обучения.
    uint mNumOfCourse;
    /// Поле номера группы обучения.
    QString mGroup;
    /// Поле номера комнаты проживания.
    uint mRoomNumber;
};

inline QDataStream &operator<< (QDataStream &ost, const habitant &h)
{
    ost << h.group() << h.roomNumber() << h.fname() << h.lname() << h.patronymic() << h.birthDate()
        << h.studentID() << h.numOfCourse();
    return ost;
}

inline QDataStream &operator>> (QDataStream &ist, habitant &h)
{
    habitant::habitantData hd;
    ist >> hd.group >> hd.roomNumber >> hd.fname >> hd.lname >> hd.patronymic;
    ist >> hd.birthDate >> hd.studentID >> hd.numOfCourse;
    h.setData(&hd);
    return ist;
}

#endif // HABITANT_H
