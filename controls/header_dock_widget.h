#ifndef HEADER_DOCK_WIDGET_H
#define HEADER_DOCK_WIDGET_H

#include <qwidget.h>

#include "dock_widget_search_connector.h"

class QLabel;
class SearchPanel;
class QHBoxLayout;
class QToolButton;

class HeaderDockWidget : public QWidget {
    Q_OBJECT

    QLabel * title_widget;
    QToolButton * search_btn;
    SearchPanel * search_widget;
    QHBoxLayout * _layout;
public:
    HeaderDockWidget(QWidget * parent = nullptr, const QString & title = QString());

    void setTitle(const QString & title);

    void insertButton(QWidget * btn, QObject * target, const char * slot, const int pos = -1, const Qt::Alignment & alignment = Qt::AlignLeft);
    QToolButton * insertButton(const QIcon & ico, QObject * target, const char * slot, const int pos = -1, const Qt::Alignment & alignment = Qt::AlignLeft);
    void registerSearchCallbacks(const DockWidgetSearchConnector & connector);
    void showSearch(const bool & show = true);


public slots:
    void initiateSearch(const QString & pattern = QString());

protected slots:
    void hideSearch();
    void toggleSearch();
};

#endif // HEADER_DOCK_WIDGET_H
