#ifndef DUMPER_H
#define DUMPER_H

#include <qstring.h>

class IDEWindow;

class Dumper {
public:
    static void load(IDEWindow * w, const QString & settings_filename = QString("fsettings"));
    static void save(IDEWindow * w, const QString & settings_filename = QString("fsettings"));
    static void locationCorrection(IDEWindow * w);
};

#endif // DUMPER_H
