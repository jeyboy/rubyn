#ifndef EDITOR_SEARCH_H
#define EDITOR_SEARCH_H

#include <qwidget.h>

#include "editor/editor_search_flags.h"

class QLineEdit;

class EditorSearch : public QWidget {
    Q_OBJECT

    int result_count;
    QLineEdit * predicate;
    QLineEdit * replace_predicate;
public:
    EditorSearch(QWidget * parent = nullptr);
signals:
    void find(const QString & pattern, const EditorSearchFlags & flags);
    void toNextResult(const bool & replace_current);
    void toPrevResult(const bool & replace_current);
    void repaceAll();
    void close();
public slots:
    void finded(const int & count);
};

#endif // EDITOR_SEARCH_H
