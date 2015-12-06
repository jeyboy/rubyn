#include "ide_window.h"
#include "ui_ide_window.h"

#include "parts/code_editor.h"

IDEWindow::IDEWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::IDEWindow) {
    ui -> setupUi(this);

    setCentralWidget(new CodeEditor(this));
}

IDEWindow::~IDEWindow() { delete ui; }
