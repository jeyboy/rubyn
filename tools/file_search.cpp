#include "file_search.h"

#include "project/file.h"
#include "controls/logger.h"
#include "tools/file_search_result.h"

FileSearch::FileSearch(const QRegularExpression & regex, File * file, QObject * parent) : QObject(parent), _file(file), regex(regex) {

}

void FileSearch::initiate() {
    if (_file -> openRaw()) {
        QIODevice * source = _file -> source();
        QTextStream in(source);

        EDITOR_POS_TYPE offset = 0;
        int min_buffer_legnth = regex.pattern().length() + 1000;
        int buffer_length = qMax(min_buffer_legnth, 10000);

        QString prev_buffer;
        prev_buffer.reserve(buffer_length);

        QString buffer;
        buffer.reserve(buffer_length);

        QString target;
        target.reserve(buffer_length * 2);


        while(!in.atEnd()/*in.readLineInto(&buffer, buffer_length)*/) {
            buffer = in.read(buffer_length);

            target.setRawData(prev_buffer.data(), prev_buffer.length());
            target.append(buffer);

            QRegularExpressionMatchIterator i = regex.globalMatch(target);

            while(i.hasNext()) {
                QRegularExpressionMatch match = i.next();
                emit finded(
                    new FileSearchResult {
                        _file -> path(),
                        offset + match.capturedStart(),
                        (EDITOR_LEN_TYPE)match.capturedLength(),
                        target,
                        match.capturedStart()
                    }
                );
            }

            offset += buffer.length();
            prev_buffer.setRawData(buffer.data(), buffer.length());
        }

        _file -> close();
    } else {
        Logger::obj().error("FileSearch", "Can't read the file '" + _file -> path() + "'");
    }
}

void FileSearch::initiateAsync() {
    QThread * thread = new QThread();

    thread -> start();

    moveToThread(thread);

    initiate();
}
