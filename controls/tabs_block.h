#ifndef TABS_BLOCK_H
#define TABS_BLOCK_H

// !TODO: if opened two tabs with same names need to extend names with path parts

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
class QListWidgetItem;
class Completer;
class QScrollBar;

class TabsBlock : public QWidget {
    Q_OBJECT

    TabBar * _bar;
    Completer * _completer;

    QToolButton * _active_btn;
    QToolButton * _list_btn;
    QToolButton * _scroll_left_btn;
    QToolButton * _scroll_right_btn;

    CodeEditor * _editor;

    QMenu * _files_list;

    QHash<QString, File *> _external_files;

    void setupLayout();
    void setupCompleter();
    bool openFileInEditor(File * file);
public:
    TabsBlock(QWidget * parent = nullptr);
    ~TabsBlock();

    void activate(const bool & act = true);
    void registerCursorPosOutput(QLabel * output);

    bool openFile(File * file, const bool & is_external = false);

    int tabsCount();
    QString tabFilePath(const int & index);
    QString currentTabFilePath();

    bool tabDumpState(const int & index, QVariant & data);
    bool tabRestoreState(const int & index, QVariant & data);

    int tabVerticalScrollPos(const int & index);
    void setTabVerticalScrollPos(const int & index, const int & pos);

    inline CodeEditor * editor() { return _editor; }

signals:
    void resourceDropped(TabsBlock *, const QUrl &);
    void activated(TabsBlock *);
    void newTabsBlockRequested(File *, const bool & vertical);
    void moveToBlankState(TabsBlock *);

public slots:
    void saveFiles();
    void currentTabChanged(QListWidgetItem * tab);
    void currentTabIndexChanged(const int & index);
    void clear();

protected slots:
    inline void resourceDrop(const QUrl & url) { emit resourceDropped(this, url); }
    inline void inFocus() { emit activated(this); }

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
