#include "highlight_format_factory.h"

void HighlightFormatFactory::registerProjectTreeLibRangeFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(0, 38, 255, 24));
    _formats.insert(hid_project_tree_lib_range, format);
}

void HighlightFormatFactory::registerProjectTreeTmpRangeFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(255, 215, 0, 24));
    _formats.insert(hid_project_tree_tmp_range, format);
}

void HighlightFormatFactory::registerProjectTreeSpecRangeFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(75, 255, 0, 24));
    _formats.insert(hid_project_tree_spec_range, format);
}

void HighlightFormatFactory::registerProjectTreePublicRangeFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(0, 255, 255, 24));
    _formats.insert(hid_project_tree_public_range, format);
}

void HighlightFormatFactory::registerProjectTreeLogRangeFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(255, 39, 220, 24));
    _formats.insert(hid_project_tree_log_range, format);
}

void HighlightFormatFactory::registerProjectTreeDbRangeFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(220, 220, 220, 108));
    _formats.insert(hid_project_tree_db_range, format);
}

void HighlightFormatFactory::registerProjectTreeConfigRangeFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(74, 90, 185, 24));
    _formats.insert(hid_project_tree_config_range, format);
}

void HighlightFormatFactory::registerProjectTreeAppRangeFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(192, 127, 92, 24));
    _formats.insert(hid_project_tree_app_range, format);
}


void HighlightFormatFactory::registerSearchOverlayFormat() {
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(0, 0, 0, 92));
    format.setBackground(QColor::fromRgb(255, 255, 0, 128));
    _formats.insert(hid_search_results_overlay, format);
}


void HighlightFormatFactory::registerLineNumberFormat() {
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(128, 128, 128, 255));
    _formats.insert(hid_line_number, format);
}


void HighlightFormatFactory::registerExtraIconsRangeFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(92, 157, 192, 64));
    _formats.insert(hid_extra_icons_range, format);
}

void HighlightFormatFactory::registerSelectionFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(51, 153, 255, 64));
    _formats.insert(hid_selection, format);
}

void HighlightFormatFactory::registerCurrentLineFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(128, 128, 128, 24));
    _formats.insert(hid_current_line, format);
}

void HighlightFormatFactory::registerFoldingLevelLineFormat() {
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(64, 64, 64, 32));
    _formats.insert(hid_folding_level_line, format);
}


void HighlightFormatFactory::registerFoldingContentPopupFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(172, 229, 238, 64));
    _formats.insert(hid_folding_content_popup, format);
}

void HighlightFormatFactory::registerFoldingHoverRangeFormat() {
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(0, 0, 0));
    format.setBackground(QColor::fromRgb(64, 64, 64, 64));
    _formats.insert(hid_folding_hover_range, format);
}

void HighlightFormatFactory::registerCurrentLineExtraFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(128, 128, 128, 48));
    _formats.insert(hid_current_line_extra, format);
}

void HighlightFormatFactory::registerFoldingParaRangeFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(145, 196, 247));
    _formats.insert(hid_folding_para_range, format);
}

void HighlightFormatFactory::registerFoldedOverlayFormat() {
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(192, 192, 192, 192));
    format.setBackground(QColor::fromRgb(224, 224, 224, 128));
    _formats.insert(hid_folded_overlay, format);
}

void HighlightFormatFactory::registerFoldedSelectedOverlayFormat() {
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(0, 0, 0, 128));
    format.setBackground(QColor::fromRgb(51, 153, 255, 64));
    _formats.insert(hid_folded_selected_overlay, format);
}

void HighlightFormatFactory::registerParaHoverLineFormat() {
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(50, 205, 50, 224));
    _formats.insert(hid_para_hover_line, format);
}

void HighlightFormatFactory::registerParaHoverSubOverlay2Format() {
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(0, 0, 0, 92));
    format.setBackground(QColor::fromRgb(255, 115, 255, 32));
    _formats.insert(hid_para_hover_sub_overlay2, format);
}

void HighlightFormatFactory::registerParaHoverOverlay2Format() {
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(0, 0, 0, 92));
    format.setBackground(QColor::fromRgb(255, 115, 255, 92));
    _formats.insert(hid_para_hover_overlay2, format);
}

void HighlightFormatFactory::registerParaHoverSubOverlayFormat() {
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(0, 0, 0, 92));
    format.setBackground(QColor::fromRgb(180, 238, 180, 64));
    _formats.insert(hid_para_hover_sub_overlay, format);
}

void HighlightFormatFactory::registerParaHoverOverlayFormat() {
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(0, 0, 0, 92));
    format.setBackground(QColor::fromRgb(180, 238, 180, 192));
    _formats.insert(hid_para_hover_overlay, format);
}

void HighlightFormatFactory::registerParaContentPopupFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(172, 229, 238, 64));
    _formats.insert(hid_para_content_popup, format);
}


void HighlightFormatFactory::registerBreakpointsRangeFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(255, 0, 0, 20));
    _formats.insert(hid_breakpoints_range, format);
}

void HighlightFormatFactory::registerBreakpointLineFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(255, 0, 0, 20));
    _formats.insert(hid_breakpoint_line, format);
}

