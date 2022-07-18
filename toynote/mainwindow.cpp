/**
 * @file mainwindow.cpp
 * @brief Файл реализации класса MainWindow.
 ***************************
 * @author Кирилл Пушкарёв
 * @date 2017
 ***************************
 * @author Кашапов Ярослав
 * @date 2020
 */
#include "mainwindow.hpp"
// Заголовочный файл UI-класса, сгенерированного на основе mainwindow.ui
#include "ui_mainwindow.h"

#include <set>
#include <stdexcept>

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextStream>
#include <QMessageBox>
#include <QSaveFile>
#include <QtGlobal> // qVersion()
#include <QDesktopServices> // openUrl()
#include <QUrl>
#include <QDate> // currentDate()

#include "config.hpp"
#include "editnotedialog.hpp"
#include "lottery.hpp"

/**
 * Конструирует объект класса с родительским объектом @a parent.
 * Параметр @p parent имеет значение по умолчанию 0. Указывать родительский
 * объект нужно, например чтобы дочерний объект был автоматически удалён
 * при удалении родительского. В случае главного окна родителя можно не указывать.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), // Передаём parent конструктору базового класса
    mUi(new Ui::MainWindow) // Создаём объект Ui::MainWindow
{
    // Присоединяем сигналы, соответствующие изменению статуса записной книжки,
    // к слоту, обеспечивающему обновление заголовка окна
    connect(this, &MainWindow::notebookReady, this, &MainWindow::refreshWindowTitle);
    connect(this, &MainWindow::notebookClosed, this, &MainWindow::refreshWindowTitle);
    // Присоединяем сигнал создания записной книжки к лямбда-выражению,
    // устанавливающему в главном окне признак изменения (имеет ли текущий
    // документ несохранённые изменения). В заголовке окна при наличии
    // несохранённых изменений будет отображаться звёздочка или другое
    // обозначение, в зависимости от системы. "[this]" в лямбда-выражении
    // означает, что оно обращается к методам данного класса (в данном случае к
    // методу MainWindow::setWindowModified()).
    //
    // Лямбда-выражение — это выражение, результатом которого является
    // функциональный объект (объект, действующий как функция). В фигурных
    // скобках записывается тело этой функции. Таким образом, в данном случае
    // сигнал MainWindow::notebookCreated будет вызывать код, записанный в
    // фигурных скобках, то есть метод MainWindow::setWindowModified() с параметром true.
    connect(this, &MainWindow::notebookCreated, [this]
    {
        isNotebookSaved = false;
        setWindowModified(true);
    });
    connect(this, &MainWindow::notebookSaved, [this]
    {
        isNotebookSaved = true;
        setWindowModified(false);
    });

    // если книга была открыта, то она находится в актуальном состоянии
    // => сохранять нечего
    connect(this, &MainWindow::notebookOpened, [this]
    {
        isNotebookSaved = true;
        setWindowModified(false);
    });
    // Действия, связанные с закрытием записной книжки
    connect(this, &MainWindow::notebookClosed, [this] { disableUIActions(true);});
    // Действия, связанные с готовностью записной книжки.
    // Протовоположны действиям, связанным с закрытием записной книжки
    connect(this, &MainWindow::notebookReady, [this] { disableUIActions(false);});
    // Для корректной работы при открытии новых записных книжек, то есть при изменении модели,
    // связываем сигналы, специфичные для каждой модели, и необходимые слоты
    connect(this, &MainWindow::notebookReady, this, &MainWindow::reconnectWithNewModel);

    // Отображаем GUI, сгенерированный из файла mainwindow.ui, в данном окне
    mUi->setupUi(this);
    // Настраиваем таблицу заметок, чтобы её последняя колонка занимала всё доступное место
    mUi->notesView->horizontalHeader()->setStretchLastSection(true);
    // Создаём новую записную книжку
    newNotebook();
}

/**
* Отвечает за уничтожение объектов MainWindow. Сюда можно поместить
* функции, которые надо выполнить перед уничтожением (например, закрыть
* какие-либо файлы или освободить память).
*/
MainWindow::~MainWindow()
{
    // Удаляем объект Ui::MainWindow
    delete mUi;
}

