#ifndef PROJECT_TREE_H
#define PROJECT_TREE_H

#include <qtreewidget.h>

#include "misc/defines.h"

// TODO: improve tooltips

// Would it be possible to reimplement QtreeWidget::mouseEvent() to get QHoverEvent, calculate which item the mouse is over and display a tooltip?
// There is a QEvent::ToolTip, so i figure you could filter the events through an eventfilter (not sure if installed in the treeWidget or in every treeWidgetItem)

// http://doc.qt.io/qt-5/qtwidgets-widgets-tooltips-example.html

class File;
class JsonObj;
class ProjectTreeItemDelegate;

class ProjectTree : public QTreeWidget {
    Q_OBJECT

    ProjectTreeItemDelegate * item_delegate;
    const QVariant property_dropper = QVariant(QVariant::Invalid);

    void saveStateHelper(QTreeWidgetItem * item, QJsonObject & obj);
    void loadStateHelper(QTreeWidgetItem * item, JsonObj & obj);
public:
    explicit ProjectTree(QWidget * parent = nullptr);
    ~ProjectTree() Q_DECL_OVERRIDE;

    QByteArray saveState();
    void restoreState(const QByteArray & state);
    void selectItem(const QString & path, const bool & ensure_visible = true);

    QTreeWidgetItem * findByPath(const QString & path);

    inline static QString name(QTreeWidgetItem * item) { return item -> data(0, Qt::DisplayRole).toString(); }
    static bool isFolder(QTreeWidgetItem * item);
    static bool getFileData(QTreeWidgetItem * item, QString & name, void *& folder);
    static bool getFile(QTreeWidgetItem * item, File *& file);
    static bool getPath(QTreeWidgetItem * item, QString & path);
protected:
    bool search(const QRegularExpression & regexp, QTreeWidgetItem * item, int & res);
    void clearSearch(QTreeWidgetItem * item);

    void keyPressEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
signals:
    void searchRequired(const QString &);
    void searchResultsCount(const int &);
    void closeSearch();
    void pathSearchRequired(const QString &);
    void consoleRequired(const QString & path);
    void closeProjectRequired(const QString & path);

    void fileActivated(const QString & name, void * folder);
//    void fileDeleted(void * folder, const QString & name);

public slots:
    void branchAdded(const uint & project_id, QTreeWidgetItem * item);
    void folderAdded(const QString & name);
    void fileAdded(const QString & name, void * folder);

    void fileIconChanged(const QString & path, const QIcon & ico);

    void itemDoubleClicked(QTreeWidgetItem * item, int /*column*/);

    bool search(const QRegularExpression & regexp);
    void clearSearch();
private slots:
    void showContextMenu(const QPoint & point);
    void collapseChildren(QTreeWidgetItem * curr_item = nullptr);
    void expandChildren(QTreeWidgetItem * curr_item = nullptr);
    void closeProject(const QString & path);
};

#endif // PROJECT_TREE_H
