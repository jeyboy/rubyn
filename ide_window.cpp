#include "ide_window.h"
#include "ui_ide_window.h"

//#include "editor/document_types/text_document.h"
//#include "editor/custom/custom_document.h"

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
#include "controls/run_menu.h"
#include "controls/color_picker.h"
#include "controls/color_button.h"
#include "controls/breakpoints_panel.h"
#include "controls/project_search_panel.h"
#include "controls/project_widget.h"
#include "controls/dock_widget_search_connector.h"
#include "controls/console_widget.h"

//#include "editor/breakpoints_controller.h"
//#include "controls/debug_panel.h"

#include "misc/run_config.h"
#include "styles/dockwidget_icon_style.h"

//#include "editor/custom/custom_chars.h"

#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qsplitter.h>
#include <qlabel.h>
#include <qplaintextedit.h>
#include <qaction.h>

#include <qtoolbutton.h>
#include <qevent.h>
#include <qmimedata.h>
#include <qlayout.h>

/////////////// TEST
#include <QRandomGenerator>

#include "tools/html/html_page.h"
#include "tools/data_preparer/rubydoc_preparer.h"
#include "tools/data_preparer/rubydoc_parser.h"

//#include "tools/archive.h"
//#include "tools/files_proc_manager.h"

IDEWindow::IDEWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::IDEWindow), color_picker_widget(nullptr), active_editor(nullptr), widgets_list(nullptr),
    tree(nullptr), color_picker(nullptr), ui_dumper(new Dumper()), run_config(nullptr), pos_status(nullptr)
{
    ui -> setupUi(this);

    QApplication::setKeyboardInputInterval(1);

    setAcceptDrops(true);
    setWindowTitle(tr("Bla bla blashka"));
//    setCorner();

//    QTabWidget::North	0	The tabs are drawn above the pages.
//    QTabWidget::South	1	The tabs are drawn below the pages.
//    QTabWidget::West	2	The tabs are drawn to the left of the pages.
//    QTabWidget::East	3	The tabs are drawn to the right of the pages.

    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::East);
    setTabPosition(Qt::RightDockWidgetArea, QTabWidget::West);
    setTabPosition(Qt::BottomDockWidgetArea, QTabWidget::North);
    setTabPosition(Qt::TopDockWidgetArea, QTabWidget::South);

    setStyleSheet(
//        "IDEWindow {"
//        "   background-image: url(:/background);"
//        "   background-position: center;"
//        "   background-repeat: no-repeat;"
//        "}"

        "IDEWindow::separator {"
        "   border: 2px solid #666;"
        "   background-color: #ddd;"
        "   border-radius: 4px;"
        "   background-repeat: no-repeat;"
        "   background-position: center center;"
        "}"

        "IDEWindow::separator:horizontal {"
        "   background-image: url(:/grape_alt);"
        "   height: 6px;"
        "}"
        "IDEWindow::separator:vertical {"
        "   background-image: url(:/grape_horizontal_alt);"
        "   width: 6px;"
        "}"
    );

    setupToolWindows();
    setupPosOutput();
    setupFileMenu();
    setupHelpMenu();
    setupSplitter();

    connect(tree, SIGNAL(fileActivated(QString, void*)), this, SLOT(fileOpenRequired(QString, void*)));
    connect(&Projects::obj(), SIGNAL(projectInitiated(const uint &, QTreeWidgetItem *)), tree, SLOT(branchAdded(const uint &, QTreeWidgetItem *)));

//    openFolder(QUrl::fromLocalFile("F:/rubyn test/projects/rails 4 - RebelsMarketplace"));
//    openFile(QUrl::fromLocalFile("F:/rubyn test/ruby/test1.rb"));


    loadSettings();


//    RubyDocPreparer().syncList();


//    QFile f("F://rubyn test//large.txt");

//    QString str = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//    if (f.open(QFile::Text | QFile::WriteOnly)) {
//        QRandomGenerator r;

//        int y = 0;
//        for(int i = 0; i < 52428800; i++, y++) {
//            f.putChar(str[r.bounded(str.length())].toLatin1());
//            if (y == 200) {
//                f.putChar(char(10));
//                y = 0;
//            }
//        }


//        f.close();
//    }


    // TESTS // REMOVE LATER

