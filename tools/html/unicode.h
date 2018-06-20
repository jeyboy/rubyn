#ifndef UNICODE_UTF8_H
#define UNICODE_UTF8_H

#include "html_global.h"

#include <qbytearray.h>
#include <qstring.h>
#include <qdebug.h>

#define         MASKBITS                0x3F
#define         MASKBYTE                0x80
#define         MASK2BYTES              0xC0
#define         MASK3BYTES              0xE0
#define         MASK4BYTES              0xF0
#define         MASK5BYTES              0xF8
#define         MASK6BYTES              0xFC

namespace Unicode {
    class Utf8 {
        static uint CP1251Table[256];

    public:
        static bool isNonCharacter(const uint & unicode);

        static QByteArray bytes(const uint & unicode);
        static void bytes(const uint & unicode, QByteArray & res);
        static QString str(const QByteArray & bytes);

        // not tested
        static QByteArray bytesCP1251(const QByteArray & iso_bytes);
        static QByteArray bytesCP1252(const QByteArray & iso_bytes);
    };
}

#endif // UNICODE_UTF8_H
