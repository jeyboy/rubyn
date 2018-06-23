#include "rubydoc_parser.h"

#include "tools/thread_utils.h"
#include "tools/html/html_page.h"

#include "controls/logger.h"

#include <qdiriterator.h>

bool RubydocParser::parseFile(const QString & inpath, const QString & outpath) {
    QByteArray description_prefix("# ");
    QByteArray description_example_prefix("#     ");

// title text -> split : -> take first

// #method-list-section li a text

// #parent-class-section p text

// #includes-section li a text

// #documentation
//
//      #constants-list
//          dt a text // name
//          dd p text // description

//      .method-section#public-class-method-details
//      .method-section#public-instance-method-details
//      .method-section#private-instance-method-details

//          .method-detail
//              .method-heading .method-callseq text

    QFile datafile(inpath);

    if (datafile.open(QFile::ReadOnly | QFile::Text)) {
        QFile outfile(outpath);

        if (outfile.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&outfile);

            out << "# encoding: UTF-8";

            Html::Page page(&datafile, Html::Decoding::charset_utf8, Html::Page::pf_skip_comment);

            Html::Tag * metadata_block = page.findFirst("#metadata");

            if (!metadata_block) {
                Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant parse metadata block in file: ") % inpath);
                datafile.close(); out.flush(); outfile.close();
                return false;
            }

            Html::Tag * doc_block = page.findFirst("#documentation");

            if (!doc_block) {
                Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant parse documentation block in file: ") % inpath);
                datafile.close(); out.flush(); outfile.close();
                return false;
            }

            Html::Tag * doc_header = doc_block -> findFirst("h1");

            if (!doc_header) {
                Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant parse doc header in file: ") % inpath);
                datafile.close(); out.flush(); outfile.close();
                return false;
            }

            QByteArray target_class = doc_header -> rawClasses();
            QByteArray target_name = doc_header -> text();
            QByteArray parent_name;

            Html::Tag * parent_tag = metadata_block -> findFirst("#parent-class-section p a");

            if (parent_tag)
                parent_name = parent_tag -> text();






            // #includes-section li a text


            /////////////////// REMOVE ME LATER
            if (target_class != "class" && target_class != "module") {
                Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("New target type: ") % target_class % QLatin1Literal("  in file: ") % inpath);
            }
            //////////////////////////////////////

            Html::Tag * doc_description = doc_block -> findFirst("#description");

            if (!doc_description) {
                Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant parse doc description in file: ") % inpath);
                datafile.close(); out.flush(); outfile.close();
                return false;
            }

            Html::Set descrition_parts = doc_description -> children();

            for(Html::Set::Iterator tag = descrition_parts.begin(); tag != descrition_parts.end(); tag++) {
                switch((*tag) -> tagID()) {
                    case Html::Tag::tg_p: {
                        writeLine(description_prefix, QString((*tag) -> texts()), &out);
                    break;}

                    case Html::Tag::tg_h2: {
                        QByteArray border((*tag) -> text().length(), '-');

                        out
                            << endl
                            << border
                            << endl
                            << description_prefix
                            << (*tag) -> text()
                            << border
                            << endl;
                    break;}

                    case Html::Tag::tg_pre: {
                        out
                            << description_example_prefix
                            << "-- EXAMPLE --"
                            << endl;

                        Html::Set code_parts = (*tag) -> children();

                        for(Html::Set::Iterator code_tag = code_parts.begin(); code_tag != code_parts.end(); code_tag++) {
                            if ((*code_tag) -> isNewline())
                                out << endl;
                            else
                                out << QString((*code_tag) -> text());
                        }
                    break;}

                    default: {
                        Logger::obj().write(
                            QLatin1Literal("RubydocParser"),
                            QLatin1Literal("Unknown tag type in description: ") % (*tag) -> name() %
                                QLatin1Literal("  in file: ") % inpath
                        );
                    }
                }
            }

//            QString description = QString(doc_description -> texts());

            int y = 0;

            // target_class // target_name // description

//            out <<  << endl;

            Html::Set sections = doc_block -> find(".section");

            while(!sections.isEmpty()) {
                Html::Tag * section = sections.takeFirst();

            //      #constants-list
            //          dt a text // name
            //          dd p text // description

//            #public-class-method-details
//            #public-instance-method-details
//            #private-instance-method-details
            }

            out.flush();
            outfile.close();
        } else {
            Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant open output file: ") % inpath);
            datafile.close();
            return false;
        }

        datafile.close();
    } else {
        Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant open file: ") % inpath);
        return false;
    }

    return true;
}

bool RubydocParser::parseFolder(const QString & path, const QString & outpath) {
    QDirIterator files_it(path, QDir::Files | QDir::Hidden, QDirIterator::Subdirectories);

    while(files_it.hasNext()) {
        QString path = files_it.next();
        QString dir_name = files_it.fileName();

        if (dir_name[0].isUpper()) {
            parseFile(path, outpath);
        }
    }

    return true;
}

void RubydocParser::writeLine(const QByteArray & prefix, const QString & datum, QTextStream * out, const uint & max_line_len) {
    uint pos = 0;

    while(true) {
        QStringRef line = datum.midRef(pos, max_line_len + 1);

        if (line.isEmpty())
            break;

        if (!line.back().isSpace()) {
            int line_size = line.length();

            for(; line_size >= 0; --line_size) {
                if (line[line_size - 1].isSpace())
                    break;
            }

            line = line.mid(0, line_size - 1);
        }

        (*out) << prefix << line << endl;

        pos += line.length();
    }
}

RubydocParser::RubydocParser(QObject * parent) : QObject(parent) {
//    ThreadUtils::obj().run(
//        this, &FilesProcManager::cleanerProc,
//        new Func()
//    );
}

bool RubydocParser::parse(const QString & inpath, const QString & outpath) {


    return true;
}
