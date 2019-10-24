#ifndef UNIVERSAL_EDITOR_H
#define UNIVERSAL_EDITOR_H

#include <qwidget.h>
#include <qhash.h>

class IEditor;
class CodeEditor;
class TreeEditor;
namespace Custom { class Editor; }

class QVBoxLayout;
class File;
class Completer;
class EditorSearch;

class UniversalEditor : public QWidget {
    Q_OBJECT

    QVBoxLayout * col_layout;

    IEditor * _active_editor;
    CodeEditor * _code_editor;
    TreeEditor * _tree_editor;
    Custom::Editor * _custom_editor;

    File * _file;
    Completer * _completer;
    EditorSearch * _search_bar;

    void setupLayout();
    void setupCodeEditor();
    void setupTreeEditor();
    void setupCustomEditor();

    void setupCompleter();
public:
    UniversalEditor(QWidget * parent = Q_NULLPTR);
    ~UniversalEditor();

    bool openFile(File * file);
    const QString & documentUid();

    int verticalScrollBar();
signals:
  void cursorPosChanged(const QString &);
  void inFocus();
  void fileDropped(const QUrl &);

protected slots:
    void showSearchPanel(const bool & show = true);
};

#endif // UNIVERSAL_EDITOR_H
