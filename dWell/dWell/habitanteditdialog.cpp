/**
 * @file habitanteditdialog.cpp
 * @brief Файл реализации класса habitantEditDialog.
 * @author Кашапов Ярослав
 * @date 2021
 */

#include "habitanteditdialog.h"
#include "ui_habitanteditdialog.h"
#include "habitant.h"

#include <QMessageBox>
#include <QIntValidator>
#include <limits>

habitantEditDialog::habitantEditDialog(QWidget *parent, QStringList availRooms) :
    QDialog(parent),
    ui(new Ui::habitantEditDialog)
{
    ui->setupUi(this);
    ui->roomNumBox->addItems(availRooms);
}

habitantEditDialog::~habitantEditDialog() {delete ui;}

void habitantEditDialog::accept()
{
    habitant::habitantData hb;

    hb.lname = ui->lnameEdit->text().trimmed();
    hb.fname = ui->fnameEdit->text().trimmed();
    hb.patronymic = ui->patroEdit->text().trimmed();
    hb.birthDate = ui->bdateEdit->date();

    QIntValidator vsid(0, std::numeric_limits<uint>::max(), this);
    int vpos = 0;
    QString sid = ui->studentID->text().trimmed();
    if (vsid.validate(sid, vpos) == QValidator::Invalid)
    {
        QMessageBox::warning(this, "Ошибка", "Номер студ. книжки - число!", QMessageBox::StandardButton::Ok);
        ui->studentID->clear();
        return;
    }

    hb.studentID = sid.toInt();
    hb.group = ui->groupEdit->text();
    hb.numOfCourse = ui->courseBox->currentText().toUInt();
    hb.roomNumber = ui->roomNumBox->currentText().toUInt();
    if(!mHabitant->setData(&hb))
        QMessageBox::warning(this, "Ошибка", "Введены некорректные данные", QMessageBox::StandardButton::Ok);
    else
        QDialog::accept();
}
