#include "tree_editor.h"

#include "project/file.h"

TreeEditor::TreeEditor(QWidget * parent) : QTreeView(parent) {

}

void TreeEditor::openDocument(File * file) {

}

//bool TreeEditor::search(const QString & pattern, QTreeWidgetItem * item) {
//    bool empty = pattern.isEmpty();
//    bool has_item = false;
//    int items_count = item -> childCount();

//    for(int i = 0; i < items_count; i++) {
//        QTreeWidgetItem * child = item -> child(i);
//        bool valid = false;

//        child -> setData(0, Qt::UserRole + 10, property_dropper);

//        if (child -> childCount() > 0) {
//            if (child -> data(0, Qt::UserRole + 11).isNull())
//                child -> setData(0, Qt::UserRole + 11, child -> isExpanded());

//            valid = search(pattern, child);

//            if (valid && !child -> isExpanded())
//                child -> setExpanded(true);
//        }

//        if (!empty) {
//            QString child_text = child -> text(0);

//            int pos = child_text.indexOf(pattern, 0, Qt::CaseInsensitive);

//            if (pos != -1) {
//                valid = true;
//                child -> setData(0, Qt::UserRole + 10, pos);
//            }
//        }

//        has_item |= empty || valid;
//        child -> setHidden(!(valid || empty));
//    }

//    return has_item;
//}

//bool TreeEditor::search(const QString & pattern) {
//    setProperty("in_search", !pattern.isEmpty());
//    setProperty("search_len", pattern.length());

//    //        return search(pattern, invisibleRootItem());

//    bool has_item = false;
//    int items_count = topLevelItemCount();

//    for(int i = 0; i < items_count; i++) {
//        QTreeWidgetItem * child = topLevelItem(i);

//        if (child -> childCount() > 0) {
//            has_item |= search(pattern, child);
//        }
//    }

//    return has_item;
//}

void TreeEditor::setVisible(bool visible) { QTreeView::setVisible(visible); }

//void TreeEditor::searchIsShow(const bool & show) {}
void TreeEditor::searchInitiated(const QRegularExpression & pattern) {}
void TreeEditor::searchNextResult(QString * replace) {}
void TreeEditor::searchPrevResult(QString * replace) {}
void TreeEditor::searchRepaceAll(const QString & replace) {}
void TreeEditor::searchClosed() {}
