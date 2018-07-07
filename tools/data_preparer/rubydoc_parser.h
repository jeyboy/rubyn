#ifndef RUBYDOC_PARSER_H
#define RUBYDOC_PARSER_H

#include <qobject.h>
#include <qhash.h>

struct DataObj;
struct DataMethod;

namespace Html {
    class Set;
    class Tag;
}

class RubydocParser : public QObject {
    Q_OBJECT

    enum Prefix : char {
        h2_prefix = 13,
        h3_prefix = 14,
        h4_prefix = 15,
        p_prefix = 16,
        li_prefix = 17,
        pre_prefix = 18,
        dt_prefix = 19,
        dd_prefix = 20,
        newline_prefix = 21,
    };

    QHash<QString, DataObj> parsed_objs;

    bool findSimbolsSub(const QString & str, const char & s, const char & e, int & spos, int & epos);
    QByteArray clearLine(const QByteArray & line);

    void writeLine(const QByteArray & datum, QStringList & out, const char & prefix, const int & max_line_len = 80);

    void procHeader(Html::Tag * h, QStringList & out, const char & prefix);
    void procDescription(const Html::Set & parts, QStringList & out, const QString & inpath);
    void procMethod(const QString & signature, Html::Tag * method_block, DataMethod & out, const QString & inpath);

    bool parseFile(const QString & path, const QString & name, DataObj & out, const uint & level = 0, const bool & attach = false);
    bool parseFolder(const QString & path);
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
