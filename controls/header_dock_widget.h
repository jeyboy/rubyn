#ifndef HEADER_DOCK_WIDGET_H
#define HEADER_DOCK_WIDGET_H

#include <qwidget.h>

class QLabel;
class SearchBox;
class QHBoxLayout;
class QToolButton;

class HeaderDockWidget : public QWidget {
    Q_OBJECT

    QLabel * title_widget;
    QToolButton * search_btn;
    SearchBox * search_widget;
    QHBoxLayout * _layout;
public:
    HeaderDockWidget(QWidget * parent = nullptr, const QString & title = QString());

    void setTitle(const QString & title);
    void showSearch(const bool & show = true);
    QToolButton * insertButton(const QIcon & ico, QObject * target, const char * slot, const int pos = -1, const Qt::Alignment & alignment = Qt::AlignLeft);
    void registerSearchCallbacks(QObject * target, const char * search_request_slot, const char * search_close_slot);

protected slots:
    void toggleSearch();
};

#endif // HEADER_DOCK_WIDGET_H
