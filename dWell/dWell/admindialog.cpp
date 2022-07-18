/**
 * @file admindialog.cpp
 * @brief Файл реализации класса adminDialog.
 * @author Кашапов Ярослав
 * @date 2021
 */

#include "admindialog.h"
#include "ui_admindialog.h"

#include "ubook.h"
#include "usereditdialog.h"
#include "tools.h"
#include "config.h"

#include <QMessageBox>
#include <set>

#define UNAME_COLUMN 0
#define HTYPE_COLUMN 1

adminDialog::adminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminDialog)
{
    ui->setupUi(this);
    m_ubook = ubook::getUbook();

    updateTable();
    ui->tableWidget->verticalHeader()->setVisible(false); // отключаем подпись строк таблицы
    connect(ui->tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged,
            [this]
    {
        // отключаем кнопку "удалить", если нет выделенных пользователей
        ui->removeButton->setDisabled(!ui->tableWidget->selectionModel()
                                                         ->hasSelection());
    });
}

adminDialog::~adminDialog()
{
    delete ui;
}

void adminDialog::on_addButton_clicked()
{
    userEditDialog userAddtDlg(this);
    user *u = new user;
    userAddtDlg.setUser(u);
    userAddtDlg.setWindowTitle("Создание пользователя");
    if (userAddtDlg.exec() != userEditDialog::Accepted)
        return;
    m_ubook->insert(*u);
    updateTable();
}

void adminDialog::on_removeButton_clicked()
{
    QModelIndexList idc = ui->tableWidget->selectionModel()->selectedRows();
    std::set<uint> rows;
    // Вставляем номера выбранных строк в rows
    for (const auto &i : qAsConst(idc))
        rows.insert(i.row());

    QString usersToDelete;

    // если выбрана одна заметка
    if (rows.size() == 1)
        usersToDelete = (*m_ubook)[idc.first().row()].name();
    else // если выбрано несколько
        for (const auto &it : rows)
            usersToDelete.append(tr("<br>• ") + (*m_ubook)[it].name());

    QMessageBox::StandardButtons ret = QMessageBox::question(this, "Удаление пользователя",
                                                             (rows.size() == 1) ? QString("Вы действительно хотите "
                                                                 "удалить пользователя <b><i>%1</i></b>?").arg(usersToDelete) :
                                                                                  QString("Вы действительно хотите "
                                                                 "удалить пользователей <b><i>%1</i></b>").arg(usersToDelete),
                                                             QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::No) return;

    for (auto it = rows.rbegin(); it != rows.rend(); ++it)
        m_ubook->remove(*it);
    updateTable();
}

void adminDialog::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    userEditDialog userEditDlg(this);
    user *u = const_cast<user *>(&(*m_ubook)[index.row()]);
    userEditDlg.setUserForEdit(u);
    userEditDlg.setWindowTitle("Редактирование пользователя");
    if (userEditDlg.exec() != userEditDialog::Accepted) return;
    m_ubook->saveToFile(config::fileUsers);
    updateTable();
}

void adminDialog::updateTable()
{
    ui->tableWidget->setRowCount(0);
    for (uint i = 0; i < m_ubook->size(); i++)
    {
        auto user = (*m_ubook)[i];
        QTableWidgetItem *username = new QTableWidgetItem(user.name());
        QTableWidgetItem *usertype = new QTableWidgetItem(tools::userTypeToStr(user.type()));
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, UNAME_COLUMN, username);
        ui->tableWidget->setItem(i, HTYPE_COLUMN, usertype);
    }
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
}

void adminDialog::on_logoutButton_clicked()
{
    this->close();
}
