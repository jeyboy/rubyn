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

    void itemDoubleClicked(QTreeWidgetItem * item, int /*column*/) {
        QVariant item_data = item -> data(0, Qt::UserRole);

        if (item_data.isNull()) {
            QTreeWidgetItem * parent = item -> parent();
            QVariant parent_data = parent -> data(0, Qt::UserRole);

            QString name = item -> data(0, Qt::DisplayRole).toString();
            void * folder = parent_data.value<void *>();

            emit fileActivated(name, folder);
        } else {
            // edit folder name
        }
    }
};

#endif // PROJECT_TREE_H
