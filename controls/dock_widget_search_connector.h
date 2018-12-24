#ifndef DOCK_WIDGET_SEARCH_CONNECTOR_H
#define DOCK_WIDGET_SEARCH_CONNECTOR_H

#include <qobject.h>

struct DockWidgetSearchConnector {
    QObject * target;

    const char * search_show_signal;
    const char * search_hide_signal;
    const char * search_amount_signal;
    const char * search_request_slot;
    const char * search_close_slot;
    const char * search_prev_result_slot;
    const char * search_next_result_slot;

    DockWidgetSearchConnector(QObject * obj = nullptr) : target(obj) {}
};

#endif // DOCK_WIDGET_SEARCH_CONNECTOR_H
