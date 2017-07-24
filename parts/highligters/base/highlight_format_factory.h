#ifndef HIGHLIGHT_FORMAT_FACTORY
#define HIGHLIGHT_FORMAT_FACTORY

#include <qtextformat.h>
#include <qhash.h>

#include "misc/singleton.h"

enum HighlightFormat {
    format_keyword = 1,
    format_variable,
    format_symbol,
    format_class,
    format_const,
    format_single_quotation,
    format_double_quotation,
    format_func,
    format_signle_line_comment,
    format_multy_line_comment,
    format_heredoc,
    format_numbers,
    format_regular_expresions,
    format_preprocessing,
    format_datatype
};

class HighlightFormatFactory : public Singleton<HighlightFormatFactory> {
    QHash<HighlightFormat, QTextCharFormat> formats;
protected:
    void registerKeywordFormat() {
        QTextCharFormat keywordFormat;
        keywordFormat.setForeground(Qt::darkBlue);
        keywordFormat.setBackground(QColor::fromRgb(0, 0, 255, 16));
        keywordFormat.setFontWeight(QFont::Black);
        formats.insert(format_keyword, keywordFormat);
    }
    void registerVariableFormat() {
        QTextCharFormat variableFormat;
        variableFormat.setFontWeight(QFont::Bold);
        variableFormat.setForeground(Qt::darkYellow);
        formats.insert(format_variable, variableFormat);
    }
    void registerSymbolFormat() {
        QTextCharFormat symbolFormat;
        symbolFormat.setFontWeight(QFont::Bold);
        symbolFormat.setForeground(Qt::darkCyan);
        formats.insert(format_symbol, symbolFormat);
    }
    void registerClassFormat() {
        QTextCharFormat classFormat;
        classFormat.setFontWeight(QFont::Bold);
        classFormat.setForeground(Qt::darkMagenta);
        formats.insert(format_class, classFormat);
    }
    void registerConstFormat() {
        QTextCharFormat constFormat;
        constFormat.setFontWeight(QFont::Bold);
        constFormat.setForeground(Qt::darkMagenta);
        formats.insert(format_const, constFormat);
    }
    void registerSingleQuotationFormat() {
        QTextCharFormat singleQuotationFormat;
        singleQuotationFormat.setForeground(Qt::darkGreen);
        formats.insert(format_single_quotation, singleQuotationFormat);
    }
    void registerDoubleQuotationFormat() {
        QTextCharFormat doubleQuotationFormat;
        doubleQuotationFormat.setForeground(Qt::darkGreen);
        formats.insert(format_double_quotation, doubleQuotationFormat);
    }
    void registerFuncFormat() {
        QTextCharFormat functionFormat;
        functionFormat.setFontItalic(true);
        functionFormat.setForeground(Qt::blue);
        formats.insert(format_func, functionFormat);
    }
    void registerSingleLineCommentFormat() {
        QTextCharFormat commentFormat;
        commentFormat.setForeground(Qt::red); // gray
        formats.insert(format_signle_line_comment, commentFormat);
    }
    void registerMultyLineCommentFormat() {
        QTextCharFormat commentFormat;
        commentFormat.setForeground(Qt::red); // gray
        formats.insert(format_multy_line_comment, commentFormat);
    }
    void registerHeredocFormat() {
        QTextCharFormat heredocFormat;
        heredocFormat.setForeground(Qt::green);
        formats.insert(format_heredoc, heredocFormat);
    }
    void registerNumbersFormat() {
        QTextCharFormat numbersFormat;
        numbersFormat.setForeground(Qt::blue);
        formats.insert(format_numbers, numbersFormat);
    }
    void registerRegularExpresionsFormat() {
        QTextCharFormat regularExpFormat;
        regularExpFormat.setBackground(QColor::fromRgb(0, 255, 0, 32));
        formats.insert(format_regular_expresions, regularExpFormat);
    }
    void registerPreprocessingFormat() {
        QTextCharFormat preprocessingFormat;
        preprocessingFormat.setForeground(QColor::fromRgb(0, 255, 0, 164));
        formats.insert(format_preprocessing, preprocessingFormat);
    }
    void registerDatatypeFormat() {
        QTextCharFormat datatypeFormat;
        datatypeFormat.setForeground(QColor::fromRgb(0, 0, 255, 164));
        formats.insert(format_datatype, datatypeFormat);
    }
public:
    HighlightFormatFactory() {
        registerKeywordFormat();
        registerVariableFormat();
        registerSymbolFormat();
        registerClassFormat();
        registerConstFormat();
        registerSingleQuotationFormat();
        registerDoubleQuotationFormat();
        registerFuncFormat();
        registerSingleLineCommentFormat();
        registerMultyLineCommentFormat();
        registerHeredocFormat();
        registerNumbersFormat();
        registerRegularExpresionsFormat();
        registerPreprocessingFormat();
        registerDatatypeFormat();
    }

    const QTextCharFormat & getFormatFor(const HighlightFormat & format) { return formats[format]; }
};

#endif // HIGHLIGHT_FORMAT_FACTORY
