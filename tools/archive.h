#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <qobject.h>
#include <qbytearray.h>

class Archive : public QObject {
    static QString store_ext;
protected:
    Archive();

    static const QString & storePath();
public:
    static void init();

    void decompress(const QString & name);

    static bool load(const QString & name, QByteArray & buf);
    static bool save(const QString & name, const QByteArray & buf);
};

#endif // ARCHIVE_H
