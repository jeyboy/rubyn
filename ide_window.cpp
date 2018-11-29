#include "ide_window.h"
#include "ui_ide_window.h"

#include "editor/document_types/text_document.h"

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
#include "controls/color_picker.h"
#include "controls/color_button.h"

#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qsplitter.h>
#include <qlabel.h>
#include <qplaintextedit.h>
#include <qaction.h>

#include <qtoolbutton.h>
#include <qevent.h>
#include <qmimedata.h>

/////////////// TEST
#include "tools/html/html_page.h"
#include "tools/data_preparer/rubydoc_preparer.h"
#include "tools/data_preparer/rubydoc_parser.h"

IDEWindow::IDEWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::IDEWindow), active_editor(nullptr), widgets_list(nullptr),
    tree(nullptr), color_picker(nullptr), ui_dumper(new Dumper()), run_config(nullptr), pos_status(nullptr)
{
    ui -> setupUi(this);

    setAcceptDrops(true);

    setupToolWindows();
    setupPosOutput();
    setupFileMenu();
    setupHelpMenu();
    setupSplitter();
//    setupEditor();

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

IDEWindow::~IDEWindow() {
    delete ui;
    delete ui_dumper;
}

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

void IDEWindow::fileOpenRequired(const QString & name, void * folder, const bool & in_new, const bool & vertical, const int & scroll_pos_y) {
    File * _file = nullptr;
    bool is_external = false;

    if (folder) {
        IFolder * _folder = reinterpret_cast<IFolder *>(folder);

        if (_folder == nullptr) {
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

//    qDebug() << "OPEN";
//    qDebug() << _file -> path();

    if (!_file -> isOpened()) {
        if (!_file -> open()) {
            if (is_external) {
                delete _file;
            }

            Logger::obj().write(QStringLiteral("IDE"), QStringLiteral("Cant open file: '") % name % '\'', Logger::log_error);
            return;
        }
    }

    if (_file -> isText())
        _file -> asText() -> setVerticalScrollPos(scroll_pos_y);

    if (!active_editor || in_new)
        newEditorRequired(_file, vertical, is_external);
    else
        active_editor -> openFile(_file, is_external);
}

void IDEWindow::newEditorRequired(File * file, const bool & vertical, const bool & is_external) {
    QSplitter * parent_splitter = parentSplitter();

    if ((parent_splitter -> orientation() == Qt::Vertical) != vertical) {
        parent_splitter = splitActiveEditor(vertical);
    }

    setupEditor(parent_splitter);
    active_editor -> openFile(file, is_external);
}

void IDEWindow::setActiveEditor(TabsBlock * new_active) {
    if (active_editor)
        active_editor -> activate(false);

    active_editor = new_active;

    if (active_editor) {
        active_editor -> activate(true);
    }
}

void IDEWindow::editorIsEmpty(TabsBlock * target_editor) {
    QSplitter * parent_splitter = static_cast<QSplitter *>(target_editor -> parentWidget());
    bool active_is_deleting = active_editor == target_editor;

    while(parent_splitter) {
        bool is_main = parent_splitter == widgets_list;
        bool del_required = !is_main && parent_splitter -> count() == 1;

        if (active_is_deleting) {
            QWidget * widget = nullptr;

            if (del_required) {
                QSplitter * psplitter = static_cast<QSplitter *>(parent_splitter -> parentWidget());

                while(psplitter) {
                    if (psplitter -> count() == 1) {
                        if (psplitter != widgets_list) {
                            QSplitter * subpsplitter = static_cast<QSplitter *>(psplitter -> parentWidget());
                            psplitter -> deleteLater();
                            psplitter = subpsplitter;
                        }
                        else break;
                    } else {
                        widget = findEditor(psplitter);
                        break;
                    }
                }
            }
            else {
                int index = parent_splitter -> indexOf(active_editor);

                if (index - 1 >= 0)
                    widget = parent_splitter -> widget(index - 1);
                else if (index + 1 < parent_splitter -> count())
                    widget = parent_splitter -> widget(index + 1);

                if (qobject_cast<QSplitter *>(widget))
                     widget = findEditor(qobject_cast<QSplitter *>(widget));
            }

            setActiveEditor(qobject_cast<TabsBlock *>(widget));
            active_is_deleting = false;
        }

        target_editor -> deleteLater();

        if (!del_required)
            break;
        else {
            QSplitter * psplitter = static_cast<QSplitter *>(parent_splitter -> parentWidget());
            parent_splitter -> deleteLater();
            parent_splitter = psplitter;
        }
    }
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

void IDEWindow::selectCurrentFileInTree() {
    if (active_editor) {
        QString path = active_editor -> currentTabFilePath();

        if (!path.isNull())
            tree -> selectItem(path);
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
        fileOpenRequired(url.toLocalFile(), nullptr);
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

void IDEWindow::saveEditor(TabsBlock * editor) {
    if (!editor)
        editor = active_editor;

    editor -> saveFiles();
}
void IDEWindow::saveAll() {
    auto editors = widgets_list -> findChildren<TabsBlock *>();

    for(auto it = editors.begin(); it != editors.end(); it++)
        saveEditor(*it);
}

void IDEWindow::setupPosOutput() {
    pos_status = new QLabel();
    pos_status -> setStyleSheet("border: 1px solid gray; border-radius: 6px;");
    ui -> status_bar -> addPermanentWidget(pos_status);
}

void IDEWindow::setupEditor(QSplitter * list) {
    if (!list)
        list = widgets_list;

    TabsBlock * new_editor = new TabsBlock(this);
    setActiveEditor(new_editor);

    new_editor -> registerCursorPosOutput(pos_status);
    connect(new_editor, SIGNAL(newTabsBlockRequested(File*, const bool &)), this, SLOT(newEditorRequired(File*, const bool &)));
    connect(new_editor, SIGNAL(moveToBlankState(TabsBlock*)), this, SLOT(editorIsEmpty(TabsBlock*)));
    connect(new_editor, SIGNAL(activated(TabsBlock*)), this, SLOT(setActiveEditor(TabsBlock*)));
    connect(new_editor, SIGNAL(resourceDropped(TabsBlock*,QUrl)), this, SLOT(openResource(TabsBlock*,QUrl)));


    list -> addWidget(new_editor);
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
    widgets_list = setupChildSplitter(this);

    setCentralWidget(widgets_list);
}

QSplitter * IDEWindow::setupChildSplitter(QWidget * parent, const bool & vertical) {
    QSplitter * list = new QSplitter(parent);
    configSplitter(list, vertical);

    connect(list, &QSplitter::splitterMoved, this, &IDEWindow::splitterMoved);

    return list;
}

void IDEWindow::configSplitter(QSplitter * splitter, const bool & vertical) {
    splitter -> setOrientation(vertical ? Qt::Vertical : Qt::Horizontal);

    splitter -> setStyleSheet(
            QLatin1Literal(
                "QSplitter::handle {"
                "   border: 2px solid #ddd;"
                "   background-color: #555;"
                "   border-radius: 6px;"
                "   background-repeat: no-repeat;"
                "   background-position: center center;"
                "   padding: 2px;"
                "}"

                "QSplitter::handle:vertical {"
                "   background-image: url(:/grape);"
                "}"

                "QSplitter::handle:horizontal {"
                "   background-image: url(:/grape_horizontal);"
                "}"
            )
    );
}

QSplitter * IDEWindow::parentSplitter() {
    if (active_editor)
        return static_cast<QSplitter *>(active_editor -> parentWidget());
    else
        return widgets_list;
}

QSplitter * IDEWindow::splitActiveEditor(const bool & vertical) {
    QSplitter * parent_splitter = parentSplitter();
    QSplitter * new_child = setupChildSplitter(this, vertical);

    int index = parent_splitter -> indexOf(active_editor);
    parent_splitter -> replaceWidget(index, new_child);
    new_child -> addWidget(active_editor);
    return new_child;
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
    QToolButton * search_target_btn = widget -> insertHeaderButton(QIcon(QLatin1Literal(":/tools/show_target")), this, SLOT(selectCurrentFileInTree()), 0);
    search_target_btn -> setToolTip(QLatin1Literal("Scroll to current active document"));

    widget -> registerSearchCallbacks(tree, SIGNAL(searchRequired(const QString &)), SIGNAL(closeSearch()), SLOT(search(const QString &)), SLOT(clearSearch()));



    color_picker = new ColorPicker(this);
    DockWidget * color_picker_widget =
        DockWidgets::obj().createWidget(
            QLatin1Literal("Color"),
            color_picker,
            (Qt::DockWidgetAreas)(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea)
        );

    color_picker_widget -> setBehaviour((DockWidget::Features)(DockWidget::dwf_movable | DockWidget::dwf_closable));

    DockWidgets::obj().append(color_picker_widget);

    ColorButton * curr_color_btn = new ColorButton(this);
    color_picker_widget -> insertHeaderButton(curr_color_btn, nullptr, nullptr, 0);
    curr_color_btn -> setDisabled(true);
    color_picker -> setCurrentColorButton(curr_color_btn);
    color_picker_widget -> insertHeaderButton(QIcon(":/tools/color_picker"), color_picker, SLOT(colorPickingRequired()), 1);
    color_picker_widget -> hide();



    Logger::obj().initiate(QLatin1Literal("loh.txt"), true);

    DockWidget * log_widget =
        DockWidgets::obj().createWidget(
            QLatin1Literal("Loh"),
            Logger::obj().getEditor(),
            (Qt::DockWidgetAreas)(Qt::BottomDockWidgetArea)
        );

    DockWidgets::obj().append(log_widget, Qt::BottomDockWidgetArea);

    // TOOLBARS

    Toolbars::obj().registerContainer(this);

    run_config = new RunConfiguration(this);

    QToolBar * control_bar = Toolbars::obj().createWidget(QLatin1Literal("Controls"));

    run_config -> buildPanel(control_bar);

    control_bar -> addSeparator();

    QAction * _color_picker = control_bar -> addAction(QIcon(QLatin1Literal(":/tools/color_picker")), QLatin1Literal());
    _color_picker -> setCheckable(true);
    _color_picker -> setChecked(color_picker_widget -> isVisible());
    connect(_color_picker, &QAction::triggered, [=]() { color_picker_widget -> setVisible(!color_picker_widget -> isVisible()); _color_picker -> setChecked(color_picker_widget -> isVisible()); });

    control_bar -> addSeparator();

    QAction * _save_doc = control_bar -> addAction(QIcon(QLatin1Literal(":/tools/save")), QLatin1Literal());
    connect(_save_doc, SIGNAL(triggered()), this, SLOT(saveEditor()));

    Toolbars::obj().append(control_bar, Qt::TopToolBarArea);
}

QWidget * IDEWindow::findEditor(QSplitter * active_table) {
    QWidget * widget = nullptr;

    while(active_table) {
        widget = active_table -> widget(0);

        if (!widget) {
            Logger::obj().write(QLatin1Literal("editorIsEmpty"), QLatin1Literal("incorrect editors table state"), Logger::log_error);
            break;
        }

        if (qobject_cast<TabsBlock *>(widget))
            break;
        else
            active_table = qobject_cast<QSplitter *>(widget);
    }

    return widget;
}

void IDEWindow::loadSettings() {
    ui_dumper -> load(this);
}
void IDEWindow::saveSettings() {
    ui_dumper -> save(this);
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
void IDEWindow::keyPressEvent(QKeyEvent * event) {
    switch(event -> key()) {
        case Qt::Key_S: {
            switch(event -> modifiers()) {
                case Qt::ControlModifier: {
                    saveEditor();
                break;}

                case Qt::ControlModifier | Qt::ShiftModifier: {
                    saveAll();
                break;}
            }
        break;}
    }

    QMainWindow::keyPressEvent(event);
}

void IDEWindow::closeEvent(QCloseEvent * event) {
    saveSettings();

    QMainWindow::closeEvent(event);
}
