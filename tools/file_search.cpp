#include "file_search.h"

#include "project/file.h"
#include "controls/logger.h"
#include "tools/file_search_result.h"

FileSearch::FileSearch(const QRegularExpression & regex, File * file, QObject * parent) : QObject(parent), _file(file), regex(regex), preview_window(0) {

}

void FileSearch::run() {
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

        while(!in.atEnd()) {
            /*in.readLineInto(&buffer, buffer_length)*/
            buffer = in.read(buffer_length);

            target.setRawData(prev_buffer.data(), prev_buffer.length());
            target.append(buffer);

            QRegularExpressionMatchIterator i = regex.globalMatch(target);
            int from = 0;

            while(i.hasNext()) {
                QRegularExpressionMatch match = i.next();

                QString preview;
                int preview_pos = 0;
                QString::ConstIterator it_begin = target.constBegin();
                QString::ConstIterator it = it_begin + match.capturedStart();

                if (preview_window > 0) {
                    if (preview_window > match.capturedStart()) {
                        preview_pos = match.capturedStart();
                    } else {
                        preview_pos = preview_window;
                    }

                    it -= preview_pos;
                    preview.append(it, preview_pos + preview_window + match.capturedLength());
                } else {
                    while(it != it_begin) {
                        if (*it == '\n' || preview_pos >= 20) {
                            ++it;
                            --preview_pos;
                            break;
                        }

                        ++preview_pos;
                        --it;
                    }

                    while(preview_pos > 0) {
                        if (*it < 33) {
                            ++it;
                            --preview_pos;
                        } else {
                            break;
                        }
                    }


                    int length = 0;

                    QString::ConstIterator tail_it = it_begin + match.capturedStart() + match.capturedLength();

                    while(tail_it != target.constEnd()) {
                        if (*tail_it == '\n' || length >= 80) {
                            break;
                        }

                        ++length;
                        ++tail_it;
                    }

                    while(length > 0) {
                        if (*tail_it < 33) {
                            --tail_it;
                            --preview_pos;
                        } else {
                            break;
                        }
                    }

                    preview.append(it, preview_pos + match.capturedLength() + length);
                }



                emit finded(
                    new FileSearchResult {
                        _file -> path(),
                        offset + match.capturedStart(),
                        (EDITOR_LEN_TYPE)match.capturedLength(),
                        preview,
                        preview_pos
                    }
                );

                from = match.capturedStart() + match.capturedLength();
            }

            offset += buffer.length();

            prev_buffer.clear();
            prev_buffer.append(buffer.data() + from, buffer.length() - from);
//            prev_buffer.setRawData(buffer.data(), buffer.length());
        }

        _file -> close();

        emit finished(_file -> path(), true);
    } else {
        Logger::obj().error("FileSearch", "Can't read the file '" + _file -> path() + "'");
        emit finished(_file -> path(), false);
    }
}

//void FileSearch::runAsync() {
//    QThread * thread = new QThread();

//    thread -> start();

//    moveToThread(thread);

//    run();
//}
