#-------------------------------------------------
#
# Project created by QtCreator 2015-12-06T23:30:22
#
#-------------------------------------------------

QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rubyn
TEMPLATE = app

SOURCES += main.cpp\
    ide_window.cpp \
    editor/document_types/text_document.cpp \
    editor/parts/body_overlay_info.cpp \
    editor/code_editor.cpp \
    highlighter/highlighter.cpp \
    highlighter/para_info.cpp \
    project/file.cpp \
    project/project.cpp \
    project/projects.cpp \
    controls/project_tree.cpp \
    controls/dock_widget.cpp \
    controls/dock_widgets.cpp \
    project/code_formats.cpp \
    controls/logger.cpp \
    project/ifolder.cpp \
    project/recursive_folder.cpp \
    lexer/ilexer.cpp \
    lexer/regexp_lexer.cpp \
    lexer/ab_lexer.cpp \
    controls/tabs_block.cpp \
    controls/tab_bar.cpp \
    controls/tab_bar_item_delegate.cpp \
    controls/completer.cpp \
    misc/variant_convertor.cpp \
    misc/country.cpp \
    tools/web_manager/web_connection.cpp \
    tools/web_manager/web_cookies.cpp \
    tools/web_manager/web_manager.cpp \
    tools/web_manager/web_proxy.cpp \
    tools/web_manager/web_request.cpp \
    tools/web_manager/web_response.cpp \
    tools/data_preparer/rubydoc_preparer.cpp \
    tools/json/json.cpp \
    tools/json/json_arr.cpp \
    tools/json/json_obj.cpp \
    tools/html/html_decoding.cpp \
    tools/html/html_keys.cpp \
    tools/html/html_page.cpp \
    tools/html/html_selector.cpp \
    tools/html/html_set.cpp \
    tools/html/html_tag.cpp \
    tools/html/unicode.cpp \
    tools/archive.cpp \
    misc/dir.cpp \
    tools/files_proc_manager.cpp

HEADERS  += ide_window.h \
    controls/dock_widgets.h \
    editor/idocument.h \
    editor/document_types/binary_document.h \
    editor/document_types/documents_types.h \
    editor/document_types/image_document.h \
    editor/document_types/text_document.h \
    editor/parts/body_overlay_info.h \
    editor/parts/extra_area.h \
    editor/parts/overlay_info.h \
    editor/code_editor.h \
    highlighter/block_user_data.h \
    highlighter/msg_info.h \
    highlighter/highlight_format_factory.h \
    highlighter/highlighter.h \
    highlighter/para_info.h \
    highlighter/para_list.h \
    lexer/ruby/flags_ruby.h \
    lexer/ruby/grammar_ruby.h \
    lexer/ruby/lexer_log.h \
    lexer/ruby/lexer_ruby.h \
    lexer/ruby/lexer_ruby_regexp.h \
    lexer/ruby/predefined_ruby.h \
    lexer/ruby/preset_ruby.h \
    misc/chain.h \
    misc/defines.h \
    misc/singleton.h \
    misc/stack.h \
    misc/token_list.h \
    misc/utils.h \
    project/file.h \
    project/project.h \
    project/projects.h \
    project/project_format.h \
    project/code_formats.h \
    controls/project_tree.h \
    controls/dock_widget.h \
    controls/logger.h \
    project/ifolder.h \
    project/recursive_folder.h \
    lexer/ilexer.h \
    lexer/regexp_lexer.h \
    lexer/ab_lexer.h \
    highlighter/highlight_rule.h \
    controls/tabs_block.h \
    controls/tab_bar.h \
    controls/tab_bar_item_delegate.h \
    controls/tab_bar_no_focus_style.h \
    controls/completer.h \
    misc/func.h \
    misc/variant_convertor.h \
    misc/variant_ptr.h \
    misc/country.h \
    tools/html/html_decoding.h \
    tools/html/html_global.h \
    tools/html/html_keys.h \
    tools/html/html_page.h \
    tools/html/html_selector.h \
    tools/html/html_set.h \
    tools/html/html_tag.h \
    tools/html/unicode.h \
    tools/json/json.h \
    tools/json/json_arr.h \
    tools/json/json_global.h \
    tools/json/json_obj.h \
    tools/web_manager/web_connection.h \
    tools/web_manager/web_cookies.h \
    tools/web_manager/web_headers.h \
    tools/web_manager/web_manager.h \
    tools/web_manager/web_manager_global.h \
    tools/web_manager/web_proxy.h \
    tools/web_manager/web_request.h \
    tools/web_manager/web_request_params.h \
    tools/web_manager/web_response.h \
    tools/web_manager/web_utils.h \
    tools/data_preparer/iruby_stubs_preparer.h \
    tools/data_preparer/rubydoc_preparer.h \
    tools/archive.h \
    tools/thread_cell.h \
    tools/thread_utils.h \
    misc/dir.h \
    tools/files_proc_manager.h \
    tools/fuzzy_comparison.h

FORMS    += ide_window.ui

RESOURCES += \
    resources.qrc

RC_FILE = rubyn.rc
