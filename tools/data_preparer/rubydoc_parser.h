#ifndef RUBYDOC_PARSER_H
#define RUBYDOC_PARSER_H

#include <qobject.h>

class QTextStream;
class DataObj;
namespace Html {
    class Set;
    class Tag;
}

class RubydocParser : public QObject {
    Q_OBJECT

    const QByteArray description_prefix         = QByteArray("# ");
    const QByteArray description_list_prefix    = QByteArray("#    - ");
    const QByteArray description_example_prefix = QByteArray("#       ");
    const QByteArray target_prefix              = QByteArray("    ");
    const QByteArray border                     = QByteArray(80, '-').prepend('#');

    bool findSimbolsSub(const QString & str, const char & s, const char & e, int & spos, int & epos);
    QByteArray clearLine(const QByteArray & line);

    void writeLine(const QByteArray & prefix, const QByteArray & datum, QTextStream * out, const int & max_line_len = 80);

    void procHeader(Html::Tag * h, const QByteArray & prefix, const QByteArray & border, QTextStream * out);
    void procDescription(const Html::Set & parts, const QByteArray & prefix, const QByteArray & example_prefix, const QByteArray & list_prefix, const QByteArray & border, QTextStream * out, const QString & inpath);
    void procMethod(const QString & signature, Html::Tag * method_block, const QByteArray & target_prefix, const QByteArray & method_prefix, const QByteArray & description_prefix, const QByteArray & description_example_prefix, const QByteArray & description_list_prefix, const QByteArray & border, QTextStream * out, const QString & inpath);

    bool parseFile(const QString & path, const QString & name, QTextStream & out, const QByteArray & offset = QByteArray(), const bool & attach = false);
    bool parseFolder(const QString & path, const QString & outpath);
public:
    RubydocParser(QObject * parent = 0);
    ~RubydocParser();

    bool parse(const QString & inpath, const QString & outpath);

    bool initParseFile(const QString & path, const QString & name, const QString & outpath, const QByteArray & offset = QByteArray());

protected slots:

signals:
    void started();
    void finished(const bool & status);
    void percentDone(int);
};

#endif // RUBYDOC_PARSER_H
