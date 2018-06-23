#include "rubydoc_parser.h"

#include "tools/thread_utils.h"
#include "tools/html/html_page.h"

#include "controls/logger.h"

#include <qdiriterator.h>

bool RubydocParser::parseFile(const QString & inpath, const QString & outpath) {
// title text -> split : -> take first

// #parent-class-section p text

// #method-list-section li a text

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

        if (datafile.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&outfile);

            Html::Page page(file);

            Html::Tag * doc_block = page.findFirst("#documentation");

            if (!doc_block) {
                Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant parse documentation_block in file: ") % inpath);
                return false;
            }

            Html::Tag * doc_header = doc_block -> findFirst("h1");

            if (!doc_header) {
                Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant parse doc header in file: ") % inpath);
                return false;
            }

            QByteArray target_class = doc_header -> rawClasses();
            QByteArray target_name = doc_header -> text();

            /////////////////// REMOVE ME LATER
            if (target_class != "class" && target_class != "module") {
                Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("New target type: ") % target_class % QLatin1Literal("  in file: ") % inpath);
            }
            //////////////////////////////////////

            Html::Tag * doc_description = doc_block -> findFirst("#description");

            if (!doc_description) {
                Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant parse doc description in file: ") % inpath);
                return false;
            }

            QByteArray description = doc_description -> texts();



            // target_class // target_name // description

            outfile.close();
        } else {
            Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant open output file: ") % inpath);
            return false;
        }

        datafile.close();
    } else {
        Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant open file: ") % inpath);
        return false;
    }
}

void RubydocParser::parseFolder(const QString & path) {
    QDirIterator files_it(path, QDir::Files | QDir::Hidden, QDirIterator::Subdirectories);

    while(files_it.hasNext()) {
        QString path = files_it.next();
        QString dir_name = files_it.fileName();

        if (dir_name[0].isUpper()) {
            parseFile(path);
        }
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
