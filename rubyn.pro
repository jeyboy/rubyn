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
    parts/editor_parts/highlighter.cpp \
    ide_window.cpp \
    parts/code_editor.cpp \
    parts/editor_parts/project.cpp \
    parts/editor_parts/file.cpp \
    parts/lexer/lexer_factory.cpp \
    parts/editor_parts/projects.cpp \
    parts/document_types/text_document.cpp

HEADERS  += ide_window.h \
    parts/editor_parts/highlighter.h \
    parts/code_editor.h \
    misc/singleton.h \
    parts/highligters/highlight_format_factory.h \
    dock_widgets.h \
    parts/document_types/text_document.h \
    parts/document_types/image_document.h \
    parts/document_types/documents_types.h \
    parts/formats/format_types.h \
    parts/langs/c_plus_preset.h \
    parts/langs/c_preset.h \
    parts/langs/java_preset.h \
    parts/editor_parts/extra_area.h \
    parts/document_types/binary_document.h \
    parts/editor_parts/block_user_data.h \
    parts/editor_parts/project.h \
    parts/editor_parts/file.h \
    parts/lexer/lexer.h \
    parts/lexer/lexems.h \
    parts/lexer/scopes/file_point.h \
    parts/langs/ruby/preset_ruby.h \
    parts/langs/css/preset_css.h \
    parts/langs/erb/preset_erb.h \
    parts/langs/haml/preset_haml.h \
    parts/langs/html/preset_html.h \
    parts/langs/javascript/preset_javascript.h \
    parts/langs/json/preset_json.h \
    parts/langs/sass/preset_sass.h \
    parts/langs/sql/preset_sql.h \
    parts/langs/xml/preset_xml.h \
    parts/langs/yaml/preset_yaml.h \
    parts/langs/ruby/lexer_ruby.h \
    parts/langs/ruby/predefined_ruby.h \
    misc/stack.h \
    parts/lexer/scopes/scope.h \
    misc/chain.h \
    parts/langs/ruby/flags_ruby.h \
    parts/lexer/lexer_state.h \
    parts/langs/ruby/lexer_ruby_regexp.h \
    parts/lexer/lexer_factory.h \
    misc/utils.h \
    parts/lexer/grammar.h \
    parts/langs/ruby/grammar_ruby.h \
    misc/token_list.h \
    parts/editor_parts/projects.h \
    parts/document_types/idocument.h \
    parts/editor_parts/para_info.h \
    parts/editor_parts/error_info.h

FORMS    += ide_window.ui

RESOURCES += \
    resources.qrc

RC_FILE = rubyn.rc