void MainWindow::disableUIActions(const bool &dis)
{
    // Отключаем возможность создания заметок через меню-бар
    mUi->actionNew_Note->     setDisabled(dis);
    // Отключаем возможность отключения вида таблицы заметок
    mUi->checkBox->           setDisabled(dis);
    // Отключаем отображение таблицы заметок
    mUi->notesView->          setDisabled(dis or
                                          static_cast<bool>(mUi->checkBox->checkState()));
    // Отключаем возможность сохранять книжку в текущий файл
    mUi->actionSave->         setDisabled(dis);
    // Отключаем возможность сохранять книжку
    mUi->actionSave_As->      setDisabled(dis);
    // Отключаем возможность сохранять книжку в текстовом формате
    mUi->actionSave_As_Text-> setDisabled(dis);
    // Отключаем возможность закрывать записную книжку
    mUi->actionCloseNotebook->setDisabled(dis);
    // Отключаем возможность удалять если нет выделенных.
    // проверяем выделение, так как disableUIActions()
    // вызывается в том числе и по сигналу notebookReady, когда записная книга открыта
    mUi->actionDelete_Notes-> setDisabled(!mUi->notesView->selectionModel()->hasSelection());
}

void MainWindow::reconnectWithNewModel()
{
    // при изменении области выделения в таблице заметок вызываем слот, отключающий кнопку удаления,
    // если нет выделенных заметок
    connect(mUi->notesView->selectionModel(), &QItemSelectionModel::selectionChanged,
            [this]
    {
        // отключаем кнопку "удалить заметку", если нет выделенных заметок
        mUi->actionDelete_Notes->setDisabled(!mUi->notesView->selectionModel()
                                                         ->hasSelection());
    });
    // данные изменились => есть что сохранить => ставим [*] в заголовке окна
    connect(mUi->notesView->model(), &QAbstractItemModel::dataChanged,
            [this]
    {
        isNotebookSaved = false;
        setWindowModified(true);
    });
}

void MainWindow::disableNoteList(bool cond)
{
    // отключаем(или нет) список заметок
    mUi->notesView->setDisabled(cond);
    // "снимаем" выделение, чтобы не было возможности удалять
    // заметки, когда список заметок выключен
    mUi->notesView->selectionModel()->clearSelection();
}

void MainWindow::aboutqt()
{
    // Во многих программах, написанных с помощью qt, есть
    // окно с информацией о qt
    QMessageBox::aboutQt(this);
}

void MainWindow::displayAbout()
{
    /*
     * Создаём простой диалог типа QMessageBox, который является дочерним
     * по отношению к главному окну. Указатель this указывает на тот объект
     * класса (MainWindow), для которого был вызван данный метод (displayAbout()).
     *
     * Для создания стандартных вариантов этих окон (окно информации, сообщение
     * об ошибке и т. д.) есть статические методы, создающие готовое окно со
     * всеми необходимыми настройками: QMessageBox::information(),
     * QMessageBox::critical() и т. д.
     */
    QMessageBox aboutDlg(this);
    // Включаем расширенное форматирование текста (разновидность HTML, позволяет
    // выделять текст, ставить ссылки и т. д.) в окне aboutDlg
    aboutDlg.setTextFormat(Qt::RichText);
    /*
     * Устанавливаем заголовок окна aboutDlg. Функция tr() отвечает за перевод строки на другой
     * язык, если он предусмотрен в данной программе. Метод arg() заменяет в строке
     * %1, %2 и т. д. на переданную ему строку. В данном случае, с его помощью
     * в строку заголовка подставляется название программы, которое хранится
     * в пространстве имён Config в файле config.hpp
     */
    aboutDlg.setWindowTitle(tr("About %1").arg(Config::applicationName));
    // Устанавливаем иконку информационного сообщения
    aboutDlg.setIcon(QMessageBox::Information);
    // Устанавливаем основной текст в окне aboutDlg
    aboutDlg.setText(tr("%1 %2<br>"
        "Author: <a href=\"mailto:kpushkarev@sfu-kras.ru\">Kirill Pushkaryov</a>, 2019.<br>"
        "Edited in 2020 by <a href=\"mailto:ykashapov-ki19@stud.sfu-kras.ru\">"
        "Yaroslav Kashapov Fanizovich</a>,<br>КИ19-07б, 031939609.<br>"
        "Sourses: <a href=\"https://github.com/kashapovd/toynote\">github</a><br>"
        "License: WTFPL.<br>"
        "This application is dynamically linked against the<br>"
        "<a href=\"https://www.qt.io/developers/\">Qt Library</a> "
        "v. %3.<br>"
        "Icons by the <a href=\"http://tango.freedesktop.org/"
        "Tango_Icon_Library\">Tango Icon Library</a>.")
        .arg(Config::applicationName).arg(Config::applicationVersion)
        .arg(qVersion()));
    // Отображаем окно как модальное (блокирующее все остальные окна)
    aboutDlg.exec();
}

