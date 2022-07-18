/**
 * @file initsetupdialog.h
 * @brief Заголовчный файл класса initSetupDialog.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef INITSETUPDIALOG_H
#define INITSETUPDIALOG_H

#include <QDialog>

// Объявляем класс Ui::initSetupDialog, чтобы ниже можно было упоминать указатели на него,
// не включая определение класса. Этот класс создаётся автоматически из UI-файла.
// Данное объявление также было создано автоматически, когда Qt Creator
// добавлял в проект UI-файл и класс для него.
namespace Ui {
class initSetupDialog;
}

/**
 * @brief Класс диалога начальной настройки системы.
 */
class initSetupDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор с необязательным указанием родительского объекта.
     * @param parent Указатель на родительский объект.
     */
    explicit initSetupDialog(QWidget *parent = nullptr);
    /// Деструктор.
    ~initSetupDialog();

private:
    /// Указатель на сгенерированный интерфейс.
    Ui::initSetupDialog *ui;

public slots:
    /// Обрабатывает подтверждение диалога.
    void accept();
};

#endif // INITSETUPDIALOG_H
