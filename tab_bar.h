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
//    void dragEnterEvent(QDragEnterEvent *event);
//    void dragMoveEvent(QDragMoveEvent *event);
//    void dragLeaveEvent(QDragLeaveEvent *event);
//    void dropEvent(QDropEvent *event);
signals:
    void layoutChanged();

public slots:
    void scrollForward();
    void scrollBackward();
};

#endif // TABBAR_H
