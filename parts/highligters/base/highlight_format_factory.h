#ifndef HIGHLIGHT_FORMAT_FACTORY
#define HIGHLIGHT_FORMAT_FACTORY

#include <qtextformat.h>
#include <qhash.h>

#include "parts/lexer/lexems.h"
#include "misc/singleton.h"

//enum HighlightFormat {
//    format_keyword = 1,
//    format_variable,
//    format_symbol,
//    format_class,
//    format_const,
//    format_single_quotation,
//    format_double_quotation,
//    format_func,
//    format_signle_line_comment,
//    format_multy_line_comment,
//    format_heredoc,
//    format_numbers,
//    format_regular_expresions,
//    format_preprocessing,
//    format_datatype,

//    format_error,
//    format_warning,
//    format_spellcheck
//};

class HighlightFormatFactory : public Singleton<HighlightFormatFactory> {
    QHash<Lexem, QTextCharFormat> formats;
protected:
    void registerErrorFormat() {
        QTextCharFormat errFormat;
        errFormat.setFontUnderline(true);
        errFormat.setUnderlineColor(QColor(Qt::red));
        errFormat.setUnderlineStyle(QTextCharFormat::WaveUnderline);
        errFormat.setFontItalic(true);
        formats.insert(lex_error, errFormat);
    }

    void registerWarningFormat() {
        QTextCharFormat errFormat;
        errFormat.setFontUnderline(true);
        errFormat.setUnderlineColor(QColor(Qt::blue));
        errFormat.setUnderlineStyle(QTextCharFormat::WaveUnderline);
        errFormat.setFontItalic(true);
        formats.insert(lex_warning, errFormat);
    }

    void registerSpellcheckFormat() {
        QTextCharFormat errFormat;
        errFormat.setFontUnderline(true);
        errFormat.setUnderlineColor(QColor(Qt::black));
        errFormat.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
        errFormat.setFontItalic(true);
        formats.insert(lex_notice, errFormat);
    }

    void registerKeywordFormat() {
        QTextCharFormat keywordFormat;
        keywordFormat.setForeground(Qt::darkBlue);
        keywordFormat.setBackground(QColor::fromRgb(0, 0, 255, 16));
        keywordFormat.setFontWeight(QFont::Black);
        formats.insert(lex_key, keywordFormat);
    }
    void registerVariableFormat() {
        QTextCharFormat variableFormat;
        variableFormat.setFontWeight(QFont::Bold);
        variableFormat.setForeground(Qt::darkYellow);
        formats.insert(lex_var, variableFormat);
    }
    void registerSymbolFormat() {
        QTextCharFormat symbolFormat;
        symbolFormat.setFontWeight(QFont::Bold);
        symbolFormat.setForeground(Qt::darkCyan);
        formats.insert(lex_symb, symbolFormat);
    }
    void registerClassFormat() {
        QTextCharFormat classFormat;
        classFormat.setFontWeight(QFont::Bold);
        classFormat.setForeground(Qt::darkMagenta);
        formats.insert(lex_class, classFormat);
        formats.insert(lex_module, classFormat);
        formats.insert(lex_method, classFormat);
    }
    void registerConstFormat() {
        QTextCharFormat constFormat;
        constFormat.setFontWeight(QFont::Bold);
        constFormat.setForeground(Qt::darkMagenta);
        formats.insert(lex_const, constFormat);
    }
    void registerQuotationFormat() {
        QTextCharFormat singleQuotationFormat;
        singleQuotationFormat.setForeground(Qt::darkGreen);
        formats.insert(lex_string, singleQuotationFormat);
    }
    void registerFuncFormat() {
        QTextCharFormat functionFormat;
        functionFormat.setFontItalic(true);
        functionFormat.setForeground(Qt::blue);
        formats.insert(lex_method, functionFormat);
    }
    void registerCommentFormat() {
        QTextCharFormat commentFormat;
        commentFormat.setForeground(Qt::red); // gray
        formats.insert(lex_commentary, commentFormat);
    }

    void registerHeredocFormat() {
        QTextCharFormat heredocFormat;
        heredocFormat.setForeground(Qt::green);
        formats.insert(lex_heredoc, heredocFormat);
    }
    void registerNumbersFormat() {
        QTextCharFormat numbersFormat;
        numbersFormat.setForeground(Qt::blue);
        formats.insert(lex_number, numbersFormat);
    }
    void registerRegularExpresionsFormat() {
        QTextCharFormat regularExpFormat;
        regularExpFormat.setBackground(QColor::fromRgb(0, 255, 0, 32));
        formats.insert(lex_regexp, regularExpFormat);
    }
//    void registerPreprocessingFormat() {
//        QTextCharFormat preprocessingFormat;
//        preprocessingFormat.setForeground(QColor::fromRgb(0, 255, 0, 164));
//        formats.insert(format_preprocessing, preprocessingFormat);
//    }
    void registerDatatypeFormat() {
        QTextCharFormat datatypeFormat;
        datatypeFormat.setForeground(QColor::fromRgb(0, 0, 255, 164));
        formats.insert(lex_datatype, datatypeFormat);
    }
public:
    HighlightFormatFactory() {
        registerKeywordFormat();
        registerVariableFormat();
        registerSymbolFormat();
        registerClassFormat();
        registerConstFormat();
        registerQuotationFormat();
        registerFuncFormat();
        registerCommentFormat();
        registerHeredocFormat();
        registerNumbersFormat();
        registerRegularExpresionsFormat();
//        registerPreprocessingFormat();
        registerDatatypeFormat();

        registerErrorFormat();
        registerWarningFormat();
        registerSpellcheckFormat();
    }

    const QTextCharFormat & getFormatFor(const HighlightFormat & format) { return formats[format]; }
};

#endif // HIGHLIGHT_FORMAT_FACTORY
