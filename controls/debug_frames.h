#ifndef DEBUG_FRAMES_H
#define DEBUG_FRAMES_H

#include "misc/defines.h"
#include "controls/debug_frames_view.h"

class DebugFrames : public QWidget {
    Q_OBJECT

    DebugFramesView * view;
//    QTreeWidgetItem * new_itm;
//    QHash<QString, QTreeWidgetItem *> records;
public:
    DebugFrames(QWidget * parent = nullptr);

//public slots:
//    void activate(const uint & project_id, const QString & path, const EDITOR_POS_TYPE & line_num);
//    void deactivate();

//    void openNewRecord();
//    void removeRecord(const QString & record);

//    void addRecord(const QString & record);
//    void changeRecord(const QString & old_record, const QString & new_record);
//    void setRecordValue(const QString & record, const QString & value);
//protected slots:
////    void itemContentChanged(QTreeWidgetItem * item, int column);
//    void editorClosed(QWidget * editor, QAbstractItemDelegate::EndEditHint hint = QAbstractItemDelegate::NoHint);
//    void removeSelectedRecordItems();
//    void clearAll();
};

#endif // DEBUG_FRAMES_H
