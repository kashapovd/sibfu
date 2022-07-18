/**
 * @file habitant.cpp
 * @brief Файл реализации класса habitant.
 * @author Кашапов Ярослав
 * @date 2021
 */

#include "habitant.h"

const QString habitant::fname() const {return mFname;}

const QString habitant::lname() const {return mLname;}

const QString habitant::patronymic() const {return mPatronymic;}

const QDate habitant::birthDate() const {return mBirthDate;}

uint habitant::studentID() const {return mStudentID;}

uint habitant::numOfCourse() const {return mNumOfCourse;}

QString habitant::group() const {return mGroup;}

uint habitant::roomNumber() const {return mRoomNumber;}

habitant::habitant(habitantData *h) {setData(h);}

bool habitant::setData(habitantData *h)
{
    if (h != nullptr)
    {
        if (!h->fname.trimmed().isEmpty() && !h->lname.trimmed().isEmpty()
                && !h->patronymic.trimmed().isEmpty() && h->numOfCourse > 0
                && h->numOfCourse <= 5 && !h->group.trimmed().isEmpty())
        {
            mFname = h->fname;
            mLname = h->lname;
            mPatronymic = h->patronymic;
            mBirthDate = h->birthDate;
            mStudentID = h->studentID;
            mNumOfCourse = h->numOfCourse;
            mGroup = h->group;
            mRoomNumber = h->roomNumber;
            return true;
        }
    }
    return false;
}

habitant::habitantData *habitant::getData() const
{
    habitantData *hd = new habitantData;
    hd->fname = mFname;
    hd->lname = mLname;
    hd->patronymic = mPatronymic;
    hd->birthDate = mBirthDate;
    hd->studentID = mStudentID;
    hd->numOfCourse = mNumOfCourse;
    hd->group = mGroup;
    hd->roomNumber = mRoomNumber;
    return hd;
}
