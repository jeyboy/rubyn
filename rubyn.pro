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
    parts/highligters/highlighter.cpp

HEADERS  += ide_window.h \
    parts/editor_parts/line_numbers.h \
    parts/code_editor.h \
    parts/highligters_factory.h \
    misc/singleton.h \
    parts/highligters/base/highlighter_rule.h \
    parts/highligters/base/highlight_format_factory.h \
    parts/highligters/presets/ruby_preset.h \
    parts/highligters/highlighter.h \
    parts/highligters/presets/ihighlight_preset.h \
    parts/highligters/presets/c_plus_preset.h \
    parts/highligters/presets/presets_list.h \
    parts/highligters/presets/sql_preset.h \
    dock_widgets.h \
    parts/documents/idocument.h \
    parts/documents.h \
    parts/documents/documents_list.h \
    parts/documents/text_document.h \
    parts/documents/image_document.h

FORMS    += ide_window.ui
