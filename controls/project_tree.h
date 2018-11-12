#ifndef PROJECT_TREE_H
#define PROJECT_TREE_H

#include <qtreewidget.h>
#include <qdebug.h>

// TODO: improve tooltips

// Would it be possible to reimplement QtreeWidget::mouseEvent() to get QHoverEvent, calculate which item the mouse is over and display a tooltip?
// There is a QEvent::ToolTip, so i figure you could filter the events through an eventfilter (not sure if installed in the treeWidget or in every treeWidgetItem)

// http://doc.qt.io/qt-5/qtwidgets-widgets-tooltips-example.html

class JsonObj;
class ProjectTreeItemDelegate;

class ProjectTree : public QTreeWidget {
    Q_OBJECT

    ProjectTreeItemDelegate * item_delegate;

    void saveStateHelper(QTreeWidgetItem * item, QJsonObject & obj);
    void loadStateHelper(QTreeWidgetItem * item, JsonObj & obj);
public:
    explicit ProjectTree(QWidget * parent = nullptr);
    ~ProjectTree() Q_DECL_OVERRIDE;

    QByteArray saveState();
    void restoreState(const QByteArray & state);
    void selectItem(const QString & path, const bool & ensure_visible = true);
protected:
    bool search(const QString & pattern, QTreeWidgetItem * item);
    void clearSearch(QTreeWidgetItem * item);

    void keyPressEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
signals:
    void searchRequired(const QString &);
    void closeSearch();

    void fileActivated(const QString & name, void * folder);
//    void fileDeleted(void * folder, const QString & name);

public slots:
    void branchAdded(QTreeWidgetItem * item);
    void folderAdded(const QString & name);
    void fileAdded(const QString & name, void *);

    void itemDoubleClicked(QTreeWidgetItem * item, int /*column*/);

    bool search(const QString & pattern);
    void clearSearch();
};

#endif // PROJECT_TREE_H
