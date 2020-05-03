#ifndef HIGHLIGHT_FORMAT_FACTORY
#define HIGHLIGHT_FORMAT_FACTORY

#include <qtextformat.h>
#include <qhash.h>

#include "identifiers.h"
#include "misc/singleton.h"

class HighlightFormatFactory : public Singleton<HighlightFormatFactory> {
    QHash<Identifier, QTextCharFormat> _formats;
protected:
    void registerProjectTreeLibRangeFormat();
    void registerProjectTreeTmpRangeFormat();
    void registerProjectTreeSpecRangeFormat();
    void registerProjectTreePublicRangeFormat();
    void registerProjectTreeLogRangeFormat();
    void registerProjectTreeDbRangeFormat();
    void registerProjectTreeConfigRangeFormat();
    void registerProjectTreeAppRangeFormat();

    void registerSearchOverlayFormat();

    void registerLineNumberFormat();

    void registerExtraIconsRangeFormat();

    void registerSelectionFormat();

    void registerCurrentLineFormat();

    void registerFoldingLevelLineFormat();

    void registerFoldingContentPopupFormat();

    void registerFoldingHoverRangeFormat();

    void registerCurrentLineExtraFormat();

    void registerFoldingParaRangeFormat();

    void registerFoldedSelectedOverlayFormat();

    void registerFoldedOverlayFormat();

//    void registerSearchResultsOverlayFormat();

    void registerParaHoverLineFormat();

    void registerParaHoverSubOverlay2Format();

    void registerParaHoverOverlay2Format();

    void registerParaHoverSubOverlayFormat();

    void registerParaHoverOverlayFormat();

    void registerParaContentPopupFormat();

    void registerBreakpointsRangeFormat();

    void registerBreakpointLineFormat();

    void registerBreakpointActiveLineFormat();

    void registerCharsLimiterLineFormat();

    void registerErrorFormat();

    void registerWarningFormat();

    void registerSpellcheckFormat();

    void registerScopeVisibilityFormat();

    void registerUnclosedParaFormat();

    void registerUnknownName();

    void registerLabelFormat();

    void registerStringLabelFormat();

    void registerOperatorFormat();

    void registerSpecKeywordFormat();

    void registerKeywordFormat();

    void registerAssigmentFormat();

    void registerNameCallFormat();

    void registerNameArgFormat();

    void registerNameDefFormat();

    void registerConstFormat();

    void registerStringBorderFormat();

    void registerStringSpecFormat();

    void registerStringCodeFormat();

    void registerStringFormat();

    void registerTernaryFormat();

    void registerCommentFormat();

    void registerNumericFormat();

    void registerRangeFormat();

    void registerRegularExpresionFormat();

    void registerRegularExpresionBorderFormat();

    void registerSecuenceFormat();

    void registerCommentMarkInfoFormat();
    void registerCommentMarkWarnFormat();
    void registerCommentMarkTodoFormat();

public:
    HighlightFormatFactory();

    const QTextCharFormat & getFormatFor(const Identifier & uid);
};

#endif // HIGHLIGHT_FORMAT_FACTORY
