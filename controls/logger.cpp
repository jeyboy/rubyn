#include "logger.h"

#include "misc/format.h"

#include <qfile.h>
#include <qdatetime.h>
#include <qtextstream.h>
#include <qfontmetrics.h>
#include <qapplication.h>
#include <qscrollbar.h>
#include <qstringbuilder.h>
#include <qelapsedtimer.h>

const char * Logger::nl = "\n";

void Logger::dump(const QByteArray & content) {
    QString p = QCoreApplication::applicationDirPath() % '/' % QDateTime::currentDateTime().toString("yyyy.MM.dd_hh.mm.ss.zzz") % QLatin1String(".html");
    QFile f(p);
    if (f.open(QFile::WriteOnly)) {
        f.write(content);
        f.close();
    }
}

Logger::Logger() : QObject(), out(nullptr), file(nullptr), m_editor(nullptr), m_showDate(true), fm(nullptr), timer(new QElapsedTimer()) {}

Logger::~Logger() {
    if (file) {
        out -> flush();
        file -> close();
    }

    delete out;
    delete file;
    delete m_editor;
    delete timer;

    fm = nullptr;
}

void Logger::write(const QString & initiator, const LogLevel & level) {
    QMetaObject::invokeMethod(
        this,
        "writeToStream",
        Qt::AutoConnection,
        Q_ARG(const QString &, initiator),
        Q_ARG(int, level)
    );
}

void Logger::write(const QString & initiator, const QString & value, const LogLevel & level) {
    QMetaObject::invokeMethod(
        this,
        "writeToStream",
        Qt::AutoConnection,
        Q_ARG(const QString &, initiator),
        Q_ARG(const QString &, value),
        Q_ARG(int, level)
    );
}
void Logger::write(const QString & initiator, const QString & value, const QString & attr, const LogLevel & level) {
    QMetaObject::invokeMethod(
        this,
        "writeToStream",
        Qt::AutoConnection,
        Q_ARG(const QString &, initiator),
        Q_ARG(const QString &, value),
        Q_ARG(const QString &, attr),
        Q_ARG(int, level)
    );
}
void Logger::write(const QString & initiator, const QString & value, const QStringList & attrs, const LogLevel & level) {
    QMetaObject::invokeMethod(
        this,
        "writeToStream",
        Qt::AutoConnection,
        Q_ARG(const QString &, initiator),
        Q_ARG(const QString &, value),
        Q_ARG(const QStringList &, attrs),
        Q_ARG(int, level)
    );
}


void Logger::initiate(const QString & file_name, const bool & create_editor) {
    if (create_editor && !m_editor) {
        m_editor = new LoggerWindow();
        m_editor -> setReadOnly(true);

        fm = new QFontMetrics(m_editor -> document() -> defaultFont());
//        QTextDocument * doc = m_editor -> document();
//        QFont font = doc -> defaultFont();
//        font.setFamily("Courier New");
//        doc -> setDefaultFont(font);
    }

    if (!file_name.isEmpty()) {
        file = new QFile(path(file_name));
        file -> open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

        out = new QTextStream(file);
        out -> setCodec("UTF-8");
    }
}

void Logger::startMark() { timer -> start(); }

void Logger::endMark(const QString & initiator, const QString & value) {
    write(initiator, value, QString::number(timer -> elapsed()) % QLatin1String(" ms (") % Info::paddedNumber(timer -> nsecsElapsed()) % QLatin1String(" ns)"));
}

QString Logger::path(const QString & file) {
    return qApp -> applicationDirPath() % '/' % file;
}

void Logger::toFile(const QString & initiator, const QString & value) {
    if (file) {
        (*out) << TIME_MARK << " ||| " << initiator << " : " << value << nl;
        out -> flush();
    }
}
void Logger::toEditor(const QString & initiator, const QString & value) {
    if (m_editor) {
        QString text;

        if (initiator != lastInitiator) {
            lastInitiator = initiator;
            text = "<br>" % initiator % "<br>";
        }

        ///////////// monkey patch for crash on missed symbols (khmer and etc)
        QString cval;
        for(QString::ConstIterator ch = value.constBegin(); ch != value.constEnd(); ch++)
            if (fm && fm -> inFont(*ch))
                cval.append(*ch);

        ///////////////////////////////////////

        text = QString("%1%2 ::: %3").arg(
            text,
            (m_showDate ? QStringLiteral("<b>") % TIME_MARK % QStringLiteral("</b>") : QStringLiteral("")),
            cval/*value*/
        );

        bool atEnd = m_editor -> verticalScrollBar() -> maximum() - m_editor -> verticalScrollBar() -> value() < 10;
        m_editor -> appendHtml(text);

        if (atEnd)
            m_editor -> ensureCursorVisible();
    }
}

void Logger::writeToStream(const QString & initiator, int level) {
    writeToStream(initiator, QString(), QString(), level);
}

void Logger::writeToStream(const QString & initiator, const QString & value, int level) {
    writeToStream(initiator, value, QString(), level);
}

void Logger::writeToStream(const QString & initiator, const QString & value, const QStringList & attrs, int level) {
    writeToStream(initiator, value, attrs.join(" , "), level);
}

void Logger::writeToStream(const QString & initiator, const QString & value, const QString & attr, int level) {
    toFile(initiator, QStringLiteral("%1   :::   %2").arg(value, attr));
    toEditor(initiator,
        QString("<span style='color: " %
            QString(level == log_error ? QLatin1String("red") : level == log_info ? QLatin1String("green") : QLatin1String("blue")) %
                "'>%1</span> ::: <span style='color: darkblue'>%2</span>").arg(value, attr)
    );
}
