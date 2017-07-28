#include "ide_window.h"
#include "ui_ide_window.h"

#include "parts/documents.h"

#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qsplitter>

IDEWindow::IDEWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::IDEWindow), activeEditor(0) {
    ui -> setupUi(this);

    setAcceptDrops(true);
    connect(&Documents::obj(), SIGNAL(textDocumentAdded(QUrl)), this, SLOT(textDocumentAdded(QUrl)));

    setupFileMenu();
    setupHelpMenu();
    setupSplitter();
    setupEditor();

    activeEditor -> hide();

    openFile(QUrl::fromLocalFile("F://rubyn test//ruby//base_parser.rb"));

    setWindowTitle(tr("Bla bla blashka"));
}

IDEWindow::~IDEWindow() { delete ui; }

void IDEWindow::textDocumentAdded(const QUrl & url) {
    activeEditor -> openDocument(Documents::obj().document(url));
    activeEditor -> show();
}

void IDEWindow::about() {
    QMessageBox::about(this, tr("About"), tr("<p>At this time this is a <b> simple editor with syntax highlighting</b>.</p>"));
}

void IDEWindow::newFile() {
    // need to show dialog for name and type inputing
}

void IDEWindow::openFile(const QUrl & url) {
    QUrl fileUrl = url;

    if (fileUrl.isEmpty())
        fileUrl = QUrl::fromLocalFile(
            QFileDialog::getOpenFileName(
                this,
                tr("Open File"), "", "All (*.*);;Ruby Files (*.rb);;SQL (*.sql)" // ;;C Sharp (*.cs);;C++ Files (*.cpp *.h)
            )
        );

    if (!fileUrl.isEmpty())
        Documents::obj().openDocument(fileUrl);
}

void IDEWindow::setupEditor() {
    editors << (activeEditor = new CodeEditor(this));

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(11);

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

void IDEWindow::dragEnterEvent(QDragEnterEvent * event) {
//    QList<QUrl> urls() const;
//    void setUrls(const QList<QUrl> &urls);
//    bool hasUrls() const;

//    QString text() const;
//    void setText(const QString &text);
//    bool hasText() const;

//    QString html() const;
//    void setHtml(const QString &html);
//    bool hasHtml() const;

//    QVariant imageData() const;
//    void setImageData(const QVariant &image);
//    bool hasImage() const;



    if (event -> mimeData() -> hasUrls())
        event -> accept();
    else event -> ignore();
}
void IDEWindow::dragMoveEvent(QDragMoveEvent * event) {
    if (event -> mimeData() -> hasUrls())
        event -> accept();
    else event -> ignore();
}

void IDEWindow::dropEvent(QDropEvent * event) {
    if (event -> mimeData() -> hasUrls()) {
        QList<QUrl> urls = event -> mimeData() -> urls();
        for(QList<QUrl>::Iterator url = urls.begin(); url != urls.end(); url++)
            openFile(*url);

        event -> accept();
    } else event -> ignore();
}