void MainWindow::toCourses()
{
    // Открываем страницу е-курсов
    // ParsingMode = TolerantMode по умолчанию
    QDesktopServices::openUrl(QUrl("https://e.sfu-kras.ru"));
}

void MainWindow::startLottery()
{
    lottery lot;
    // Получаем приз
    const QString prize = lot.kick_the_bucket();
    // Создаём окно с датой и результатами лотереи
    QMessageBox lotBox(this);
    lotBox.setWindowTitle(tr("Lottery"));
    // Устанавливаем текст окна. Вместо %1 метод arg() подставит в строку
    // текущую дату, а вместо %2 наименование приза
    lotBox.setText(tr("Date: %1<br>"
                      "Your prize: %2")
                   .arg(QDate().currentDate().toString(Qt::ISODate))
                   .arg(prize));
    // Добавляем единственную кнопку "выход"
    lotBox.setStandardButtons(QMessageBox::Cancel);
    // QMessageBox не поддерживает изменение размеров. В данном случае не будет видно заголовка окна,
    // и это зависит от текста в нём. С помощью манипуляций с сеткой окна можно установить минимальный
    // фиксированный размер - 300 точек
    reinterpret_cast<QGridLayout *>(lotBox.layout())->setColumnMinimumWidth(1, 300);
    // Отображаем окно
    lotBox.exec();
}

void MainWindow::exit()
{
    // Если есть несохранённые данные, то отображаем окно с
    // предложением сохранить
    closeNotebook();
    // ... и закрываем приложение
    qApp->quit();
}

void MainWindow::newNotebook()
{
    // Прежде чем открыть новую, закрываем текущую записную книжку
    if (!closeNotebook())
    {
        // Если записная книжка не была закрыта, прерываем операцию
        return;
    }
    // Создаём новую записную книжку
    createNotebook();
    // Сбрасываем имя файла текущей записной книжки
    setNotebookFileName();
    // Сигнализируем о готовности
    emit notebookReady();
    // Сигнализируем о создании записной книжки
    emit notebookCreated();
}

bool MainWindow::saveNotebook()
{
    // Если для текущей записной книжки не установлено имя файла...
    if (mNotebookFileName.isEmpty())
    {
        // Задействуем функцию "сохранить как" и выходим
        return saveNotebookAs();
    }
    else
    {
        // Cохраняем в текущий файл в двоичном формате
        saveNotebookToFile(mNotebookFileName, saveMode::BINARY);
    }
    // Сигнализируем о готовности
    emit notebookReady();
    // Сигнализируем о сохранении записной книжки
    emit notebookSaved();
    return true;
}

bool MainWindow::saveNotebookAs(const saveMode &mode)
{
    // Выводим диалог выбора файла для сохранения
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Notebook As"),
                                                    QString(),
                                     (mode==TEXT) ? Config::textNotebookFileNameFilter :
                                                    Config::binNotebookFileNameFilter);
    // Если пользователь не выбрал файл, возвращаем false
    if (fileName.isEmpty())
    {
        return false;
    }
    // Сохраняем записную книжку в выбранный файл
    saveNotebookToFile(fileName, mode);
    if (mode != TEXT)
    {
        // Сигнализируем о готовности
        emit notebookReady();
        // Сигнализируем о сохранении записной книжки
        emit notebookSaved();
    }
    return true;
}

bool MainWindow::saveNotebookAsText()
{
    return saveNotebookAs(saveMode::TEXT);
}

