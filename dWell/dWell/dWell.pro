QT      +=  core gui \
            printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG  +=  c++11
#QMAKE_CXXFLAGS += -Wall

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
            user.cpp \
            room.cpp \
            book.cpp \
            ubook.cpp \
            rbook.cpp \
            main.cpp \
            admindialog.cpp \
            commandantdialog.cpp \
            doc.cpp \
            dormitory.cpp \
            habitant.cpp \
            habitanteditdialog.cpp \
            initsetupdialog.cpp \
            mainwindow.cpp \
            relocationdialog.cpp \
            studentdialog.cpp \
            tools.cpp \
            usereditdialog.cpp \

HEADERS += \
            writereadableitem.h \
            bookentry.h \
            room.h \
            user.h \
            book.h \
            ubook.h \
            rbook.h \
            admindialog.h \
            commandantdialog.h \
            config.h \
            doc.h \
            dormitory.h \
            habitant.h \
            habitanteditdialog.h \
            initsetupdialog.h \
            mainwindow.h \
            relocationdialog.h \
            studentdialog.h \
            tools.h \
            usereditdialog.h \

FORMS   += \
            admindialog.ui \
            commandantdialog.ui \
            habitanteditdialog.ui \
            initsetupdialog.ui \
            mainwindow.ui \
            relocationdialog.ui \
            studentdialog.ui \
            usereditdialog.ui

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
