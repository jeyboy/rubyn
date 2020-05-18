#ifndef IPROCESS_LOGGER_H
#define IPROCESS_LOGGER_H

#include <qstring.h>

class IProcessLogger {
    public:
        virtual void setReadOnly(const bool & read_only = true) = 0;

        virtual void printAlert(const QString & msg) = 0;
        virtual void printNotify(const QString & msg) = 0;
        virtual void printText(const QString & msg) = 0;
        virtual void printError(const QString & msg) = 0;
};

#endif // IPROCESS_LOGGER_H
