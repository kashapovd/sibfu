/**
 * @file habitanteditdialog.h
 * @brief Заголовчный файл класса habitantEditDialog.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef HABITANTEDITDIALOG_H
#define HABITANTEDITDIALOG_H

#include <QDialog>

// Объявляем класс habitant, чтобы ниже можно было упоминать указатели на него,
// не включая определение класса. Это увеличивает скорость сборки проекта за
// счёт уменьшения количества обрабатываемых заголовочных файлов.
class habitant;

// Объявляем класс Ui::habitantEditDialog, чтобы ниже можно было упоминать указатели на него,
// не включая определение класса. Этот класс создаётся автоматически из UI-файла.
// Данное объявление также было создано автоматически, когда Qt Creator
// добавлял в проект UI-файл и класс для него.
namespace Ui {
class habitantEditDialog;
}

/**
 * @brief Класс диалога редактирования проживающего
 * (его данных).
 */
class habitantEditDialog : public QDialog
{
    /// Для использования слотов и/или сигналов необходим макрос Q_OBJECT внутри класса.
    Q_OBJECT

public:
    /**
     * @brief Конструктор с необязательным указанием родительского объекта.
     * @param parent Указатель на родительский объект.
     * @param availRooms Доступный для заселения комнаты.
     */
    habitantEditDialog(QWidget *parent, QStringList availRooms);
    /// Деструктор.
    ~habitantEditDialog();
    /// Установливает редактируемого проживающего.
    void setHabitant(habitant *h) {mHabitant = h;};

private:
    /// Указатель на редактируемого проживающего.
    habitant *mHabitant;
    /// Указатель на сгенерированный интерфейс.
    Ui::habitantEditDialog *ui;

private slots:
    /// Обрабатывает подтверждение диалога.
    void accept();
};

#endif // HABITANTEDITDIALOG_H
