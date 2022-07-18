/**
 * @file notebook.cpp
 * @brief Файл реализации класса Notebook.
 ***************************
 * @author Кирилл Пушкарёв
 * @date 2017
 ***************************
 * @author Кашапов Ярослав
 * @date 2020
 */
#include "notebook.hpp"

#include <iterator> // next()
#include <stdexcept> // runtime_error

#include <QString> // QString::number()

#include "note.hpp"

Notebook::Notebook()
{}

/**
 * Возвращает ссылку на заметку с индексом @a idx. Слово @c const после
 * списка параметров означает, что это константная версия метода,
 * она не может изменять данные класса. Результат также имеет квалификатор
 * @c const, т. е. по этой ссылке заметку нельзя изменить.
 *
 * Таким образом, данный метод позволяет прочитать заметку с индексом @a idx
 * из коллекции, но не изменить её.
 *
 * Можно было бы определить метод, позволяющий изменить заметку. Его объявление
 * выглядело бы так:
 * @code
 * Note &operator[](SizeType idx);
 * @endcode
 * В данном случае делать этого нельзя, поскольку возвращённая ссылка на заметку
 * неподконтрольна данному классу и он не имеет возможности узнать,
 * была ли заметка реально изменена и когда это произошло, а значит не может
 * уведомить присоединённые виды о том, что данные изменились.
 * @sa @ref faq_const_method
 */
const Note &Notebook::operator[](Notebook::SizeType idx) const
{
    return mNotes[idx];
}

Notebook::SizeType Notebook::size() const
{
    return mNotes.size();
}

/**
 * Данная модель является табличной, каждая заметка занимает одну строку,
 * поэтому метод возвращает количество заметок для корневого элемента.
 * Для всех остальных элементов возвращает 0 (см. QAbstractItemModel::rowCount()).
 * @sa @ref faq_qt_model_structure
 */
int Notebook::rowCount(const QModelIndex &parent) const
{
    return !parent.isValid() ? mNotes.size() : 0;
}

/**
 * Для каждой заметки отображается только её заголовок, поэтому метод возвращает 1
 * для корневого элемента. Для всех остальных элементов возвращает 0
 * (см. QAbstractItemModel::columnCount()).
 * @sa @ref faq_qt_model_structure
 */
int Notebook::columnCount(const QModelIndex &parent) const
{
    return !parent.isValid() ? 1 : 0;
}

/**
 * Возвращает для элемента модели с индексом @a index данные с ролью @a role.
 * @note QVariant — это универсальный тип данных Qt, позволяющий хранить
 * данные различных типов.
 * @sa @ref faq_qt_model_index @ref faq_qt_model_role
 */
QVariant Notebook::data(const QModelIndex &index, int role) const
{
    // Если требуется текст для отображения...
    if (role == Qt::DisplayRole)
    {
        // Если столбец первый, возвращаем заголовок заметки, находящейся
        // в соответствующей строке таблицы
        if (index.column() == 0)
        {
            // При возврате строка заголовка (QString) автоматически преобразуется
            // в QVariant
            return mNotes[index.row()].title();
        }
    }
    // Игнорируем все остальные запросы, возвращая пустой QVariant
    return QVariant();
}

/**
 * Возвращает для элемента @a section заголовка модели с ориентацией @a orientation
 * данные с ролью @a role.
 *
 * Горизонтальная ориентация означает заголовки столбцов, вертикальная — строк.
 * @sa @ref faq_qt_model_index @ref faq_qt_model_role
 */
QVariant Notebook::headerData(int section, Qt::Orientation orientation, int role) const
{
    // Если требуется текст для отображения...
    if (role == Qt::DisplayRole)
    {
        // Если речь о заголовках столбцов...
        if (orientation == Qt::Horizontal)
        {
            // Если столбец первый, возвращаем заголовок
            if (section == 0)
            {
                return tr("Title");
            }
        }
        // Если речь о заголовках строк...
        else if (orientation == Qt::Vertical)
        {
            // Возвращаем номер строки
            return QString::number(section);
        }
    }
    // Игнорируем все остальные запросы, возвращая пустой QVariant
    return QVariant();
}

void Notebook::save(QDataStream &ost) const
{
    // Цикл по всем заметкам
    for (const Note &n : mNotes)
    {
        // Выводим заметку в поток
        ost << n;
        // Если возникла ошибка, запускаем исключительную ситуацию
        if (ost.status() == QDataStream::WriteFailed)
        {
            throw std::runtime_error(tr("Write to the stream failed").toStdString());
        }
    }
}

Notebook::SizeType Notebook::load(QDataStream &ist)
{
    // В соответствии с требованиями Qt, уведомляем привязанные виды о том,
    // что мы начинаем сброс модели (данные и структура модели могут
    // радикально измениться, поэтому сохранённая где-либо информация о модели
    // должна быть обновлена).
    // См. QAbstractItemModel
    beginResetModel();
    // Удаляем все заметки
    mNotes.clear();
    // Пока в потоке есть данные
    while (!ist.atEnd())
    {
        Note n;
        // Читаем очередную заметку из потока
        ist >> n;
        // Если возникла ошибка, запускаем исключительную ситуацию
        if (ist.status() == QDataStream::ReadCorruptData)
        {
            throw std::runtime_error(tr("Corrupt data were read from the stream").toStdString());
        }
        // Вставляем прочитанную заметку в конец вектора mNotes
        mNotes.push_back(n);
    }
    // В соответствии с требованиями Qt, уведомляем привязанные виды о том,
    // что мы закончили сброс модели
    endResetModel();
    return mNotes.size();
}

void Notebook::insert(const Note &note)
{
    // В соответствии с требованиями Qt, уведомляем привязанные виды о том,
    // что мы начинаем вставлять строки в модель.
    // Вставку производим в конец, поэтому номер новой строки будет равен size()
    beginInsertRows(QModelIndex(), // Индекс родителя, в список потомков которого добавляются строки
                    size(), // Номер первой добавляемой строки
                    size() // Номер последней добавляемой строки
                    );
    // Вставляем заметку в конец вектора mNotes
    mNotes.push_back(note);
    // В соответствии с требованиями Qt, уведомляем привязанные виды о том,
    // что мы закончили вставлять строки в модель.
    endInsertRows();
    dataChanged(index(size(), 1, QModelIndex()),index(size(), 1, QModelIndex()));
}

void Notebook::erase(const SizeType &idx)
{
    // В соответствии с требованиями Qt, уведомляем привязанные виды о том,
    // что мы начинаем удалять строки из модели
    beginRemoveRows(QModelIndex(), // Индекс родителя, из списка потомков которого удаляются строки
                    idx, // Номер первой удаляемой строки
                    idx // Номер последней удаляемой строки
                    );
    // Удаляем из вектора элемент с индексом idx
    mNotes.erase(std::next(mNotes.begin(), idx));
    // В соответствии с требованиями Qt, уведомляем привязанные виды о том,
    // что мы закончили удалять строки из модели
    endRemoveRows();
    dataChanged(index(idx, 1, QModelIndex()),index(idx, 1, QModelIndex()));
}

void Notebook::signalIfEdited(const QModelIndex &idx, const QString &prevtext, const QString &prevtitle)
{
    if (mNotes[idx.row()].text() != prevtext or mNotes[idx.row()].title() != prevtitle)
    {
        dataChanged(idx, idx);
    }
}
