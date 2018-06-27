#ifndef RUBYDOC_PARSER_H
#define RUBYDOC_PARSER_H

#include <qobject.h>

class QTextStream;
template <class T> class QList;

namespace Html {
    class Set;
    class Tag;
}

class RubydocParser : public QObject {
    Q_OBJECT

    struct MethodMask {
        QString name;
        QString name_end;
        QString mask;

        QStringList examples;
    };

    QByteArray clearLine(const QByteArray & line);

    void writeLine(const QByteArray & prefix, const QString & datum, QTextStream * out, const int & max_line_len = 80);

    void procDescription(const Html::Set & parts, const QByteArray & prefix, const QByteArray & example_prefix, const QByteArray & list_prefix, const QByteArray & border, QTextStream * out, const QString & inpath);
    void procMethod(const QString & signature, Html::Tag * method_block, const QByteArray & target_prefix, const QByteArray & method_prefix, const QByteArray & description_prefix, const QByteArray & description_example_prefix, const QByteArray & description_list_prefix, const QByteArray & border, QTextStream * out, const QString & inpath);

    QList<RubydocParser::MethodMask> * methodsSamling(const QString & signature, const QStringList & list);

//    bool parseFile(const QString & inpath, const QString & outpath);
    bool parseFolder(const QString & path, const QString & outpath);
public:
    RubydocParser(QObject * parent = 0);
    ~RubydocParser();

    bool parse(const QString & inpath, const QString & outpath);

    bool parseFile(const QString & inpath, const QString & outpath);

protected slots:

signals:
    void started();
    void finished(const bool & status);
    void percentDone(int);
};

#endif // RUBYDOC_PARSER_H
