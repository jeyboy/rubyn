#ifndef VERSION_H
#define VERSION_H

#include <qstring.h>
#include <qstringlist.h>

class Version {
    uint _major;
    uint _minor;
    QString _patch;
    QString v;

    Version(const QString & vstr) {
        v = vstr;
        QStringList parts = vstr.split(".");

        if (!parts.isEmpty()) {
            _major = parts.takeFirst().toUInt();
        } else _major = 0;

        if (!parts.isEmpty()) {
            _minor = parts.takeFirst().toUInt();
        } else _minor = 0;

        if (!parts.isEmpty()) {
            _patch = parts.join('.');
        }
    }

    QString toString() { return v; }
};

#endif // VERSION_H
