#ifndef IPROCESS_LOGGER_H
#define IPROCESS_LOGGER_H

#include <qstring.h>

class IProcessLogger {
    protected:
        bool _last_is_error;
    public:
        IProcessLogger() { _last_is_error = false; }

        inline bool lastPrintedIsError() { return _last_is_error; }
        virtual void setReadOnly(const bool & read_only = true) = 0;

        virtual void printAlert(const QString & msg, const bool add_new_line = false) = 0;
        virtual void printNotify(const QString & msg, const bool add_new_line = false) = 0;
        virtual void printText(const QString & msg, const bool add_new_line = false) = 0;
        virtual void printError(const QString & msg, const bool add_new_line = false) = 0;
};

#endif // IPROCESS_LOGGER_H
