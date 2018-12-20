#ifndef UNIVERSAL_EDITOR_H
#define UNIVERSAL_EDITOR_H

#include <qwidget.h>

class IEditor;
class CodeEditor;
class TreeEditor;

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

    File * _file;
    Completer * _completer;
    EditorSearch * _search_bar;

    void setupLayout();
    void setupCodeEditor();
    void setupTreeEditor();

    void setupCompleter();
public:
    UniversalEditor(QWidget * parent = Q_NULLPTR);

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
