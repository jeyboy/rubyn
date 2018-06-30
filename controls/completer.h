#ifndef COMPLETER_H
#define COMPLETER_H

#include <qcompleter.h>

class QAbstractItemModel;
class QIcon;

class Completer : public QCompleter {
    Q_OBJECT

    QAbstractItemModel * mdl;
public:
    Completer(QObject * parent = 0);

    void setModel(QAbstractItemModel * new_mdl = 0);

    void addItem(const QString & text, const QString & tooltip, const QIcon & ico);
    void clear();
    void update();
};

#endif // COMPLETER_H
