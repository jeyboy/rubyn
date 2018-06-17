#ifndef TABBAR_H
#define TABBAR_H

#include <qtabbar.h>
#include <qlistwidget.h>

class TabBar : public QListWidget {
    Q_OBJECT
public:
    TabBar(QWidget * parent = 0);

    QListWidgetItem * addTab(const QIcon & ico, const QString & text);
    void removeTab(QListWidgetItem *);
protected:
    Qt::DropActions supportedDropActions() const;
    QMimeData * mimeData(const QList<QListWidgetItem *> items) const;
    bool dropMimeData(int index, const QMimeData * data, Qt::DropAction action);

    void rowsInserted(const QModelIndex & parent, int start, int end);
    void rowsAboutToBeRemoved(const QModelIndex & parent, int start, int end);
    QSize viewportSizeHint() const;
signals:
    void itemsCountChanged(const int & correction = 0);
    void tabCloseRequested(QListWidgetItem*);
protected slots:
    void itemCloseRequested(const QModelIndex &);

public slots:
    void scrollForward();
    void scrollBackward();
};

#endif // TABBAR_H
