#ifndef TREE_DOCUMENT
#define TREE_DOCUMENT

#include <qabstractitemmodel.h>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>


#include "misc/defines.h"
#include "editor/idocument.h"

class Project;
//class IHighlighter;


class TreeItem {
public:
    enum Type {
        Null =  0x0,
        Bool = 0x1,
        Double = 0x2,
        String = 0x3,
        Array = 0x4,
        Object = 0x5,
        Int = 0x6,
        Undefined = 0x80
    };

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
    TreeItem::Type type() const;
    void setType(const TreeItem::Type & type);

protected:


private:
    QString mKey;
    QString mValue;
    TreeItem::Type mType;
    QList<TreeItem *> mChilds;
    TreeItem * mParent;
};


class TreeDocument : public QAbstractItemModel, public IDocument {
    Q_OBJECT

//    IHighlighter * highlighter;

    QJsonValue genJson(TreeItem *) const;
protected:
    TreeItem * mRootItem;
    QStringList mHeaders;

//    bool identificateLexer();
    bool registerStateChangedCallback(QObject * target, const char * slot) Q_DECL_OVERRIDE;
signals:
    void hasChanges(const QString & uid, const bool & has);
//    void wordHovered(const QPoint & point, const int & start, const int & end);
//    void highlightingComplete();
public:
    TreeDocument(File * file, QObject * parent = nullptr);

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

    void highlight(QRegularExpression * reg_exp, const bool & scroll = true);

////    inline void setRevision(const int & new_revision) { _revision = new_revision; }
////    inline int revision() { return _revision; }

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    bool setText(const QByteArray & new_data, const FormatType & ftype);
    QByteArray text() const;



//protected slots:
//    void hasUnsavedChanges(const bool & has = true);
//    void changesInContent(int position, int removed_count, int added_count);
//    void highlighterFinished();
};

#endif // TREE_DOCUMENT
