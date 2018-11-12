#ifndef DOCK_WIDGET_H
#define DOCK_WIDGET_H

#include <qdockwidget.h>

#include <qdebug.h>

//// Recursively update all the layouts, starting from the main window
//forceUpdate(mainW);

//// Remove the size constraint
//widget()->setMinimumHeight(QWIDGETSIZE_MAX);
//widget()->setMaximumHeight(QWIDGETSIZE_MAX);

class HeaderDockWidget;
class QToolButton;

class DockWidget : public QDockWidget {
    Q_OBJECT

    HeaderDockWidget * header;
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

    void setWindowTitle(const QString & new_title);

    QToolButton * insertHeaderButton(const QIcon & ico, QObject * target, const char * slot, const int pos = -1, const Qt::Alignment & alignment = Qt::AlignLeft);

    void registerSearchCallbacks(QObject * target, const char * search_show_signal, const char * search_hide_signal, const char * search_request_slot, const char * search_close_slot);

//    inline void initiateSearch() { titleWidget -> initiateSearch(mainWidget(), SLOT(startInnerSearch(QString)), SLOT(endInnerSearch()), SIGNAL(searchFinished())); }
signals:
    void closing();

public slots:
    void showSearch(const bool & show = true);

//    inline void onSetDefaultIco(const QImage & ico) { titleWidget -> setIco(ico); }
//    inline void floatingChanged(bool floating) { if (!floating) setTabBarSettings(); }
//    inline void onDockLocationChanged(Qt::DockWidgetArea area) { if (area != Qt::NoDockWidgetArea) setTabBarSettings(); }

protected:
//    bool event(QEvent * event);
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
