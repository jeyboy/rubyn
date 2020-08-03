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
//    btn -> setStyleSheet(QLatin1String("QToolButton { border: none; } QToolButton::menu-indicator { top: 3px; left: 3px; width: 4px, height: 4px; } "));
    options_btn -> setDefaultWidget(btn);

    addAction(options_btn, QLineEdit::LeadingPosition);


    move_prev_btn = new QWidgetAction(this);
    btn = new QToolButton(this);
    btn -> setIcon(QPixmap(":/row_right").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    btn -> setCursor(QCursor(Qt::PointingHandCursor));
    move_prev_btn -> setDefaultWidget(btn);
    btn -> setToolTip(QLatin1String("Move to next"));
    addAction(move_prev_btn, QLineEdit::TrailingPosition);
    connect(btn, &QToolButton::clicked, [=]() { emit toNextResult(); });


    move_next_btn = new QWidgetAction(this);
    btn = new QToolButton(this);
    btn -> setIcon(QPixmap(":/row_left").scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    btn -> setCursor(QCursor(Qt::PointingHandCursor));
    move_next_btn -> setDefaultWidget(btn);
    btn -> setToolTip(QLatin1String("Move to prev"));
    addAction(move_next_btn, QLineEdit::TrailingPosition);
    connect(btn, &QToolButton::clicked, [=]() { emit toPrevResult(); });


    flag_case_sensitive = new QCheckBox(QLatin1String("Match Case"), menu);
    QWidgetAction * flag_case_sensitive_action = new QWidgetAction(menu);
    flag_case_sensitive_action -> setDefaultWidget(flag_case_sensitive);
    menu -> addAction(flag_case_sensitive_action);
    connect(flag_case_sensitive, &QCheckBox::clicked, [=](bool) {
        QRegularExpression regex = buildRegex(text());
        if (regex.isValid())
            emit find(regex);
    });

    flag_whole_word_only = new QCheckBox(QLatin1String("Words"), menu);
    QWidgetAction * flag_whole_word_only_action = new QWidgetAction(menu);
    flag_whole_word_only_action -> setDefaultWidget(flag_whole_word_only);
    menu -> addAction(flag_whole_word_only_action);
    connect(flag_whole_word_only, &QCheckBox::clicked, [=](bool) {
        QRegularExpression regex = buildRegex(text());
        if (regex.isValid())
            emit find(regex);
    });

    flag_reg_exp = new QCheckBox(QLatin1String("Regex"), menu);
    QWidgetAction * flag_reg_exp_action = new QWidgetAction(menu);
    flag_reg_exp_action -> setDefaultWidget(flag_reg_exp);
    menu -> addAction(flag_reg_exp_action);
    connect(flag_reg_exp, &QCheckBox::clicked, [=](bool) {
        QRegularExpression regex = buildRegex(text());
        if (regex.isValid())
            emit find(regex);
    });

    flag_unicode = new QCheckBox(QLatin1String("Unicode"), menu);
    QWidgetAction * flag_unicode_action = new QWidgetAction(menu);
    flag_unicode_action -> setDefaultWidget(flag_unicode);
    menu -> addAction(flag_unicode_action);
    connect(flag_unicode, &QCheckBox::clicked, [=](bool) {
        QRegularExpression regex = buildRegex(text());
        if (regex.isValid())
            emit find(regex);
    });
}

QRegularExpression SearchPanel::buildRegex(const QString & pattern) {
    if (pattern.isEmpty()) {
        emit clearRequires();
        return QRegularExpression();
    }

    QString val = pattern;
    bool is_multiline = false;

    QRegularExpression::PatternOptions options = QRegularExpression::DotMatchesEverythingOption;

    if (!flag_case_sensitive -> isChecked())
        options |= QRegularExpression::CaseInsensitiveOption;

    if (flag_unicode -> isChecked())
        options |= QRegularExpression::UseUnicodePropertiesOption;

    val = val.replace(QRegularExpression(QLatin1String("\r|\n")), QLatin1String("|"));

    is_multiline = val != pattern;

    if (!flag_reg_exp -> isChecked() && !is_multiline)
        val = QRegularExpression::escape(val);

    if (flag_whole_word_only -> isChecked())
        val = QLatin1String("\\b") % val % QLatin1String("\\b");

    QRegularExpression res(val, options);
    res.optimize();

    if (res.isValid())
        predicateIsCorrect();
    else
        predicateHasError(res.errorString());

    return res;
}

SearchPanel::SearchPanel(QWidget * parent) : QLineEdit(parent), infinity_pad(false), flag_case_sensitive(nullptr), flag_whole_word_only(nullptr), flag_reg_exp(nullptr), flag_unicode(nullptr) {
//    setMinimumSize(0, 0);
//    setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
//    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    buildLayout();

    connect(this, &SearchPanel::textChanged, [=](const QString & text) {
        QRegularExpression regex = buildRegex(text);
        if (regex.isValid())
            emit find(regex);
    });
}

SearchPanel::~SearchPanel() {}

void SearchPanel::removePrevNext() {
    move_prev_btn -> deleteLater();
    move_next_btn -> deleteLater();
}

void SearchPanel::activate() {
    if (!text().isEmpty()) {
        QRegularExpression regex = buildRegex(text());
        if (regex.isValid())
            emit find(regex);

        selectAll();
    }
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
    emit closed();
    QLineEdit::hideEvent(e);
}

QSize SearchPanel::sizeHint() const {
    QSize res = QLineEdit::sizeHint();

    if (infinity_pad)
        res.rwidth() += 99999;

    return res;
}

void SearchPanel::predicateIsCorrect() {
    qDebug() << "SearchPanel::predicateIsCorrect";

    setToolTip(QLatin1String("Searching..."));
    qDebug() << "predicateIsCorrect";
    setStyleSheet(QLatin1String());
}
void SearchPanel::predicateHasError(const QString & error) {
    qDebug() << "SearchPanel::predicateHasError" << error;

    setToolTip(error);
    setStyleSheet(QLatin1String("SearchPanel { border: 2px solid #FF0000;}"));
}

void SearchPanel::finded(const int & count) {
    qDebug() << "SearchPanel::finded" << count;

    if (count == 0 && !text().isEmpty()) {
        setStyleSheet(QLatin1String("SearchPanel { background-color: rgba(255, 0, 0, 0.4); color: #FFFFFF; }"));
    } else {
        setStyleSheet(QLatin1String());
    }

    setToolTip(QLatin1String("Found: ") + QString::number(count));
}
