#include "highlight_format_factory.h"

void HighlightFormatFactory::registerSelectionFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(51, 153, 255, 32));
    _formats.insert(hid_selection, format);
}

void HighlightFormatFactory::registerCurrentLineFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(128, 128, 128, 24));
    _formats.insert(hid_current_line, format);
}

void HighlightFormatFactory::registerFoldingScopeLineFormat() {
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(64, 64, 64, 92));
    _formats.insert(hid_folding_scope_line, format);
}


void HighlightFormatFactory::registerFoldingContentOverlayFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(172, 229, 238, 64));
    _formats.insert(hid_folding_content_overlay, format);
}

void HighlightFormatFactory::registerFoldingDescriptionFormat() {
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(0, 0, 0));
    format.setBackground(QColor::fromRgb(64, 64, 64, 64));
    _formats.insert(hid_folding_description, format);
}

void HighlightFormatFactory::registerFoldingRangeFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(128, 128, 128, 48));
    _formats.insert(hid_folding_range, format);
}

void HighlightFormatFactory::registerFoldingScopeRangeFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(145, 196, 247));
    _formats.insert(hid_folding_scope_range, format);
}

void HighlightFormatFactory::registerBreakpointsRangeFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(255, 0, 0, 16));
    _formats.insert(hid_breakpoints_range, format);
}

void HighlightFormatFactory::registerBreakpointLineFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(255, 0, 0, 16));
    _formats.insert(hid_breakpoint_line, format);
}

void HighlightFormatFactory::registerCharsLimiterLineFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(255, 0, 0, 64));
    _formats.insert(hid_chars_limiter_line, format);
}


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

void HighlightFormatFactory::registerScopeVisibilityFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setTextOutline(QPen(QColor::fromRgb(220, 0, 220, 64)));
    format.setForeground(QColor::fromRgb(220, 0, 220));

    _formats.insert(hid_scope_visibility, format);
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


void HighlightFormatFactory::registerSpecKeywordFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setForeground(QColor::fromRgb(220, 0, 220));
    _formats.insert(hid_spec_keyword, format);
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
    format.setFontWeight(QFont::Bold);
    format.setBackground(QColor::fromRgb(255, 0, 0, 32));
    _formats.insert(hid_regexp_border, format);
}



HighlightFormatFactory::HighlightFormatFactory() {
    registerSelectionFormat();
    registerCurrentLineFormat();
    registerFoldingScopeLineFormat();
    registerFoldingContentOverlayFormat();
    registerFoldingDescriptionFormat();
    registerFoldingRangeFormat();
    registerScopeVisibilityFormat();
    registerFoldingScopeRangeFormat();
    registerBreakpointsRangeFormat();
    registerBreakpointLineFormat();
    registerCharsLimiterLineFormat();

    registerLabelFormat();
    registerOperatorFormat();
    registerSpecKeywordFormat();
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
