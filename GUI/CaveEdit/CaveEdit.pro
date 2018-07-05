#-------------------------------------------------
#
# Project created by QtCreator 2018-07-04T22:05:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CaveEdit
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0




FORMS +=

HEADERS += \
    mainwindow.h \
    caveedit/file_editor.hpp \
    caveedit/flag.hpp \
    caveedit/flag_data.hpp \
    caveedit/item_ids.hpp \
    caveedit/utils.hpp \
    caveedit/weapon.hpp \
    caveedit/weapon_ids.hpp

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    caveedit/file_editor.cpp \
    caveedit/utils.cpp \
    caveedit/weapon.cpp
