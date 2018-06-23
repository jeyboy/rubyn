#ifndef LOGGER
#define LOGGER

#include <qpointer.h>

#include "misc/singleton.h"

#define TIME_MARK QDateTime::currentDateTime().toString(QLatin1String("dd.MM.yyyy hh:mm:ss "))

class QPlainTextEdit;
class QFile;
class QTextStream;
class QFontMetrics;
class QElapsedTimer;

class Logger : public QObject, public Singleton<Logger> {
    Q_OBJECT
public:
    enum LogLevel : int {
        log_info = 0,
        log_error = 1,
        log_url
    };

    ~Logger();

    static void dump(const QByteArray & content);

    void write(const QString & initiator, const QString & value, const LogLevel & level = log_info);
    void write(const QString & initiator, const QString & value, const QString & attr, const LogLevel & level = log_info);
    void write(const QString & initiator, const QString & value, const QStringList & attrs, const LogLevel & level = log_info);

    void initiate(const QString & fileName = "", const bool & create_editor = false);
    inline void setShowDateTime(bool show) { m_showDate = show; }
    inline QPointer<QPlainTextEdit> & getEditor() { return m_editor; }

    void startMark();
    void endMark(const QString & initiator, const QString & value);

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

    QElapsedTimer * timer;

    static Logger * self;
private slots:
    void writeToStream(const QString & initiator, const QString & value, int level = log_info);
    void writeToStream(const QString & initiator, const QString & value, const QStringList & attrs, int level = log_info);
    void writeToStream(const QString & initiator, const QString & value, const QString & attr, int level = log_info);
};

#endif // LOGGER

