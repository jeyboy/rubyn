#ifndef RUBYDOC_PARSER_H
#define RUBYDOC_PARSER_H

#include <qobject.h>

class RubydocParser : public QObject {
    Q_OBJECT

    bool parseFile(const QString & inpath, const QString & outpath);
public:
    RubydocParser(QObject * parent = 0);
    bool parse(const QString & inpath, const QString & outpath);

protected slots:

signals:
    void started();
    void finished(const bool & status);
    void percentDone(int);
};

#endif // RUBYDOC_PARSER_H
