#ifndef DEBUG_PANEL_H
#define DEBUG_PANEL_H

#include "controls/debug_view.h"

class DebugPanel : public QWidget {
    Q_OBJECT

    static const QLatin1String def_val;

    DebugView * view;
    QTreeWidgetItem * new_itm;
    QHash<QString, QTreeWidgetItem *> records;
public:
    DebugPanel(QWidget * parent = nullptr);

public slots:
    void openNewRecord();
    void removeRecord(const QString & record);

    void addRecord(const QString & record);
    void changeRecord(const QString & old_record, const QString & new_record);
    void setRecordValue(const QString & record, const QString & value);
protected slots:
//    void itemContentChanged(QTreeWidgetItem * item, int column);
    void editorClosed(QWidget * editor, QAbstractItemDelegate::EndEditHint hint = QAbstractItemDelegate::NoHint);
    void removeSelectedRecordItems();
    void clearAll();
};

#endif // DEBUG_PANEL_H
