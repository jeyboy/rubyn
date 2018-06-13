#ifndef TABS_BLOCK_H
#define TABS_BLOCK_H

#include <qwidget.h>
#include <qhash.h>
#include <qurl.h>
#include <qdebug.h>

class TabBar;
class QToolButton;
class CodeEditor;
class File;
class QLabel;
class QFocusEvent;
class QMenu;

class TabsBlock : public QWidget {
    Q_OBJECT

    TabBar * bar;

    QToolButton * list_btn;
    CodeEditor * editor;

    QMenu * files_list;

    QHash<QString, int> tab_links;

    int menu_target_index;

    void setupLayout();
    bool openFileInEditor(File * file);
    void rebuildIndexes(const int & rindex);

public:
    TabsBlock(QWidget * parent = 0);
    ~TabsBlock();

    void registerCursorPosOutput(QLabel * output);

    bool openFile(File * file);

signals:
    void resourceDropped(TabsBlock *, const QUrl &);
    void activated(TabsBlock *);
    void newTabsBlockRequested(File *);
    void moveToBlankState(TabsBlock *);

protected slots:
    inline void resourceDrop(const QUrl & url) { emit resourceDropped(this, url); }
    inline void inFocus() { emit activated(this); }

    void buildFilesList();
    void fileListClicked();

    void tabsLayoutChanged();
    void currentTabChanged(const int &);
    void tabRemoved(const int &);
    void tabMoved(const int &, const int &);
    void showTabsContextMenu(const QPoint &);

    void newTabsBlockRequest();
};

#endif // TABS_BLOCK_H
