/**
 * @file commandantdialog.cpp
 * @brief Файл реализации класса commandantDialog.
 * @author Кашапов Ярослав
 * @date 2021
 */

#include "commandantdialog.h"
#include "ui_commandantdialog.h"

#include "habitanteditdialog.h"
#include "relocationdialog.h"
#include "doc.h"
#include "dormitory.h"
#include "config.h"
#include "rbook.h"

#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QStandardPaths>
#include <QTextDocument>
#include <QFileInfo>

#define ROOM_COLUMN 0
#define SID_COLUMN 1
#define NAME_COLUMN 2
#define BDATE_COLUMN 3

commandantDialog::commandantDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::commandantDialog)
{
    ui->setupUi(this);
    m_rbook = rbook::getRbook();

    updateSumLabel();
    updateTable();

    ui->tableWidget->resizeColumnsToContents();

    ui->tableWidget->verticalHeader()->setVisible(false); // отключаем подпись строк таблицы

    connect(ui->tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged,
            [this]
    {
        // отключаем кнопку "удалить", если нет выделенных проживающих
        // или включаем, если они есть
        ui->checkoutButton->setDisabled(!ui->tableWidget->selectionModel()
                                                         ->hasSelection());
        // кнопка "переселить"
        ui->relocButton->setDisabled(!ui->tableWidget->selectionModel()
                                                         ->hasSelection());
        // кнопка "выдать справку"
        ui->giveDocButton->setDisabled(!ui->tableWidget->selectionModel()
                                                         ->hasSelection());
    });
}

commandantDialog::~commandantDialog() { delete ui; }

void commandantDialog::updateTable()
{
    ui->tableWidget->setRowCount(0);
    int row =0;
    auto roomCount = m_rbook->size();
    for (uint i=0; i < roomCount; i++)
    {
        auto room = (*m_rbook)[i];
        auto roomSize = room.size();
        for (uint j=0; j < roomSize; j++)
        {
            auto habitant = room[j];

            QTableWidgetItem *roomNumber = new QTableWidgetItem(QString("%1").arg(habitant.roomNumber()));
            QTableWidgetItem *name = new QTableWidgetItem(QString("%1 %2 %3")
                                                          .arg(habitant.fname(),
                                                               habitant.lname(),
                                                               habitant.patronymic()));

            QTableWidgetItem *bdate = new QTableWidgetItem(habitant.birthDate().toString("dd.MM.yyyy"));
            QTableWidgetItem *sid = new QTableWidgetItem(QString("%1").arg(habitant.studentID()));

            ui->tableWidget->insertRow (row);
            ui->tableWidget->setItem(row, ROOM_COLUMN, roomNumber);
            ui->tableWidget->setItem(row, SID_COLUMN, sid);
            ui->tableWidget->setItem(row, NAME_COLUMN, name);
            ui->tableWidget->setItem(row, BDATE_COLUMN, bdate);
            row++;
        }
    }
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
}

void commandantDialog::updateSumLabel()
{
    dormitory *d = dormitory::getDormCfg();
    ui->label->setText(QString("Заполненность: %1 из %2")
                       .arg(m_rbook->fullness())
                       .arg((d->roomCapacity()*d->capacity())));
}

void commandantDialog::on_checkinButton_clicked()
{
    if (!m_rbook->availableForCheckin())
    {
        QMessageBox::warning(this, "Ошибка", "Нет доступных мест", QMessageBox::Ok);
    }
    else
        {
            habitantEditDialog habAddtDlg(this, m_rbook->availRooms());
            habitant *h = new habitant;

            habAddtDlg.setHabitant(h);
            habAddtDlg.setWindowTitle("Заселение проживающего");

            if (habAddtDlg.exec() != habitantEditDialog::Accepted)
                return;

            m_rbook->checkin(h->roomNumber(), h);
        }
    updateSumLabel();
    updateTable();
}

void commandantDialog::on_pushButton_clicked()
{
    this->close();
}

void commandantDialog::on_checkoutButton_clicked()
{

    QMessageBox::StandardButtons ret = QMessageBox::question(this,
                                                             "Удаление пользователя",
                                                             "Вы действительно хотите выселить?",
                                                             QMessageBox::No | QMessageBox::Yes);
    if (ret == QMessageBox::No) return;

    int row = ui->tableWidget->currentIndex().row();
    auto room =  ui->tableWidget->item(row, ROOM_COLUMN)->text().toUInt();
    auto sid = ui->tableWidget->item(row, SID_COLUMN)->text().toUInt();
    m_rbook->checkout(room, sid);
    updateSumLabel();
    updateTable();
}

void commandantDialog::on_relocButton_clicked()
{
    int row = ui->tableWidget->currentIndex().row();
    auto curRoom =  ui->tableWidget->item(row, ROOM_COLUMN)->text().toUInt();
    auto sid = ui->tableWidget->item(row, SID_COLUMN)->text().toUInt();

    if (!m_rbook->availableForCheckin())
    {
        QMessageBox::warning(this, "Ошибка", "Нет доступных мест", QMessageBox::Ok);
    }
    else
        {
            auto oldh = m_rbook->getHabitantBySid(sid);
            relocationDialog relocDlg(this, m_rbook->availRooms(curRoom));
            habitant *newh = new habitant(oldh->getData());
            relocDlg.setHabitant(newh);
            relocDlg.setWindowTitle("Переселение проживающего");
            if (relocDlg.exec() != habitantEditDialog::Accepted)
            {
                return;
            }

            m_rbook->checkin(newh->roomNumber(), newh);
            m_rbook->checkout(oldh->roomNumber(), oldh->studentID());
        }
    updateTable();
}

void commandantDialog::on_giveDocButton_clicked()
{
    int row = ui->tableWidget->currentIndex().row();
    auto sid = ui->tableWidget->item(row, SID_COLUMN)->text().toUInt();
    auto h = m_rbook->getHabitantBySid(sid);

    QString filename = QString("dWell_%1_%2_%3").arg(h->fname()).arg(h->lname()).arg(h->studentID());
    if(QFileInfo(filename).suffix().isEmpty())
                filename.append(".pdf");

    auto path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(path + "/" + filename);

    QPrintDialog printDlg(&printer,this);
    printDlg.setWindowTitle("Печать справки");
    if (printDlg.exec() != QPrintDialog::Accepted)
        return;

    doc::generate(h, &printer);
}
