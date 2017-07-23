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
    parts/highligters/highlighter.cpp \
    parts/langs/ruby/format_ruby.cpp \
    parts/document_types/idocument.cpp \
    parts/formats/iformat.cpp

HEADERS  += ide_window.h \
    parts/code_editor.h \
    misc/singleton.h \
    parts/highligters/base/highlighter_rule.h \
    parts/highligters/base/highlight_format_factory.h \
    parts/highligters/highlighter.h \
    parts/highligters/ihighlight_preset.h \
    dock_widgets.h \
    parts/documents.h \
    parts/document_types/idocument.h \
    parts/document_types/text_document.h \
    parts/document_types/image_document.h \
    parts/document_types/documents_types.h \
    parts/langs/ruby/format_ruby.h \
    parts/formats/iformat.h \
    parts/formats/format_types.h \
    parts/langs/css/css_preset.h \
    parts/langs/erb/erb_preset.h \
    parts/langs/haml/haml_preset.h \
    parts/langs/html/html_preset.h \
    parts/langs/javascript/javascript_preset.h \
    parts/langs/json/json_preset.h \
    parts/langs/ruby/ruby_preset.h \
    parts/langs/sass/sass_preset.h \
    parts/langs/sql/sql_preset.h \
    parts/langs/xml/xml_preset.h \
    parts/langs/yaml/yaml_preset.h \
    parts/langs/c_plus_preset.h \
    parts/langs/c_preset.h \
    parts/langs/c_sharp_preset.h \
    parts/langs/delphi_preset.h \
    parts/langs/java_preset.h \
    parts/langs/php_preset.h \
    parts/langs/python_preset.h \
    parts/langs/vb_preset.h \
    parts/formats/format_text.h \
    parts/formats/format_image.h \
    parts/editor_parts/extra_area.h \
    parts/document_types/binary_document.h

FORMS    += ide_window.ui
