#include "search_panel.h"

#include <qcheckbox.h>
#include <qlineedit.h>
#include <qevent.h>
#include <qstringbuilder.h>
#include <qmenu.h>
#include <qwidgetaction.h>
#include <qtoolbutton.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qpainter.h>

#include <qdebug.h>

void SearchPanel::buildLayout() {
    QMenu * menu = new QMenu(this);
    QWidgetAction * options_btn = new QWidgetAction(this);
    QToolButton * btn = new QToolButton(this);

    btn -> setIcon(QPixmap(":/search_btn").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    btn -> setMenu(menu);
    btn -> setPopupMode(QToolButton::InstantPopup);
    btn -> setCursor(QCursor(Qt::PointingHandCursor));
//    btn -> setStyleSheet(QLatin1Literal("QToolButton { border: none; } QToolButton::menu-indicator { top: 3px; left: 3px; width: 4px, height: 4px; } "));
    options_btn -> setDefaultWidget(btn);

    addAction(options_btn, QLineEdit::LeadingPosition);


    move_prev_btn = new QWidgetAction(this);
    btn = new QToolButton(this);
    btn -> setIcon(QPixmap(":/row_right").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    btn -> setCursor(QCursor(Qt::PointingHandCursor));
    move_prev_btn -> setDefaultWidget(btn);
    btn -> setToolTip(QLatin1Literal("Move to next"));
    addAction(move_prev_btn, QLineEdit::TrailingPosition);
    connect(btn, &QToolButton::clicked, [=]() { emit toNextResult(); });


    move_next_btn = new QWidgetAction(this);
    btn = new QToolButton(this);
    btn -> setIcon(QPixmap(":/row_left").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    btn -> setCursor(QCursor(Qt::PointingHandCursor));
    move_next_btn -> setDefaultWidget(btn);
    btn -> setToolTip(QLatin1Literal("Move to prev"));
    addAction(move_next_btn, QLineEdit::TrailingPosition);
    connect(btn, &QToolButton::clicked, [=]() { emit toPrevResult(); });


    flag_case_sensitive = new QCheckBox(QLatin1Literal("Match Case"), menu);
    QWidgetAction * flag_case_sensitive_action = new QWidgetAction(menu);
    flag_case_sensitive_action -> setDefaultWidget(flag_case_sensitive);
    menu -> addAction(flag_case_sensitive_action);
    connect(flag_case_sensitive, &QCheckBox::clicked, [=](bool) { emit find(buildRegex(text())); });

    flag_whole_word_only = new QCheckBox(QLatin1Literal("Words"), menu);
    QWidgetAction * flag_whole_word_only_action = new QWidgetAction(menu);
    flag_whole_word_only_action -> setDefaultWidget(flag_whole_word_only);
    menu -> addAction(flag_whole_word_only_action);
    connect(flag_whole_word_only, &QCheckBox::clicked, [=](bool) { emit find(buildRegex(text())); });

    flag_reg_exp = new QCheckBox(QLatin1Literal("Regex"), menu);
    QWidgetAction * flag_reg_exp_action = new QWidgetAction(menu);
    flag_reg_exp_action -> setDefaultWidget(flag_reg_exp);
    menu -> addAction(flag_reg_exp_action);
    connect(flag_reg_exp, &QCheckBox::clicked, [=](bool) { emit find(buildRegex(text())); });

    flag_unicode = new QCheckBox(QLatin1Literal("Unicode"), menu);
    QWidgetAction * flag_unicode_action = new QWidgetAction(menu);
    flag_unicode_action -> setDefaultWidget(flag_unicode);
    menu -> addAction(flag_unicode_action);
    connect(flag_unicode, &QCheckBox::clicked, [=](bool) { emit find(buildRegex(text())); });
}

QRegularExpression SearchPanel::buildRegex(QString pattern) {
    QString val = pattern;

    QRegularExpression::PatternOptions options = QRegularExpression::DotMatchesEverythingOption;

    if (!flag_case_sensitive -> isChecked())
        options |= QRegularExpression::CaseInsensitiveOption;

    if (flag_unicode -> isChecked())
        options |= QRegularExpression::UseUnicodePropertiesOption;

    val = val.remove(QRegularExpression(QLatin1Literal("/r|/n|<br>|<br/>")));

    if (pattern.length() != val.length())
        options |= QRegularExpression::MultilineOption;

    if (!flag_reg_exp -> isChecked())
        val = QRegularExpression::escape(val);

    if (flag_whole_word_only -> isChecked())
        val = QLatin1Literal("\\b") % val % QLatin1Literal("\\b");

    QRegularExpression res(val, options);
    res.optimize();

    return res;
}

SearchPanel::SearchPanel(QWidget * parent) : QLineEdit(parent), infinity_pad(false), flag_case_sensitive(nullptr), flag_whole_word_only(nullptr), flag_reg_exp(nullptr), flag_unicode(nullptr) {
//    setMinimumSize(0, 0);
//    setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
//    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    buildLayout();

    connect(this, &SearchPanel::textChanged, [=](const QString & text) { emit find(buildRegex(text)); });
}

SearchPanel::~SearchPanel() {}

void SearchPanel::removePrevNext() {
    move_prev_btn -> deleteLater();
    move_next_btn -> deleteLater();
}

void SearchPanel::paintEvent(QPaintEvent * event) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style() -> drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QLineEdit::paintEvent(event);
}

void SearchPanel::keyPressEvent(QKeyEvent * e) {
    switch(e -> key()) {
        case Qt::Key_Escape: { emit returnPressed(); break;}

        default: QLineEdit::keyPressEvent(e);
    }
}

void SearchPanel::hideEvent(QHideEvent * e) {
    emit close();
    QLineEdit::hideEvent(e);
}

QSize SearchPanel::sizeHint() const {
    QSize res = QLineEdit::sizeHint();

    if (infinity_pad)
        res.rwidth() += 99999;

    return res;
}

void SearchPanel::predicateIsCorrect() {
    qDebug() << "EditorSearch::predicateIsCorrect";

    setToolTip(QLatin1Literal("Searching..."));
    setStyleSheet(QLatin1Literal("QLineEdit { border: 1px solid green;}"));
}
void SearchPanel::predicateHasError(const QString & error) {
    qDebug() << "EditorSearch::predicateHasError" << error;

    setToolTip(error);
    setStyleSheet(QLatin1Literal("QLineEdit { border: 1px solid red;}"));
}

void SearchPanel::finded(const int & count) {
    qDebug() << "EditorSearch::finded" << count;

    setToolTip(QLatin1Literal("Found ") + QString::number(count));
}
