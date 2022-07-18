/**
 * @file studentdialog.h
 * @brief Заголовчный файл класса studentDialog.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef STUDENTDIALOG_H
#define STUDENTDIALOG_H

#include <QDialog>

// Объявляем класс Ui::adminDialog, чтобы ниже можно было упоминать указатели на него,
// не включая определение класса. Этот класс создаётся автоматически из UI-файла.
// Данное объявление также было создано автоматически, когда Qt Creator
// добавлял в проект UI-файл и класс для него.
namespace Ui {
class studentDialog;
}

/**
 * @brief Класс диалога студента.
 */
class studentDialog : public QDialog
{
    /// Для использования слотов и/или сигналов необходим макрос Q_OBJECT внутри класса.
    Q_OBJECT

public:
    /**
     * @brief Конструктор с необязательным указанием родительского объекта.
     * @param parent Указатель на родительский объект.
     */
    explicit studentDialog(QWidget *parent = nullptr);
    /// Деструктор.
    ~studentDialog();

private:
    /// Указатель на сгенерированный интерфейс.
    Ui::studentDialog *ui;
};

#endif // STUDENTDIALOG_H
