/**
 * @file doc.h
 * @brief Заголовчный файл класса doc.
 * @author Кашапов Ярослав
 * @date 2021
 */

#ifndef DOC_H
#define DOC_H

#include "habitant.h"

#include <QPrinter>

/**
 * @brief Класс справки.
 */
class doc
{
public:
    /// Конструктор по умолчанию
    doc() {}
    /**
     * @brief Статический метод, выполняющий сохранение PDF-файла справки.
     * @param h Константный указатель на проживающего, для которого генерируется справка.
     * @param printer Содержит настройки печати PDF-файла.
     */
    static void generate(const habitant *h, QPrinter *printer);
};

#endif // DOC_H
