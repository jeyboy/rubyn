#ifndef EDITOR_SEARCH_H
#define EDITOR_SEARCH_H

#include <qwidget.h>

class QLineEdit;

class EditorSearch : public QWidget {
    Q_OBJECT

    QLineEdit * predicate;
    QLineEdit * replace_predicate;
public:
    EditorSearch(QWidget * parent = nullptr);
protected slots:
    void showPredicateMenu();
};

#endif // EDITOR_SEARCH_H
