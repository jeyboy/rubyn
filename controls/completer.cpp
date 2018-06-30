#include "completer.h"

#include <qstandarditemmodel.h>
//#include <qabstractitemview.h>

Completer::Completer(QObject * parent) : QCompleter(parent) {
    mdl = new QStandardItemModel(this);

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

void Completer::setModel(QAbstractItemModel * new_mdl) {
    QCompleter::setModel(new_mdl ? new_mdl : mdl);
}

void Completer::addItem(const QString & text, const QString & tooltip, const QIcon & ico) {

}

void Completer::clear() {

}

void Completer::update() {
    QCompleter::setModel(mdl);
//    popup() -> setModel(mdl);
}
