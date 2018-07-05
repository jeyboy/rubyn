#ifndef RUBYDOC_PARSER_H
#define RUBYDOC_PARSER_H

#include <qobject.h>
#include <qhash.h>

class DataObj;
namespace Html {
    class Set;
    class Tag;
}

class RubydocParser : public QObject {
    Q_OBJECT

//    const QByteArray description_prefix         = QByteArray("# ");
//    const QByteArray description_list_prefix    = QByteArray("#    - ");
//    const QByteArray description_example_prefix = QByteArray("#       ");
//    const QByteArray target_prefix              = QByteArray("    ");
//    const QByteArray border                     = QByteArray(80, '-').prepend('#');

    QHash<QByteArray, DataObj> parsed_objs;

    bool findSimbolsSub(const QString & str, const char & s, const char & e, int & spos, int & epos);
    QByteArray clearLine(const QByteArray & line);

    void writeLine(const QByteArray & datum, DataObj & out, const int & max_line_len = 80);

    void procHeader(Html::Tag * h, DataObj & out);
    void procDescription(const Html::Set & parts, DataObj & out, const QString & inpath);
    void procMethod(const QString & signature, Html::Tag * method_block, DataObj & out, const QString & inpath);

    bool parseFile(const QString & path, const QString & name, DataObj & out, const uint & level = 0, const bool & attach = false);
    bool parseFolder(const QString & path, const QString & outpath);
public:
    RubydocParser(QObject * parent = 0);
    ~RubydocParser();

    bool parse(const QString & inpath);
    bool saveParsedDatum(const QString & outpath);

    bool initParseFile(const QString & path, const QString & name, const QString & outpath, const QByteArray & offset = QByteArray());

protected slots:

signals:
    void started();
    void finished(const bool & status);
    void percentDone(int);
};

#endif // RUBYDOC_PARSER_H
