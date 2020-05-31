#ifndef BASIC_LOGGER_H
#define BASIC_LOGGER_H

#include <qplaintextedit.h>

#include "iprocess_logger.h"

class BasicLogger : public QPlainTextEdit, public IProcessLogger {
    public:
        BasicLogger(QWidget * parent = Q_NULLPTR);
        virtual ~BasicLogger() {}

        void setReadOnly(const bool & read_only = true);

    public slots:
        void printAlert(const QString & msg, const bool add_new_line = false);
        void printNotify(const QString & msg, const bool add_new_line = false);
        void printText(const QString & msg, const bool add_new_line = false);
        void printError(const QString & msg, const bool add_new_line = false);
};

#endif // BASIC_LOGGER_H
