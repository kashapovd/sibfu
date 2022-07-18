/**
 * @file main.cpp
 * @brief Файл, содержащий точку входа в программу.
 * @author Кашапов Ярослав
 * @date 2021
 */

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
