#include "dock_widget.h"

#include <qdebug.h>
#include <qevent.h>

//#include <qdatetime.h>

//LayoutRequest
//UpdateRequest

DockWidget::DockWidget(const QString & title, QWidget * parent, const Qt::DockWidgetAreas & areas) : QDockWidget(title, parent, Qt::WindowCloseButtonHint) {
    setObjectName(title);
    setAllowedAreas(areas);
    setFeatures(QDockWidget::NoDockWidgetFeatures);
}

void DockWidget::closeEvent(QCloseEvent * e) {
    emit closing();
    QDockWidget::closeEvent(e);
}

//DockBar::DockBar(const QString & title, QWidget * parent, bool closable, Qt::WindowFlags flags, const QString & objName)
//    : QDockWidget(title, parent, flags), sticked(false), inProcess(false), mWidget(0), spinner(0) {

//    installEventFilter(parent);

//    setObjectName(objName.isEmpty() ? title + QString::number(QDateTime::currentMSecsSinceEpoch()) : objName);
//    setTitleBarWidget((titleWidget = new WindowTitle(true, this, 26, QMargins(10, 0, 10, 0), QMargins(0, 8, 0, 0), 5, 0, false, false, false)));
////  INFO: rotate is a little buggy
////    titleWidget -> addCustomButton(QLatin1String("Rotate"), QPixmap(QLatin1String(":/controls/rotate_off")), QPixmap(QLatin1String(":/controls/rotate_on")), this, SLOT(rotate()));
//    titleWidget -> addMaxiButton(this, SLOT(toggleFloating()));
//    titleWidget -> addCloseButton(this, SLOT(close()));
//    setWindowTitle(title);

//    if (Settings::currentStyle -> isTransparent())
//        setAttribute(Qt::WA_TranslucentBackground, true);

//    setAttribute(Qt::WA_DeleteOnClose, closable);

//    connect(this, SIGNAL(topLevelChanged(bool)), this, SLOT(floatingChanged(bool)));
//    connect(this, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), this, SLOT(onDockLocationChanged(Qt::DockWidgetArea)));
//    useVerticalTitles(false);
//}

//bool DockWidget::event(QEvent * event) {
//    qDebug() << event -> type();

////    switch(event -> type()) {
////        case QEvent::WindowActivate:
////        case QEvent::WindowDeactivate:
////            ;
////    }

//    return QDockWidget::event(event);
//}

//void DockBar::resizeEvent(QResizeEvent * event) {
//    Settings::currentStyle -> calcBorderRect(rect(), borderRect);
//    QDockWidget::resizeEvent(event);
//}

//void DockBar::setTabBarSettings() {
//    QList<QTabBar *> tabbars = parentWidget() -> findChildren<QTabBar *>(QString(), Qt::FindDirectChildrenOnly);

//    for(QList<QTabBar *>::Iterator it = tabbars.begin(); it != tabbars.end(); it++)
//        (*it) -> setElideMode(Qt::ElideRight);
//}

//TabifyParams DockBar::tabIndex() const {
//    if (titleWidget && parent()) {
//        QWidget * widget = parentWidget();

//        if (widget) {
//            QList<QTabBar *> tabbars = widget -> findChildren<QTabBar *>(QString(), Qt::FindDirectChildrenOnly);
//            QList<QTabBar *>::Iterator it = tabbars.begin();

//            for(; it != tabbars.end(); it++) {
//                for(int index = 0; index < (*it) -> count(); index++) {
//                    if (this == ((DockBar *)((*it) -> tabData(index).toInt())))
//                        return TabifyParams(*it, index);
//                }
//            }
//        }
//    }

//    return TabifyParams();
//}

