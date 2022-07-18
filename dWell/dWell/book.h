/**
 * @file book.h
 * @brief Заголовчный файл класса book.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef BOOK_H
#define BOOK_H

#include "writereadableitem.h"

#include <QVector>

/**
 * @brief Шаблонный класс-контейнер с функциями сохранения в файл.
 * Используется для хранения пользователей и комнат в системе.
 * Наследуется от класса writeReadableItem, переопределяя его методы.
 * @tparam entry объект, хранящийся в контейнере.
 */
template <typename entry>
class book : writeReadableItem
{
public:
    /// Конструктор класса по умолчанию.
    book() {}
    /**
     * @brief Метод, позволяющий загрузить контейнер из файла.
     * @param filename Имя файла.
     */
    void loadFromFile(const QString &filename);
    /**
     * @brief Константный метод, позволяющий сохранить контейнер в файл.
     * @param filename Имя файла.
     */
    void saveToFile(const QString &filename) const;
    /**
     * @brief Оператор [].
     * @param idx Индекс читаемого элемента.
     * @return Константная ссылка на читаемый элемент.
     */
    const entry &operator[](uint idx) const;
    /// Определяет размер контейнера.
    uint size() const;

private:
    /**
     * @brief Определение базового метода записи в поток
     * @param ost Ссылка на поток.
     */
    void write(QDataStream &ost) const override;
    /**
     * @brief Определение базового метода считывания из потока
     * @param ist Ссылка на поток.
     */
    void read(QDataStream &ist) override;

protected:
    /// Контейнер, хранящий шаблонные элементы
    QVector<entry> mEntries;
};

#endif // BOOK_H
