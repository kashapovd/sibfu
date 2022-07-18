#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QIODevice>
#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <dbdriver.cpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->modeButtonGroup->setId(ui->mode1RadioButton, 1);
    ui->modeButtonGroup->setId(ui->mode2RadioButton, 2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_execPushButton_clicked()
{
    QMessageBox::information(this, tr("Нажата кнопка выполнения"), tr("Выбран режим %1").arg(ui->modeButtonGroup->checkedId()));

    QString out_text;

    QTextStream ost(&out_text, QIODevice::WriteOnly);
    ost << tr("Текстовый файл: ") << ui->textFileLineEdit->text() << "\n"
        << tr("Двоичный файл: ") << ui->binFileLineEdit->text() << "\n"
        << tr("Режим: ") << ui->modeButtonGroup->checkedId() << "\n";

    dbdriver dbiface(ui->textFileLineEdit->text(), ui->binFileLineEdit->text()); // передаём пути файлов в класс,
                                                                                 // отвечающий за работу режимов программы
                                                                                 // в соответствии с заданием
    dbiface.work(ui->modeButtonGroup->checkedId(), ost); // выполняем работу по заданию в соответсвии с режимом

    ui->outTextEdit->setPlainText(out_text);

}