bool MainWindow::openNotebook()
{
    // Если записная книжка открыта, сначала закрываем её
    if (isNotebookOpen() && !closeNotebook())
    {
        // Если записная книжка не была закрыта, возвращаем false
        return false;
    }

    // Выводим диалог выбора файла для открытия
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Notebook"),
                                                    QString(),
                                                    Config::binNotebookFileNameFilter);
    // Если пользователь не выбрал файл, возвращаем false
    if (fileName.isEmpty()) {

        return false;
    }
    // Блок обработки исключительных ситуаций
    try
    {

        // Создаём объект inf, связанный с файлом fileName
        QFile inf(fileName);
        // Открываем файл только для чтения
        if (!inf.open(QIODevice::ReadOnly))
        {
            throw std::runtime_error((tr("open(): ") + inf.errorString()).toStdString());
        }
        // Привязываем к файлу поток, позволяющий считывать объекты Qt
        QDataStream ist(&inf);
        // Создаём новый объект записной книжки
        std::unique_ptr<Notebook> nb(new Notebook);
        // Загружаем записную книжку из файла
        ist >> *nb;
        // Устанавливаем новую записную книжку в качестве текущей.
        // Метод release() забирает указатель у объекта nb
        setNotebook(nb.release());
    }
    catch (const std::exception &e)
    {
        // Если при открытии файла возникла исключительная ситуация, сообщить пользователю
        QMessageBox::critical(this, Config::applicationName, tr("Unable to open "
                                                                "the file %1: %2")
                                                                .arg(fileName)
                                                                .arg(e.what()));
        return false;
    }
    // Устанавливаем текущее имя файла
    setNotebookFileName(fileName);
    // Сигнализируем о готовности
    emit notebookReady();
    // Сигнализируем об открытии записной книжки
    emit notebookOpened(mNotebookFileName);
    return true;
}

bool MainWindow::closeNotebook()
{
    // Если записная книжка не открыта, возвращаем true
    if (!isNotebookOpen())
    {
        return true;
    }
    // Если записная книжка уже сохранена, просто закрываем её
    if (isNotebookSaved)
    {
        // Уничтожаем объект записной книжки
        destroyNotebook();
        // Сбрасываем текущее имя файла
        setNotebookFileName();
        // Сигнализируем о закрытии записной книжки
        emit notebookClosed();
        return true;
    }
    // Создаём окно с вопросом о сохранении файла
    QMessageBox saveQuery(this);
    // Устанавливаем иконку вопроса
    saveQuery.setIcon(QMessageBox::Question);
    // Ставим название программы в заголовок
    saveQuery.setWindowTitle(Config::applicationName);
    // Устанавливаем текст вопроса. Вместо %1 метод arg() подставит в строку
    // результат notebookName() (название документа)
    saveQuery.setText(tr("Would you like to save <i>%1<i>?").arg(notebookName()));
    // Добавляем в окно стандартные кнопки: сохранить, не сохранять и отменить
    saveQuery.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    // Выбираем кнопку по умолчанию — сохранить
    saveQuery.setDefaultButton(QMessageBox::Save);
    // Выводим модальный диалог saveQuery и смотрим результат
    switch (saveQuery.exec())
    {
    case QMessageBox::Save: // Сохранить
        // Сохранить записную книжку
        if (!saveNotebook())
        {
            return false;
        }
        // Здесь не должно быть break
    case QMessageBox::Discard: // Закрыть без сохранения
        // Уничтожаем объект записной книжки
        destroyNotebook();
        // Сбрасываем текущее имя файла
        setNotebookFileName();
        // Сигнализируем о закрытии записной книжки
        emit notebookClosed();
        break;
    case QMessageBox::Cancel: // Отмена
        return false;
    }
    return true;
}

bool MainWindow::newNote()
{
    // Создаём диалог редактирования заметки
    EditNoteDialog noteDlg(this);
    // Устанавливаем заголовок noteDlg
    noteDlg.setWindowTitle(tr("New Note"));
    // Создаём заметку и передаём указатель на неё noteDlg
    Note note;
    noteDlg.setNote(&note);
    // Если пользователь не подтвердил изменения, возвращаем false
    if (noteDlg.exec() != EditNoteDialog::Accepted)
    {
        return false;
    }
    // Вставляем заметку в записную книжку
    mNotebook->insert(note);
    return true;
}

