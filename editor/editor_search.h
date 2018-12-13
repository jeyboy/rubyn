#ifndef EDITOR_SEARCH_H
#define EDITOR_SEARCH_H

#include <qwidget.h>

#include "editor/editor_search_flags.h"

class QLineEdit;
class QCheckBox;
class QLabel;

class EditorSearch : public QWidget {
    Q_OBJECT

    int result_count;
    QLineEdit * predicate;
    QLineEdit * replace_predicate;

    QLabel * l1;
    QLabel * l2;

    QCheckBox * flag_case_sensitive;
    QCheckBox * flag_whole_word_only;
    QCheckBox * flag_reg_exp;
    QCheckBox * flag_unicode;

    EditorSearchFlags flags();
public:
    EditorSearch(const bool & has_replace, QWidget * parent = nullptr);
signals:
    void find(const QString & pattern, const EditorSearchFlags & flags);
    void toNextResult(const bool & replace_current);
    void toPrevResult(const bool & replace_current);
    void replaceAll();
    void close();
public slots:
    void predicateIsCorrect();
    void predicateHasError(const QString & error);
    void finded(const int & count);
};

#endif // EDITOR_SEARCH_H
