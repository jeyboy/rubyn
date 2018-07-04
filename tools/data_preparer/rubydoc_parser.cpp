#include "rubydoc_parser.h"

#include "data_obj.h"

#include "tools/thread_utils.h"
#include "tools/html/html_page.h"

#include "controls/logger.h"
#include "misc/dir.h"
#include "misc/format.h"

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
                    case ')':
                    case 44: // ,
                    case 32: {
                        ++ptr;
                        continue;
                    break;}
                }
            break;}

            case 44: {
                if (*(ptr + 1) == ')') { // ignore typo like (a,)
                    ++ptr;
                    continue;
                }
            break;}
        }

        res.append(*ptr);
        ++ptr;
    }

    return res;
}

void RubydocParser::writeLine(const QByteArray & prefix, const QByteArray & datum, QTextStream * out, const int & max_line_len) {
    if (datum.length() <= max_line_len) {
        (*out) << prefix << datum << Logger::nl;
        return;
    }

    char buff[datum.length()];
    int pos = -1, len = 0, qty = 0;

    const char * datum_buff = datum.constData();

    while(*datum_buff) {
        for(len = 0, pos = -1; ; datum_buff++, len++) {
            if (len > max_line_len) {
                if (pos > 0) {
                    datum_buff -= (len - pos);
                    buff[pos] = 0;
                    ++qty;
                    break;
                }
            }

            if ((*datum_buff) == ' ') {
               pos = len;
            }

            buff[len] = *datum_buff;

            if (!*datum_buff) {
                ++qty;
                break;
            }
        }

        (*out) << prefix;

        if (qty > 1)
            (*out) << ' ';

        (*out) << buff << Logger::nl;
    }
}

void RubydocParser::procHeader(Html::Tag * h, const QByteArray & prefix, const QByteArray & border, QTextStream * out) {
    (*out)
        << border
        << Logger::nl
        << prefix;

    Html::Set hchilds = h -> children();

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
}

