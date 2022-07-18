#-------------------------------------------------
#
# Project created by QtCreator 2017-05-30T12:10:48
#
#-------------------------------------------------

QT          +=  core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET       =  toynote
TEMPLATE     =  app

TRANSLATIONS =  toynote_ru.ts

DEFINES     +=  QT_DEPRECATED_WARNINGS

SOURCES     +=  main.cpp \
                lottery.cpp \
                mainwindow.cpp \
                notebook.cpp \
                note.cpp \
                editnotedialog.cpp

HEADERS     +=  mainwindow.hpp \
                lottery.hpp \
                notebook.hpp \
                note.hpp \
                config.hpp \
                editnotedialog.hpp

FORMS       +=  mainwindow.ui \
                editnotedialog.ui

RESOURCES   +=  resources.qrc

CONFIG      +=  c++11
