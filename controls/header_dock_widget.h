#ifndef HEADER_DOCK_WIDGET_H
#define HEADER_DOCK_WIDGET_H

#include <qwidget.h>

class QLabel;
class QLineEdit;
class QHBoxLayout;
class QToolButton;

class HeaderDockWidget : public QWidget {
    Q_OBJECT

    QLabel * title_widget;
    QLineEdit * search_widget;
    QHBoxLayout * _layout;
public:
    HeaderDockWidget(QWidget * parent = nullptr, const QString & title = QString());

    void setTitle(const QString & title);
    void showSearch(const bool & show = true);
    QToolButton * insertButton(const QIcon & ico, QObject * target, const char * slot, const int pos = -1, const Qt::Alignment & alignment = Qt::AlignLeft);

protected slots:
    void toggleSearch();
};

#endif // HEADER_DOCK_WIDGET_H
