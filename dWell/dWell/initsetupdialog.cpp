/**
 * @file initsetupdialog.cpp
 * @brief Файл реализации класса initSetupDialog.
 * @author Кашапов Ярослав
 * @date 2021
 */

#include "initsetupdialog.h"
#include "ui_initsetupdialog.h"

#include "ubook.h"
#include "dormitory.h"
#include "rbook.h"

#include <QMessageBox>

initSetupDialog::initSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::initSetupDialog) {ui->setupUi(this);}

initSetupDialog::~initSetupDialog() {delete ui;}

void initSetupDialog::accept()
{
    QString dormName = ui->dormName->text().trimmed();
    if(dormName.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Введите название общежития", QMessageBox::Ok);
        return;
    }

    uint roomCap = ui->comboBox->currentText().toUInt();
    uint dormCap = ui->dormCapBox->text().toUInt();
    dormitory dorm(dormName, roomCap, dormCap);

    QString adminName = ui->admiLogin->text().trimmed();
    QString adminPasswd = ui->adminPasswd->text().trimmed();

    if(adminName.isEmpty() or adminPasswd.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Некорректные данные учтёной записи", QMessageBox::Ok);
        return;
    }

    //user admin(adminName, adminPasswd, user::utype::ADMIN);
    user admin;
    user::utype t = user::utype::ADMIN;
    admin.setData(adminName, adminPasswd, t);
    ubook usersbook;
    usersbook.insert(admin);

    rbook rb;
    rb.touchFile(dormCap, roomCap);

    QDialog::accept();
}
