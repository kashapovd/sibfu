/**
 * @file notebook.hpp
 * @brief Заголовочный файл класса Notebook.
 ***************************
 * @author Кирилл Пушкарёв
 * @date 2017
 ***************************
 * @author Кашапов Ярослав
 * @date 2020
 */
#ifndef NOTEBOOK_HPP
#define NOTEBOOK_HPP

#include <cstddef> // size_t

#include <QAbstractTableModel>
#include <QDataStream>
#include <QVector>

#include "note.hpp"

/**
 * @brief Класс записной книжки.
 *
 * Контейнер заметок (типа Note), реализующий интерфейс QAbstractTableModel,
 * а через него QAbstractItemModel. Реализация интерфейса @e модели позволяет использовать
 * объекты Notebook в качестве моделей при работе с @e видами Qt, в частности с видом
 * QTableView, который отображает данные модели в виде таблицы.
 *
 * На класс модели возлагаются обязательства уведомлять присоединённые виды о том,
 * что данные или их структура изменились. Делается это с помощью вызова специальных
 * методов, таких как QAbstractItemModel::beginInsertRows(), или отправки сигналов,
 * таких как QAbstractItemModel::dataChanged(). Если поменять содержимое модели,
 * никого не уведомив, то виды будут отображать его неправильно.
 *
 * @sa @ref faq_interface @ref faq_modelview @ref faq_qt_model_structure
 */
class Notebook : public QAbstractTableModel
{
    Q_OBJECT
public:
    /**
     * @brief Тип индексов и размера контейнера.
     *
     * Используется int, так как это тип индексов строк в QAbstractTableModel.
     * В то же время, в стандартных контейнерах C++ (std::vector и др.) для этого
     * применяются беззнаковые типы.
     */
    using SizeType = int;

    /// Конструктор по умолчанию.
    Notebook();
    /**
     * @brief Оператор [].
     * @param idx Индекс читаемого элемента.
     * @return Константная ссылка на заметку.
     */
    const Note &operator[](SizeType idx) const;
    /// Определяет размер коллекции (количество заметок).
    SizeType size() const;

    /**
     * @name Реализация интерфейса модели.
     *
     * Ниже идут методы, являющиеся определениями методов интерфейса
     * модели. Подробное описание их предназначения и требований к ним можно
     * найти в документации классов Qt QAbstractTableModel, QAbstractItemModel.
     * @{
     */
    /**
     * @brief Определяет количество строк в модели (заметок).
     * @param parent Ссылка на индекс родительского объекта.
     * @note Q_DECL_OVERRIDE — это макроконстанта (\#define), которая заменяется
     * спецификатором @c override, если компилятор его поддерживает. Этот спецификатор
     * означает, что данный метод является переопределением соответствующего
     * метода базового класса.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    /**
     * @brief Определяет количество столбцов в модели.
     * @param parent Ссылка на индекс родительского объекта.
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    /**
     * @brief Возвращает данные указанной роли для указанного элемента модели.
     * @param index Индекс элемента модели.
     * @param role Роль, для которой надо вернуть данные.
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    /**
     * @brief Возвращает данные указанной роли для указанного заголовка модели.
     * @param section Раздел заголовка (номер строки для вертикального заголовка
     * или номер столбца для горизонтального).
     * @param orientation Ориентация заголовка (вертикальный — заголовок строк,
     * горизонтальный — заголовок столбцов).
     * @param role Роль, для которой надо вернуть данные.
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    /// @}
    // Конец реализации интерфейса модели

    /// Сохраняет записную книжку в поток @a ost.
    void save(QDataStream &ost) const;
    /// Очищает записную книжку и загружает новую из потока @a ist. Возвращает количество загруженных заметок.
    SizeType load(QDataStream &ist);
    /// Вставляет заметку @a note в записную книжку.
    void insert(const Note &note);
    /// Удаляет заметку с индексом @a idx из записной книжки.
    void erase(const SizeType &idx);
    /// Сигнализирует о изменении данных, если они были в результате редактирования заметки
    void signalIfEdited(const QModelIndex &idx, const QString &prevtext, const QString &prevtitle);
private:
    /// Внутренний контейнер для хранения заметок записной книжки.
    QVector<Note> mNotes;
};

/**
 * @brief Реализация оператора << для вывода Notebook в QDataStream.
 * @param ost Поток для вывода.
 * @param notebook Записная книжка.
 * @return Поток @a ost после вывода.
 *
 * Данная функция объявлена @c inline, чтобы компилятор мог подставить её код
 * вместо полноценного вызова функции. В данном случае это оправданно, так как
 * функция всего лишь перенаправляет вызов методу save().
 */
inline QDataStream &operator<<(QDataStream &ost, const Notebook &notebook)
{
    notebook.save(ost);
    return ost;
}

/**
 * @brief Реализация оператора >> для ввода Notebook из QDataStream.
 * @param ist Поток для ввода.
 * @param notebook Записная книжка.
 * @return Поток @a ist после ввода.
 */
inline QDataStream &operator>>(QDataStream &ist, Notebook &notebook)
{
    notebook.load(ist);
    return ist;
}

#endif // NOTEBOOK_HPP
