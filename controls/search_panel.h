#ifndef SEARCH_PANEL_H
#define SEARCH_PANEL_H

#include <qlineedit.h>
#include <qregularexpression.h>

class QCheckBox;

class SearchPanel : public QLineEdit {
    Q_OBJECT

    bool infinity_pad;
    QCheckBox * flag_case_sensitive;
    QCheckBox * flag_whole_word_only;
    QCheckBox * flag_reg_exp;
    QCheckBox * flag_unicode;

    void buildLayout();
    QRegularExpression buildRegex(QString pattern);
public:
    SearchPanel(QWidget * parent = nullptr);
    ~SearchPanel() Q_DECL_OVERRIDE;

    inline void setInfinityPad(const bool & pad = true) { infinity_pad = pad; }
protected:
    void paintEvent(QPaintEvent * event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
    void hideEvent(QHideEvent * e) Q_DECL_OVERRIDE;

    QSize sizeHint() const Q_DECL_OVERRIDE;
signals:
    void find(const QRegularExpression & pattern);
    void toNextResult(QString * replace = nullptr);
    void toPrevResult(QString * replace = nullptr);
    void close();
public slots:
    void predicateIsCorrect();
    void predicateHasError(const QString & error);
    void finded(const int & count);
};

#endif // SEARCH_PANEL_H
