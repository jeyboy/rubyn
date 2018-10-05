#ifndef HIGHLIGHT_FORMAT_FACTORY
#define HIGHLIGHT_FORMAT_FACTORY

#include <qtextformat.h>
#include <qhash.h>

#include "identifiers.h"
#include "misc/singleton.h"

class HighlightFormatFactory : public Singleton<HighlightFormatFactory> {
    QHash<Identifier, QTextCharFormat> _formats;
protected:
    void registerSelectionFormat();

    void registerErrorFormat();

    void registerWarningFormat();

    void registerSpellcheckFormat();

    void registerUnknownName();

    void registerLabelFormat();

    void registerOperatorFormat();

    void registerSpecKeywordFormat();

    void registerKeywordFormat();

    void registerAssigmentFormat();

    void registerNameCallFormat();

    void registerNameDefFormat();

    void registerConstFormat();

    void registerStringBorderFormat();

    void registerStringFormat();

//    void registerMethodFormat() {
//        QTextCharFormat format;
//        format.setForeground(Qt::darkBlue);
//        format.setBackground(QColor::fromRgb(0, 0, 255, 16));
//        format.setFontWeight(QFont::Black);
//        formats.insert(hid_method, format);
//    }

    void registerCommentFormat();

    void registerNumericFormat();

    void registerRegularExpresionFormat();

    void registerRegularExpresionBorderFormat();

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
    HighlightFormatFactory();

    const QTextCharFormat & getFormatFor(const Identifier & uid);
};

#endif // HIGHLIGHT_FORMAT_FACTORY