void MainWindow::editNote(QModelIndex idx)
{
    // получаем количество выделенных заметок
    int selectSize = mUi->notesView->selectionModel()->selectedRows().size();
    // Проверяем, что выделена одна заметка. Если нет, то выдаём ошибку и выходим.
    if (selectSize != 1)
    {
        // entered() срабатывает даже если нет выделеных заметок, но вид таблицы активен
        if (selectSize == 0)
        {
            QMessageBox::warning(this, tr("Error"), tr("Please, choose a note"), QMessageBox::Ok);
        }
        else
        {
            QMessageBox::warning(this, tr("Error"), tr("Unable to edit several notes"), QMessageBox::Ok);
        }
        return;
    }

    Note *note = const_cast<Note *>(&(*mNotebook)[idx.row()]);
    // сохраняем значения текущей и ещё не отредактированной заметки
    QString noteText = note->text();
    QString noteTitle = note->title();
    // Создаём диалог редактирования заметки
    EditNoteDialog editDlg(this);
    // Устанавливаем заголовок окна редактирования
    editDlg.setWindowTitle(tr("Note Editor"));
    // Передаём указатель на заметку, связанную с idx, и заполняем поля окна редактирования
    // в соответствии с данными заметки
    editDlg.setNoteForEdit(note);
    // Запускаем отображение окна и обрабатываем результат "отмена"
    if (editDlg.exec() != EditNoteDialog::Accepted)
    {
        return;
    }
    // Сигнализируем видам о изменении таблицы данных, если заметка была изменена
    mNotebook->signalIfEdited(idx, noteText, noteTitle);
}

void MainWindow::deleteNotes()
{
    // Получаем от таблицы заметок список индексов выбранных в настоящий момент
    // элементов
    QModelIndexList idc = mUi->notesView->selectionModel()->selectedRows();
    // Для хранения номеров строк создаём STL-контейнер "множество", элементы
    // которого автоматически упорядочиваются по возрастанию
    std::set<int> rows;
    {
        // Вставляем номера выбранных строк в rows
        for (const auto &i : idc)
        {
            rows.insert(i.row());
        }
    }
    // Cтрока, содержащая названия заметок для удаления (выделенных заметок)
    // будет отображена в окне подтверждения удаления заметок
    QString rmNote;

    // если выбрана одна заметка
    if (rows.size() == 1)
    {
        rmNote = (*mNotebook)[idc.first().row()].title();
    }
    else // если выбрано несколько
    {
        for (const auto &it : rows)
        {
            rmNote.append(tr("<br>• ") + (*mNotebook)[it].title());
        }
    }

    QMessageBox::StandardButtons ret = QMessageBox::question(this, Config::applicationName,
               (rows.size() != 1) ? tr("Do you really want to remove the "
                                       "following notes:<br><i>%1<i>").arg(rmNote) :
                                    tr("Do you really want to remove the "
                                       "<i>%1<i>?").arg(rmNote),
                                    QMessageBox::Yes | QMessageBox::No);
    // Если No, удалять не нужно.
    if (ret == QMessageBox::No) return;

    for (auto it = rows.rbegin(); it != rows.rend(); ++it)
    {
        // Удаляем строку
        mNotebook->erase(*it);
    }
}

void MainWindow::refreshWindowTitle()
{
    QString nbname = notebookName();
    // Если имя записной книжки не пусто...
    if (!nbname.isEmpty())
    {
        // Ставим в заголовок окна название программы (Config::applicationName)
        // и имя текущей записной книжки (nbname)
        // Метка "[*]" обозначает место, куда будет подставлена звёздочка, если
        // установлен флаг изменения окна (см. QWidget::setWindowModified())
        setWindowTitle(tr("%1 - %2[*]").arg(Config::applicationName).arg(nbname));
    }
    else
    {
        // Ставим в заголовок окна только название программы (Config::applicationName)
        setWindowTitle(Config::applicationName);
    }
}

/**
 * Сохраняет в соответствии с режимом @a mode текущую записную книжку в файл @a fileName.
 * Данный метод отвечает непосредственно за сохранение и не предусматривает диалога с
 * пользователем.
 */
