#ifndef SEARCH_PANEL_H
#define SEARCH_PANEL_H

#include <qlineedit.h>
#include <qregularexpression.h>

class QCheckBox;
class QWidgetAction;

class SearchPanel : public QLineEdit {
    Q_OBJECT

    bool infinity_pad;
    QCheckBox * flag_case_sensitive;
    QCheckBox * flag_whole_word_only;
    QCheckBox * flag_reg_exp;
    QCheckBox * flag_unicode;

    QWidgetAction * move_prev_btn;
    QWidgetAction * move_next_btn;

    void buildLayout();
    QRegularExpression buildRegex(const QString & pattern);
public:
    SearchPanel(QWidget * parent = nullptr);
    ~SearchPanel() Q_DECL_OVERRIDE;

    inline void setInfinityPad(const bool & pad = true) { infinity_pad = pad; }
    void removePrevNext();
    void activate();
protected:
    void paintEvent(QPaintEvent * event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
    void hideEvent(QHideEvent * e) Q_DECL_OVERRIDE;

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void predicateIsCorrect();
    void predicateHasError(const QString & error);
signals:
    void closed();
    void find(const QRegularExpression & pattern);
    void toNextResult(QString * replace = nullptr);
    void toPrevResult(QString * replace = nullptr);
    void clearRequires();
public slots:
    void finded(const int & count);
};

#endif // SEARCH_PANEL_H
