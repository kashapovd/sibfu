/**
 * @file relocationdialog.cpp
 * @brief Файл реализации класса relocationdialog.
 * @author Кашапов Ярослав
 * @date 2021
 */

#include "relocationdialog.h"
#include "ui_relocationdialog.h"
#include "habitant.h"

relocationDialog::relocationDialog(QWidget *parent, QStringList availRooms) :
    QDialog(parent),
    ui(new Ui::relocationDialog)
{
    ui->setupUi(this);
    ui->roomNumBox->addItems(availRooms);
}

relocationDialog::~relocationDialog()
{
    delete ui;
}

void relocationDialog::accept()
{
    auto hd = mHabitant->getData();
    auto newRoom = ui->roomNumBox->currentText().toUInt();
    hd->roomNumber = newRoom;
    mHabitant->setData(hd);
    QDialog::accept();
}

void relocationDialog::setHabitant(habitant *h)
{
    mHabitant = h;
    ui->habitantLabel->setText(QString("%1 %2 %3").arg(
                                   mHabitant->fname(),
                                   mHabitant->lname(),
                                   mHabitant->patronymic()));
    ui->curRoomLabel->setText(QString("%1").arg(mHabitant->roomNumber()));
}
