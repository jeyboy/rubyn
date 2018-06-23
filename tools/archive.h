#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <qobject.h>
#include <qbytearray.h>
#include <qprocess.h>

class Archive : public QObject {
    Q_OBJECT

    static QString store_ext;
protected:
    Archive();

    static const QString & storePath();
protected slots:
    void begin();
    void errorOccurred(QProcess::ProcessError error);
    void hasError();
    void hasOutput();
    void done(int status);
public:
    enum OutputType : quint8 {
        ot_error = 0,
        ot_data = 1
    };

    static void init();

    void decompress(const QString & path);

    static bool load(const QString & name, QByteArray & buf);
    static bool save(const QString & name, const QByteArray & buf);
signals:
    void started();
    void finished(const bool & status);
    void hasStatusData(const QByteArray &, const OutputType &);
};

#endif // ARCHIVE_H
