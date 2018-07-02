#ifndef PROJECT_TREE_H
#define PROJECT_TREE_H

#include <qtreewidget.h>
#include <qdebug.h>

// TODO: improve tooltips

// Would it be possible to reimplement QtreeWidget::mouseEvent() to get QHoverEvent, calculate which item the mouse is over and display a tooltip?
// There is a QEvent::ToolTip, so i figure you could filter the events through an eventfilter (not sure if installed in the treeWidget or in every treeWidgetItem)

// http://doc.qt.io/qt-5/qtwidgets-widgets-tooltips-example.html

class ProjectTree : public QTreeWidget {
    Q_OBJECT
public:
    explicit ProjectTree(QWidget * parent = nullptr);

signals:
    void fileActivated(const QString & name, void * folder);
//    void fileDeleted(void * folder, const QString & name);

public slots:
    void branchAdded(QTreeWidgetItem * item);
    void folderAdded(const QString & name);
    void fileAdded(const QString & name, void *);

    void itemDoubleClicked(QTreeWidgetItem * item, int /*column*/);
};

#endif // PROJECT_TREE_H
