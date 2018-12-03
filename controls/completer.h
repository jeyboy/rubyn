#ifndef COMPLETER_H
#define COMPLETER_H

#include <qcompleter.h>
#include <qstandarditemmodel.h>
#include <qabstractitemview.h>
#include <qscrollbar.h>

class Completer : public QCompleter {
    Q_OBJECT

    QStandardItemModel * mdl;
public:
    Completer(QObject * parent = nullptr);

    void setModel(QStandardItemModel * new_mdl = nullptr);
    void prepareMemory(int & new_items_amount, const int & columns_count = 1) {
        mdl -> setColumnCount(columns_count);
        mdl -> setRowCount(new_items_amount);
    }

    inline void addItem(QStandardItem * item) { mdl -> appendRow(item); }

    void reset();
    void hide();
    void clear();
    void update();

    inline bool isVisible() { return popup() -> isVisible(); }
    inline int execWidth(const int & exec_column = 0) { return popup() -> sizeHintForColumn(exec_column) + popup() -> verticalScrollBar() -> sizeHint().width(); }
};

#endif // COMPLETER_H
