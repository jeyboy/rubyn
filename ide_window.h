#ifndef IDE_WINDOW_H
#define IDE_WINDOW_H

#include <qmainwindow.h>

namespace Ui { class IDEWindow; }

class IDEWindow : public QMainWindow {
    Q_OBJECT

    Ui::IDEWindow * ui;
public:
    explicit IDEWindow(QWidget * parent = 0);
    ~IDEWindow();
};

#endif // IDE_WINDOW_H
