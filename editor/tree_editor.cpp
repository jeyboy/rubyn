#include "tree_editor.h"

#include "project/file.h"
#include "editor/document_types/tree_document.h"
#include "styles/click_fix_style.h"
#include "delegates/tree_view_item_delegate.h"

TreeEditor::TreeEditor(QWidget * parent) : QTreeView(parent), searcher_is_opened(false) {
    setStyle(new ClickFixStyle());
}

void TreeEditor::openDocument(File * file) {   
    QAbstractItemModel * mdl = file -> asTree();

    setItemDelegate(new TreeViewItemDelegate(this));

    setModel(mdl);

    resizeColumnToContents(0);
    expandAll();
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

QScrollBar * TreeEditor::verticalScrollBar() { return QTreeView::verticalScrollBar(); }

void TreeEditor::ensureVisibleBlock(const qint64 & block_num) {

}

void TreeEditor::focusInEvent(QFocusEvent * e) {
    emit inFocus();

    QTreeView::focusInEvent(e);
}

void TreeEditor::keyPressEvent(QKeyEvent * e) {
    int curr_key = e -> key();

    if (curr_key == Qt::Key_Escape && searcher_is_opened) {
        emit searchRequired(false);
        return;
    }

    if (curr_key == Qt::Key_F && e -> modifiers() == Qt::ControlModifier) {
//        QTextCursor cursor = textCursor();

//        if (cursor.hasSelection()) {
//            QString str = cursor.selectedText();

//            str.replace(QChar(8233), char(13));

//            emit searchRequestRequired(str);
//        }
//        else emit searchRequired(true);

        emit searchRequired(true);
        return;
    }

    QTreeView::keyPressEvent(e);
}

//void TreeEditor::searchIsShow(const bool & show) {}
void TreeEditor::searchInitiated(const QRegularExpression & pattern, const bool & scroll) {
    qDebug() << "TreeEditor::searchInitiated" << pattern;

//    if (pattern.pattern().isEmpty()) {
//        searcher.clearSearch();
//        emit searchResultsFinded(0);
//    } else {
//        searcher.beginSearch(pattern);
//        Pair match = searcher.search(wrapper -> firstBlock());

//        if (scroll && match.first != NO_INFO) {
//            QTextCursor c = textCursor();
//            c.setPosition(match.first);

//            setTextCursor(c);
//            ensureCursorVisible();
//        }

//        emit searchResultsFinded(searcher.search_results);
//    }
    viewport() -> update();
}
void TreeEditor::searchNextResult(QString * replace) {}
void TreeEditor::searchPrevResult(QString * replace) {}
void TreeEditor::searchRepaceAll(const QString & replace) {}
void TreeEditor::searchClosed() {}
