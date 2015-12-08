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
    services/highligters/highlighter.cpp

HEADERS  += ide_window.h \
    parts/line_numbers.h \
    parts/code_editor.h \
    services/highligters/highligters_factory.h \
    misc/singleton.h \
    services/highligters/base/highlighter_rule.h \
    services/highligters/base/highlight_format_factory.h \
    services/highligters/presets/ruby_preset.h \
    services/highligters/highlighter.h \
    services/highligters/presets/ihighlight_preset.h \
    services/highligters/presets/c_plus_preset.h \
    services/highligters/presets/presets_list.h

FORMS    += ide_window.ui
