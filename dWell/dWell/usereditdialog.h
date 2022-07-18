/**
 * @file userEditdialog.h
 * @brief Заголовчный файл класса userEditDialog.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef USEREDITDIALOG_H
#define USEREDITDIALOG_H

#include <QDialog>

// Объявляем классы ubook и user, чтобы ниже можно было упоминать указатели на них,
// не включая определение класса. Это увеличивает скорость сборки проекта за
// счёт уменьшения количества обрабатываемых заголовочных файлов.
class ubook;
class user;

// Объявляем класс Ui::userEditDialog, чтобы ниже можно было упоминать указатели на него,
// не включая определение класса. Этот класс создаётся автоматически из UI-файла.
// Данное объявление также было создано автоматически, когда Qt Creator
// добавлял в проект UI-файл и класс для него.
namespace Ui {
class userEditDialog;
}

/**
 * @brief Класс диалога редактирования пользователя.
 */
class userEditDialog : public QDialog
{
    /// Для использования слотов и/или сигналов необходим макрос Q_OBJECT внутри класса.
    Q_OBJECT

public:
    /**
     * @brief Конструктор с необязательным указанием родительского объекта.
     * @param parent Указатель на родительский объект.
     */
    explicit userEditDialog(QWidget *parent);
    /// Деструктор.
    ~userEditDialog();
    /// Устанавливает нового пользователя для редактирования.
    void setUser(user *u);
    /// Устанавливает существующего пользователя для редактирования.
    void setUserForEdit(user *u);

private:
    /// Режим редактирования: новый пользователь или существующий.
    bool editMode;
    /// Указатель на контейнер пользователей.
    ubook *m_ubook;
    /// Указатель на редактируемого пользователя.
    user *m_user;
    /// Указатель на сгенерированный интерфейс.
    Ui::userEditDialog *ui;

private slots:
    /// Обрабатывает подтверждение диалога.
    void accept();
    void on_usernameEdit_textChanged(const QString &username);
    void on_passwdEdit_textChanged(const QString &passwd);
};

#endif // USEREDITDIALOG_H
