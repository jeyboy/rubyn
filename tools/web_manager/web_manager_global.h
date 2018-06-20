#ifndef WEBMANAGER_GLOBAL_H
#define WEBMANAGER_GLOBAL_H

//#include <QtCore/qglobal.h>
#include "misc/defines.h"

#include <qbytearray.h>

#define REQUEST_DELAY 100 // ms
#define COOKIES_KEY QByteArrayLiteral("cookies")

#define JSON_ERR_FIELD QByteArrayLiteral("json_err")
#define DEF_JSON_FIELD QByteArrayLiteral("response")

#endif // WEBMANAGER_GLOBAL_H
