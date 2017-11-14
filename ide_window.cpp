#include "ide_window.h"
#include "ui_ide_window.h"

#include "parts/editor_parts/projects.h"
#include "parts/editor_parts/project.h"
#include "parts/editor_parts/file.h"

#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qsplitter>
#include <qcompleter.h>

IDEWindow::IDEWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::IDEWindow), active_editor(0), editors_spliter(0) {
    ui -> setupUi(this);

    setAcceptDrops(true);
    connect(&Projects::obj(), SIGNAL(textAdded(QObject*,QUrl)), this, SLOT(textDocumentAdded(QObject*,QUrl)));


//    void projectAdded(QObject * project);
//    void projectRemoved(QObject * project);
//    void projectRenamed(QObject * project, const QString & prev_name);

//    void textAdded(QObject * project, const QUrl & file_uri);
//    void imageAdded(QObject * project, const QUrl & file_uri);
//    void binaryAdded(QObject * project, const QUrl & file_uri);

//    void fileAdded(QObject * project, const QUrl & file_uri);
//    void fileRemoved(QObject * project, const QUrl & file_uri);
//    void fileRenamed(QObject * project, const QUrl & from_uri, const QUrl & to_uri);



    setupFileMenu();
    setupHelpMenu();
    setupSplitter();
    setupEditor();

    active_editor -> hide();

    openFile(QUrl::fromLocalFile("F://rubyn test//ruby//test1.rb"));

    setWindowTitle(tr("Bla bla blashka"));
}

IDEWindow::~IDEWindow() { delete ui; }

void IDEWindow::textDocumentAdded(QObject * project, const QUrl & file_uri) {
    Project * _project = reinterpret_cast<Project *>(project);
    File * _file = _project -> file(file_uri);
//    IDocument * doc = _file -> document();

    switch(_file -> formatType()) {
        case ft_text: {
            active_editor -> openDocument(_file);

            QStringList wordList;
            wordList << "alpha" << "omega" << "omicron" << "zeta";
            QCompleter * completer = new QCompleter(wordList, this);
            active_editor -> setCompleter(completer);

            active_editor -> show();
        break;}
        case ft_image: //{ emit parent() -> imageAdded(url); break;}
        case ft_binary: //{ emit parent() -> binaryAdded(url); break;}
        default:;
    };
}

void IDEWindow::about() {
    QMessageBox::about(this, tr("About"), tr("<p>At this time this is a <b> simple editor with syntax highlighting</b>.</p>"));
}

void IDEWindow::newFile() {
    // need to show dialog for name and type inputing
}

void IDEWindow::openFile(const QUrl & url) {
    QUrl file_url = url;

    if (file_url.isEmpty())
        file_url = QUrl::fromLocalFile(
            QFileDialog::getOpenFileName(
                this,
                tr("Open File"), "", "All (*.*);;Ruby Files (*.rb);;SQL (*.sql)" // ;;C Sharp (*.cs);;C++ Files (*.cpp *.h)
            )
        );

    if (!file_url.isEmpty())
        Projects::obj().defaultProject() -> addFile(file_url);
}

void IDEWindow::setupEditor() {
    editors << (active_editor = new CodeEditor(this));

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(11);

    active_editor -> setFont(font);
    editors_spliter -> addWidget(active_editor);
}

void IDEWindow::setupFileMenu() {
    QMenu * file_menu = new QMenu(tr("&File"), this);
    menuBar() -> addMenu(file_menu);

    file_menu -> addAction(tr("&New"), this, SLOT(newFile()), QKeySequence::New);
    file_menu -> addAction(tr("&Open..."), this, SLOT(openFile()), QKeySequence::Open);
    file_menu -> addAction(tr("E&xit"), qApp, SLOT(quit()), QKeySequence::Quit);
}

void IDEWindow::setupHelpMenu() {
    QMenu * help_menu = new QMenu(tr("&Help"), this);
    menuBar() -> addMenu(help_menu);
    help_menu -> addAction(tr("&About"), this, SLOT(about()));
}

void IDEWindow::setupSplitter() {
    editors_spliter = new QSplitter(this);
    setCentralWidget(editors_spliter);
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
