#ifndef HIGHLIGHT_FORMAT_FACTORY
#define HIGHLIGHT_FORMAT_FACTORY

#include <qtextformat.h>
#include <qhash.h>

#include "parts/lexer/lexems.h"
#include "misc/singleton.h"

class HighlightFormatFactory : public Singleton<HighlightFormatFactory> {
    QHash<Lexem, QTextCharFormat> formats;
protected:
    void registerErrorFormat() {
        QTextCharFormat format;
        format.setFontUnderline(true);
        format.setUnderlineColor(QColor(Qt::red));
        format.setUnderlineStyle(QTextCharFormat::WaveUnderline);
        format.setFontItalic(true);
        formats.insert(lex_error, format);
    }

    void registerWarningFormat() {
        QTextCharFormat format;
        format.setFontUnderline(true);
        format.setUnderlineColor(QColor(Qt::blue));
        format.setUnderlineStyle(QTextCharFormat::WaveUnderline);
        format.setFontItalic(true);
        formats.insert(lex_warning, format);
    }

    void registerSpellcheckFormat() {
        QTextCharFormat format;
        format.setFontUnderline(true);
        format.setUnderlineColor(QColor(Qt::black));
        format.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
        format.setFontItalic(true);
        formats.insert(lex_notice, format);
    }

    void registerMarkFormat() {
        QTextCharFormat format;
        format.setFontWeight(QFont::Black);
        format.setForeground(Qt::black);
        format.setFontUnderline(true);
        format.setUnderlineColor(QColor(Qt::black));
        format.setUnderlineStyle(QTextCharFormat::SingleUnderline);
        formats.insert(lex_mark, format);
    }

    void registerKeywordFormat() {
        QTextCharFormat format;
        format.setFontItalic(true);
        format.setForeground(QColor::fromRgb(215, 58, 73));
        formats.insert(lex_key, format);
    }

    void registerAssigmentFormat() {
        QTextCharFormat format;
        format.setFontWeight(QFont::Bold);
        format.setForeground(QColor::fromRgb(0, 92, 197));
//        formats.insert(lex_var, format);

        formats.insert(lex_symbol, format);
    }

    void registerNameFormat() {
        QTextCharFormat format;
        format.setFontWeight(QFont::Bold);
        format.setForeground(Qt::darkCyan);
        formats.insert(lex_name, format);
    }

    void registerDefNameFormat() {
        QTextCharFormat format;
        format.setFontWeight(QFont::Bold);
        format.setForeground(Qt::darkMagenta);
        formats.insert(lex_def_name, format);
    }

//    void registerConstFormat() {
//        QTextCharFormat format;
//        format.setFontWeight(QFont::Bold);
//        format.setForeground(Qt::darkMagenta);
//        formats.insert(lex_const, format);
//    }
    void registerStringFormat() {
        QTextCharFormat format;
        format.setFontWeight(QFont::Bold);
        format.setBackground(Qt::green);
//        format.setForeground(Qt::darkGreen);
        formats.insert(lex_string, format);
    }
    void registerMethodFormat() {
        QTextCharFormat format;
        format.setForeground(Qt::darkBlue);
        format.setBackground(QColor::fromRgb(0, 0, 255, 16));
        format.setFontWeight(QFont::Black);
        formats.insert(lex_method, format);
    }
    void registerCommentFormat() {
        QTextCharFormat format;
        format.setFontWeight(QFont::Bold);
        format.setForeground(QColor::fromRgb(128, 128, 128, 192));
        formats.insert(lex_commentary, format);
    }

    void registerPredefinedsFormat() {
        QTextCharFormat format;
        format.setForeground(Qt::blue);
        formats.insert(lex_predefined, format);
    }
    void registerRegularExpresionsFormat() {
        QTextCharFormat format;
        format.setBackground(QColor::fromRgb(0, 255, 0, 32));
        formats.insert(lex_regexp, format);
    }
//    void registerPreprocessingFormat() {
//        QTextCharFormat format;
//        format.setForeground(QColor::fromRgb(0, 255, 0, 164));
//        formats.insert(format_preprocessing, format);
//    }
//    void registerDatatypeFormat() {
//        QTextCharFormat format;
//        format.setForeground(QColor::fromRgb(0, 0, 255, 164));
//        formats.insert(lex_datatype, format);
//    }
public:
    HighlightFormatFactory() {
        registerMarkFormat();
        registerKeywordFormat();
        registerAssigmentFormat();
        registerNameFormat();
        registerDefNameFormat();
//        registerConstFormat();
        registerStringFormat();
        registerMethodFormat();
        registerCommentFormat();
        registerPredefinedsFormat();
        registerRegularExpresionsFormat();
//        registerPreprocessingFormat();
//        registerDatatypeFormat();

        registerErrorFormat();
        registerWarningFormat();
        registerSpellcheckFormat();
    }

    const QTextCharFormat & getFormatFor(const Lexem & lexem) { return formats[lexem]; }
};

#endif // HIGHLIGHT_FORMAT_FACTORY
