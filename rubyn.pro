#-------------------------------------------------
#
# Project created by QtCreator 2015-12-06T23:30:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rubyn
TEMPLATE = app


SOURCES += main.cpp\
        ide_window.cpp \
    parts/code_editor.cpp \
    services/highligters/ihighlighter.cpp

HEADERS  += ide_window.h \
    parts/line_numbers.h \
    parts/code_editor.h \
    services/highligters/highligters_factory.h \
    services/highligters/ihighlighter.h \
    misc/singleton.h \
    services/highligters/highlighter_rule.h \
    services/highligters/c_plus_highlighter.h

FORMS    += ide_window.ui
