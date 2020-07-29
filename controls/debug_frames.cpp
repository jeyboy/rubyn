#include "debug_frames.h"

#include "delegates/debug_view_item_delegate.h"

#include <qlayout.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qdebug.h>
#include <qheaderview.h>

DebugFrames::DebugFrames(QWidget * parent) : QWidget(parent), view(nullptr)/*, new_itm(nullptr)*/ {
    view = new DebugFramesView(this);
    view -> setColumnCount(1);
    view -> setHeaderLabels(QStringList() << QString());
    view -> setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
//    view -> setWordWrap(true);
    view -> setAlternatingRowColors(true);
    view -> setAcceptDrops(false);
//    view -> setCornerWidget()

    view -> setRootIsDecorated(false);
//    view -> hideColumn(0);

//    view -> header() -> setMinimumSectionSize(16);
//    view -> header() -> setResizeContentsPrecision(-1);
//    view -> header() -> resizeSection(1, 200);

//    view -> setItemDelegate(new DebugViewItemDelegate(view));

    QHBoxLayout * l = new QHBoxLayout(this);
    l -> setContentsMargins(0, 0, 0, 0);
    l -> setSpacing(0);

//    QToolBar * control_panel = new QToolBar(this);
//    control_panel -> setOrientation(Qt::Vertical);
//    control_panel -> setIconSize(QSize(18, 18));

//    QToolButton * btn0 = new QToolButton(control_panel);
//    btn0 -> setIcon(QIcon(QLatin1Literal(":/add")));
//    btn0 -> setToolTip(QLatin1Literal("Add"));
//    control_panel -> addWidget(btn0);

//    QToolButton * btn1 = new QToolButton(control_panel);
//    btn1 -> setIcon(QIcon(QLatin1Literal(":/remove")));
//    btn1 -> setToolTip(QLatin1Literal("Remove"));
//    control_panel -> addWidget(btn1);

//    QToolButton * btn2 = new QToolButton(control_panel);
//    btn2 -> setIcon(QIcon(QLatin1Literal(":/clear")));
//    btn2 -> setToolTip(QLatin1Literal("Clear"));
//    control_panel -> addWidget(btn2);

//    l -> addWidget(control_panel, 0);
    l -> addWidget(view, 1);

//    connect(btn0, &QToolButton::pressed, this, &DebugPanel::openNewRecord);
//    connect(btn1, &QToolButton::pressed, this, &DebugPanel::removeSelectedRecordItems);
//    connect(btn2, &QToolButton::pressed, this, &DebugPanel::clearAll);

//    connect(view -> itemDelegate(), SIGNAL(closeEditor(QWidget *, QAbstractItemDelegate::EndEditHint)), this, SLOT(editorClosed(QWidget *, QAbstractItemDelegate::EndEditHint)));
//    connect(view, SIGNAL(newItemRequired()), this, SLOT(openNewRecord()));

//    void itemChanged(QTreeWidgetItem *item, int column);
}

//void DebugFrames::activate(const uint & project_id, const QString & /*path*/, const EDITOR_POS_TYPE & /*line_num*/) {
//    qDebug() << "DebugPanel::activate";
//}

//void DebugFrames::deactivate() {
//    qDebug() << "DebugPanel::deactivate";
//}

//void DebugFrames::openNewRecord() {
//    if (!new_itm) {
//        new_itm = new QTreeWidgetItem(QStringList() << QString() << QString("") << QString(""));
//        new_itm -> setFlags(new_itm -> flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEditable);
//        new_itm -> setCheckState(0, Qt::Checked);
//        view -> addTopLevelItem(new_itm);
//    }

//    if (!view -> isPersistentEditorOpen(new_itm, 1)) {
//        view -> openPersistentEditor(new_itm, 1);
//    }
//}

//void DebugFrames::removeRecord(const QString & record) {

//}

//void DebugFrames::addRecord(const QString & record) {
//    QTreeWidgetItem * itm = new QTreeWidgetItem(QStringList() << QString("") << record << DebugViewItemDelegate::default_text);
//    itm -> setFlags(itm -> flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsEditable);
//    itm -> setCheckState(0, Qt::Checked);

//    records.insert(record, itm);

//    view -> addTopLevelItem(itm);
//}

//void DebugFrames::changeRecord(const QString & old_record, const QString & new_record) {
//    records.remove(old_record);

//    addRecord(new_record);
//}

//void DebugFrames::setRecordValue(const QString & record, const QString & value) {
//    if (records.contains(record)) {
//        QTreeWidgetItem * itm = records[record];

//        itm -> setText(2, value);
//    }
//}

////void DebugFrames::itemContentChanged(QTreeWidgetItem * item, int column) {
////    if (item == new_itm) {

////    } else {

////    }
////}

//void DebugFrames::editorClosed(QWidget * /*editor*/, QAbstractItemDelegate::EndEditHint /*hint*/) {
//    if (!new_itm) return;

//    view -> closePersistentEditor(new_itm, 1);

//    QString txt = new_itm -> text(1).simplified();

//    if (txt.length() == 0) {
//        delete new_itm;
//    }
//    else {
//        new_itm -> setText(2, DebugViewItemDelegate::default_text);
//    }

//    new_itm = nullptr;
//}

//void DebugFrames::removeSelectedRecordItems() {
//    QList<QTreeWidgetItem *> items = view -> selectedItems();

//    if (items.isEmpty())
//        return;

//    for(int i = items.length() - 1; i >= 0; --i) {
//        QTreeWidgetItem * itm = items.at(i);
//        records.remove(itm -> text(0));

//        if (new_itm && new_itm == itm) {
//            view -> closePersistentEditor(new_itm, 1);
//            new_itm = nullptr;
//        }

//        delete itm;
//    }
//}

//void DebugFrames::clearAll() {
//    new_itm = nullptr;
//    records.clear();
//    view -> clear();
//}
