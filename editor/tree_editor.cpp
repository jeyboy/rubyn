#include "tree_editor.h"

#include "project/file.h"

TreeEditor::TreeEditor(QWidget * parent) : QTreeView(parent) {

}

void TreeEditor::openDocument(File * file) {

}

void TreeEditor::setVisible(bool visible) { QTreeView::setVisible(visible); }

void TreeEditor::searchIsShow(const bool & show) {}
void TreeEditor::searchInitiated(const QString & pattern, const EditorSearchFlags & flags) {}
void TreeEditor::searchNextResult(QString * replace) {}
void TreeEditor::searchPrevResult(QString * replace) {}
void TreeEditor::searchRepaceAll(const QString & replace) {}
void TreeEditor::searchClosed() {}
