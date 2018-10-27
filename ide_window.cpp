#include "ide_window.h"
#include "ui_ide_window.h"

#include "project/projects.h"
#include "project/project.h"
#include "project/file.h"
#include "project/ifolder.h"

#include "controls/toolbars.h"
#include "controls/dock_widgets.h"
#include "controls/dock_widget.h"
#include "controls/project_tree.h"
#include "controls/tabs_block.h"
#include "controls/logger.h"
#include "controls/dumper.h"
#include "controls/run_configuration.h"
#include "controls/eblet.h"

#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qsplitter.h>
#include <qlabel.h>
#include <qplaintextedit.h>

#include <qevent.h>
#include <qmimedata.h>

/////////////// TEST
#include "tools/html/html_page.h"
#include "tools/data_preparer/rubydoc_preparer.h"
#include "tools/data_preparer/rubydoc_parser.h"

IDEWindow::IDEWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::IDEWindow), active_editor(nullptr), widgets_list(nullptr), tree(nullptr), run_config(nullptr), pos_status(nullptr) {
    ui -> setupUi(this);

    setAcceptDrops(true);

    setupToolWindows();
    setupPosOutput();
    setupFileMenu();
    setupHelpMenu();
    setupSplitter();
    setupEditor();

    connect(tree, SIGNAL(fileActivated(QString, void*)), this, SLOT(fileOpenRequired(QString, void*)));
    connect(&Projects::obj(), SIGNAL(projectInitiated(QTreeWidgetItem*)), tree, SLOT(branchAdded(QTreeWidgetItem*)));

//    openFolder(QUrl::fromLocalFile("F:/rubyn test/projects/rails 4 - RebelsMarketplace"));
//    openFile(QUrl::fromLocalFile("F:/rubyn test/ruby/test1.rb"));

    setWindowTitle(tr("Bla bla blashka"));
    loadSettings();

    // TESTS // REMOVE LATER

//    DocsList res;
//    RubyDocPreparer().takeListOfAvailableDocs(res);

//    VersionUrls urls;

//    urls.core_url = "F://rubyn test//ruby_2_5_1_core_rdocs.tgz";
//    urls.stdlib_url = "F://rubyn test//ruby_2_5_1_stdlib_rdocs.tgz";

//    RubyDocPreparer().parseRubyPack(urls);



//    QFile f("F://rubyn test//LDAP.html");

//    if (f.open(QFile::Text | QFile::ReadOnly)) {
//        Logger::obj().startMark();
//        Html::Page page(&f); //, Html::Decoding::charset_utf8, Html::Page::pf_skip_comment);
//        page.findFirst(">a");
//        Logger::obj().endMark(QLatin1Literal("HTML"), QLatin1Literal("parsing"));
//        page.output();

//        f.close();
//    }

//    RubydocParser().parseFile(QLatin1Literal("F://rubyn test//SpecificationProvider.html"), QLatin1Literal("F://rubyn test//specification_provider.rb"));
//    RubydocParser().parseFile(QLatin1Literal("F://rubyn test//Array.html"), QLatin1Literal("F://rubyn test//array.rb"));
//    RubydocParser().initParseFile(QLatin1Literal("F://rubyn test//"), QLatin1Literal("Encoding.html"), QLatin1Literal("F://rubyn test//encoding.rb"));

//    Logger::obj().startMark();
//    RubydocParser parser;

////    parser.parse(QLatin1Literal("F://rubyn test//111"));

//    parser.parse(QLatin1Literal("F://rubyn test//ruby_2_5_1_core"));
//    parser.parse(QLatin1Literal("F://rubyn test//ruby_2_5_1_stdlib"));

//    parser.saveParsedDatum(QLatin1Literal("F://rubyn test//ruby_2_5_1_parsed"));

//    Logger::obj().endMark(QLatin1Literal("Rubydoc"), QLatin1Literal("parsing"));
}

IDEWindow::~IDEWindow() { delete ui; }

