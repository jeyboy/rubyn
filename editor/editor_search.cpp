#include "editor_search.h"

#include <qlineedit.h>
#include <qcheckbox.h>
#include <qtoolbutton.h>
#include <qlabel.h>
#include <qaction.h>
#include <qwidgetaction.h>
#include <qmenu.h>
#include <qlayout.h>
#include <qevent.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qpainter.h>

#include <qdebug.h>

EditorSearchFlags EditorSearch::flags() {
    int res = esf_none;

    if (flag_case_sensitive -> isChecked())
        res |= esf_match_case;

    if (flag_whole_word_only -> isChecked())
        res |= esf_words_only;

    if (flag_reg_exp -> isChecked())
        res |= esf_regex;

    if (flag_unicode -> isChecked())
        res |= esf_unicode;

    return (EditorSearchFlags)res;
}

void EditorSearch::paintEvent(QPaintEvent * event) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style() -> drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}

EditorSearch::EditorSearch(const bool & has_replace, QWidget * parent) : QWidget(parent), result_count(0), predicate(nullptr), replace_predicate(nullptr),
    l1(nullptr), l2(nullptr), flag_case_sensitive(nullptr), flag_whole_word_only(nullptr), flag_reg_exp(nullptr), flag_unicode(nullptr)
{
    setStyleSheet(
        QLatin1Literal(
            "EditorSearch {"
            "   background-color: #555;"
            "}"

            "EditorSearch QLabel {"
            "   color: #fff;"
            "   background-color: #555;"
            "}"
        )
    );


    QToolButton * btn = nullptr;

    QHBoxLayout * search_layout = new QHBoxLayout();
    search_layout -> setContentsMargins(0, 0, 0, 0);

    if (has_replace) {
        QVBoxLayout * main_layout = new QVBoxLayout(this);
        main_layout -> setContentsMargins(2, 1, 1, 1);
        main_layout -> setSpacing(3);

        QHBoxLayout * replace_layout = new QHBoxLayout();
        replace_layout -> setContentsMargins(0, 0, 0, 0);

        main_layout -> addLayout(search_layout);
        main_layout -> addLayout(replace_layout);

        l2 = new QLabel(QLatin1Literal("Replace with:"), this);
        QFont f = l2 -> font();
        f.setBold(true);
        f.setKerning(true);
        l2 -> setFont(f);

        replace_layout -> addWidget(l2, 0);
        replace_predicate = new QLineEdit(this);
        replace_predicate -> setPlaceholderText(QLatin1Literal("Replacement"));
        replace_predicate -> setMinimumWidth(150);
        replace_layout -> addWidget(replace_predicate, 1);


        QWidgetAction * replace_all_btn = new QWidgetAction(this);
        btn = new QToolButton(this);
        btn -> setIcon(QPixmap(":/search_replace_btn").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        btn -> setCursor(QCursor(Qt::PointingHandCursor));
        replace_all_btn -> setDefaultWidget(btn);
        btn -> setToolTip(QLatin1Literal("Replace all"));
        replace_predicate -> addAction(replace_all_btn, QLineEdit::TrailingPosition);
        connect(btn, &QToolButton::clicked, [=]() { emit replaceAll(replace_predicate -> text()); });


        QWidgetAction * replace_prev_btn = new QWidgetAction(this);
        btn = new QToolButton(this);
        btn -> setIcon(QPixmap(":/row_right").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        btn -> setCursor(QCursor(Qt::PointingHandCursor));
        replace_prev_btn -> setDefaultWidget(btn);
        btn -> setToolTip(QLatin1Literal("Replace current and move to next"));
        replace_predicate -> addAction(replace_prev_btn, QLineEdit::TrailingPosition);
        connect(btn, &QToolButton::clicked, [=]() { emit toNextResult(new QString(replace_predicate -> text())); });


        QWidgetAction * replace_next_btn = new QWidgetAction(this);
        btn = new QToolButton(this);
        btn -> setIcon(QPixmap(":/row_left").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        btn -> setCursor(QCursor(Qt::PointingHandCursor));
        replace_next_btn -> setDefaultWidget(btn);
        btn -> setToolTip(QLatin1Literal("Replace current and move to prev"));
        replace_predicate -> addAction(replace_next_btn, QLineEdit::TrailingPosition);
        connect(btn, &QToolButton::clicked, [=]() { emit toPrevResult(new QString(replace_predicate -> text())); });
    }
    else {
        setLayout(search_layout);
        search_layout -> setContentsMargins(2, 1, 1, 1);
    }


    l1 = new QLabel(QLatin1Literal("Search:"), this);

    if (l2)
        l1 -> setFixedWidth(l2 -> sizeHint().rwidth());

    QFont f = l1 -> font();
    f.setBold(true);
    f.setKerning(true);
    l1 -> setFont(f);

    search_layout -> addWidget(l1, 0);
    predicate = new QLineEdit(this);
    predicate -> setMinimumWidth(150);
    predicate -> setPlaceholderText(QLatin1Literal("Search"));
    search_layout -> addWidget(predicate, 1);
    connect(predicate, &QLineEdit::textChanged, [=](const QString & text) { emit find(text, flags()); });


    btn = new QToolButton(this);
    btn -> setIcon(QPixmap(":/tools/close").scaled(btn -> iconSize().width(), btn -> iconSize().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    btn -> setToolTip(QLatin1Literal("Close"));
    btn -> setStyleSheet(QLatin1Literal("border: none;"));
    connect(btn, &QToolButton::clicked, [=]() { hide(); emit close(); });
    search_layout -> addWidget(btn, 0);


    QMenu * menu = new QMenu(this);
    QWidgetAction * options_btn = new QWidgetAction(this);
    btn = new QToolButton(this);

    btn -> setIcon(QPixmap(":/search_btn").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    btn -> setMenu(menu);
    btn -> setPopupMode(QToolButton::InstantPopup);
    btn -> setCursor(QCursor(Qt::PointingHandCursor));
//    btn -> setStyleSheet(QLatin1Literal("QToolButton { border: none; } QToolButton::menu-indicator { top: 3px; left: 3px; width: 4px, height: 4px; } "));
    options_btn -> setDefaultWidget(btn);

    predicate -> addAction(options_btn, QLineEdit::LeadingPosition);



    QWidgetAction * move_prev_btn = new QWidgetAction(this);
    btn = new QToolButton(this);
    btn -> setIcon(QPixmap(":/row_right").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    btn -> setCursor(QCursor(Qt::PointingHandCursor));
    move_prev_btn -> setDefaultWidget(btn);
    btn -> setToolTip(QLatin1Literal("Move to next"));
    predicate -> addAction(move_prev_btn, QLineEdit::TrailingPosition);
    connect(btn, &QToolButton::clicked, [=]() { emit toNextResult(); });


    QWidgetAction * move_next_btn = new QWidgetAction(this);
    btn = new QToolButton(this);
    btn -> setIcon(QPixmap(":/row_left").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    btn -> setCursor(QCursor(Qt::PointingHandCursor));
    move_next_btn -> setDefaultWidget(btn);
    btn -> setToolTip(QLatin1Literal("Move to prev"));
    predicate -> addAction(move_next_btn, QLineEdit::TrailingPosition);
    connect(btn, &QToolButton::clicked, [=]() { emit toPrevResult(); });


    flag_case_sensitive = new QCheckBox(QLatin1Literal("Match Case"), menu);
    QWidgetAction * flag_case_sensitive_action = new QWidgetAction(menu);
    flag_case_sensitive_action -> setDefaultWidget(flag_case_sensitive);
    menu -> addAction(flag_case_sensitive_action);
    connect(flag_case_sensitive, &QCheckBox::clicked, [=](bool) { emit find(predicate -> text(), flags()); });

    flag_whole_word_only = new QCheckBox(QLatin1Literal("Words"), menu);
    QWidgetAction * flag_whole_word_only_action = new QWidgetAction(menu);
    flag_whole_word_only_action -> setDefaultWidget(flag_whole_word_only);
    menu -> addAction(flag_whole_word_only_action);
    connect(flag_whole_word_only, &QCheckBox::clicked, [=](bool) { emit find(predicate -> text(), flags()); });

    flag_reg_exp = new QCheckBox(QLatin1Literal("Regex"), menu);
    QWidgetAction * flag_reg_exp_action = new QWidgetAction(menu);
    flag_reg_exp_action -> setDefaultWidget(flag_reg_exp);
    menu -> addAction(flag_reg_exp_action);
    connect(flag_reg_exp, &QCheckBox::clicked, [=](bool) { emit find(predicate -> text(), flags()); });

    flag_unicode = new QCheckBox(QLatin1Literal("Unicode"), menu);
    QWidgetAction * flag_unicode_action = new QWidgetAction(menu);
    flag_unicode_action -> setDefaultWidget(flag_unicode);
    menu -> addAction(flag_unicode_action);
    connect(flag_unicode, &QCheckBox::clicked, [=](bool) { emit find(predicate -> text(), flags()); });
}

void EditorSearch::predicateIsCorrect() {
    qDebug() << "EditorSearch::predicateIsCorrect";

    predicate -> setToolTip(QLatin1Literal("Searching..."));
    predicate -> setStyleSheet(QLatin1Literal("QLineEdit { border: 1px solid green;}"));
}
void EditorSearch::predicateHasError(const QString & error) {
    qDebug() << "EditorSearch::predicateHasError" << error;

    predicate -> setToolTip(error);
    predicate -> setStyleSheet(QLatin1Literal("QLineEdit { border: 1px solid red;}"));
}

void EditorSearch::finded(const int & count) {
    qDebug() << "EditorSearch::finded" << count;

    predicate -> setToolTip(QLatin1Literal("Found ") + QString::number(count));
}