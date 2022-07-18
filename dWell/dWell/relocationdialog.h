/**
 * @file relocationdialog.h
 * @brief Заголовчный файл класса relocationDialog.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef RELOCATIONDIALOG_H
#define RELOCATIONDIALOG_H

#include <QDialog>

// Объявляем класс ubook, чтобы ниже можно было упоминать указатели на него,
// не включая определение класса. Это увеличивает скорость сборки проекта за
// счёт уменьшения количества обрабатываемых заголовочных файлов.
class habitant;

// Объявляем класс Ui::relocationDialog, чтобы ниже можно было упоминать указатели на него,
// не включая определение класса. Этот класс создаётся автоматически из UI-файла.
// Данное объявление также было создано автоматически, когда Qt Creator
// добавлял в проект UI-файл и класс для него.
namespace Ui {
class relocationDialog;
}

/**
 * @brief Класс диалога переселения проживающего.
 */
class relocationDialog : public QDialog
{
    /// Для использования слотов и/или сигналов необходим макрос Q_OBJECT внутри класса.
    Q_OBJECT

public:
    /**
     * @brief Конструктор с необязательным указанием родительского объекта.
     * @param parent Указатель на родительский объект.
     * @param availRooms Список доступных для переселения комнат
     */
    relocationDialog(QWidget *parent, QStringList availRooms);
    /// Деструктор.
    ~relocationDialog();
    /// Уставливает переселяемого проживающего.
    void setHabitant(habitant *h);

private:
    /// Указатель на переселяемого проживающего.
    habitant *mHabitant;
    /// Указатель на сгенерированный интерфейс.
    Ui::relocationDialog *ui;

private slots:
    /// Обрабатывает подтверждение диалога.
    void accept();
};

#endif // RELOCATIONDIALOG_H
