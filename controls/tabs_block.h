#ifndef TABS_BLOCK_H
#define TABS_BLOCK_H

// !TODO: if opened two tabs with same names need to extend names with path parts

#include <qwidget.h>
#include <qhash.h>
#include <qurl.h>
#include <qdebug.h>

class TabBar;
class QToolButton;
class UniversalEditor;
class File;
class QLabel;
class QFocusEvent;
class QMenu;
class QListWidgetItem;
class QScrollBar;
class BreakpointsPanel;

class TabsBlock : public QWidget {
    Q_OBJECT

    TabBar * _bar;

    QToolButton * _active_btn;
    QToolButton * _list_btn;
    QToolButton * _scroll_left_btn;
    QToolButton * _scroll_right_btn;

    UniversalEditor * _editor;
    BreakpointsPanel * _breakpoints;

    QMenu * _files_list;

    void setupLayout();
public:
    TabsBlock(QWidget * parent = nullptr);
    ~TabsBlock();

    void activate(const bool & act = true);
    void registerCursorPosOutput(QLabel * output);
    void registerBreakpointsPanel(BreakpointsPanel * panel);

    bool openFile(File * file);

    int tabsCount();
    QString tabFilePath(const int & index);
    QString currentTabFilePath();

    bool tabDumpState(const int & index, QVariant & data);
    bool tabRestoreState(const int & index, QVariant & data);

    QPoint currentTabScrollPos();
    QPoint tabScrollPos(const int & index);
    void setTabScrollPos(const int & index, const QPoint & pos);

//    inline UniversalEditor * editor() { return _editor; }

signals:
    void resourceDropped(TabsBlock *, const QUrl &);
    void activated(TabsBlock *);
    void newTabsBlockRequested(File *, const bool & vertical);
    void moveToBlankState(TabsBlock *);

public slots:
    void fileClosed(const QString & uid);
    void saveFiles();
    void currentTabChanged(QListWidgetItem * tab);
    void currentTabIndexChanged(const int & index);
    void clear();

protected slots:
    void buildFilesList();
    void fileListClicked();
    void tabsCountChanged(const int & correction);
    void scrollsVisiabilityChange(const bool & show);
    void closeTab(QListWidgetItem * tab);
    void closeCurrentTab();
    void closeExceptCurrentTab();
    void showTabsContextMenu(const QPoint &);

    void newTabsBlockRequest();
};

#endif // TABS_BLOCK_H
