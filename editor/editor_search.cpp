#include "editor_search.h"

#include <qlineedit.h>
#include <qcheckbox.h>
#include <qtoolbutton.h>
#include <qlabel.h>
#include <qaction.h>
#include <qwidgetaction.h>
#include <qmenu.h>
#include <qlayout.h>

#include <qdebug.h>

EditorSearch::EditorSearch(QWidget * parent) : QWidget(parent), result_count(0) {
    QVBoxLayout * main_layout = new QVBoxLayout(this);

    QHBoxLayout * search_layout = new QHBoxLayout();
    QHBoxLayout * replace_layout = new QHBoxLayout();

    QLabel * l2 = new QLabel(QLatin1Literal("Replace with:"), this);
    replace_layout -> addWidget(l2, 0);
    QLineEdit * replace_predicate = new QLineEdit(this);
    replace_predicate -> setPlaceholderText(QLatin1Literal("Replacement"));
    replace_predicate -> setMinimumWidth(100);
    replace_layout -> addWidget(replace_predicate, 1);


    QWidgetAction * replace_all_btn = new QWidgetAction(this);
    QToolButton * btn = new QToolButton(this);
    btn -> setIcon(QPixmap(":/search_replace_btn").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    btn -> setCursor(QCursor(Qt::PointingHandCursor));
    replace_all_btn -> setDefaultWidget(btn);
    btn -> setToolTip(QLatin1Literal("Replace all"));
    replace_predicate -> addAction(replace_all_btn, QLineEdit::TrailingPosition);
    connect(replace_all_btn, &QWidgetAction::triggered, [=]() {});


    QWidgetAction * replace_prev_btn = new QWidgetAction(this);
    btn = new QToolButton(this);
    btn -> setIcon(QPixmap(":/row_right").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    btn -> setCursor(QCursor(Qt::PointingHandCursor));
    replace_prev_btn -> setDefaultWidget(btn);
    btn -> setToolTip(QLatin1Literal("Replace current and move to next"));
    replace_predicate -> addAction(replace_prev_btn, QLineEdit::TrailingPosition);
    connect(replace_prev_btn, &QWidgetAction::triggered, [=]() {});


    QWidgetAction * replace_next_btn = new QWidgetAction(this);
    btn = new QToolButton(this);
    btn -> setIcon(QPixmap(":/row_left").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    btn -> setCursor(QCursor(Qt::PointingHandCursor));
    replace_next_btn -> setDefaultWidget(btn);
    btn -> setToolTip(QLatin1Literal("Replace current and move to prev"));
    replace_predicate -> addAction(replace_next_btn, QLineEdit::TrailingPosition);
    connect(replace_next_btn, &QWidgetAction::triggered, [=]() {});









    QLabel * l1 = new QLabel(QLatin1Literal("Search:"), this);
    l1 -> setFixedWidth(l2 -> sizeHint().rwidth());
    search_layout -> addWidget(l1, 0);
    QLineEdit * predicate = new QLineEdit(this);
    predicate -> setMinimumWidth(100);
    predicate -> setPlaceholderText(QLatin1Literal("Search"));
    search_layout -> addWidget(predicate, 1);


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
    connect(move_prev_btn, &QWidgetAction::triggered, [=]() {});


    QWidgetAction * move_next_btn = new QWidgetAction(this);
    btn = new QToolButton(this);
    btn -> setIcon(QPixmap(":/row_left").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    btn -> setCursor(QCursor(Qt::PointingHandCursor));
    move_next_btn -> setDefaultWidget(btn);
    btn -> setToolTip(QLatin1Literal("Move to prev"));
    predicate -> addAction(move_next_btn, QLineEdit::TrailingPosition);
    connect(move_next_btn, &QWidgetAction::triggered, [=]() {});


    QCheckBox * flag_case_sensitive = new QCheckBox(QLatin1Literal("Match Case"), menu);
    QWidgetAction * flag_case_sensitive_action = new QWidgetAction(menu);
    flag_case_sensitive_action -> setDefaultWidget(flag_case_sensitive);
    menu -> addAction(flag_case_sensitive_action);

    QCheckBox * flag_whole_word_only = new QCheckBox(QLatin1Literal("Words"), menu);
    QWidgetAction * flag_whole_word_only_action = new QWidgetAction(menu);
    flag_whole_word_only_action -> setDefaultWidget(flag_whole_word_only);
    menu -> addAction(flag_whole_word_only_action);

    QCheckBox * flag_reg_exp = new QCheckBox(QLatin1Literal("Regex"), menu);
    QWidgetAction * flag_reg_exp_action = new QWidgetAction(menu);
    flag_reg_exp_action -> setDefaultWidget(flag_reg_exp);
    menu -> addAction(flag_reg_exp_action);

    main_layout -> addLayout(search_layout);
    main_layout -> addLayout(replace_layout);
}

void EditorSearch::finded(const int & count) {

}
