#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <qobject.h>
#include <qbytearray.h>
#include <qprocess.h>

class Archive : public QObject {
    Q_OBJECT

    static QString store_ext;
    static QStringList supported_formats;

    bool prepareUniqFolderName(QString & name);
protected:
    static const QString & storePath();
    static QByteArray errToString(const QProcess::ProcessError & error);

    QString buildAvailableFormatsCmd();
    QString buildDecompressCmd(const QString & path, const QString & target_folder);
    bool runCmd(const QString & cmd, QString & output);
    QStringList supportedUncompressFormats();

protected slots:
    void begin();
    void errorOccurred(QProcess::ProcessError error);
    void hasError();
    void hasOutput();
    void done(int status);
public:
    Archive();
    enum OutputType : quint8 {
        ot_error = 0,
        ot_data = 1
    };

    bool decompress(const QString & path);

    static bool load(const QString & name, QByteArray & buf);
    static bool save(const QString & name, const QByteArray & buf);
signals:
    void started();
    void finished(const bool & status);
    void hasStatusData(const QByteArray &, const OutputType &);
};

#endif // ARCHIVE_H
