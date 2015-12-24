#include "ide_window.h"
#include "ui_ide_window.h"

#include "parts/documents.h"

#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qsplitter>

IDEWindow::IDEWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::IDEWindow), activeEditor(0) {
    ui -> setupUi(this);

    connect(&Documents::obj(), SIGNAL(textDocumentAdded(QString)), this, SLOT(textDocumentAdded(QString)));

    setupFileMenu();
    setupHelpMenu();
    setupSplitter();
    setupEditor();

    setWindowTitle(tr("Bla bla blashka"));
}

IDEWindow::~IDEWindow() { delete ui; }

void IDEWindow::textDocumentAdded(QString path) {
    activeEditor -> openDocument((TextDocument *)Documents::obj().document(path));
}

void IDEWindow::about() {
    QMessageBox::about(this, tr("About"), tr("<p>At this time this is a <b> simple editor with syntax highlighting</b>.</p>"));
}

void IDEWindow::newFile() {
    // need to show dialog for name and type inputing
}

void IDEWindow::openFile(const QString & path) {
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "Ruby Files (*.rb);;C++ Files (*.cpp *.h);;SQL (*.sql);;C Sharp (*.cs)");

    if (!fileName.isEmpty())
        Documents::obj().openDocument(fileName);
}

void IDEWindow::setupEditor() {
    editors << (activeEditor = new CodeEditor(this));

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    activeEditor -> setFont(font);
    editorsSpliter -> addWidget(activeEditor);
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

void IDEWindow::setupSplitter() {
    editorsSpliter = new QSplitter(this);
    setCentralWidget(editorsSpliter);
}
