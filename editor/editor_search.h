#ifndef EDITOR_SEARCH_H
#define EDITOR_SEARCH_H

#include <qwidget.h>

class QLineEdit;
class SearchPanel;
class QCheckBox;
class QLabel;

#define SEARCH_LABEL_TEXT QLatin1String("Search:")

class EditorSearch : public QWidget {
    Q_OBJECT

    int result_count;
    SearchPanel * predicate;
    QLineEdit * replace_predicate;

    QLabel * l1;
    QLabel * l2;
protected:
    void paintEvent(QPaintEvent * event);
public:
    EditorSearch(const bool & has_replace, QWidget * parent = nullptr);
signals:
    void find(const QRegularExpression & pattern);
    void toNextResult(QString * replace = nullptr);
    void toPrevResult(QString * replace = nullptr);
    void replaceAll(const QString & replace);
    void close();
public slots:
    void initiateSearch(const QString & pattern = QString());
    void changeVisibility(const bool & show);
    void predicateIsCorrect();
    void predicateHasError(const QString & error);
    void finded(const int & count); 
};

#endif // EDITOR_SEARCH_H
