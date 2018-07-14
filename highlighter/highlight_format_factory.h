#ifndef HIGHLIGHT_FORMAT_FACTORY
#define HIGHLIGHT_FORMAT_FACTORY

#include <qtextformat.h>
#include <qhash.h>

#include "identifiers.h"
#include "misc/singleton.h"

class HighlightFormatFactory : public Singleton<HighlightFormatFactory> {
    QHash<Identifier, QTextCharFormat> formats;
protected:
    void registerErrorFormat() {
        QTextCharFormat format;
        format.setFontUnderline(true);
        format.setUnderlineColor(QColor(Qt::red));
        format.setUnderlineStyle(QTextCharFormat::WaveUnderline);
        format.setFontItalic(true);
        formats.insert(hid_error, format);
    }

    void registerWarningFormat() {
        QTextCharFormat format;
        format.setFontUnderline(true);
        format.setUnderlineColor(QColor(Qt::blue));
        format.setUnderlineStyle(QTextCharFormat::WaveUnderline);
        format.setFontItalic(true);
        formats.insert(hid_warning, format);
    }

    void registerSpellcheckFormat() {
        QTextCharFormat format;
        format.setFontUnderline(true);
        format.setUnderlineColor(QColor(Qt::black));
        format.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
        format.setFontItalic(true);
        formats.insert(hid_notice, format);
    }

    void registerLabelFormat() {
        QTextCharFormat format;
        format.setFontWeight(QFont::Black);
        format.setForeground(Qt::black);
        format.setFontUnderline(true);
        format.setUnderlineColor(QColor(Qt::black));
        format.setUnderlineStyle(QTextCharFormat::SingleUnderline);
        formats.insert(hid_label, format);
    }

    void registerKeywordFormat() {
        QTextCharFormat format;
        format.setFontItalic(true);
        format.setForeground(QColor::fromRgb(215, 58, 73));
        formats.insert(hid_keyword, format);
    }

    void registerAssigmentFormat() {
        QTextCharFormat format;
        format.setFontWeight(QFont::Bold);
        format.setForeground(QColor::fromRgb(0, 92, 197));
//        formats.insert(lex_var, format);

        formats.insert(hid_symbol, format);
    }

    void registerNameCallFormat() {
        QTextCharFormat format;
        format.setFontWeight(QFont::Bold);
        format.setForeground(Qt::darkCyan);
        formats.insert(hid_name_call, format);
    }

    void registerNameDefFormat() {
        QTextCharFormat format;
        format.setFontWeight(QFont::Bold);
        format.setForeground(Qt::darkMagenta);
        formats.insert(hid_name_def, format);
    }

    void registerConstFormat() {
        QTextCharFormat format;
        format.setFontWeight(QFont::Bold);
        format.setForeground(Qt::darkMagenta);
        formats.insert(hid_const, format);
    }

    void registerStringFormat() {
        QTextCharFormat format;
        format.setFontWeight(QFont::Bold);
        format.setBackground(Qt::green);
//        format.setForeground(Qt::darkGreen);
        formats.insert(hid_string, format);
    }
//    void registerMethodFormat() {
//        QTextCharFormat format;
//        format.setForeground(Qt::darkBlue);
//        format.setBackground(QColor::fromRgb(0, 0, 255, 16));
//        format.setFontWeight(QFont::Black);
//        formats.insert(hid_method, format);
//    }
    void registerCommentFormat() {
        QTextCharFormat format;
        format.setFontWeight(QFont::Bold);
        format.setForeground(QColor::fromRgb(128, 128, 128, 192));
        formats.insert(hid_commentary, format);
    }

    void registerNumericFormat() {
        QTextCharFormat format;
        format.setForeground(Qt::blue);
        formats.insert(hid_numeric, format);
    }
    void registerRegularExpresionsFormat() {
        QTextCharFormat format;
        format.setBackground(QColor::fromRgb(0, 255, 0, 32));
        formats.insert(hid_regexp, format);
    }
//    void registerPreprocessingFormat() {
//        QTextCharFormat format;
//        format.setForeground(QColor::fromRgb(0, 255, 0, 164));
//        formats.insert(hid_preprocessing, format);
//    }
//    void registerDatatypeFormat() {
//        QTextCharFormat format;
//        format.setForeground(QColor::fromRgb(0, 0, 255, 164));
//        formats.insert(hid_datatype, format);
//    }
public:
    HighlightFormatFactory() {
        registerLabelFormat();
        registerKeywordFormat();
        registerAssigmentFormat();
        registerNameCallFormat();
        registerNameDefFormat();
        registerConstFormat();
        registerStringFormat();
//        registerMethodFormat();
        registerCommentFormat();
        registerNumericFormat();
        registerRegularExpresionsFormat();
//        registerPreprocessingFormat();
//        registerDatatypeFormat();

        registerErrorFormat();
        registerWarningFormat();
        registerSpellcheckFormat();
    }

    const QTextCharFormat & getFormatFor(const Identifier & uid) { return formats[uid]; }
};

#endif // HIGHLIGHT_FORMAT_FACTORY
