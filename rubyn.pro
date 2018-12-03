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
    tools/files_proc_manager.cpp \
    tools/data_preparer/rubydoc_parser.cpp \
    misc/format.cpp \
    controls/completer_factory.cpp \
    controls/dumper.cpp \
    controls/toolbars.cpp \
    controls/run_configuration.cpp \
    lexer/yaml/lexer_frontend_yaml.cpp \
    lexer/lexers_factory.cpp \
    lexer/ruby/lexer_frontend_ruby.cpp \
    lexer/ruby/lexer_regexp_ruby.cpp \
    highlighter/highlight_format_factory.cpp \
    lexer/ruby/predefined_ruby.cpp \
    lexer/ruby/grammar_ruby.cpp \
    editor/block_user_data.cpp \
    lexer/igrammar.cpp \
    editor/text_document_layout.cpp \
    controls/logger_window.cpp \
    editor/code_editor_cache.cpp \
    editor/active_para_info.cpp \
    controls/header_dock_widget.cpp \
    controls/search_box.cpp \
    controls/project_tree_item_delegate.cpp \
    controls/color_picker.cpp \
    controls/color_grabber.cpp \
    controls/color_picker_property.cpp \
    controls/color_button.cpp \
    controls/jslider_style.cpp \
    controls/color_slider.cpp \
    misc/color.cpp \
    tools/filesystem_watcher/watcher.cpp \
    highlighter/ihighlighter.cpp \
    editor/document_types/pseudo_text_document.cpp \
    editor/idocument.cpp \
    highlighter/pseudo_highlighter.cpp \
    controls/debug_panel.cpp

HEADERS  += ide_window.h \
    controls/dock_widgets.h \
    editor/idocument.h \
    editor/document_types/binary_document.h \
    editor/document_types/documents_types.h \
    editor/document_types/image_document.h \
    editor/document_types/text_document.h \
    editor/parts/body_overlay_info.h \
    editor/parts/extra_area.h \
    editor/code_editor.h \
    editor/block_user_data.h \
    highlighter/msg_info.h \
    highlighter/highlight_format_factory.h \
    highlighter/highlighter.h \
    highlighter/para_info.h \
    highlighter/para_list.h \
    lexer/ruby/grammar_ruby.h \
    lexer/ruby/predefined_ruby.h \
    misc/defines.h \
    misc/singleton.h \
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
    tools/fuzzy_comparison.h \
    lexer/yaml/yml_lexer.h \
    tools/data_preparer/rubydoc_parser.h \
    misc/format.h \
    misc/screen.h \
    controls/completer_factory.h \
    controls/dumper.h \
    tools/data_preparer/data_obj.h \
    controls/toolbars.h \
    controls/run_configuration.h \
    editor/parts/overlay_info.h \
    lexer/yaml/lexems_yaml.h \
    highlighter/identifiers.h \
    lexer/yaml/lexer_frontend_yaml.h \
    misc/dumper_obj.h \
    lexer/lexers_factory.h \
    lexer/ruby/lexer_frontend_ruby.h \
    lexer/ruby/lexer_regexp_ruby.h \
    lexer/ruby/_flags_ruby.h \
    lexer/lexer_control.h \
    lexer/state_lexems.h \
    lexer/obj_lexems.h \
    lexer/igrammar.h \
    lexer/ruby/_lexer_ruby.h \
    misc/_stack.h \
    misc/_chain.h \
    highlighter/para_type.h \
    editor/text_document_layout.h \
    controls/logger_window.h \
    editor/code_editor_cache.h \
    editor/active_para_info.h \
    editor/active_folding_info.h \
    controls/header_dock_widget.h \
    controls/search_box.h \
    controls/project_tree_item_delegate.h \
    controls/color_picker.h \
    controls/color_grabber.h \
    controls/color_picker_property.h \
    controls/color_button.h \
    controls/jslider_style.h \
    controls/color_slider.h \
    misc/color.h \
    tools/filesystem_watcher/watcher.h \
    editor/completer_info.h \
    highlighter/ihighlighter.h \
    editor/document_types/pseudo_text_document.h \
    highlighter/pseudo_highlighter.h \
    controls/debug_panel.h

FORMS    += ide_window.ui

RESOURCES += \
    resources.qrc

RC_FILE = rubyn.rc

unix:!mac {
#        QT += gui-private
#        CONFIG += link_pkgconfig
#        PKGCONFIG += x11
#        LDFLAGS =- lX11
#        DEFINES += HAVE_X11
#        SOURCES += modules/controls/qxtglobalshortcut_x11.cpp
        SOURCES += tools/filesystem_watcher/watcher_x11.cpp
}
win32: {
#    SOURCES += modules/controls/qxtglobalshortcut_win.cpp
    SOURCES += tools/filesystem_watcher/watcher_win.cpp
}
mac: {
#    SOURCES += modules/controls/qxtglobalshortcut_mac.cpp
    SOURCES += tools/filesystem_watcher/watcher_mac.cpp
}
