#ifndef LOGGER
#define LOGGER

#include <qpointer.h>
#include <qhash.h>

#include "misc/singleton.h"
#include "controls/logger_window.h"

#define TIME_MARK QDateTime::currentDateTime().toString(QLatin1String("dd.MM.yyyy hh:mm:ss "))

class QFile;
class QTextStream;
class QFontMetrics;
class QElapsedTimer;

struct TimeMark {
    quint64 sum;
    quint32 quantity;

    TimeMark(const quint64 & part = 0, const quint32 & qty = 0) : sum(part), quantity(qty) {}

    void append(const quint64 & part) {
        sum += part;
        ++quantity;
    }

    quint64 average() {
        if (sum == 0 || quantity == 0)
            return 0;
        else
            return sum / quantity;
    }

    quint64 appendAndAverage(const quint64 & part) {
        append(part);
        return average();
    }
};

class Logger : public QObject, public Singleton<Logger> {
    Q_OBJECT

    QHash<QString, TimeMark> mark_averages;
public:
    static const char * nl;

    enum LogLevel : int {
        log_info = 0,
        log_error = 1,
        log_success = 2,
        log_url
    };

    ~Logger();

    static void dump(const QByteArray & content);

    static void info(const QString & initiator, const QString & value = QString());
    static void error(const QString & initiator, const QString & value = QString());
    static void success(const QString & initiator, const QString & value = QString());


    void write(const QString & initiator, const LogLevel & level = log_info);
    void write(const QString & initiator, const QString & value, const LogLevel & level = log_info);
    void write(const QString & initiator, const QString & value, const QString & attr, const LogLevel & level = log_info);
    void write(const QString & initiator, const QString & value, const QStringList & attrs, const LogLevel & level = log_info);

    void initiate(const QString & fileName = "", const bool & create_editor = false);
    inline void setShowDateTime(bool show) { m_showDate = show; }
    inline QPointer<LoggerWindow> & getEditor() { return m_editor; }

    void startMark();
    void endMark(const bool & append_to_average = false, const QString & initiator = QLatin1Literal("Time:"), const QString & value = QString());
    void clearMarks() { mark_averages.clear(); }

private:
    QString path(const QString & file);

    void toFile(const QString & initiator, const QString & value);
    void toEditor(const QString & initiator, const QString & value, const int & level);

    QLatin1String textColor(const int & level);
    QLatin1String backColor(const int & level);

    Logger(); friend class Singleton<Logger>;

    QTextStream * out;
    QFile * file;
    QPointer<LoggerWindow> m_editor;
    bool m_showDate;
    QString lastInitiator;
    QFontMetrics * fm;

    QElapsedTimer * timer;

    static Logger * self;
private slots:
    void writeToStream(const QString & initiator, int level);
    void writeToStream(const QString & initiator, const QString & value, int level = log_info);
    void writeToStream(const QString & initiator, const QString & value, const QStringList & attrs, int level = log_info);
    void writeToStream(const QString & initiator, const QString & value, const QString & attr, int level = log_info);
};

#endif // LOGGER

