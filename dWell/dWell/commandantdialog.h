/**
 * @file commandantdialog.h
 * @brief Заголовчный файл класса commandantDialog.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef COMMANDANTDIALOG_H
#define COMMANDANTDIALOG_H

#include <QDialog>

// Объявляем класс rbook, чтобы ниже можно было упоминать указатели на него,
// не включая определение класса. Это увеличивает скорость сборки проекта за
// счёт уменьшения количества обрабатываемых заголовочных файлов.
class rbook;

// Объявляем класс Ui::commandantDialog, чтобы ниже можно было упоминать указатели на него,
// не включая определение класса. Этот класс создаётся автоматически из UI-файла.
// Данное объявление также было создано автоматически, когда Qt Creator
// добавлял в проект UI-файл и класс для него.
namespace Ui {
class commandantDialog;
}

/**
 * @brief Класс диалога панели коменданта.
 * Для функционирования необходима коллекция комнат.
 */
class commandantDialog : public QDialog
{
    /// Для использования слотов и/или сигналов необходим макрос Q_OBJECT внутри класса.
    Q_OBJECT

public:
    /**
     * @brief Конструктор с необязательным указанием родительского объекта.
     * @param parent Указатель на родительский объект.
     */
    explicit commandantDialog(QWidget *parent = nullptr);
    /// Деструктор
    ~commandantDialog();

private:
    /// Указатель на контейнер комнат.
    rbook *m_rbook;
    /// Указатель на сгенерированный интерфейс.
    Ui::commandantDialog *ui;

private slots:
    /// Обновляет таблицу проживающих в интерфейсе.
    void updateTable();
    /// Обновляет статистику о заполненности общежития.
    void updateSumLabel();
    /// Обработчик кнопки "Заселить".
    void on_checkinButton_clicked();
    /// Обработчик кнопки "Выйти".
    void on_pushButton_clicked();
    /// Обработчик кнопки "Выселить".
    void on_checkoutButton_clicked();
    /// Обработчик кнопки "Переселить".
    void on_relocButton_clicked();
    /// Обработчик кнопки "Выдать справку".
    void on_giveDocButton_clicked();
};

#endif // COMMANDANTDIALOG_H