void HighlightFormatFactory::registerBreakpointActiveLineFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(0, 255, 0, 64));
    _formats.insert(hid_breakpoint_active_line, format);
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
    format.setTextOutline(QPen(QColor::fromRgb(220, 0, 220, 48)));
    format.setForeground(QColor::fromRgb(220, 0, 220));

    _formats.insert(hid_scope_visibility, format);
}

void HighlightFormatFactory::registerUnclosedParaFormat() {
    QTextCharFormat format;
    format.setBackground(QColor::fromRgb(255, 105, 180, 128));

    _formats.insert(hid_unclosed_para, format);
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

void HighlightFormatFactory::registerNameArgFormat() {
    QTextCharFormat format;
    format.setForeground(QColor::fromRgb(197, 83, 2));
    _formats.insert(hid_name_arg, format);
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
    format.setTextOutline(QPen(QColor::fromRgb(0, 160, 0, 192)));
    format.setForeground(QColor::fromRgb(0, 120, 0)); // QColor::fromRgb(0, 255, 0, 92)
//        format.setForeground(Qt::darkGreen);
    _formats.insert(hid_string_border, format);
}

void HighlightFormatFactory::registerStringSpecFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setBackground(QColor::fromRgb(0, 145, 0, 32));
    format.setForeground(QColor::fromRgb(255, 165, 0));
    _formats.insert(hid_string_spec, format);
}

void HighlightFormatFactory::registerStringCodeFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setBackground(QColor::fromRgb(0, 145, 0, 32));
    format.setForeground(QColor::fromRgb(255, 127, 80));
    _formats.insert(hid_string_code, format);
}

void HighlightFormatFactory::registerStringFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setBackground(QColor::fromRgb(0, 145, 0, 32));
    format.setForeground(Qt::black);
    _formats.insert(hid_string, format);
}

void HighlightFormatFactory::registerTernaryFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setForeground(QColor::fromRgb(255, 86, 150));
    _formats.insert(hid_ternary, format);
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

void HighlightFormatFactory::registerSecuenceFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setForeground(QColor::fromRgb(183, 149, 11));
    _formats.insert(hid_sequence, format);
}

void HighlightFormatFactory::registerCommentMarkInfoFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setForeground(QColor::fromRgb(0, 182, 255));
    _formats.insert(hid_comment_mark_info, format);
}
void HighlightFormatFactory::registerCommentMarkWarnFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setForeground(QColor::fromRgb(255, 159, 0));
    _formats.insert(hid_comment_mark_warn, format);
}
void HighlightFormatFactory::registerCommentMarkTodoFormat() {
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setForeground(QColor::fromRgb(255, 0, 0));
    _formats.insert(hid_comment_mark_todo, format);
}


HighlightFormatFactory::HighlightFormatFactory() {
    registerProjectTreeLibRangeFormat();
    registerProjectTreeTmpRangeFormat();
    registerProjectTreeSpecRangeFormat();
    registerProjectTreePublicRangeFormat();
    registerProjectTreeLogRangeFormat();
    registerProjectTreeDbRangeFormat();
    registerProjectTreeConfigRangeFormat();
    registerProjectTreeAppRangeFormat();

    registerLineNumberFormat();
    registerExtraIconsRangeFormat();
    registerSearchOverlayFormat();
    registerSelectionFormat();
    registerCurrentLineFormat();
    registerFoldingLevelLineFormat();
    registerFoldingContentPopupFormat();
    registerFoldingHoverRangeFormat();
    registerCurrentLineExtraFormat();
    registerScopeVisibilityFormat();
    registerFoldingParaRangeFormat();
    registerParaContentPopupFormat();
    registerParaHoverLineFormat();
    registerFoldedOverlayFormat();
    registerParaHoverSubOverlay2Format();
    registerParaHoverOverlay2Format();
    registerParaHoverSubOverlayFormat();
    registerParaHoverOverlayFormat();
    registerBreakpointsRangeFormat();
    registerBreakpointLineFormat();
    registerBreakpointActiveLineFormat();
    registerCharsLimiterLineFormat();
    registerFoldedSelectedOverlayFormat();

    registerUnclosedParaFormat();
    registerLabelFormat();
    registerOperatorFormat();
    registerSpecKeywordFormat();
    registerKeywordFormat();
    registerAssigmentFormat();
    registerNameCallFormat();
    registerNameArgFormat();
    registerNameDefFormat();
    registerConstFormat();
    registerStringBorderFormat();
    registerStringSpecFormat();
    registerStringCodeFormat();
    registerStringFormat();
    registerTernaryFormat();
//        registerMethodFormat();
    registerCommentFormat();
    registerNumericFormat();
    registerRegularExpresionFormat();
    registerRegularExpresionBorderFormat();
//        registerPreprocessingFormat();
//        registerDatatypeFormat();
    registerSecuenceFormat();

    registerErrorFormat();
    registerWarningFormat();
    registerSpellcheckFormat();

    registerUnknownName();

    registerCommentMarkInfoFormat();
    registerCommentMarkWarnFormat();
    registerCommentMarkTodoFormat();
}

const QTextCharFormat & HighlightFormatFactory::getFormatFor(const Identifier & uid) { return _formats[uid]; }
