#ifndef LOGGER
#define LOGGER

#include <qpointer.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qelapsedtimer.h>
#include <qdatetime.h>
#include <qscrollbar.h>
#include <qstringbuilder.h>
#include <qapplication.h>
#include <qfontmetrics.h>

#include "misc/singleton.h"

#define TIME_MARK QDateTime::currentDateTime().toString(QLatin1String("dd.MM.yyyy hh:mm:ss "))

class QPlainTextEdit;

class Logger : public QObject, public Singleton<Logger> {
    Q_OBJECT
public:
    enum LogLevel : int {
        log_info = 0,
        log_error = 1,
        log_url
    };

    ~Logger();

    static void dump(const QByteArray & content) {
        QString p = QCoreApplication::applicationDirPath() % '/' % QDateTime::currentDateTime().toString("yyyy.MM.dd_hh.mm.ss.zzz") % QLatin1String(".html");
        QFile f(p);
        if (f.open(QFile::WriteOnly)) {
            f.write(content);
            f.close();
        }
    }

    void write(const QString & initiator, const QString & value, const LogLevel & level = log_info);
    void write(const QString & initiator, const QString & value, const QString & attr, const LogLevel & level = log_info);
    void write(const QString & initiator, const QString & value, const QStringList & attrs, const LogLevel & level = log_info);

    void initiate(const QString & fileName = "", const bool & create_editor = false);
    inline void setShowDateTime(bool show) { m_showDate = show; }
    inline QPointer<QPlainTextEdit> & getEditor() { return m_editor; }

//    inline void startMark() { timer.start(); }
//    inline void endMark(QString initiator, QString value) {
//        write(initiator, value, QString::number(timer.elapsed()) % QLatin1String(" ms (") % Info::paddedNumber(timer.nsecsElapsed()) % QLatin1String(" ns)"));
//    }

private:
    QString path(const QString & file);

    void toFile(const QString & initiator, const QString & value);
    void toEditor(const QString & initiator, const QString & value);

    Logger(); friend class Singleton<Logger>;

    QTextStream * out;
    QFile * file;
    QPointer<QPlainTextEdit> m_editor;
    bool m_showDate;
    QString lastInitiator;
    QFontMetrics * fm;

    QElapsedTimer timer;

    static Logger * self;
private slots:
    void writeToStream(const QString & initiator, const QString & value, int level = log_info);
    void writeToStream(const QString & initiator, const QString & value, const QStringList & attrs, int level = log_info);
    void writeToStream(const QString & initiator, const QString & value, const QString & attr, int level = log_info);
};

#endif // LOGGER