void IDEWindow::splitterMoved(int /*pos*/, int index) {
    QSplitter * obj = static_cast<QSplitter *>(sender());

    if (obj) {
        QList<int> sizes = obj -> sizes();

        if (sizes.at(index) == 0) {
            if (active_editor == obj -> widget(index)) {
                setActiveEditor(dynamic_cast<TabsBlock *>(obj -> widget(index - 1)));
            }
        } else if (sizes.at(index - 1) == 0) {
            if (active_editor == obj -> widget(index - 1)) {
                setActiveEditor(dynamic_cast<TabsBlock *>(obj -> widget(index)));
            }
        }
    }
}

void IDEWindow::fileOpenRequired(const QString & name, void * folder, const bool & in_new) {
    File * _file = nullptr;
    bool is_external = false;

    if (folder) {
        IFolder * _folder = reinterpret_cast<IFolder *>(folder);

        if (_folder == 0) {
            Logger::obj().write(QStringLiteral("IDE"), QStringLiteral("Cant find folder for file: '") % name % '\'', Logger::log_error);
            return;
        }

        _file = _folder -> getFile(name);
    } else {
        _file = Projects::obj().findFile(QUrl::fromLocalFile(name));

        if (!_file) {
            QFileInfo finfo(name);
            _file = new File(0, finfo.baseName(), name);

            is_external = true;
        }
    }

    if (_file == nullptr) {
        qDebug() << "FILE IS NULL";
        Logger::obj().write(QLatin1Literal("IDE"), QLatin1Literal("Cant find file: '") % name % '\'',  Logger::log_error);
        return;
    }

    qDebug() << "OPEN";
    qDebug() << _file -> path();

    if (!_file -> isOpened()) {
        if (!_file -> open()) {
            if (is_external) {
                delete _file;
            }

            Logger::obj().write(QStringLiteral("IDE"), QStringLiteral("Cant open file: '") % name % '\'', Logger::log_error);
            return;
        }
    }

    if (!active_editor || in_new)
        newEditorRequired(_file, is_external);
    else
        active_editor -> openFile(_file, is_external);
}

void IDEWindow::newEditorRequired(File * file, const bool & is_external) {
    setupEditor();
    active_editor -> openFile(file, is_external);
}

void IDEWindow::setActiveEditor(TabsBlock * new_active) {
    if (active_editor)
        active_editor -> activate(false);

    active_editor = new_active;

    if (active_editor)
        active_editor -> activate(true);
}