//    VersionUrls urls;

//    urls.core_url = "F://rubyn test//ruby_2_5_1_core_rdocs.tgz";
//    urls.stdlib_url = "F://rubyn test//ruby_2_5_1_stdlib_rdocs.tgz";

//    RubyDocPreparer().parseRubyPack(urls);



//    QFile f("F://rubyn test//LDAP.html");

//    if (f.open(QFile::Text | QFile::ReadOnly)) {
//        Logger::obj().startMark();
//        Html::Page page(&f); //, Html::Decoding::charset_utf8, Html::Page::pf_skip_comment);
//        page.findFirst(">a");
//        Logger::obj().endMark(QLatin1String("HTML"), QLatin1String("parsing"));
//        page.output();

//        f.close();
//    }

//    RubyDocParser parser;

//    parser.parse(QLatin1String("F://rubyn test//ruby_t"));
//    parser.saveParsedDatum(QLatin1String("F://rubyn test//ruby_t_parsed"));


//    RubydocParser().parseFile(QLatin1String("F://rubyn test//Array.html"), QLatin1String("F://rubyn test//array.rb"));
//    RubydocParser().initParseFile(QLatin1String("F://rubyn test//"), QLatin1String("Encoding.html"), QLatin1String("F://rubyn test//encoding.rb"));

//    Logger::obj().startMark();

////    parser.parse(QLatin1String("F://rubyn test//111"));

//    parser.parse(QLatin1String("F://rubyn test//ruby_2_5_1_core"));
//    parser.parse(QLatin1String("F://rubyn test//ruby_2_5_1_stdlib"));

//    parser.saveParsedDatum(QLatin1String("F://rubyn test//ruby_2_5_1_parsed"));

//    Logger::obj().endMark(QLatin1String("Rubydoc"), QLatin1String("parsing"));
}

IDEWindow::~IDEWindow() {
    // do not send signals about closing of files
    Projects::obj().disconnect();

    delete ui;
    delete ui_dumper;
}


ConsoleWidget * IDEWindow::createConsole(const QString & path, const bool & read_only) {
    return new ConsoleWidget(read_only, path, QLatin1String("#"), QString(), this);
}

void IDEWindow::setupConsole(ConsoleWidget * console, const QString & header) {
    DockWidget * console_widget =
        DockWidgets::obj().createWidget(
            header,
            console,
            Qt::AllDockWidgetAreas
        );

    console_widget -> setWindowIco(
        ":/tools/console2",
        ":/tools/console"
    );

    console_widget -> setBehaviour(DockWidget::Features(DockWidget::dwf_movable | DockWidget::dwf_closable));

    DockWidgets::obj().append(console_widget, Qt::BottomDockWidgetArea);
}

void IDEWindow::setupConsole(const QString & path, const QString & header) {
    ConsoleWidget * console = createConsole(path);

    setupConsole(console, header);
}


ProjectWidget * IDEWindow::setupProjectPanel(RunConfig * conf) {
    QString token = conf -> token();

    if (!project_widgets.contains(token)) {
        ProjectWidget * pw = new ProjectWidget(conf, this);

        DockWidget * widget = DockWidgets::obj().createWidget(conf -> name, pw, Qt::BottomDockWidgetArea);

        pw -> initButtons(widget);

        widget -> setWindowIco(
            /*conf -> cmd_type & RunConfig::rc_debug ? ":/tabs/debug" : ":/tools/run"*/ "",
            conf -> cmd_type & RunConfig::rc_debug ? ":/tools/debug" : ":/tools/run2"
        );
        widget -> setBehaviour(DockWidget::Features(DockWidget::dwf_movable | DockWidget::dwf_closable));
        widget -> setObjectName("project_" % token);

        connect(widget, &DockWidget::closing, [=]() {
            DockWidget * w = project_widgets.take(token);

            if (w) {
                w -> deleteLater();
            }
        });

        DockWidgets::obj().append(widget, Qt::BottomDockWidgetArea);
        project_widgets.insert(token, widget);
    } else {
        delete conf;
    }

    project_widgets[token] -> raise();

    return qobject_cast<ProjectWidget *>(project_widgets[token] -> widget());
}

