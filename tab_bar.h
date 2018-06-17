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
    QMimeData * mimeData(const QList<QListWidgetItem *> items) const;
    bool dropMimeData(int index, const QMimeData * data, Qt::DropAction action);
signals:
    void layoutChanged();

public slots:
    void scrollForward();
    void scrollBackward();
};

#endif // TABBAR_H