void RubydocParser::procDescription(const Html::Set & parts, const QByteArray & prefix, const QByteArray & example_prefix, const QByteArray & list_prefix, const QByteArray & border, QTextStream * out, const QString & inpath) {
    int curr_uid = Html::Tag::tg_none;
    int last_uid = curr_uid;

    for(Html::Set::ConstIterator tag = parts.cbegin(); tag != parts.cend(); tag++) {
        curr_uid = (*tag) -> tagID();

        switch(curr_uid) {
            case Html::Tag::tg_p: {
                Html::Set pparts = (*tag) -> children();
                QByteArray text;
                QByteArray child_texts;

                for(Html::Set::Iterator ptag = pparts.begin(); ptag != pparts.end(); ptag++) {
                    if ((*ptag) -> isLink()) {
                        child_texts = (*ptag) -> link();

                        QByteArrayList parts = child_texts.split('#');

                        if (parts.length() > 1 && parts[1].startsWith("method-")) {
                            child_texts = (*ptag) -> text();

                            if (child_texts[0] != '#' && child_texts[0] != ':')
                                child_texts.prepend(
                                    (parts[1][7] == 'i' ? QByteArrayLiteral("#") : QByteArrayLiteral("::"))
                                );

                            parts = parts[0].split('.');

                            child_texts = parts[0] + child_texts;
                        } else {
                            child_texts = (*ptag) -> texts();
                        }
                    } else {
                        child_texts = (*ptag) -> texts();
                    }

                    if (!child_texts.isEmpty()) {
                        if (!text.isEmpty())
                            child_texts.prepend(' ');

                        text = text % child_texts;
                    }
                }

                writeLine(prefix, clearLine(text), out);
                last_uid = curr_uid;
            break;}

            case Html::Tag::tg_h2: {
                procHeader((*tag), prefix, border, out);
            break;}

            case Html::Tag::tg_h3: {
                procHeader((*tag), prefix, border.mid(0, 60), out);
            break;}

            case Html::Tag::tg_h4: {
                procHeader((*tag), prefix, border.mid(0, 40), out);
            break;}

            case Html::Tag::tg_pre: {
                last_uid = curr_uid;

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

            case Html::Tag::tg_dl: {
                (*out) << Logger::nl;
                Html::Set list_items = (*tag) -> children();

                for(Html::Set::Iterator list_item_tag = list_items.begin(); list_item_tag != list_items.end(); list_item_tag++) {
                    Html::Tag * curr_tag = (*list_item_tag);
                    switch((*list_item_tag) -> tagID()) {
                        case Html::Tag::tg_dt: {
                            (*out) << prefix << "  * " << ((*list_item_tag) -> texts()) << Logger::nl;
                        break;}

                        case Html::Tag::tg_dd: {
                            (*out) << prefix << "      " << ((*list_item_tag) -> texts()) << Logger::nl;
                        break;}
                    }
                }

                (*out) << Logger::nl;
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

    if (last_uid == Html::Tag::tg_p)
        (*out) << example_prefix << Logger::nl;
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
                    QString(clearLine(mseq -> text())) % Logger::nl
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

    bool is_mask = false;
    QString sig_mask;

    if (sigs_count == 1) {
        int sig_pos, sig_len;

        if (findSimbolsSub(signatures, '(', ')', sig_pos, sig_len)) {
            sig_mask = signatures.mid(sig_pos, sig_len).trimmed();
            is_mask = sig_mask.endsWith('.');
        }
    }

    if (sigs_count > 1 || is_mask) { // print all signatures
        (*out) << description_prefix << signatures << description_prefix << Logger::nl;
    }

    (*out) << method_prefix << signature << '(';

    if (!is_mask && sigs_count == 1) {
        if (!sig_mask.isEmpty()) {
            (*out) << sig_mask;
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
        Html::Tag * a = aliases_block -> findFirst("a");
        QString alias_name;

        if (a)
            alias_name = QString(a -> text());
        else
            alias_name = QString(aliases_block -> texts()).section(':', 1).trimmed();

        (*out) << target_prefix << "alias " << alias_name << ' ' << signature << Logger::nl;
    }
}

bool RubydocParser::parseFile(const QString & path, const QString & name, QTextStream & out, const QByteArray & offset, const bool & attach) {
    QString inpath(path % '/' % name);

    QFile datafile(inpath);

    if (datafile.open(QFile::ReadOnly | QFile::Text)) {
        Html::Page page(
            &datafile,
            Html::Decoding::charset_utf8,
            (Html::Page::ParseFlags)(Html::Page::pf_skip_comment | Html::Page::pf_skip_links_decoding | Html::Page::pf_simplify_mnemonics)
        );

        Html::Tag * metadata_block = page.findFirst("#metadata");

        if (!metadata_block) {
            Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant parse metadata block in file: ") % inpath);
            datafile.close();
            return false;
        }

        Html::Tag * doc_block = page.findFirst("#documentation");

        if (!doc_block) {
            Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant parse documentation block in file: ") % inpath);
            datafile.close();
            return false;
        }

        if (!attach) {
            Html::Tag * doc_header = doc_block -> findFirst("h1");

            if (!doc_header) {
                Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant parse doc header in file: ") % inpath);
                datafile.close();
                return false;
            }

            Html::Tag * doc_description = doc_block -> findFirst("#description");

            if (!doc_description) {
                Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant parse doc description in file: ") % inpath);
                datafile.close();
                return false;
            }

            Html::Set descrition_parts = doc_description -> children();

            procDescription(
                descrition_parts,
                offset % description_prefix,
                offset % description_example_prefix,
                offset % description_list_prefix,
                offset % border, &out, inpath
            );

            out << Logger::nl; // one extra line before begin of the class description

            QByteArray target_class = doc_header -> rawClasses();
            QByteArray target_name = doc_header -> text();
            QByteArray parent_name;

            Html::Tag * parent_tag = metadata_block -> findFirst("#parent-class-section p");

            if (parent_tag) {
                Html::Tag * parent_a_tag = parent_tag -> findFirst("a");

                if (parent_a_tag)
                    parent_tag = parent_a_tag;

                parent_name = parent_tag -> text();

                if (parent_name[0] < 'A' || parent_name[0] > 'Z') { // if we have some trash text
                    for(int i = 1; i < parent_name.length(); i++) {
                        if (parent_name[i] >= 'A' && parent_name[i] <= 'Z') {
                            parent_name = parent_name.mid(i);
                            break;
                        }
                    }
                }
            }

            /////////////////// REMOVE ME LATER
            if (target_class != "class" && target_class != "module") {
                Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("New target type: ") % target_class % QLatin1Literal("  in file: ") % inpath);
            }
            //////////////////////////////////////

            out << offset << target_class << ' ' << target_name;

            if (!parent_name.isEmpty())
                out << " < " << parent_name;

            out << Logger::nl;


            Html::Set includes_texts = metadata_block -> find("#includes-section li a text");

            if (!includes_texts.isEmpty()) {
                for(Html::Set::Iterator include_tag = includes_texts.begin(); include_tag != includes_texts.end(); include_tag++) {
                    out << offset << target_prefix << "include " << QString((*include_tag) -> text()) << Logger::nl;
                }
            }
        }

        /////////////////////////////////////////////////

        Html::Tag * methods_list = metadata_block -> findFirst("#method-list-section");
        QHash<QString, QString> methods_formats;

        if (methods_list) {
            Html::Set methods_list_children = methods_list -> find("li a");

            for(Html::Set::Iterator chld_tag = methods_list_children.begin(); chld_tag != methods_list_children.end(); chld_tag++) {
                QString sig = (*chld_tag) -> text();

                methods_formats.insert(
                    (*chld_tag) -> link(),
                    sig[0] == ':' ? sig.mid(2) : sig.mid(1)
                );
            }
        }
        /////////////////////////////////////////////////

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
                    out << Logger::nl;
                    Html::Set constants = list_tag -> children();
                    Html::Tag * dt_tag = 0;

                    for(Html::Set::Iterator const_tag = constants.begin(); const_tag != constants.end(); const_tag++) {
                        switch((*const_tag) -> tagID()) {
                            case Html::Tag::tg_dt: {
                                if (dt_tag) {
                                    out << offset << target_prefix << (dt_tag -> texts()) << " = nil # Using for indexing. Value is unknown" << Logger::nl << Logger::nl;
                                }

                                dt_tag = (*const_tag);
                            break;}

                            case Html::Tag::tg_dd: {
                                out << offset << target_prefix << description_prefix << ((*const_tag) -> texts()) << Logger::nl;

                                if (dt_tag) {
                                    out << offset << target_prefix << (dt_tag -> texts()) << " = nil # Using for indexing. Value is unknown" << Logger::nl << Logger::nl;
                                    dt_tag = 0;
                                }
                            break;}
                        }
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
                        offset % target_prefix,
                        offset % target_prefix + methods_prefix,
                        offset % target_prefix + description_prefix,
                        offset % target_prefix + description_example_prefix,
                        offset % target_prefix + description_list_prefix,
                        offset % target_prefix % border, &out, inpath
                    );
                }
            }
        }

        Html::Tag * namespaces = metadata_block -> findFirst("#namespace-list-section");

        if (namespaces) {
            Html::Set entries = namespaces -> find("li a");

            QStringList snames;

            for(Html::Set::Iterator entry = entries.begin(); entry != entries.end(); entry++) {
                Html::Tag * tag = *entry;

                QByteArray file_path = tag -> link();
                QByteArrayList namespace_name_parts = tag -> text().split(':');

                if (QChar(namespace_name_parts.last()[0]).isLower()) {
                    file_path.prepend('1');
                    snames.prepend(file_path);
                } else {
                    file_path.prepend('2');
                    snames.append(file_path);
                }
            }

            for(QStringList::Iterator sname = snames.begin(); sname != snames.end(); sname++) {
                out << Logger::nl << Logger::nl;

                bool is_attach = (*sname)[0] == '1';
                bool res = parseFile(path, (*sname).mid(1), out, offset % target_prefix, is_attach);
                if (res && !is_attach)
                    out << offset % target_prefix << "end" << Logger::nl;
            }
        }

        datafile.close();
    } else {
        Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant open file: ") % inpath);
        return false;
    }

    return true;
}

bool RubydocParser::initParseFile(const QString & path, const QString & name, const QString & outpath, const QByteArray & offset) {
    QFile outfile(outpath);

    if (outfile.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&outfile);
        out.setCodec("UTF-8");

        out << "# encoding: UTF-8" << Logger::nl;
        out << "# GENERATED BY @JB FU" << Logger::nl << Logger::nl << Logger::nl;

        bool res = parseFile(path, name, out, offset);
        if (res)
            out << "end";

        out.flush();
        outfile.close();
        return res;
    } else {
        Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant open output file: ") % outpath);
        return false;
    }
}

bool RubydocParser::parseFolder(const QString & path, const QString & outpath) {
    QDirIterator files_it(path, QDir::Files | QDir::Hidden, QDirIterator::Subdirectories);

    while(files_it.hasNext()) {
        QString path = files_it.next();
        QString dir_name = files_it.fileName();

        if (dir_name[0].isUpper()) {
            QString name = dir_name.section('.', 0, 0);
            Info::camelcaseToUnderscore(name);

            qDebug() << "!!!!!" << path;

            initParseFile(
                path.mid(0, path.length() - dir_name.length()),
                dir_name,
                outpath % '/' % name % QLatin1Literal(".rb")
            );
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
    if (!Dir::createPath(outpath))
        return false;

    return parseFolder(inpath, outpath);
}
