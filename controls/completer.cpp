#include "completer.h"

#include <qabstractitemview.h>

Completer::Completer(QObject * parent) : QCompleter(parent), mdl(new QStandardItemModel(this)) {
    popup() -> setIconSize(QSize(22, 22));

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

void Completer::clear() {
    mdl -> clear();
}

void Completer::update() {
    QCompleter::setModel(mdl);
//    popup() -> setModel(mdl);
}
