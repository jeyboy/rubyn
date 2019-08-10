#ifndef TREE_DOCUMENT
#define TREE_DOCUMENT

#include <qabstractitemmodel.h>

#include "misc/defines.h"
#include "editor/idocument.h"

class Project;
class File;
//class IHighlighter;


class TreeItem {
public:
    static TreeItem * load(const QJsonValue & value, TreeItem * parent = nullptr);

    TreeItem(TreeItem * parent = nullptr);
    ~TreeItem();
    void appendChild(TreeItem * item);
    TreeItem * child(int row);
    TreeItem * parent();
    int childCount() const;
    int row() const;

    QString key() const;
    void setKey(const QString & key);
    QString value() const;
    void setValue(const QString & value);
//    QJsonValue::Type type() const;
//    void setType(const QJsonValue::Type& type);

protected:


private:
    QString mKey;
    QString mValue;
//    QJsonValue::Type mType;
    QList<TreeItem *> mChilds;
    TreeItem * mParent;


};


class TreeDocument : public QAbstractItemModel, public IDocument {
    Q_OBJECT

//    IHighlighter * highlighter;

//    QJsonValue genJson(TreeItem *) const;
protected:
    File * _file;
    TreeItem * mRootItem;
    QStringList mHeaders;

//    bool identificateLexer();
    bool registerStateChangedCallback(QObject * target, const char * slot) Q_DECL_OVERRIDE;
signals:
    void hasChanges(const QString & uid, const bool & has);
//    void wordHovered(const QPoint & point, const int & start, const int & end);
//    void highlightingComplete();
public:
    TreeDocument(File * file);

    ~TreeDocument() Q_DECL_OVERRIDE;

//    const QLatin1String & tabSpace() { return tab_space; }

    const QString & documentUid();

////    void readNextBlock();

//    void lexicate(const QString & text, IHighlighter * highlighter);

//    bool isChanged() const { return isModified(); }
//    bool isCompleterInitiable(const LEXEM_TYPE & lex, const bool & at_end);
//    bool isCompleterContinuable(const LEXEM_TYPE & lex, const bool & at_end);
//    bool isCompleterReplaceable(const LEXEM_TYPE & lex, const bool & at_start);

//    void paraOpositionStr(const PARA_TYPE & para, QString & res);

//    LEXEM_TYPE getWordBoundaries(EDITOR_POS_TYPE & start, EDITOR_POS_TYPE & length, const QTextBlock & block, const EDITOR_POS_TYPE & pos, const bool & global_offset = true);
//    ParaCell * getPara(const QTextBlock & block, const EDITOR_POS_TYPE & pos);

    bool save() Q_DECL_OVERRIDE;
    bool dump(QVariant & data) Q_DECL_OVERRIDE;
    bool restore(const QVariant & data) Q_DECL_OVERRIDE;

////    inline void setRevision(const int & new_revision) { _revision = new_revision; }
////    inline int revision() { return _revision; }

    inline void setVerticalScrollPos(const int & pos) { scroll_pos_y = pos; }
    inline int verticalScrollPos(const bool & drop = true) {
        int res = scroll_pos_y;
        if (drop)
            scroll_pos_y = 0;
        return res;
    }



    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    QByteArray text() const;



//protected slots:
//    void hasUnsavedChanges(const bool & has = true);
//    void changesInContent(int position, int removed_count, int added_count);
//    void highlighterFinished();
};

#endif // TREE_DOCUMENT