void IDEWindow::splitterMoved(int /*pos*/, int index) {
    QSplitter * obj = static_cast<QSplitter *>(sender());

    if (obj) {
        QList<int> sizes = obj -> sizes();
        QWidget * target = nullptr;

        if (sizes.at(index) == 0) {
            if (editorInWidget(active_editor, obj -> widget(index))) {
                target = obj -> widget(index - 1);
            }
        } else if (sizes.at(index - 1) == 0) {
            if (editorInWidget(active_editor, obj -> widget(index - 1))) {
                target = obj -> widget(index);
            }
        }

        if (target) {
            if (!qobject_cast<TabsBlock *>(target))
                target = findEditor(qobject_cast<QSplitter *>(target));

            setActiveEditor(qobject_cast<TabsBlock *>(target));
        }
    }
}

void IDEWindow::fileOpenRequired(const QString & name, void * folder, const bool & in_new, const bool & vertical, const QPoint & scroll_pos, QRegularExpression * reg_exp) {
    File * _file = nullptr;

    if (!Projects::identificate(name, folder, _file)) {
        Logger::error(QStringLiteral("IDE"), QStringLiteral("Cant find folder for file: '") % name % '\'');
        delete reg_exp;
        return;
    }


//    if (folder) {
//        IFolder * _folder = reinterpret_cast<IFolder *>(folder);

//        if (_folder == nullptr) {
//            Logger::error(QStringLiteral("IDE"), QStringLiteral("Cant find folder for file: '") % name % '\'');
//            return;
//        }

//        _file = _folder -> getFile(name);
//    } else {
//        _file = Projects::obj().findFile(QUrl::fromLocalFile(name));

//        if (!_file) {
//            QFileInfo finfo(name);
//            _file = new File(0, finfo.baseName(), name);

//            is_external = true;
//        }
//    }

    if (_file == nullptr) {
        qDebug() << "FILE IS NULL";
        Logger::error(QLatin1String("IDE"), QLatin1String("Cant find file: '") % name % '\'');
        delete reg_exp;
        return;
    }

//    qDebug() << "OPEN";
//    qDebug() << _file -> path();

    if (!_file -> isOpened()) {
        if (!_file -> open()) {
            if (_file -> isExternal()) {
                delete _file;
            }

            Logger::error(QStringLiteral("IDE"), QStringLiteral("Cant open file: '") % name % '\'');
            return;
        }
    }

    IDocument * doc = _file -> document();

    if (doc) {
         if (scroll_pos.y() != NO_INFO) {
            doc -> setHorizontalScrollPos(scroll_pos.x());
            doc -> setVerticalScrollPos(scroll_pos.y());
         } else {
             doc -> setMoveToCharPos(scroll_pos.x());
         }
    }

//    if (_file -> isText()) {
//        _file -> asText() -> setVerticalScrollPos(scroll_pos_y);
//    } else if (_file -> isCustomText()) {
//        _file -> asCustomText() -> setVerticalScrollPos(scroll_pos_y);
//    }


    if (!active_editor || in_new)
        newEditorRequired(_file, vertical);
    else
        active_editor -> openFile(_file);

    if (doc) {
        doc -> highlight(reg_exp);
    }

    delete reg_exp;
}

