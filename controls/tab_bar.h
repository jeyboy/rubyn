#ifndef TABBAR_H
#define TABBAR_H

#include <qtabbar.h>
#include <qlistwidget.h>

class File;

class TabBar : public QListWidget {
    Q_OBJECT

    bool _internal_move;
    QHash<QString, QListWidgetItem *> * _tabs_linkages;
public:
    TabBar(QWidget * parent = 0);

    QListWidgetItem * addTab(const QIcon & ico, const QString & text);
    void removeTab(QListWidgetItem *);

    File * tabFile(QListWidgetItem * tab);

    inline void setTabsLinkages(QHash<QString, QListWidgetItem *> * linkages = 0) { _tabs_linkages = linkages; }
protected:
    Qt::DropActions supportedDropActions() const;
    void dropEvent(QDropEvent * event);
//    QMimeData * mimeData(const QList<QListWidgetItem *> items) const;
    bool dropMimeData(int index, const QMimeData * data, Qt::DropAction action);

    void rowsInserted(const QModelIndex & parent, int start, int end);
    void rowsAboutToBeRemoved(const QModelIndex & parent, int start, int end);
    void updateGeometries();
signals:
    void scrollsRequired(const bool & show);
    void itemsCountChanged(const int & correction = 0);
    void tabCloseRequested(QListWidgetItem *);
protected slots:
    void itemCloseRequested(const QModelIndex &);
public slots:
    void scrollForward();
    void scrollBackward();
};

#endif // TABBAR_H