void IDEWindow::editorIsEmpty(TabsBlock * target_editor) {
    if (active_editor == target_editor) {
        int index = widgets_list -> indexOf(active_editor);

        if (index - 1 >= 0)
            --index;
        else if (index + 1 < widgets_list -> count())
            ++index;
        else {
            setActiveEditor(nullptr);
            return;
        }

        QWidget * widget = widgets_list -> widget(index);
        setActiveEditor(dynamic_cast<TabsBlock *>(widget));

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

void IDEWindow::newFolder() {
    // need to show dialog for name and type inputing
}

void IDEWindow::openResource(TabsBlock * target_editor, const QUrl & url) {
    if (url.isLocalFile()) {
        setActiveEditor(target_editor);

        QFileInfo f(url.toLocalFile());

        if (f.isDir()) {
//            openFolder(url);
            Logger::obj().write(QLatin1Literal("IDE"), QLatin1Literal("Unsupported resource: DIR: '") % url.toString() % '\'',  Logger::log_error);
        } else {
            openFile(url);
        }
    } else {
        Logger::obj().write(QLatin1Literal("IDE"), QLatin1Literal("Unsupported resource: '") % url.toString() % '\'',  Logger::log_error);
    }
}

void IDEWindow::openFile(const QUrl & url) {
    QUrl file_url = url;

    if (file_url.isEmpty()) {
        file_url =
            QUrl::fromLocalFile(
                QFileDialog::getOpenFileName(
                    this,
                    tr("Open File"), "", "All (*.*);;Ruby Files (*.rb);;SQL (*.sql)" // ;;C Sharp (*.cs);;C++ Files (*.cpp *.h)
                )
            );
    }

    if (!file_url.isEmpty())
        fileOpenRequired(url.toLocalFile(), 0);
//        Projects::obj().defaultProject() -> addFile(file_url);
}

void IDEWindow::openFolder(const QUrl & url) {
    QUrl folder_url = url;

    if (folder_url.isEmpty()) {
        folder_url =
            QUrl::fromLocalFile(
                QFileDialog::getExistingDirectory(this, QLatin1Literal("Select Project Folder"), QDir::currentPath())
            );
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
    setActiveEditor(new_editor);

    new_editor -> registerCursorPosOutput(pos_status);
    connect(new_editor, SIGNAL(newTabsBlockRequested(File*)), this, SLOT(newEditorRequired(File*)));
    connect(new_editor, SIGNAL(moveToBlankState(TabsBlock*)), this, SLOT(editorIsEmpty(TabsBlock*)));
    connect(new_editor, SIGNAL(activated(TabsBlock*)), this, SLOT(setActiveEditor(TabsBlock*)));
    connect(new_editor, SIGNAL(resourceDropped(TabsBlock*,QUrl)), this, SLOT(openResource(TabsBlock*,QUrl)));

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

//    "QSplitter::handle:horizontal {"
//    "   border: 2px solid #ddd;"
//    "   background-color: #708090;"
//    "   border-radius: 6px;"
//    "   background-image: url(:/grape);"
//    "   height: 20px;"
//    "}"

    widgets_list -> setStyleSheet(
        QLatin1Literal(
            "QSplitter::handle:vertical {"
            "   border: 2px solid #ddd;"
            "   background-color: #555;"
            "   border-radius: 6px;"
            "   background-image: url(:/grape);"
            "   background-repeat: no-repeat;"
            "   background-position: center center;"
            "   height: 4px;"
            "}"
        )
    );

    setCentralWidget(widgets_list);

    connect(widgets_list, &QSplitter::splitterMoved, this, &IDEWindow::splitterMoved);
}

void IDEWindow::setupToolWindows() {
    DockWidgets::obj().registerContainer(this);


    ///////////////// PROJECT TREE ///////////////////////
    tree = new ProjectTree(this);
    DockWidget * widget =
        DockWidgets::obj().createWidget(
            QLatin1Literal("Files"),
            tree,
            (Qt::DockWidgetAreas)(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea)
        );

    widget -> setBehaviour(DockWidget::dwf_movable);

    DockWidgets::obj().append(widget);
    /////////////////////////////////////////////////////



    ///////////////// EBLET ///////////////////////
    Eblet * _eblet_btn = new Eblet(this);
    _eblet_btn -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _eblet_btn -> setMinimumSize(60, 60);

    DockWidget * eblo_widget =
        DockWidgets::obj().createWidget(
            QLatin1Literal("Eblet"),
            _eblet_btn,
            (Qt::DockWidgetAreas)(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea)
        );

    eblo_widget -> setBehaviour(DockWidget::dwf_movable);

    DockWidgets::obj().append(eblo_widget);
    /////////////////////////////////////////////////////



    ///////////////////// LOGGER //////////////////////////
    Logger::obj().initiate(QLatin1Literal("loh.txt"), true);

    DockWidget * log_widget =
        DockWidgets::obj().createWidget(
            QLatin1Literal("Loh"),
            Logger::obj().getEditor(),
            (Qt::DockWidgetAreas)(Qt::BottomDockWidgetArea)
        );

    DockWidgets::obj().append(log_widget, Qt::BottomDockWidgetArea);
    /////////////////////////////////////////////////////

    // TOOLBARS

    Toolbars::obj().registerContainer(this);

    run_config = new RunConfiguration(this);

    QToolBar * control_bar = Toolbars::obj().createWidget(QLatin1Literal("Controls"));

    run_config -> buildPanel(control_bar);

    Toolbars::obj().append(control_bar, Qt::TopToolBarArea);
}

void IDEWindow::loadSettings() {
    Dumper::load(this);
}
void IDEWindow::saveSettings() {
    Dumper::save(this);
}

void IDEWindow::dragEnterEvent(QDragEnterEvent * event) {
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
            openResource(active_editor, *url);
        }

        event -> accept();
    } else event -> ignore();
}

void IDEWindow::closeEvent(QCloseEvent * event) {
    saveSettings();

    QMainWindow::closeEvent(event);
}