void MainWindow::saveNotebookToFile(const QString &fileName, const saveMode &mode)
{
    // Блок обработки исключительных ситуаций
    try
    {
        /*
         * Создаём объект outf, связанный с файлом fileName.
         * QSaveFile обеспечивает безопасное сохранение (через промежуточный
         * временный файл), чтобы избежать потери данных в случае нештатного
         * завершения операции сохранения. Само сохранение происходит при вызове
         * метода commit().
         */
        QSaveFile outf(fileName);
        // если необходимо записать в текстовый файл
        if (mode == TEXT)
        {
            // Открываем текстовый файл только для записи
            outf.open(QIODevice::WriteOnly | QIODevice::Text);
            // Привязываем к файлу текстовый поток, позволяющий выводить объекты Qt
            QTextStream ost(&outf);
            // Выводим записную книжку в файл
            for (int i = 0; i < mNotebook->size(); i++) {
                // выводим номер записи и количество записей в текущей записной книжке
                ost << tr("+++ %1/%2 +++\n").arg(i+1).arg(mNotebook->size());
                // выводим заголовок и текст записи
                ost << tr("Title: %1\n").arg((*mNotebook)[i].title()) << (*mNotebook)[i].text();
                ost << tr("\n--- %1/%2 ---\n").arg(i+1).arg(mNotebook->size());
                ost << tr("\n");
            }
        }
        // записываем в двоичный файл
        else
        {
            // Открываем файл только для записи
            outf.open(QIODevice::WriteOnly);
            // Привязываем к файлу поток, позволяющий выводить объекты Qt
            QDataStream ost(&outf);
            // Выводим записную книжку в файл
            ost << *mNotebook;
        }
        // Запускаем сохранение и смотрим результат.
        // В случае неудачи запускаем исключительную ситуацию (блок прерывается,
        // управление передаётся в блок catch)
        if (!outf.commit())
        {
            throw std::runtime_error(tr("Unable to commit the save").toStdString());
        }
        // Если сохранение осуществляется в текстовый файл, менять имя
        // текущего файла нет смысла, поскольку считать данные из такого файла
        // невозможно. Другими словами, *просто* сохранили заметки в текстовый файл
        if (mode != TEXT)
        {
            setNotebookFileName(fileName);
        }
    }

    catch (const std::exception &e)
    {
        // Если при сохранении файла возникла исключительная ситуация, сообщить пользователю
        QMessageBox::critical(this, Config::applicationName, tr("Unable to write to the file %1: %2").arg(fileName).arg(e.what()));
    }
}

bool MainWindow::isNotebookOpen() const
{
    // Преобразуем указатель mNotebook к типу bool. Нулевой указатель при этом
    // даст false, ненулевой — true
    return static_cast<bool>(mNotebook);
}

void MainWindow::setNotebookFileName(const QString &name)
{
    // Устанавливаем имя файла
    mNotebookFileName = name;
    // Сигнализируем о смене имени файла
    emit notebookFileNameChanged(name);
}

QString MainWindow::notebookName() const
{
    // Если записная книжка не открыта, возвращаем пустую строку
    if (!isNotebookOpen())
    {
        return QString();
    }
    // Иначе, если имя текущего файла пустое, возвращаем строку "Untitled"
    else if (mNotebookFileName.isEmpty())
    {
        return tr("Untitled");
    }
    // Возвращаем короткое имя текущего файла (без пути)
    return QFileInfo(mNotebookFileName).fileName();
}

void MainWindow::createNotebook()
{
    setNotebook(new Notebook);
}

void MainWindow::setNotebook(Notebook *nb)
{
    /*
     * Заменяем имеющийся указатель на объект записной книжки новым.
     * Если в mNotebook хранился какой-то ненулевой указатель на объект,
     * то метод reset() удалит его автоматически
     */
    mNotebook.reset(nb);
    // Связываем новый объект записной книжки с таблицей заметок в главном окне
    mUi->notesView->setModel(mNotebook.get());
}

/**
 * Прекращает отображение текущей записной книжки в графическом интерфейсе
 * и удаляет объект Notebook по указателю mNotebook.
 */
void MainWindow::destroyNotebook()
{
    // Отключаем объект записной книжки от таблицы заметок в главном окне
    mUi->notesView->setModel(0);
    // Удаляем объект записной книжки
    mNotebook.reset();
}
