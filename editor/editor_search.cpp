#include "editor_search.h"

#include "controls/search_panel.h"

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
#include <qstringbuilder.h>

#include <qdebug.h>

void EditorSearch::paintEvent(QPaintEvent * event) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style() -> drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}

EditorSearch::EditorSearch(const bool & has_replace, QWidget * parent) : QWidget(parent), result_count(0), predicate(nullptr), replace_predicate(nullptr), l1(nullptr), l2(nullptr) {
//    QPalette Pal(palette());

//    // устанавливаем цвет фона
//    Pal.setColor(QPalette::Background, Qt::black);
//    m_pMyWidget->setAutoFillBackground(true);
//    m_pMyWidget->setPalette(Pal);


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

    QFont cfont = font();
    cfont.setBold(true);
    cfont.setKerning(true);


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
        l2 -> setFont(cfont);

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

    l1 = new QLabel(SEARCH_LABEL_TEXT, this);

    if (l2)
        l1 -> setFixedWidth(l2 -> sizeHint().rwidth());

    l1 -> setFont(cfont);

    search_layout -> addWidget(l1, 0);
    predicate = new SearchPanel(this);
    predicate -> setMinimumWidth(150);
    predicate -> setPlaceholderText(QLatin1Literal("Search"));
    search_layout -> addWidget(predicate, 1);

    connect(predicate, &SearchPanel::find, [=](const QRegularExpression & pattern) { emit find(pattern); });
    connect(predicate, &SearchPanel::toNextResult, [=](QString * replace) { emit toNextResult(replace); });
    connect(predicate, &SearchPanel::toPrevResult, [=](QString * replace) { emit toPrevResult(replace); });
    connect(predicate, &SearchPanel::closed, [=]() { emit close(); });
    connect(predicate, &SearchPanel::clearRequires, [=]() { l1 -> setText(SEARCH_LABEL_TEXT); });


    btn = new QToolButton(this);
    btn -> setIcon(QPixmap(":/tools/close").scaled(btn -> iconSize().width(), btn -> iconSize().height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    btn -> setToolTip(QLatin1Literal("Close"));
    btn -> setStyleSheet(QLatin1Literal("border: none;"));
    connect(btn, &QToolButton::clicked, [=]() { hide(); emit close(); });
    search_layout -> addWidget(btn, 0);
}

void EditorSearch::initiateSearch(const QString & pattern) {
    predicate -> setText(pattern);
    changeVisibility(true);
}

void EditorSearch::changeVisibility(const bool & show) {
    setHidden(!show);

    if (show) {
        predicate -> setFocus();
        predicate -> activate();
    }
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

    if (count > 0) {
        predicate -> setStyleSheet(QLatin1Literal());
        l1 -> setText(SEARCH_LABEL_TEXT % '\n' % '(' % QString::number(count) % ')');
    } else if (!predicate -> text().isEmpty()) {
        predicate -> setStyleSheet(QLatin1Literal("QLineEdit { color: #FFFFFF; background-color: rgba(255, 0, 0, .4);}"));
        l1 -> setText(SEARCH_LABEL_TEXT);
    }

    predicate -> setToolTip(QLatin1Literal("Found ") + QString::number(count));
}
