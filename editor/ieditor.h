#ifndef IEDITOR_H
#define IEDITOR_H

#include "misc/defines.h"
#include "editor/editor_search_flags.h"

class File;

class IEditor {
public:
    IEditor();
    virtual ~IEditor();

    virtual void openDocument(File * file) = 0;

    virtual void searchIsShow(const bool & show) = 0;
    virtual void searchInitiated(const QString & pattern, const EditorSearchFlags & flags) = 0;
    virtual void searchNextResult(QString * replace = nullptr) = 0;
    virtual void searchPrevResult(QString * replace = nullptr) = 0;
    virtual void searchRepaceAll(const QString & replace) = 0;
    virtual void searchClosed() = 0;

//    virtual void cursorPosChanged(const QString &) = 0;
//    virtual void fileDropped(const QUrl &) = 0;
//    virtual void inFocus() = 0;
};

#endif // IEDITOR_H
