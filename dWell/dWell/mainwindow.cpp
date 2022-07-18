/**
 * @file mainwindow.cpp
 * @brief Файл реализации класса MainWindow.
 * @author Кашапов Ярослав
 * @date 2021
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "admindialog.h"
#include "commandantdialog.h"
#include "studentdialog.h"
#include "initsetupdialog.h"

#include "config.h"
#include "user.h"
#include "tools.h"

#include <QMessageBox>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QFile>
#include <QLineEdit>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionAbout_Qt, &QAction::triggered, this, &MainWindow::about_qt);
    connect(ui->actionAbout_dWell, &QAction::triggered, this, &MainWindow::about_dwell);
    connect(ui->actionAutors, &QAction::triggered, this, &MainWindow::about_autors);

    tools::initSystem(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::about_qt()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::about_autors()
{
    QMessageBox aboutDlg(this);
    aboutDlg.setTextFormat(Qt::RichText);
    aboutDlg.setIcon(QMessageBox::Information);
    aboutDlg.setWindowTitle(tr("About autors"));
    aboutDlg.setText(tr("<a href=\"mailto:ykashapov-ki19@stud.sfu-kras.ru\">"
                        "Yaroslav Kashapov Fanizovich</a>, 2020."));
    aboutDlg.exec();
}

void MainWindow::about_dwell()
{
    QMessageBox aboutDlg(this);
    aboutDlg.setTextFormat(Qt::RichText);
    aboutDlg.setIcon(QMessageBox::Information);
    aboutDlg.setWindowTitle(tr("About %1").arg(config::applicationName));
    aboutDlg.setText(tr("%1 %2<br>"
            "Sourses: <a href=\"https://github.com/kashapovd/dWell\">github</a><br>"
            "License: MIT.<br>"
            "This application is dynamically linked against the<br>"
            "<a href=\"https://www.qt.io/developers/\">Qt Library</a> "
            "v. %3.")
            .arg(config::applicationName, config::applicationVersion, qVersion()));
    aboutDlg.exec();
}

void MainWindow::on_loginButton_clicked()
{
    auto *usersbook = ubook::getUbook();
    const QString login = ui->usernameEdit->text();
    const QString password = ui->passwdEdit->text();
    auto userType = usersbook->findUser(login, password);

    if (userType == user::UNKNOWN)
        QMessageBox::critical(this, "Ошибка", "Неверный пароль или логин", QMessageBox::Ok);
    else
    {
        auto userDialog = tools::getUserInterface(this, userType);
        userDialog->exec();
        delete userDialog;
    }
    ui->usernameEdit->clear();
    ui->passwdEdit->clear();
    //delete usersbook;
}
