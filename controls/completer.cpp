#include "completer.h"

#include <qabstractitemview.h>

Completer::Completer(QObject * parent) : QCompleter(parent), mdl(new QStandardItemModel(this)) {
    popup() -> setIconSize(QSize(22, 22));
    setFilterMode(Qt::MatchContains);
    setMaxVisibleItems(12);

//    setModelSorting(QCompleter::UnsortedModel);

//    // initialize the model
//    int rows = names.count();  // assuming this is a QStringList
//    model->setRowCount(rows);
//    model->setColumnCount(1);

//    // load the items
//    int row = 0;
//    foreach(name, names) {
//        QStandardItem* item = new QStandardItem(name);
//        item->setIcon(QIcon(":some/icon.png");
//        item->setToolTip("some tool tip");
//        model->setItem(row, 0, item);
//        row++;
//    }



//    QTreeView::item:selected{background-color: #bedcf0;} //light blue
//    QTreeView::item:hover:selected{background-color: #94c8ea;} //darker blue
//    QTreeView::item:hover:!selected{background-color: #e6e6e6;} //gray


    popup() -> setStyleSheet(
        QLatin1Literal(
            "   selection-background-color: rgba(135, 206, 250, 0.2);"
            "   selection-color: black;"
        )
    );
}

void Completer::setModel(QStandardItemModel * new_mdl) {
    if (new_mdl) {
        if (new_mdl != mdl) {
            delete mdl;
            mdl = new_mdl;
        }
    }
    else {
        delete mdl;
        mdl = new QStandardItemModel(this);
    }

    QCompleter::setModel(mdl);
}

void Completer::reset() {
    popup() -> reset();
}
void Completer::hide() {
    popup() -> hide();
}

void Completer::clear() {
    mdl -> clear();
}

void Completer::update() {
    QCompleter::setModel(mdl);
//    popup() -> setModel(mdl);
}
