#ifndef COMPLETER_H
#define COMPLETER_H

#include <qcompleter.h>
#include <qstandarditemmodel.h>

class Completer : public QCompleter {
    Q_OBJECT

    QStandardItemModel * mdl;
public:
    Completer(QObject * parent = 0);

    void setModel(QStandardItemModel * new_mdl = 0);
    void prepareMemory(uint & new_items_amount) {
        mdl -> setColumnCount(1);
        mdl -> setRowCount(new_items_amount);
    }

    inline void addItem(QStandardItem * item) { mdl -> appendRow(item); }
    void clear();
    void update();
};

#endif // COMPLETER_H
