/**
 * @file mainwindow.h
 * @brief Заголовчный файл класса MainWindow.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Класс диалога входа в систему.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор с необязательным указанием родительского объекта.
     * @param parent Указатель на родительский объект.
     */
    MainWindow(QWidget *parent = nullptr);
    /// Деструктор.
    ~MainWindow();

private:
    /// Указатель на сгенерированный интерфейс.
    Ui::MainWindow *ui;

private slots:
    /// Обрабатывает нажатие на кнопку "О Qt" в меню.
    void about_qt();
    /// Обрабатывает нажатие на кнопку "О программе" в меню.
    void about_dwell();
    /// Обрабатывает нажатие на кнопку "Об авторах" в меню.
    void about_autors();
    /// Обрабатывает нажатие на кнопку "Войти".
    void on_loginButton_clicked();
};
#endif // MAINWINDOW_H
