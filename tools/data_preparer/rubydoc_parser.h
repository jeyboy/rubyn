#ifndef RUBYDOC_PARSER_H
#define RUBYDOC_PARSER_H

#include <qobject.h>
#include <qhash.h>

struct DataObj;
struct DataMethod;
class QTextStream;

namespace Html {
    class Set;
    class Tag;
}

class RubydocParser : public QObject {
    Q_OBJECT

    enum Prefix : char {
        h1_prefix = 13,
        h2_prefix = 14,
        h3_prefix = 15,
        h4_prefix = 16,
        p_prefix = 17,
        ul_prefix = 18,
//        ol_prefix = 19,
        pre_prefix = 20,
        dt_prefix = 21,
        dd_prefix = 22,
        hr_prefix = 23
    };

    QHash<QString, DataObj> parsed_objs;

    const QByteArray target_prefix              = QByteArray("    ");
    const QByteArray description_prefix         = QByteArray("# ");
    const QByteArray description_list_prefix    = QByteArray("#  - ");
    const QByteArray data_head_prefix           = QByteArray("#  * ");
    const QByteArray description_example_prefix = QByteArray("#      ");
    const QByteArray hr_border                  = QByteArray(90, '-').prepend('#');
    const QByteArray h1_border                  = QByteArray(90, '*').prepend('#');
    const QByteArray h2_border                  = h1_border.mid(0, 71);
    const QByteArray h3_border                  = h1_border.mid(0, 51);
    const QByteArray h4_border                  = h1_border.mid(0, 31);
    const char def_const_val[47]                = " = nil # Using for indexing. Value is unknown\0";

    bool findSimbolsSub(const QString & str, const char & s, const char & e, int & spos, int & epos);
    QByteArray clearLine(const QByteArray & line);

    void writeLine(const QByteArray & datum, QStringList & out, const char & prefix, const int & max_line_len = 80);

    void procHeader(Html::Tag * h, QStringList & out, const char & prefix);
    void procDescription(const Html::Set & parts, QStringList & out, const QString & inpath);
    void procMethod(const QString & signature, Html::Tag * method_block, DataMethod & out, const QString & inpath);

    bool parseFile(const QString & path, const QString & name, DataObj & out, const uint & level = 0, const bool & attach = false);
    bool parseFolder(const QString & path);

    void dumpDescription(QStringList & desc, QTextStream & out, const QByteArray & level_padding);
    void dumpObject(DataObj & data_obj, QTextStream & out);

public:
    RubydocParser(QObject * parent = nullptr);
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
