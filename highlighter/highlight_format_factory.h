#ifndef HIGHLIGHT_FORMAT_FACTORY
#define HIGHLIGHT_FORMAT_FACTORY

#include <qtextformat.h>
#include <qhash.h>

#include "identifiers.h"
#include "misc/singleton.h"

class HighlightFormatFactory : public Singleton<HighlightFormatFactory> {
    QHash<Identifier, QTextCharFormat> _formats;
protected:
    void registerProjectTreeTmpRangeFormat();
    void registerProjectTreeSpecRangeFormat();
    void registerProjectTreePublicRangeFormat();
    void registerProjectTreeLogRangeFormat();
    void registerProjectTreeDbRangeFormat();
    void registerProjectTreeConfigRangeFormat();
    void registerProjectTreeAppRangeFormat();


    void registerSearchOverlayFormat();

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

    void registerSearchResultsOverlayFormat();

    void registerParaHoverLineFormat();

    void registerParaHoverOverlay2Format();

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

    void registerOperatorFormat();

    void registerSpecKeywordFormat();

    void registerKeywordFormat();

    void registerAssigmentFormat();

    void registerNameCallFormat();

    void registerNameDefFormat();

    void registerConstFormat();

    void registerStringBorderFormat();

    void registerStringFormat();

    void registerTernaryFormat();

    void registerCommentFormat();

    void registerNumericFormat();

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
