#include "highlight_format_factory.h"

void HighlightFormatFactory::registerErrorFormat() {
    QTextCharFormat format;
    format.setFontUnderline(true);
    format.setUnderlineColor(QColor(Qt::red));
    format.setUnderlineStyle(QTextCharFormat::WaveUnderline);
    format.setFontItalic(true);
    _formats.insert(hid_error, format);
}

void HighlightFormatFactory::registerWarningFormat() {
    QTextCharFormat format;
    format.setFontUnderline(true);
    format.setUnderlineColor(QColor(Qt::blue));
    format.setUnderlineStyle(QTextCharFormat::WaveUnderline);
    format.setFontItalic(true);
    _formats.insert(hid_warning, format);
}

void HighlightFormatFactory::registerSpellcheckFormat() {
    QTextCharFormat format;
    format.setFontUnderline(true);
    format.setUnderlineColor(QColor(Qt::black));
    format.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
    format.setFontItalic(true);
    _formats.insert(hid_notice, format);
}

void HighlightFormatFactory::registerUnknownName() {
    QTextCharFormat format;
    format.setFontItalic(true);
    format.setFontUnderline(true);
    format.setUnderlineColor(QColor(Qt::gray));
    format.setUnderlineStyle(QTextCharFormat::WaveUnderline);
    _formats.insert(hid_unknown_name, format);
}

void HighlightFormatFactory::registerLabelFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Black);
    format.setForeground(Qt::black);
    format.setFontUnderline(true);
    format.setUnderlineColor(QColor(Qt::black));
    format.setUnderlineStyle(QTextCharFormat::SingleUnderline);
    _formats.insert(hid_label, format);
}

void HighlightFormatFactory::registerOperatorFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Black);
    _formats.insert(hid_operator, format);
}

void HighlightFormatFactory::registerKeywordFormat() {
    QTextCharFormat format;
    format.setFontItalic(true);
    format.setForeground(QColor::fromRgb(215, 58, 73));
    _formats.insert(hid_keyword, format);
}

void HighlightFormatFactory::registerAssigmentFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setForeground(QColor::fromRgb(0, 92, 197));

    _formats.insert(hid_var, format);
    _formats.insert(hid_symbol, format);
}

void HighlightFormatFactory::registerNameCallFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setForeground(Qt::darkCyan);
    _formats.insert(hid_name_call, format);
}

void HighlightFormatFactory::registerNameDefFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setForeground(Qt::darkMagenta);
    _formats.insert(hid_name_def, format);
}

void HighlightFormatFactory::registerConstFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setForeground(Qt::darkMagenta);
    _formats.insert(hid_const, format);
}

void HighlightFormatFactory::registerStringBorderFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setBackground(QColor::fromRgb(0, 255, 0, 92));
//        format.setForeground(Qt::darkGreen);
    _formats.insert(hid_string_border, format);
}

void HighlightFormatFactory::registerStringFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setBackground(QColor::fromRgb(0, 255, 0, 92));
//        format.setForeground(Qt::darkGreen);
    _formats.insert(hid_string, format);
}

void HighlightFormatFactory::registerCommentFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setForeground(QColor::fromRgb(128, 128, 128, 192));
    _formats.insert(hid_commentary, format);
}

void HighlightFormatFactory::registerNumericFormat() {
    QTextCharFormat format;
    format.setForeground(Qt::blue);
    _formats.insert(hid_numeric, format);
}

void HighlightFormatFactory::registerRegularExpresionFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(0, 255, 0, 32));
    _formats.insert(hid_regexp, format);
}

void HighlightFormatFactory::registerRegularExpresionBorderFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(0, 255, 0, 32));
    _formats.insert(hid_regexp_border, format);
}



HighlightFormatFactory::HighlightFormatFactory() {
    registerLabelFormat();
    registerOperatorFormat();
    registerKeywordFormat();
    registerAssigmentFormat();
    registerNameCallFormat();
    registerNameDefFormat();
    registerConstFormat();
    registerStringBorderFormat();
    registerStringFormat();
//        registerMethodFormat();
    registerCommentFormat();
    registerNumericFormat();
    registerRegularExpresionFormat();
    registerRegularExpresionBorderFormat();
//        registerPreprocessingFormat();
//        registerDatatypeFormat();

    registerErrorFormat();
    registerWarningFormat();
    registerSpellcheckFormat();

    registerUnknownName();
}

const QTextCharFormat & HighlightFormatFactory::getFormatFor(const Identifier & uid) { return _formats[uid]; }
