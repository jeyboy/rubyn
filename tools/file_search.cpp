#include "file_search.h"

#include <qstringbuilder.h>
#include <qdebug.h>

#include "project/file.h"
#include "controls/logger.h"

FileSearch * FileSearch::asyncSearchInFile(const QRegularExpression & regex, File * file, QObject * parent) {
    QThread * thread = new QThread();
    FileSearch * search = new FileSearch(regex, file, parent);

    thread -> start();

    search -> moveToThread(thread);

    search -> initiate();

    return search;
}

FileSearch::FileSearch(const QRegularExpression & regex, File * file, QObject * parent) : QObject(parent), _file(file), regex(regex) {

}

void FileSearch::initiate() {
    if (_file -> openRaw()) {
        QIODevice * source = _file -> source();
        QTextStream in(source);

        qint64 offset = 0;
        int min_buffer_legnth = regex.pattern().length() + 1000;
        int buffer_length = qMax(min_buffer_legnth, 10000);

        QString prev_buffer;
        prev_buffer.reserve(buffer_length);

        QString buffer;
        buffer.reserve(buffer_length);

        QString target;
        target.reserve(buffer_length * 2);

        while(in.readLineInto(&buffer, buffer_length)) {
            target.setRawData(prev_buffer.data(), prev_buffer.length());
            target.append(buffer);

            QRegularExpressionMatchIterator i = regex.globalMatch(target);

            while (i.hasNext()) {
                QRegularExpressionMatch match = i.next();
                emit finded(_file -> path(), offset + match.capturedStart(), match.capturedLength(), target, match.capturedStart());
            }

            offset += buffer.length();
            prev_buffer.setRawData(buffer.data(), buffer.length());
        }

        _file -> close();
    } else {
        Logger::obj().error("FileSearch", "Can't read the file '" + _file -> path() + "'");
    }
}
