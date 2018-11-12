#ifndef SEARCH_BOX_H
#define SEARCH_BOX_H

#include <qlineedit.h>

class SearchBox : public QLineEdit {
    Q_OBJECT
public:
    SearchBox(QWidget * parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
    void hideEvent(QHideEvent * e) Q_DECL_OVERRIDE;

signals:
    void hidden();
};

#endif // SEARCH_BOX_H
