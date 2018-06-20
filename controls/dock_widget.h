#ifndef DOCK_WIDGET_H
#define DOCK_WIDGET_H

#include <qdockwidget.h>

class DockWidget : public QDockWidget {
    Q_OBJECT
public:
    enum Features {
        dwf_none        = 0,
        dwf_closable    = DockWidgetClosable,
        dwf_movable     = DockWidgetMovable,
        dwf_floatable   = DockWidgetFloatable,

        dwf_destroyable = 128
    };
    Q_DECLARE_FLAGS(DockFeatures, Features)
    Q_FLAG(DockFeatures)

    explicit DockWidget(const QString & title, QWidget * parent = nullptr, const Qt::DockWidgetAreas & areas = Qt::AllDockWidgetAreas);

    void setBehaviour(const DockFeatures & params) {
        if (params & dwf_destroyable)
            setAttribute(Qt::WA_DeleteOnClose, true);

        setFeatures((DockWidgetFeatures)(int)(params & (dwf_destroyable - 1)));
    }

//    DockBar(const QString & title, QWidget * parent = 0, bool closable = true, Qt::WindowFlags flags = 0, const QString & objName = QString());

//    inline void setWindowTitle(const QString & newTitle) {
//        titleWidget -> setText(newTitle);
//        QDockWidget::setWindowTitle(newTitle);
//    }

//    inline void initiateSearch() { titleWidget -> initiateSearch(mainWidget(), SLOT(startInnerSearch(QString)), SLOT(endInnerSearch()), SIGNAL(searchFinished())); }
signals:
    void closing();
public slots:
//    inline void showSearch() { titleWidget -> showSearch(); }

//    inline void onSetDefaultIco(const QImage & ico) { titleWidget -> setIco(ico); }
//    inline void floatingChanged(bool floating) { if (!floating) setTabBarSettings(); }
//    inline void onDockLocationChanged(Qt::DockWidgetArea area) { if (area != Qt::NoDockWidgetArea) setTabBarSettings(); }

protected:
//        bool event(QEvent *event);
//    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent * e);
//    void paintEvent(QPaintEvent *);

private:
//    void setTabBarSettings();

//    WindowTitle * titleWidget;
};

#endif // DOCK_WIDGET_H

//namespace Controls {
//    struct TabifyParams {
//        TabifyParams() : tabbar(0), index(-1) {}
//        TabifyParams(QTabBar * bar, int ind) : tabbar(bar), index(ind) {}

//        bool operator == (TabifyParams & oth) { return index == oth.index && tabbar == oth.tabbar; }

//        QTabBar * tabbar;
//        int index;
//    };
//}