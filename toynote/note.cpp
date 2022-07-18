/**
 * @file note.cpp
 * @brief Файл реализации класса Note.
 ***************************
 * @author Кирилл Пушкарёв
 * @date 2017
 ***************************
 * @author Кашапов Ярослав
 * @date 2020
 */
#include "note.hpp"

Note::Note()
{}

Note::Note(QString title, QString text)
    : mTitle(title) // Передаём заголовок конструктору mTitle
    , mText(text) // Передаём заголовок конструктору mText
{}

const QString &Note::title() const
{
    return mTitle;
}

void Note::setTitle(const QString &title)
{
    mTitle = title;
}

const QString &Note::text() const
{
    return mText;
}

void Note::setText(const QString &text)
{
    mText = text;
}

void Note::save(QDataStream &ost) const
{
    ost << mTitle << mText;
}

void Note::load(QDataStream &ist)
{
    ist >> mTitle >> mText;
}
