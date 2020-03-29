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
    controls/line_dialog.cpp \
    controls/project_search_dialog.cpp \
    controls/project_search_panel.cpp \
    editor/custom/custom_chars.cpp \
    editor/custom/custom_cursor.cpp \
    editor/custom/custom_document.cpp \
    editor/custom/custom_editor.cpp \
    delegates/tree_view_item_delegate.cpp \
    editor/custom/custom_editor_searcher.cpp \
    editor/custom/custom_iblock.cpp \
    editor/custom/custom_layout_text_block.cpp \
    editor/custom/custom_selection.cpp \
    editor/custom/custom_text_block.cpp \
    ide_window.cpp \
    editor/document_types/text_document.cpp \
    editor/parts/body_overlay_info.cpp \
    editor/code_editor.cpp \
    highlighter/highlighter.cpp \
    lexer/css/css_lexer_frontend.cpp \
    lexer/css/css_predefined.cpp \
    lexer/html/html_lexer_frontend.cpp \
    lexer/html/html_predefined.cpp \
    lexer/js/js_lexer_frontend.cpp \
    lexer/js/js_predefined.cpp \
    lexer/lexer_context.cpp \
    lexer/ruby/ruby_grammar.cpp \
    lexer/ruby/ruby_lexer.cpp \
    lexer/ruby/ruby_lexer_control.cpp \
    lexer/ruby/ruby_predefined.cpp \
    lexer/yaml/yaml_lexer_frontend.cpp \
    lexer/yaml/yaml_predefined.cpp \
    misc/info_collector.cpp \
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
    delegates/tab_bar_item_delegate.cpp \
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
    lexer/lexers_factory.cpp \
    highlighter/highlight_format_factory.cpp \
    editor/block_user_data.cpp \
    lexer/igrammar.cpp \
    editor/text_document_layout.cpp \
    controls/logger_window.cpp \
    editor/code_editor_cache.cpp \
    editor/active_para_info.cpp \
    controls/header_dock_widget.cpp \
    delegates/project_tree_item_delegate.cpp \
    controls/color_picker.cpp \
    controls/color_grabber.cpp \
    controls/color_picker_property.cpp \
    controls/color_button.cpp \
    styles/jslider_style.cpp \
    controls/color_slider.cpp \
    misc/color.cpp \
    tools/filesystem_watcher/watcher.cpp \
    highlighter/ihighlighter.cpp \
    editor/document_types/pseudo_text_document.cpp \
    editor/idocument.cpp \
    highlighter/pseudo_highlighter.cpp \
    controls/debug_panel.cpp \
    controls/breakpoints_panel.cpp \
    controls/debug_view.cpp \
    delegates/debug_view_item_delegate.cpp \
    debugging/debug.cpp \
    debugging/idebug_interface.cpp \
    debugging/debug_stub_interface.cpp \
    delegates/base_item_delegate.cpp \
    editor/editor_search.cpp \
    editor/code_editor_searcher.cpp \
    editor/document_types/tree_document.cpp \
    controls/universal_editor.cpp \
    editor/tree_editor.cpp \
    editor/ieditor.cpp \
    editor/document_types/pad_tree_document.cpp \
    controls/search_panel.cpp \
    editor/breakpoints_controller.cpp \
    tools/process.cpp \
    controls/console_widget.cpp

