/**
 * @file tools.cpp
 * @brief Файл реализации класса tools.
 * @author Кашапов Ярослав
 * @date 2021
 */

#include "tools.h"
#include "config.h"

#include "initsetupdialog.h"
#include "admindialog.h"
#include "commandantdialog.h"
#include "studentdialog.h"

#include <QFile>
#include <QMessageBox>

QString tools::userTypeToStr(const user::utype &t)
{
    switch (t)
    {
        case user::utype::ADMIN:
            return QString("админ");
        case user::utype::COMMANDANT:
            return QString("комендант");
        case user::utype::STUDENT:
            return QString("студент");
        default:
            return QString();
    }
}

void tools::initSystem(QWidget *parent)
{
    if (!QFile(config::fileUsers).exists())
    {
        QMessageBox::warning(parent, "Ошибка", "<b>Система не инсталлирована<b>\n"
                                             "Будет открыто окно начальной настройки.",
                             QMessageBox::Ok);
        initSetupDialog *initDlg = new initSetupDialog(parent);
        initDlg->setWindowTitle("Мастер начальной настройки");
        initDlg->exec();
    }
}

QDialog *tools::getUserInterface(QWidget *parent, const user::utype &t)
{
    switch (t)
    {
        case user::utype::ADMIN:
        {
            adminDialog *adminDlg = new adminDialog(parent);
            adminDlg->setWindowTitle("Панель администрирования");
            return adminDlg;
        }
        break;
        case user::utype::COMMANDANT:
        {
            commandantDialog *comDlg = new commandantDialog(parent);
            comDlg->setWindowTitle("Панель управления проживающими");
            return comDlg;
        }
        break;
        case user::utype::STUDENT:
        {
            studentDialog *studDlg = new studentDialog(parent);
            studDlg->setWindowTitle("Личный кабинет студента");
            return studDlg;
        }
        default:
        return nullptr;
    }
}
