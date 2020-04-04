#ifndef IEDITOR_H
#define IEDITOR_H

#include "misc/defines.h"

class File;
class QScrollBar;

class IEditor {
public:
    IEditor();
    virtual ~IEditor();

    virtual QScrollBar * verticalScrollBar() = 0;
    virtual QScrollBar * horizontalScrollBar() = 0;

    virtual void setVisible(bool visible) = 0;

    virtual void openDocument(File * file) = 0;
    virtual void ensureVisibleBlock(const qint64 & block_num, const qint64 & char_in_line = 0) = 0;

//    virtual void searchIsShow(const bool & show) = 0;
    virtual void searchInitiated(const QRegularExpression & pattern, const bool & scroll = true) = 0;
    virtual void searchNextResult(QString * replace = nullptr) = 0;
    virtual void searchPrevResult(QString * replace = nullptr) = 0;
    virtual void searchRepaceAll(const QString & replace) = 0;
    virtual void searchClosed() = 0;

//    virtual void cursorPosChanged(const QString &) = 0;
//    virtual void fileDropped(const QUrl &) = 0;
//    virtual void inFocus() = 0;
};

#endif // IEDITOR_H