void IDEWindow::newEditorRequired(File * file, const bool & vertical) {
    QSplitter * parent_splitter = parentSplitter();

    if ((parent_splitter -> orientation() == Qt::Vertical) != vertical) {
        parent_splitter = splitActiveEditor(vertical);
    }

    setupEditor(parent_splitter);
    active_editor -> openFile(file);
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

    target_editor -> setParent(nullptr);
    target_editor -> deleteLater();

    while(parent_splitter) {
        bool is_main = parent_splitter == widgets_list;
        bool del_required = !is_main && parent_splitter -> count() == 0;

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

        if (!del_required)
            break;
        else {
            QSplitter * psplitter = static_cast<QSplitter *>(parent_splitter -> parentWidget());
            parent_splitter -> setParent(nullptr);
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

        if (File::isFolder(url)) {
//            openFolder(url);
            Logger::error(QLatin1String("IDE"), QLatin1String("Unsupported resource: DIR: '") % url.toString() % '\'');
        } else {
            openFile(url);
        }
    } else {
        Logger::error(QLatin1String("IDE"), QLatin1String("Unsupported resource: '") % url.toString() % '\'');
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
                QFileDialog::getExistingDirectory(this, QLatin1String("Select Project Folder"), QDir::currentPath())
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

    new_editor -> registerCursorPosOutput(pos_status);
    connect(new_editor, SIGNAL(newTabsBlockRequested(File*, const bool &)), this, SLOT(newEditorRequired(File*, const bool &)));
    connect(new_editor, SIGNAL(moveToBlankState(TabsBlock*)), this, SLOT(editorIsEmpty(TabsBlock*)));
    connect(new_editor, SIGNAL(activated(TabsBlock*)), this, SLOT(setActiveEditor(TabsBlock*)));
    connect(new_editor, SIGNAL(resourceDropped(TabsBlock*,QUrl)), this, SLOT(openResource(TabsBlock*,QUrl)));
    connect(&Projects::obj(), SIGNAL(fileRemoved(const QString &)), new_editor, SLOT(fileClosed(const QString &)));

    if (active_editor && active_editor -> parentWidget() == list) {
        int index = list -> indexOf(active_editor);

        list -> insertWidget(index + 1, new_editor);
    }
    else list -> addWidget(new_editor);


    setActiveEditor(new_editor);
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
            QLatin1String(
                "QSplitter::handle {"
                "   border: 2px solid #ddd;"
                "   background-color: #555;"
                "   border-radius: 4px;"
                "   background-repeat: no-repeat;"
                "   background-position: center center;"
                "   padding: 1px;"
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

    int size;

    if (vertical) {
        size = parent_splitter -> height() / 2;
    } else {
        size = parent_splitter -> width() / 2;
    }

    QList<int> sizes({size, size});
    new_child -> setSizes(sizes);

    return new_child;
}

bool IDEWindow::editorInWidget(TabsBlock * editor, QWidget * target) {
    if (!qobject_cast<QSplitter *>(target))
        return editor == target;

    QWidget * w = editor -> parentWidget();

    while(w) {
        if (!qobject_cast<QSplitter *>(w))
            return false;

        if (w == target)
            return true;

        w = w -> parentWidget();
    }

    return false;
}

void IDEWindow::setupToolWindows() {
    DockWidgets::obj().registerContainer(this);
    Toolbars::obj().registerContainer(this);


    tree = new ProjectTree(this);

    connect(tree, SIGNAL(closeProjectRequired(const QString &)), &Projects::obj(), SLOT(closeProject(const QString &)));

    DockWidget * widget =
        DockWidgets::obj().createWidget(
            QLatin1String("Files"),
            tree,
            Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea
        );

//    widget -> setStyle(new DockwidgetIconStyle(QIcon(":/tools/indent"), widget -> style()));
    widget -> setBehaviour(DockWidget::dwf_movable);

    DockWidgets::obj().append(widget);
    QToolButton * search_target_btn = widget -> insertHeaderButton(QIcon(QLatin1String(":/tools/show_target")), this, SLOT(selectCurrentFileInTree()), 0);
    search_target_btn -> setToolTip(QLatin1String("Scroll to current active document"));

    connect(tree, SIGNAL(consoleRequired(const QString &)), this, SLOT(setupConsole(const QString &)));

    DockWidgetSearchConnector connector(tree);

    connector.search_show_signal = SIGNAL(searchRequired(const QString &));
    connector.search_hide_signal = SIGNAL(closeSearch());
    connector.search_amount_signal = SIGNAL(searchResultsCount(const int &));

    connector.search_request_slot = SLOT(search(const QRegularExpression &));
    connector.search_close_slot = SLOT(clearSearch());
    connector.search_prev_result_slot = nullptr;
    connector.search_next_result_slot = nullptr;

    widget -> registerSearchCallbacks(connector);

    setupColorBoxWindow();

    setupLogWindow();

    setupSearchWindow();

    // TOOLBARS

    run_config = new RunMenu(this);

    QToolBar * control_bar = Toolbars::obj().createWidget(QLatin1String("Controls"));

    run_config -> buildPanel(control_bar);

    connect(&Projects::obj(), &Projects::projectInitiated, [=](const uint & project_id, QTreeWidgetItem * tree_item) {
        run_config -> projectAdded(project_id, tree_item -> data(0, TREE_PATH_UID).toString(), tree_item -> data(0, Qt::DisplayRole).toString());
    });

    connect(&Projects::obj(), &Projects::projectRemoved, run_config, &RunMenu::projectRemoved);

//    void runRequires(const QString & path, const QString & name, const QString & run_type);

    connect(run_config, &RunMenu::runRequires, this, &IDEWindow::setupProjectPanel);

    control_bar -> addSeparator();

    QAction * _color_picker = control_bar -> addAction(QIcon(QLatin1String(":/tools/color_picker")), QLatin1String());
    _color_picker -> setCheckable(true);
    _color_picker -> setChecked(color_picker_widget -> isVisible());
    connect(_color_picker, &QAction::triggered, [=]() { color_picker_widget -> setVisible(!color_picker_widget -> isVisible()); _color_picker -> setChecked(color_picker_widget -> isVisible()); });

    control_bar -> addSeparator();

    QAction * _save_doc = control_bar -> addAction(QIcon(QLatin1String(":/tools/save")), QLatin1String());
    connect(_save_doc, SIGNAL(triggered()), this, SLOT(saveEditor()));

    control_bar -> layout();

    Toolbars::obj().append(control_bar, Qt::TopToolBarArea);
}

void IDEWindow::setupLogWindow() {
    Logger::obj().initiate(QLatin1String("loh.txt"), true);

    DockWidget * log_widget =
        DockWidgets::obj().createWidget(
            QLatin1String("Loh"),
            Logger::obj().getEditor(),
            Qt::BottomDockWidgetArea
        );

    log_widget -> setBehaviour(DockWidget::dwf_movable);
    log_widget -> setWindowIco(":/tabs/logger", ":/tools/logger");
    DockWidgets::obj().append(log_widget, Qt::BottomDockWidgetArea);
}

void IDEWindow::setupSearchWindow() {
    project_search_panel = new ProjectSearchPanel(this);
    project_search_panel -> setProjectTree(tree);

    DockWidget * project_search_widget =
        DockWidgets::obj().createWidget(
            QLatin1String("Search"),
            project_search_panel,
            Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea
        );

    project_search_widget -> setBehaviour(DockWidget::dwf_movable);
    project_search_widget -> setWindowIco(":/tabs/search", ":/tools/search");

    connect(tree, &ProjectTree::pathSearchRequired, [=](const QString & paths) {
        qDebug() << "!!!" << paths;
        project_search_widget -> raise();
        project_search_panel -> activate(paths);
    });

    connect(project_search_panel, &ProjectSearchPanel::resultClicked, [=](const QString & path, const EDITOR_POS_TYPE & pos, const QRegularExpression & regex) {
        fileOpenRequired(path, nullptr, false, true, QPoint(pos, NO_INFO), new QRegularExpression(regex));
    });

    DockWidgets::obj().append(project_search_widget);
}

void IDEWindow::setupColorBoxWindow() {
    color_picker = new ColorPicker(this);
    color_picker_widget =
        DockWidgets::obj().createWidget(
            QLatin1String("Color"),
            color_picker,
            Qt::AllDockWidgetAreas
        );

    color_picker_widget -> setBehaviour(DockWidget::Features(DockWidget::dwf_movable | DockWidget::dwf_closable));
    color_picker_widget -> setWindowIco(":/tabs/color_picker", ":/tools/color_picker");

    DockWidgets::obj().append(color_picker_widget);

    ColorButton * curr_color_btn = new ColorButton(this);
    color_picker_widget -> insertHeaderButton(curr_color_btn, nullptr, nullptr, 0);
    curr_color_btn -> setDisabled(true);
    color_picker -> setCurrentColorButton(curr_color_btn);
    color_picker_widget -> insertHeaderButton(QIcon(":/tools/color_picker"), color_picker, SLOT(colorPickingRequired()), 1);
    color_picker_widget -> hide();
}

QWidget * IDEWindow::findEditor(QSplitter * active_table) {
    QWidget * widget = nullptr;

    while(active_table) {
        widget = active_table -> widget(0);

        if (!widget) {
            Logger::error(QLatin1String("editorIsEmpty"), QLatin1String("incorrect editors table state"));
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