HEADERS  += ide_window.h \
    controls/line_dialog.h \
    controls/project_search_dialog.h \
    controls/project_search_panel.h \
    editor/custom/custom_chars.h \
    editor/custom/custom_cursor.h \
    editor/custom/custom_document.h \
    editor/custom/custom_draw_context.h \
    editor/custom/custom_editor.h \
    delegates/tree_view_item_delegate.h \
    editor/custom/custom_editor_searcher.h \
    editor/custom/custom_iblock.h \
    editor/custom/custom_layout_text_block.h \
    editor/custom/custom_selection.h \
    editor/custom/custom_text_block.h \
    editor/custom/custom_visualization.h \
    lexer/css/css_grammar.h \
    lexer/css/css_lexer_control.h \
    lexer/css/css_lexer_frontend.h \
    lexer/css/css_predefined.h \
    lexer/css/css_state_lexems.h \
    lexer/html/html_grammar.h \
    lexer/html/html_lexer_control.h \
    lexer/html/html_lexer_frontend.h \
    lexer/html/html_predefined.h \
    lexer/html/html_state_lexems.h \
    lexer/ilexer_control.h \
    lexer/ilexer_scope.h \
    lexer/js/js_grammar.h \
    lexer/js/js_lexer_control.h \
    lexer/js/js_lexer_frontend.h \
    lexer/js/js_predefined.h \
    lexer/js/js_state_lexems.h \
    lexer/lexer_context.h \
    lexer/lexer_stack_flags.h \
    lexer/para_type.h \
    lexer/ruby/_ruby_flags.h \
    lexer/ruby/ruby_grammar.h \
    lexer/ruby/ruby_lexer.h \
    lexer/ruby/ruby_lexer_control.h \
    lexer/ruby/ruby_para_lexem.h \
    lexer/ruby/ruby_predefined.h \
    lexer/ruby/ruby_state_lexems.h \
    lexer/scope_type.h \
    lexer/state_lexem.h \
    lexer/yaml/yaml_grammar.h \
    lexer/yaml/yaml_lexer_control.h \
    lexer/yaml/yaml_lexer_frontend.h \
    lexer/yaml/yaml_predefined.h \
    lexer/yaml/yaml_state_lexems.h \
    misc/info_collector.h \
    misc/msg_info.h \
    misc/para_info.h \
    misc/para_list.h \
    misc/scope_list.h \
    styles/click_fix_style.h \
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
    delegates/tab_bar_item_delegate.h \
    styles/tab_bar_no_focus_style.h \
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
    tools/data_preparer/rubydoc_parser.h \
    misc/format.h \
    misc/screen.h \
    controls/completer_factory.h \
    controls/dumper.h \
    tools/data_preparer/data_obj.h \
    controls/toolbars.h \
    controls/run_configuration.h \
    editor/parts/overlay_info.h \
    highlighter/identifiers.h \
    misc/dumper_obj.h \
    lexer/lexers_factory.h \
    lexer/obj_lexems.h \
    lexer/igrammar.h \
    misc/_stack.h \
    misc/_chain.h \
    editor/text_document_layout.h \
    controls/logger_window.h \
    editor/code_editor_cache.h \
    editor/active_para_info.h \
    editor/active_folding_info.h \
    controls/header_dock_widget.h \
    delegates/project_tree_item_delegate.h \
    controls/color_picker.h \
    controls/color_grabber.h \
    controls/color_picker_property.h \
    controls/color_button.h \
    styles/jslider_style.h \
    controls/color_slider.h \
    misc/color.h \
    tools/filesystem_watcher/watcher.h \
    editor/completer_info.h \
    highlighter/ihighlighter.h \
    editor/document_types/pseudo_text_document.h \
    highlighter/pseudo_highlighter.h \
    controls/debug_panel.h \
    controls/breakpoints_panel.h \
    controls/debug_view.h \
    delegates/debug_view_item_delegate.h \
    debugging/idebug_interface.h \
    debugging/debug.h \
    debugging/debug_stub_interface.h \
    debugging/debug_breakpoint.h \
    delegates/base_item_delegate.h \
    editor/editor_search.h \
    editor/code_editor_searcher.h \
    editor/document_types/tree_document.h \
    controls/universal_editor.h \
    editor/tree_editor.h \
    editor/ieditor.h \
    editor/document_types/pad_tree_document.h \
    controls/search_panel.h \
    controls/dock_widget_search_connector.h \
    editor/breakpoints_controller.h \
    tools/process.h \
    controls/console_widget.h

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
