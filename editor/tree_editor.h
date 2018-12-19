#ifndef TREE_EDITOR_H
#define TREE_EDITOR_H

#include <qtreeview.h>

#include "editor/ieditor.h"

class TreeEditor : public QTreeView, public IEditor {
    Q_OBJECT
public:
    TreeEditor(QWidget * parent = Q_NULLPTR);

public slots:
    void searchIsShow(const bool & show) Q_DECL_OVERRIDE;
    void searchInitiated(const QString & pattern, const EditorSearchFlags & flags) Q_DECL_OVERRIDE;
    void searchNextResult(QString * replace = nullptr) Q_DECL_OVERRIDE;
    void searchPrevResult(QString * replace = nullptr) Q_DECL_OVERRIDE;
    void searchRepaceAll(const QString & replace) Q_DECL_OVERRIDE;
    void searchClosed() Q_DECL_OVERRIDE;
};

#endif // TREE_EDITOR_H
