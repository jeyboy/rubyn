#include "ide_window.h"
#include "ui_ide_window.h"

#include "project/projects.h"
#include "project/project.h"
#include "project/file.h"
#include "project/ifolder.h"

#include "dock_widgets.h"
#include "dock_widget.h"
#include "project_tree.h"
#include "tabs_block.h"
#include "logger.h"

#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qsplitter>
#include <qlabel.h>
#include <qplaintextedit.h>

#include <qevent.h>
#include <qmimedata.h>

IDEWindow::IDEWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::IDEWindow), active_editor(0), widgets_list(0), tree(0), pos_status(0) {
    ui -> setupUi(this);

    setAcceptDrops(true);

    setupToolWindows();
    setupPosOutput();
    setupFileMenu();
    setupHelpMenu();
    setupSplitter();

    connect(tree, SIGNAL(fileActivated(QString, void*)), this, SLOT(fileOpenRequired(QString, void*)));
    connect(&Projects::obj(), SIGNAL(projectInitiated(QTreeWidgetItem*)), tree, SLOT(branchAdded(QTreeWidgetItem*)));

    openFolder(QUrl::fromLocalFile("F://rubyn test//RebelsMarketplace"));
//    openFile(QUrl::fromLocalFile("F://rubyn test//ruby//test1.rb"));

    setWindowTitle(tr("Bla bla blashka"));
}

IDEWindow::~IDEWindow() { delete ui; }

void IDEWindow::fileOpenRequired(const QString & name, void * folder) {
    File * _file = 0;

    if (folder) {
        IFolder * _folder = reinterpret_cast<IFolder *>(folder);

        if (_folder == 0) {
            Logger::obj().write(QStringLiteral("IDE"), QStringLiteral("Cant find folder for file: '") % name % '\'', Logger::log_error);
            return;
        }

        _file = _folder -> getFile(name);
    } else {
        // need to register somewhere temp files
        return;
    }

    if (_file == 0) {
        qDebug() << "FILE IS NULL";
        Logger::obj().write(QLatin1Literal("IDE"), QLatin1Literal("Cant find file: '") % name % '\'',  Logger::log_error);
        return;
    }

    qDebug() << "OPEN";
    qDebug() << _file -> path();

    if (!_file -> isOpened()) {
        if (!_file -> open()) {
            Logger::obj().write(QStringLiteral("IDE"), QStringLiteral("Cant open file: '") % name % '\'', Logger::log_error);
            return;
        }
    }

    if (!active_editor)
        newEditorRequired(_file);
    else
        active_editor -> openFile(_file);
}

void IDEWindow::newEditorRequired(File * file) {
    setupEditor();
    active_editor -> openFile(file);
}

void IDEWindow::editorActivated(TabsBlock * target_editor) {
    active_editor = target_editor;
}

void IDEWindow::editorIsEmpty(TabsBlock * target_editor) {
    if (active_editor == target_editor) {
        int index = widgets_list -> indexOf(active_editor);

        if (index - 1 >= 0)
            --index;
        else if (index + 1 < widgets_list -> count())
            ++index;
        else {
            active_editor = 0;
            return;
        }

        QWidget * widget = widgets_list -> widget(index);
        active_editor = dynamic_cast<TabsBlock *>(widget);

        if (active_editor) {
            active_editor -> setFocus();
        }
    }

    target_editor -> deleteLater();
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
        fileOpenRequired(url.toLocalFile(), 0);
//        Projects::obj().defaultProject() -> addFile(file_url);
}

void IDEWindow::openFolder(const QUrl & url) {
    QUrl folder_url = url;

    if (folder_url.isEmpty()) {
        folder_url =
            QFileDialog::getExistingDirectory(this, QLatin1Literal("Select Project Folder"), QDir::currentPath());
    }

    if (!folder_url.isEmpty())
        Projects::obj().open(folder_url);
}

void IDEWindow::setupPosOutput() {
    pos_status = new QLabel();
    pos_status -> setStyleSheet("border: 1px solid gray; border-radius: 6px;");
    ui -> status_bar -> addPermanentWidget(pos_status);
}

void IDEWindow::setupEditor() {
    TabsBlock * new_editor = new TabsBlock(this);
    active_editor = new_editor;

    new_editor -> registerCursorPosOutput(pos_status);
    connect(new_editor, SIGNAL(newTabsBlockRequested(File*)), this, SLOT(newEditorRequired(File*)));
    connect(new_editor, SIGNAL(moveToBlankState(TabsBlock*)), this, SLOT(editorIsEmpty(TabsBlock*)));
    connect(new_editor, SIGNAL(activated(TabsBlock*)), this, SLOT(editorActivated(TabsBlock*)));

    widgets_list -> addWidget(new_editor);

    active_editor -> hide();
}

void IDEWindow::setupFileMenu() {
    QMenu * file_menu = new QMenu(tr("&File"), this);
    menuBar() -> addMenu(file_menu);

    file_menu -> addAction(tr("&New"), this, SLOT(newFile()), QKeySequence::New);
    file_menu -> addAction(tr("&Open..."), this, SLOT(openFile()), QKeySequence::Open);
    file_menu -> addAction(tr("&Open project..."), this, SLOT(openFolder()), QKeySequence::Open);
    file_menu -> addAction(tr("E&xit"), qApp, SLOT(quit()), QKeySequence::Quit);
}

void IDEWindow::setupHelpMenu() {
    QMenu * help_menu = new QMenu(tr("&Help"), this);
    menuBar() -> addMenu(help_menu);
    help_menu -> addAction(tr("&About"), this, SLOT(about()));
}

void IDEWindow::setupSplitter() {
    widgets_list = new QSplitter(this);
    widgets_list -> setOrientation(Qt::Vertical);
    setCentralWidget(widgets_list);
}

void IDEWindow::setupToolWindows() {
    DockWidgets::obj().registerContainer(this);

    tree = new ProjectTree(this);
    DockWidget * widget =
        DockWidgets::obj().createWidget(
            QLatin1Literal("Files"),
            tree,
            (Qt::DockWidgetAreas)(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea)
        );

    widget -> setBehaviour(DockWidget::dwf_movable);

    DockWidgets::obj().append(widget);


    Logger::obj().initiate(QLatin1Literal("loh.txt"), true);

    DockWidget * log_widget =
        DockWidgets::obj().createWidget(
            QLatin1Literal("Loh"),
            Logger::obj().getEditor(),
            (Qt::DockWidgetAreas)(Qt::BottomDockWidgetArea)
        );

    DockWidgets::obj().append(log_widget, Qt::BottomDockWidgetArea);
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
        for(QList<QUrl>::Iterator url = urls.begin(); url != urls.end(); url++) {
            QFileInfo info((*url).toLocalFile());

//            (*url).adjusted(QUrl::NormalizePathSegments)

            if (info.isFile())
                openFile(*url);
            else
                openFolder(*url);
        }

        event -> accept();
    } else event -> ignore();
}
