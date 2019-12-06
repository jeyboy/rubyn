#ifndef TREE_EDITOR_H
#define TREE_EDITOR_H

#include <qtreeview.h>
#include <qevent.h>
#include <qmimedata.h>

#include "editor/ieditor.h"

class TreeEditor : public QTreeView, public IEditor {
    Q_OBJECT

    bool searcher_is_opened;
public:
    TreeEditor(QWidget * parent = Q_NULLPTR);

    void openDocument(File * file) Q_DECL_OVERRIDE;

    void setVisible(bool visible) Q_DECL_OVERRIDE;

    QScrollBar * verticalScrollBar() Q_DECL_OVERRIDE;

    void ensureVisibleBlock(const qint64 & block_num, const qint64 & char_in_line = 0) Q_DECL_OVERRIDE;

    void focusInEvent(QFocusEvent * e) Q_DECL_OVERRIDE;

    void keyPressEvent(QKeyEvent * e) Q_DECL_OVERRIDE;

    void dropEvent(QDropEvent * e) Q_DECL_OVERRIDE {
        const QMimeData * source = e -> mimeData();

        if (source -> hasUrls()) {
            QList<QUrl> urls = source -> urls();
//            bool multiple(urls.count() > 1);

            for(QList<QUrl>::Iterator url = urls.begin(); url != urls.end(); url++)
                emit fileDropped(
                    (*url).adjusted(QUrl::NormalizePathSegments)/*,*/ // KDE may give a double slash
//                    multiple
                );
        }
        else QTreeView::dropEvent(e);
    }

//    verticalScrollBar();

signals:
    void inFocus();
    void fileDropped(const QUrl & uri/*, bool multiple*/); // Multiple files are dropped?
    void cursorPosChanged(const QString & pos_coords); // not implemented

    void searchRequired(const bool & show = true);
    void searchRequestRequired(const QString & pattern);
    void searchResultsFinded(const int & count);

public slots:
//    void searchIsShow(const bool & show) Q_DECL_OVERRIDE;
    void searchInitiated(const QRegularExpression & pattern, const bool & scroll = true) Q_DECL_OVERRIDE;
    void searchNextResult(QString * replace = nullptr) Q_DECL_OVERRIDE;
    void searchPrevResult(QString * replace = nullptr) Q_DECL_OVERRIDE;
    void searchRepaceAll(const QString & replace) Q_DECL_OVERRIDE;
    void searchClosed() Q_DECL_OVERRIDE;
};

#endif // TREE_EDITOR_H
