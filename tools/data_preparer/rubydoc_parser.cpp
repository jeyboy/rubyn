#include "rubydoc_parser.h"

#include "tools/thread_utils.h"
#include "tools/html/html_page.h"

#include "controls/logger.h"

#include <qlist.h>
#include <qdiriterator.h>
#include <qhash.h>

bool RubydocParser::findSimbolsSub(const QString & str, const char & s, const char & e, int & spos, int & len) {
    spos = str.indexOf(s);

    if (spos > -1) {
        int epos = str.lastIndexOf(e);

        len = epos - spos - 1;
        ++spos;

        return true;
    }

    return false;
}

QByteArray RubydocParser::clearLine(const QByteArray & line) {
    QByteArray res;
    res.reserve(line.size());

    const char * ptr = line.constData();

    while(*ptr) {
        switch(*ptr) {
            case 32: {
                switch(*(ptr + 1)) {
                    case 46: { // .
                        if (*(ptr + 2) == '.') // ignore blanks before ... and .. sequences
                            break;
                    }
                    case 44: // ,
                    case 32: {
                        ++ptr;
                        continue;
                    break;}
                }
            break;}
        }

        res.append(*ptr);
        ++ptr;
    }

    return res;
}

void RubydocParser::writeLine(const QByteArray & prefix, const QString & datum, QTextStream * out, const int & max_line_len) {
    uint pos = 0;

    if (datum.length() < max_line_len) {
        (*out) << prefix << datum << Logger::nl;
        return;
    }

    while(true) {
        QStringRef line = datum.midRef(pos, max_line_len + 1);

        if (line.isEmpty())
            break;

        if (line.length() == max_line_len + 1) {
            int line_size = line.length();

            for(; line_size >= 0; --line_size) {
                if (line[line_size - 1].isSpace())
                    break;
            }

            line = line.mid(0, line_size - 1);
        }

        (*out) << prefix;
        if (pos > 0)
            (*out) << ' ';
        (*out) << line << Logger::nl;

        pos += line.length();
    }
}

void RubydocParser::procDescription(const Html::Set & parts, const QByteArray & prefix, const QByteArray & example_prefix, const QByteArray & list_prefix, const QByteArray & border, QTextStream * out, const QString & inpath) {
    for(Html::Set::ConstIterator tag = parts.cbegin(); tag != parts.cend(); tag++) {
        switch((*tag) -> tagID()) {
            case Html::Tag::tg_p: {
                writeLine(prefix, QString(clearLine((*tag) -> texts())), out);
            break;}

            case Html::Tag::tg_h2: {
                (*out)
                    << border
                    << Logger::nl
                    << prefix;

                Html::Set hchilds = (*tag) -> children();

                for(Html::Set::Iterator htag = hchilds.begin(); htag != hchilds.end(); htag++) {
                    if ((*htag) -> tagID() == Html::Tag::tg_span)
                        break;
                    else
                        (*out) << (*htag) -> text();
                }

                (*out)
                    << Logger::nl
                    << border
                    << Logger::nl;
            break;}

            case Html::Tag::tg_h3: {
                (*out)
                    << border.mid(0, 40)
                    << Logger::nl
                    << prefix;

                Html::Set hchilds = (*tag) -> children();

                for(Html::Set::Iterator htag = hchilds.begin(); htag != hchilds.end(); htag++) {
                    if ((*htag) -> tagID() == Html::Tag::tg_span)
                        break;
                    else
                        (*out) << (*htag) -> text();
                }

                (*out)
                    << Logger::nl
                    << border.mid(0, 40)
                    << Logger::nl;
            break;}

            case Html::Tag::tg_pre: {
                (*out)
                    << example_prefix << Logger::nl << example_prefix;

                Html::Set code_parts = (*tag) -> children();

                for(Html::Set::Iterator code_tag = code_parts.begin(); code_tag != code_parts.end(); code_tag++) {
                    if ((*code_tag) -> isNewline()) {
                        (*out) << Logger::nl;

                        if (code_tag + 1 != code_parts.end())
                           (*out) << example_prefix;
                    } else
                        (*out) << QString((*code_tag) -> text());
                }

                (*out) << example_prefix << Logger::nl;
            break;}

            case Html::Tag::tg_ul: {
                Html::Set lis = (*tag) -> children();

                (*out) << example_prefix << Logger::nl;

                for(Html::Set::Iterator li = lis.begin(); li != lis.end(); li++) {
                    (*out) << list_prefix << QString(clearLine((*li) -> texts())) << Logger::nl;
                }

                (*out) << example_prefix << Logger::nl;
            break;}

            case Html::Tag::tg_newline: { break;}

            case Html::Tag::tg_text: { break;}

            case Html::Tag::tg_div: {
                if ((*tag) -> rawClasses() != QByteArrayLiteral("method-source-code"))
                    Logger::obj().write(
                        QLatin1Literal("RubydocParser"),
                        QLatin1Literal("Unknown tag type in description: ") % (*tag) -> name() %
                            QLatin1Literal(" in file: ") % inpath
                    );
            break;}

            default: {
                Logger::obj().write(
                    QLatin1Literal("RubydocParser"),
                    QLatin1Literal("Unknown tag type in description: ") % (*tag) -> name() %
                        QLatin1Literal(" in file: ") % inpath
                );
            }
        }
    }
}

