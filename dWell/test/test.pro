QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS +=  ../dWell/user.h \
            ../dWell/book.h \
            ../dWell/ubook.h \
            ../dWell/room.h \
            ../dWell/habitant.h

SOURCES +=  tst_testdwell.cpp \
            ../dWell/user.cpp \
            ../dWell/book.cpp \
            ../dWell/ubook.cpp \
            ../dWell/room.cpp \
            ../dWell/habitant.cpp
