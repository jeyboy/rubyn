#include "ide_window.h"
#include "ui_ide_window.h"

#include <qmessagebox.h>
#include <qfiledialog.h>

IDEWindow::IDEWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::IDEWindow) {
    ui -> setupUi(this);

    setupFileMenu();
    setupHelpMenu();
    setupEditor();

    setWindowTitle(tr("Bla bla blashka"));
    setCentralWidget(editor);
}

IDEWindow::~IDEWindow() { delete ui; }

void IDEWindow::about() {
    QMessageBox::about(this, tr("About Syntax Highlighter"),
                tr("<p>The <b>Syntax Highlighter</b> example shows how " \
                   "to perform simple syntax highlighting by subclassing " \
                   "the QSyntaxHighlighter class and describing " \
                   "highlighting rules using regular expressions.</p>"));
}

void IDEWindow::newFile() { editor -> clear(); }

void IDEWindow::openFile(const QString & path) {
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "C++ Files (*.cpp *.h), Ruby Files (*.rb)");

    if (!fileName.isEmpty())
        editor -> openDocument(fileName);
}

void IDEWindow::setupEditor() {
    editor = new CodeEditor(this);

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    editor -> setFont(font);

//    highlighter = new Highlighter(editor -> document());
//    QFile file("mainwindow.h");
//    if (file.open(QFile::ReadOnly | QFile::Text))
//        editor->setPlainText(file.readAll());
}

void IDEWindow::setupFileMenu() {
    QMenu * fileMenu = new QMenu(tr("&File"), this);
    menuBar() -> addMenu(fileMenu);

    fileMenu -> addAction(tr("&New"), this, SLOT(newFile()), QKeySequence::New);
    fileMenu -> addAction(tr("&Open..."), this, SLOT(openFile()), QKeySequence::Open);
    fileMenu -> addAction(tr("E&xit"), qApp, SLOT(quit()), QKeySequence::Quit);
}

void IDEWindow::setupHelpMenu() {
    QMenu * helpMenu = new QMenu(tr("&Help"), this);
    menuBar() -> addMenu(helpMenu);

    helpMenu -> addAction(tr("&About"), this, SLOT(about()));
}
