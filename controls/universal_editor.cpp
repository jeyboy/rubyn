#include "universal_editor.h"

#include "completer_factory.h"

#include "controls/logger.h"

#include "project/file.h"

#include "editor/code_editor.h"
#include "editor/editor_search.h"
//#include "editor/document_types/text_document.h"

#include <qboxlayout.h>

void UniversalEditor::setupLayout() {
    QVBoxLayout * col_layout = new QVBoxLayout(this);

    col_layout -> setContentsMargins(1,1,1,1);
    col_layout -> setSpacing(1);


    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(11);

    _code_editor = new CodeEditor(this);
    _code_editor -> setFont(font);

    col_layout -> addWidget(_code_editor, 1);

    _search_bar = new EditorSearch(true, this);
    col_layout -> addWidget(_search_bar, 0);
    _search_bar -> hide();

    connect(_code_editor, &CodeEditor::searchResultsFinded, _search_bar, &EditorSearch::finded);
    connect(_code_editor, &CodeEditor::searchWrongPattern, _search_bar, &EditorSearch::predicateHasError);
    connect(_code_editor, &CodeEditor::searchCorrectPattern, _search_bar, &EditorSearch::predicateIsCorrect);
    connect(_code_editor, &CodeEditor::searchRequired, this, &UniversalEditor::showSearchPanel);

    connect(_search_bar, &EditorSearch::find, _code_editor, &CodeEditor::searchInitiated);
    connect(_search_bar, &EditorSearch::toNextResult, _code_editor, &CodeEditor::searchNextResult);
    connect(_search_bar, &EditorSearch::toPrevResult, _code_editor, &CodeEditor::searchPrevResult);
    connect(_search_bar, &EditorSearch::replaceAll, _code_editor, &CodeEditor::searchRepaceAll);
    connect(_search_bar, &EditorSearch::close, _code_editor, &CodeEditor::searchClosed);
}

void UniversalEditor::setupCompleter() {
    _completer = new Completer(this);

    _completer -> addItem(new QStandardItem(CompleterFactory::obj().ico(lmt_const), QLatin1Literal("alpha")));
    _completer -> addItem(new QStandardItem(CompleterFactory::obj().ico(lmt_global_method), QLatin1Literal("omega")));
    _completer -> addItem(new QStandardItem(CompleterFactory::obj().ico(lmt_global_var), QLatin1Literal("omicron")));
    _completer -> addItem(new QStandardItem(CompleterFactory::obj().ico(lmt_instance_method), QLatin1Literal("zeta")));
    _completer -> addItem(new QStandardItem(CompleterFactory::obj().ico(lmt_instance_var), QLatin1Literal("instance_var")));
    _completer -> addItem(new QStandardItem(CompleterFactory::obj().ico(lmt_local_var), QLatin1Literal("local_var")));
    _completer -> addItem(new QStandardItem(CompleterFactory::obj().ico(lmt_object_method), QLatin1Literal("obj_method")));
    _completer -> addItem(new QStandardItem(CompleterFactory::obj().ico(lmt_object_var), QLatin1Literal("obj_var")));
    _completer -> addItem(new QStandardItem(CompleterFactory::obj().ico(lmt_private_const), QLatin1Literal("private_const")));
    _completer -> addItem(new QStandardItem(CompleterFactory::obj().ico(lmt_private_instance_method), QLatin1Literal("private_instance_method")));
    _completer -> addItem(new QStandardItem(CompleterFactory::obj().ico(lmt_private_obj_method), QLatin1Literal("private_obj_method")));

    _completer -> addItem(new QStandardItem(CompleterFactory::obj().ico(lmt_class), QLatin1Literal("Class")));
    _completer -> addItem(new QStandardItem(CompleterFactory::obj().ico(lmt_module), QLatin1Literal("Module")));

    _completer -> addItem(new QStandardItem(CompleterFactory::obj().ico(lmt_template), QLatin1Literal("template")));
    _completer -> addItem(new QStandardItem(CompleterFactory::obj().ico(lmt_unknow), QLatin1Literal("unknow")));

    _completer -> update();
}

UniversalEditor::UniversalEditor(QWidget * parent) : QWidget(parent), _code_editor(nullptr), _file(nullptr), _completer(nullptr) {
    setupLayout();

    setupCompleter();
}

bool UniversalEditor::openFile(File * file) {
    switch(file -> baseFormatType()) {
        case ft_text: {
            _code_editor -> show();

            _code_editor -> openDocument(file);
//            _code_editor -> setCompleter(_completer);
        break;}
        case ft_image: //{ emit parent() -> imageAdded(url); break;}
        case ft_binary: //{ emit parent() -> binaryAdded(url); break;}
        case ft_tree: //{ emit parent() -> binaryAdded(url); break;}
        default: {
            Logger::error(QLatin1Literal("IDE"), QLatin1Literal("Undefined format of file: '") % QString::number(file -> formatType()) % '\'');
            return false;
        }
    };

    return true;
}

const QString & UniversalEditor::documentUid() {
    return _file ? _file -> uid() : File::default_uid;
}

int UniversalEditor::verticalScrollBar() {
    QScrollBar * scroll = _code_editor -> verticalScrollBar();
    return scroll -> value();
}

void UniversalEditor::showSearchPanel(const bool & show) {
    qDebug() << "TabsBlock::showSearchPanel" << show;

    _search_bar -> changeVisibility(show);

    if (!show)
        _code_editor -> searchClosed();
}