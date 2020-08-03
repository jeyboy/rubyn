#include "dock_widget.h"

#include <qevent.h>
#include <qtoolbutton.h>
#include <qtabbar.h>
//#include <qdatetime.h>

#include "header_dock_widget.h"

//LayoutRequest
//UpdateRequest

DockWidget::DockWidget(const QString & title, QWidget * parent, const Qt::DockWidgetAreas & areas) : QDockWidget(title, parent, Qt::WindowCloseButtonHint) {
    header = new HeaderDockWidget(this, title);

    setTitleBarWidget(header);

    setObjectName(title);
    setAllowedAreas(areas);
    setFeatures(QDockWidget::NoDockWidgetFeatures);

    connect(this, &DockWidget::topLevelChanged, [=](bool /*top_level*/) {
        updateIcons();
    });

    connect(this, &DockWidget::dockLocationChanged, [=](Qt::DockWidgetArea /*area*/) {
        updateIcons();
    });
}

void DockWidget::setBehaviour(const Features & params) {
    if (params & dwf_destroyable)
        setAttribute(Qt::WA_DeleteOnClose, true);

    if (params & dwf_closable) {
        QToolButton * cls_btn = insertHeaderButton(QIcon(QLatin1String(":/tools/close")), this, SLOT(close()), -2);
        cls_btn -> setStyleSheet("background: transparent");
    }

    setFeatures((DockWidgetFeatures)(params & (dwf_destroyable - 1)));
}

QString DockWidget::windowTitle() {
    return header -> title();
}

void DockWidget::setWindowTitle(const QString & new_title) {
    header -> setTitle(new_title);
    QDockWidget::setWindowTitle(new_title);
}

void DockWidget::setWindowIco(const QString & ico_path, const QString & tab_ico_path) {
    header -> setIcon(ico_path);
    setProperty("ico", tab_ico_path);
    updateIcons();
}

void DockWidget::showSearch(const bool & show) {
    header -> showSearch(show);
}

void DockWidget::insertHeaderButton(QWidget * btn, QObject * target, const char * slot, const int pos, const Qt::Alignment & alignment) {
    return header -> insertButton(btn, target, slot, pos, alignment);
}
QToolButton * DockWidget::insertHeaderButton(const QIcon & ico, QObject * target, const char * slot, const int pos, const Qt::Alignment & alignment) {
    return header -> insertButton(ico, target, slot, pos, alignment);
}

void DockWidget::registerSearchCallbacks(const DockWidgetSearchConnector & connector) {
    header -> registerSearchCallbacks(connector);
}

void DockWidget::updateIcons() {
    QWidget * widget = parentWidget();

    if (widget) {
        QList<QTabBar *> tabbars = widget -> findChildren<QTabBar *>(QString(), Qt::FindDirectChildrenOnly);
        QList<QTabBar *>::Iterator it = tabbars.begin();

        for(; it != tabbars.end(); it++) {
            for(int index = 0; index < (*it) -> count(); index++) {

            DockWidget * widget = (DockWidget *)((*it) -> tabData(index).toLongLong());
            if (!widget -> property("ico").isNull()) {
                (*it) -> setTabIcon(index, QIcon(widget -> property("ico").toString()));
            }

//                if (this == ((DockWidget *)((*it) -> tabData(index).toInt()))) {

//                }
            }
        }
    }
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