void RubydocParser::procMethod(const QString & signature, Html::Tag * method_block, const QByteArray & target_prefix, const QByteArray & method_prefix, const QByteArray & description_prefix, const QByteArray & description_example_prefix, const QByteArray & description_list_prefix, const QByteArray & border, QTextStream * out, const QString & inpath) {
    Html::Set divs = method_block -> find("div");

    QString signatures;
    uint sigs_count = 0;

    Html::Tag * aliases_block = 0;
    Html::Tag * description_block = 0;

    for(Html::Set::ConstIterator div = divs.cbegin(); div != divs.cend(); div++) {
        QByteArray div_class = (*div) -> rawClasses();

        if (div_class == QByteArrayLiteral("method-heading")) {
            ++sigs_count;

            Html::Tag * mseq = (*div) -> findFirst(".method-callseq");

            if (sigs_count > 1)
                signatures.append(description_prefix);

            if (mseq) {
                signatures.append(
                    QString(clearLine(mseq -> text()))
                        .replace(QChar(8594), QLatin1Literal("#=>")) %
                            Logger::nl
                );
            } else {
                Html::Tag * mname = (*div) -> findFirst(".method-name");
                Html::Tag * margs = (*div) -> findFirst(".method-args");

                QString msig;

                if (mname) {
                    msig.append(mname -> text());

                    if (margs)
                        msig.append(margs -> text());

                    signatures.append(msig % Logger::nl);
                } else {
                    Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant parse method name in file: ") % inpath, QStringList() << divs[0] -> texts());
                }
            }
        } else if (div_class == QByteArrayLiteral("aliases")) {
            aliases_block = (*div);
        } else description_block = (*div);
    }

    (*out) << Logger::nl << Logger::nl;

    procDescription(description_block -> children(), description_prefix, description_example_prefix, description_list_prefix, border, out, inpath);

    // print all signatures
    (*out) << description_prefix << signatures << description_prefix << Logger::nl;

    (*out) << method_prefix << signature << '(';

    if (sigs_count == 1) {
        int pos, len;

        if (findSimbolsSub(signatures, '(', ')', pos, len)) {
            (*out) << signatures.mid(pos, len);
        } else {
            if (signature[0] == '[') {
                for(QString::Iterator ch = signatures.begin() + 1; ch != signatures.end(); ch++)
                    if (*ch == ']')
                        break;
                    else {
                        (*out) << *ch;
                    }
            } else {
                int pos = signatures.indexOf(signature[0]);

                if (pos == -1) {
                    pos = 0;
                    Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant parse method inner args:") % signature % QLatin1Literal("in file: ") % inpath);
                }
                else {
                    pos += signature.length();
                    if (signatures[pos] == 32)
                        ++pos;
                }

                for(QString::Iterator ch = signatures.begin() + pos; ch != signatures.end(); ch++)
                    if (*ch != '_' && !(*ch).isLetterOrNumber())
                        break;
                    else {
                        (*out) << *ch;
                    }
            }
        }
    } else {
        (*out) << "*several_variants";
    }

    (*out) << ')' << Logger::nl << target_prefix << "end" << Logger::nl;

    if (aliases_block) {
        QString alias_name = aliases_block -> findFirst("a") -> text();

        (*out) << target_prefix << "alias " << alias_name << ' ' << signature << Logger::nl;
    }
}

