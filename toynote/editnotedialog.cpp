/**
 * @file editnotedialog.cpp
 * @brief Файл реализации класса EditNoteDialog.
 ***************************
 * @author Кирилл Пушкарёв
 * @date 2017
 ***************************
 * @author Кашапов Ярослав
 * @date 2020
 */
#include "editnotedialog.hpp"
// Заголовочный файл UI-класса, сгенерированного на основе editnotedialog.ui
#include "ui_editnotedialog.h"

#include <QMessageBox>

#include "note.hpp"

/**
* Конструирует объект класса с родительским объектом @a parent.
* Параметр @p parent имеет значение по умолчанию 0. Указывать родительский
* объект нужно, например чтобы дочерний объект был автоматически удалён
* при удалении родительского. Для EditNoteDialog родителем будет
* окно более высокого уровня, например главное.
*/
EditNoteDialog::EditNoteDialog(QWidget *parent) :
    QDialog(parent), // Передаём parent конструктору базового класса
    mUi(new Ui::EditNoteDialog) // Создаём объект Ui::EditNoteDialog
{
    // Отображаем GUI, сгенерированный из файла editnotedialog.ui, в данном окне
    mUi->setupUi(this);
    // инициализируем переменную notNewNote для избежания неопределённости
    notNewNote = false;
}

/**
* Отвечает за уничтожение объектов EditNoteDialog. Сюда можно поместить
* функции, которые надо выполнить перед уничтожением (например, закрыть
* какие-либо файлы или освободить память).
*/
EditNoteDialog::~EditNoteDialog()
{
    // Удаляем объект Ui::EditNoteDialog
    delete mUi;
}

Note *EditNoteDialog::note() const
{
    return mNote;
}

void EditNoteDialog::setNote(Note *note)
{
    mNote = note;
}

void EditNoteDialog::setNoteForEdit(Note *note)
{
    setNote(note);
    mUi->plainTextEdit->setPlainText(mNote->text());
    mUi->titleEdit->setText(mNote->title());
    notNewNote = true;
}

/**
 * Этот метод вызывается, когда пользователь подтверждает диалог, например
 * нажатием кнопки «OK». Метод изначально определён в базовом классе QDialog,
 * а здесь он переопределяется, то есть при вызове метода accept() у объекта
 * EditNoteDialog будет выполняться этот код, а не тот, что есть в классе
 * QDialog.
 *
 * Метод отвечает за обработку введённых пользователем в диалоге данных.
 * Он считывает данные из полей диалога и записывает их в соответствующие
 * атрибуты редактируемой заметки.
 */
void EditNoteDialog::accept()
{
    if ((mUi->titleEdit->text().isEmpty() and mUi->plainTextEdit->toPlainText().isEmpty()))
    {
        QMessageBox::warning(this, tr("Error"),
             (!notNewNote) ? tr("Unable to create the note with empty title and body") :
                             tr("Unable to save the note with empty title and body"),
                             QMessageBox::Ok);
        return;
    }
    if (mUi->titleEdit->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),
             (!notNewNote) ? tr("Unable to create the note with empty title") :
                             tr("Unable to save the note with empty title"),
                             QMessageBox::Ok);
        return;
    }
    if (mUi->plainTextEdit->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, tr("Error"),
             (!notNewNote) ? tr("Unable to create the note with empty body") :
                             tr("Unable to save the note with empty body"),
                             QMessageBox::Ok);
        return;
    }

    // Читаем заголовок и текст заметки из полей диалога и записываем
    // их в соответствующие атрибуты заметки по указателю mNote
    mNote->setTitle(mUi->titleEdit->text());
    // Получаем текст заметки из QPlainTextEdit
    mNote->setText(mUi->plainTextEdit->toPlainText());
    // Вызываем метод базового класса, чтобы он выполнил стандартные операции
    // при закрытии диалогового окна. Если не вызвать его, то диалог не
    // будет считаться подтверждённым и не закроется.
    // Таким образом, в данном случае метод EditNoteDialog::accept() не подменяет
    // собой метод QDialog::accept() совсем, а дополняет его.

    // сбрасываем флаг, если он был установлен
    if (notNewNote) notNewNote = false;
    QDialog::accept();
}
