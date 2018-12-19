#include "tree_editor.h"

TreeEditor::TreeEditor(QWidget * parent) : QTreeView(parent) {

}

void TreeEditor::searchIsShow(const bool & show) {}
void TreeEditor::searchInitiated(const QString & pattern, const EditorSearchFlags & flags) {}
void TreeEditor::searchNextResult(QString * replace) {}
void TreeEditor::searchPrevResult(QString * replace) {}
void TreeEditor::searchRepaceAll(const QString & replace) {}
void TreeEditor::searchClosed() {}