bool RubydocParser::parseFile(const QString & inpath, const QString & outpath) {
    QByteArray description_prefix("# ");
    QByteArray description_list_prefix("#    - ");
    QByteArray description_example_prefix("#       ");
    QByteArray target_prefix("    ");

    QByteArray border(80, '-');
    border[0] = '#';

    QFile datafile(inpath);

    if (datafile.open(QFile::ReadOnly | QFile::Text)) {
        QFile outfile(outpath);

        if (outfile.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&outfile);

            out << "# encoding: UTF-8" << Logger::nl;
            out << "# GENERATED BY @JB FU" << Logger::nl << Logger::nl << Logger::nl;

            Html::Page page(
                &datafile,
                Html::Decoding::charset_utf8,
                (Html::Page::ParseFlags)(Html::Page::pf_skip_comment | Html::Page::pf_skip_links_decoding)
            );

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

            Html::Tag * doc_description = doc_block -> findFirst("#description");

            if (!doc_description) {
                Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant parse doc description in file: ") % inpath);
                datafile.close(); out.flush(); outfile.close();
                return false;
            }

            Html::Set descrition_parts = doc_description -> children();

            procDescription(descrition_parts, description_prefix, description_example_prefix, description_list_prefix, border, &out, inpath);

            out << Logger::nl; // one extra line before begin of the class description

            QByteArray target_class = doc_header -> rawClasses();
            QByteArray target_name = doc_header -> text();
            QByteArray parent_name;

            Html::Tag * parent_tag = metadata_block -> findFirst("#parent-class-section p a");

            if (parent_tag)
                parent_name = parent_tag -> text();

            /////////////////// REMOVE ME LATER
            if (target_class != "class" && target_class != "module") {
                Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("New target type: ") % target_class % QLatin1Literal("  in file: ") % inpath);
            }
            //////////////////////////////////////

            out << target_class << ' ' << target_name;

            if (!parent_name.isEmpty())
                out << " < " << parent_name;

            out << Logger::nl;


            Html::Set includes_texts = metadata_block -> find("#includes-section li a text");

            if (!includes_texts.isEmpty()) {
                for(Html::Set::Iterator include_tag = includes_texts.begin(); include_tag != includes_texts.end(); include_tag++) {
                    out << target_prefix << "include " << QString((*include_tag) -> text()) << Logger::nl;
                }
            }


//            /////////////////////////////////////////////////

            Html::Tag * methods_list = metadata_block -> findFirst("#method-list-section");
            Html::Set methods_list_children = methods_list -> find("li a");

            QHash<QString, QString> methods_formats;

            for(Html::Set::Iterator chld_tag = methods_list_children.begin(); chld_tag != methods_list_children.end(); chld_tag++) {
                QString sig = (*chld_tag) -> text();

                methods_formats.insert(
                    (*chld_tag) -> link(),
                    sig[0] == ':' ? sig.mid(2) : sig.mid(1)
                );
            }

//            /////////////////////////////////////////////////

            Html::Set sections = doc_block -> find(".section");

            QByteArray constants_section("constants-list");

            QByteArray public_class_methods_section("public-class-method-details");
            QByteArray public_instance_methods_section("public-instance-method-details");

//            QByteArray private_class_methods_section("private-class-method-details"); // ???
            QByteArray private_instance_methods_section("private-instance-method-details");

            QByteArray methods_prefix;

            for(Html::Set::Iterator section_tag = sections.begin(); section_tag != sections.end(); section_tag++) {
                const QByteArray & id = (*section_tag) -> id();

                if (id == constants_section) {
                    Html::Tag * list_tag = (*section_tag) -> findFirst("dl");

                    if (list_tag -> hasChildren()) {
                        Html::Set constants = list_tag -> children();

                        for(Html::Set::Iterator const_tag = constants.begin(); const_tag != constants.end(); const_tag++) {
                            out << target_prefix << ((*const_tag) -> text()) << " # " << ((*++const_tag) -> text()) << Logger::nl;
                        }
                    }
                } else {
                    if (id == public_class_methods_section) {
                        methods_prefix = QByteArray("public def self.");
                    } else if (id == public_instance_methods_section) {
                        methods_prefix = QByteArray("public def ");
                    } else if (id == private_instance_methods_section) {
                        methods_prefix = QByteArray("private def ");
                    }

                    Html::Set methods = (*section_tag) -> find(".method-detail");

                    for(Html::Set::Iterator method_tag = methods.begin(); method_tag != methods.end(); method_tag++) {
                        Html::Tag * linker = (*method_tag) -> findFirst(">a");

                        QString signature('#' % linker -> attr(QByteArrayLiteral("name")));

                        if (methods_formats.contains(signature))
                            signature = methods_formats[signature];
                        else {
                            Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant find signature for method: ") % signature % QLatin1Literal("  in file: ") % inpath);
                            signature.clear();
                        }

                        procMethod(
                            signature,
                            *method_tag,
                            target_prefix,
                            target_prefix + methods_prefix,
                            target_prefix + description_prefix,
                            target_prefix + description_example_prefix,
                            target_prefix + description_list_prefix,
                            target_prefix % border, &out, inpath
                        );
                    }
                }
            }

            out << "end";

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

RubydocParser::RubydocParser(QObject * parent) : QObject(parent) {
//    ThreadUtils::obj().run(
//        this, &FilesProcManager::cleanerProc,
//        new Func()
//    );
}

RubydocParser::~RubydocParser() {

}

bool RubydocParser::parse(const QString & inpath, const QString & outpath) {


    return true;
}
