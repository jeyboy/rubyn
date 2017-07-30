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
    parts/formats/iformat.cpp \
    parts/editor_parts/project.cpp \
    parts/editor_parts/file.cpp

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
    parts/langs/c_plus_preset.h \
    parts/langs/c_preset.h \
    parts/langs/java_preset.h \
    parts/langs/php_preset.h \
    parts/langs/python_preset.h \
    parts/langs/vb_preset.h \
    parts/formats/format_text.h \
    parts/formats/format_image.h \
    parts/editor_parts/extra_area.h \
    parts/document_types/binary_document.h \
    parts/editor_parts/block_user_data.h \
    parts/editor_parts/project.h \
    parts/editor_parts/file.h \
    parts/lexer/lexer.h \
    parts/lexer/lexems.h \
    parts/lexer/scopes/iscope.h \
    parts/lexer/scopes/global_scope.h \
    parts/lexer/scopes/class_scope.h \
    parts/lexer/scopes/instance_scope.h \
    parts/lexer/scopes/local_scope.h \
    parts/editor_parts/file_point.h \
    parts/lexer/scopes/module_scope.h \
    parts/lexer/scopes/scope_node.h \
    parts/lexer/scopes/scope_types.h \
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
    parts/lexer/scopes/scope_node_type.h \
    parts/langs/ruby/lexer_ruby.h \
    parts/langs/ruby/predefined_ruby.h \
    misc/stack.h

FORMS    += ide_window.ui

RESOURCES += \
    resources.qrc
