/**
 * @file doc.cpp
 * @brief Файл реализации класса doc.
 * @author Кашапов Ярослав
 * @date 2021
 */

#include "doc.h"
#include "dormitory.h"

#include <QStandardPaths>
#include <QTextDocument>

void doc::generate(const habitant *h, QPrinter *printer)
{
    dormitory *dorm = dormitory::getDormCfg();
    const QString docTemplate = QString (
                "<p style=\"text-align: center;\"><strong>СПРАВКА </strong></p>"
                "<p style=\"text-align: center;\">&nbsp;</p>"
                "<p style=\"text-align: center;\">&nbsp;</p>"
                "<p style=\"text-align: justify; padding-left: 40px;\">Дана студенту %1 %2 года рождения в том, что"
                " он действительно является студентом, проживающим в общежитии %3, комната №%4.</p>"
                "<p style=\"text-align: justify;\">&nbsp;</p>"
                "<p style=\"text-align: justify; padding-left: 40px;\">Справка выдана для предъявления по месту требования.</p>"
                "<p style=\"text-align: justify; padding-left: 40px;\">&nbsp;</p>"
                "<p style=\"text-align: justify; padding-left: 440px;\">М. П.</p>"
                "<p style=\"text-align: justify; padding-left: 40px;\">&nbsp;</p>"
                "<p style=\"text-align: justify; padding-left: 40px;\">Дата %5</p>")
                    .arg(h->fname() + " " + h->lname() + " " + h->patronymic())
                    .arg(h->birthDate().toString())
                    .arg(dorm->name())
                    .arg(h->roomNumber())
                    .arg(QDateTime::currentDateTime().toString());

    QTextDocument document;
    document.setHtml(docTemplate);
    document.print(printer);
}
