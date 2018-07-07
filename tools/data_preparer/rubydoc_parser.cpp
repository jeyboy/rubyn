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

//TODO: refactor required
void RubydocParser::writeLine(const QByteArray & datum, QStringList & out, const char & prefix, const int & max_line_len) {
    if (datum.length() <= max_line_len) {
        out << datum;
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

        QByteArray str(buff);

        if (qty > 1)
            str.prepend(' ');

        out << str.prepend(prefix);
    }
}

void RubydocParser::procHeader(Html::Tag * h, QStringList & out, const char & prefix) {
    QByteArray str;

    Html::Set hchilds = h -> children();

    for(Html::Set::Iterator htag = hchilds.begin(); htag != hchilds.end(); htag++) {
        if ((*htag) -> tagID() == Html::Tag::tg_span)
            break;
        else
            str.append((*htag) -> text());
    }

    out << str.prepend(prefix);
}

void RubydocParser::procDescription(const Html::Set & parts, QStringList & out, const QString & inpath) {
    int curr_uid = Html::Tag::tg_none;

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

                writeLine(clearLine(text), out, p_prefix);
            break;}

            case Html::Tag::tg_h2: {
                procHeader((*tag), out, h2_prefix);
            break;}

            case Html::Tag::tg_h3: {
                procHeader((*tag), out, h3_prefix);
            break;}

            case Html::Tag::tg_h4: {
                procHeader((*tag), out, h4_prefix);
            break;}

            case Html::Tag::tg_pre: {
                Html::Set code_parts = (*tag) -> children();

                out << QLatin1String();
                QString & str = out.last();

                for(Html::Set::Iterator code_tag = code_parts.begin(); code_tag != code_parts.end(); code_tag++) {
                    if ((*code_tag) -> isNewline()) {
                        out << QLatin1String();
                        str = out.last();
                    }
                    else str.append((*code_tag) -> text());
                }
            break;}

            case Html::Tag::tg_ul: {
                Html::Set lis = (*tag) -> children();

                for(Html::Set::Iterator li = lis.begin(); li != lis.end(); li++) {
                    out << clearLine((*li) -> texts()).prepend(li_prefix);
                }
            break;}

            case Html::Tag::tg_dl: {
                Html::Set list_items = (*tag) -> children();

                for(Html::Set::Iterator list_item_tag = list_items.begin(); list_item_tag != list_items.end(); list_item_tag++) {
                    switch((*list_item_tag) -> tagID()) {
                        case Html::Tag::tg_dt: {
                            out << ((*list_item_tag) -> texts()).prepend(dt_prefix);
                        break;}

                        case Html::Tag::tg_dd: {
                            out << ((*list_item_tag) -> texts()).prepend(dd_prefix);
                        break;}
                    }
                }
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

void RubydocParser::procMethod(const QString & signature, Html::Tag * method_block, DataMethod & out, const QString & inpath) {
    Html::Set divs = method_block -> find("div");

    uint sigs_count = 0;

    Html::Tag * aliases_block = 0;
    Html::Tag * description_block = 0;

    for(Html::Set::ConstIterator div = divs.cbegin(); div != divs.cend(); div++) {
        QByteArray div_class = (*div) -> rawClasses();

        if (div_class == QByteArrayLiteral("method-heading")) {
            ++sigs_count;

            Html::Tag * mseq = (*div) -> findFirst(".method-callseq");

            if (mseq) {
                out.signatures.append(
                    QString(clearLine(mseq -> text()))
                );
            } else {
                Html::Tag * mname = (*div) -> findFirst(".method-name");
                Html::Tag * margs = (*div) -> findFirst(".method-args");

                QString msig;

                if (mname) {
                    msig.append(mname -> text());

                    if (margs)
                        msig.append(margs -> text());

                    out.signatures.append(msig);
                } else {
                    Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant parse method name in file: ") % inpath, QStringList() << divs[0] -> texts());
                }
            }
        } else if (div_class == QByteArrayLiteral("aliases")) {
            aliases_block = (*div);
        } else description_block = (*div);
    }

    procDescription(description_block -> children(), out.description, inpath);

    bool is_mask = false;

    out.args_mask = out.signatures.first();

    if (sigs_count == 1) {
        int sig_pos, sig_len;

        if (findSimbolsSub(out.args_mask, '(', ')', sig_pos, sig_len)) {
            out.args_mask = out.args_mask.mid(sig_pos, sig_len).trimmed();
            is_mask = out.args_mask.endsWith('.');
        }
    }

//    if (sigs_count > 1 || is_mask) { // print all signatures
//        (*out) << description_prefix << signatures << description_prefix << Logger::nl;
//    }

//    (*out) << method_prefix << signature << '(';

    if (!is_mask && sigs_count == 1) {
        if (out.args_mask.isEmpty()) {
            QString first_signature = out.signatures.first();

            if (signature[0] == '[') {
                for(QString::Iterator ch = first_signature.begin() + 1; ch != first_signature.end(); ch++)
                    if (*ch == ']')
                        break;
                    else {
                        out.args_mask.append(*ch);
                    }
            } else {
                int pos = first_signature.indexOf(signature[0]);

                if (pos == -1) {
                    pos = 0;
                    Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant parse method inner args:") % signature % QLatin1Literal("in file: ") % inpath);
                }
                else {
                    pos += signature.length();
                    if (first_signature[pos] == 32)
                        ++pos;
                }

                for(QString::Iterator ch = first_signature.begin() + pos; ch != first_signature.end(); ch++) {
                    if (*ch != '_' && !(*ch).isLetterOrNumber())
                        break;
                    else {
                        out.args_mask.append(*ch);
                    }
                }
            }
        }
    } else {
        out.args_mask = QLatin1Literal("*several_variants");
    }

//    (*out) << ')' << Logger::nl << target_prefix << "end" << Logger::nl;

    if (aliases_block) {
        Html::Tag * a = aliases_block -> findFirst("a");

        if (a)
            out.alias_name = QString(a -> text());
        else
            out.alias_name = QString(aliases_block -> texts()).section(':', 1).trimmed();

//        (*out) << target_prefix << "alias " << alias_name << ' ' << signature << Logger::nl;
    }
}

bool RubydocParser::parseFile(const QString & path, const QString & name, DataObj & out, const uint & level, const bool & attach) {
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
            out.level = level;

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

            procDescription(descrition_parts, out.description, inpath);

            out.obj_type = doc_header -> rawClasses();
            out.name = doc_header -> text();

            Html::Tag * parent_tag = metadata_block -> findFirst("#parent-class-section p");

            if (parent_tag) {
                Html::Tag * parent_a_tag = parent_tag -> findFirst("a");

                if (parent_a_tag)
                    parent_tag = parent_a_tag;

                out.parent = parent_tag -> text();

                if (out.parent[0] < 'A' || out.parent[0] > 'Z') { // if we have some trash text
                    for(int i = 1; i < out.parent.length(); i++) {
                        if (out.parent[i] >= 'A' && out.parent[i] <= 'Z') {
                            out.parent = out.parent.mid(i);
                            break;
                        }
                    }
                }
            }

            /////////////////// REMOVE ME LATER
            if (out.obj_type != "class" && out.obj_type != "module") {
                Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("New target type: ") % out.obj_type % QLatin1Literal(" in file: ") % inpath);
            }
            //////////////////////////////////////

            Html::Set includes_texts = metadata_block -> find("#includes-section li a text");

            if (!includes_texts.isEmpty()) {
                for(Html::Set::Iterator include_tag = includes_texts.begin(); include_tag != includes_texts.end(); include_tag++) {
                    out.includes << QString((*include_tag) -> text());
                }
            }
        }

        /////////////////////////////////////////////////

        Html::Tag * methods_list = metadata_block -> findFirst("#method-list-section");
        QHash<QByteArray, QByteArray> methods_formats;

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

        LexerMeanType methods_prefix;

        for(Html::Set::Iterator section_tag = sections.begin(); section_tag != sections.end(); section_tag++) {
            const QByteArray & id = (*section_tag) -> id();

            if (id == constants_section) {
                Html::Tag * list_tag = (*section_tag) -> findFirst("dl");

                if (list_tag -> hasChildren()) {
                    Html::Set constants = list_tag -> children();
                    Html::Tag * dt_tag = 0;

                    for(Html::Set::Iterator const_tag = constants.begin(); const_tag != constants.end(); const_tag++) {
                        switch((*const_tag) -> tagID()) {
                            case Html::Tag::tg_dt: {
                                if (dt_tag) {
                                    out.constants.insert(dt_tag -> texts(), QLatin1Literal("No description"));
//                                    out << offset << target_prefix << (dt_tag -> texts()) << " = nil # Using for indexing. Value is unknown" << Logger::nl << Logger::nl;
                                }

                                dt_tag = (*const_tag);
                            break;}

                            case Html::Tag::tg_dd: {
                                if (!dt_tag) {
                                    Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Wrong order in constants list: ") % out.name % QLatin1Literal(" in file: ") % inpath);
                                } else {
                                    out.constants.insert(dt_tag -> texts(), (*const_tag) -> texts());
                                    dt_tag = 0;
                                }
                            break;}
                        }
                    }
                }
            } else {
                if (id == public_class_methods_section) {
                    methods_prefix = (LexerMeanType)(lmt_public | lmt_object_method);
                } else if (id == public_instance_methods_section) {
                    methods_prefix = (LexerMeanType)(lmt_public | lmt_instance_method);
                } else if (id == private_instance_methods_section) {
                    methods_prefix = (LexerMeanType)(lmt_private | lmt_instance_method);
                }

                Html::Set methods = (*section_tag) -> find(".method-detail");

                for(Html::Set::Iterator method_tag = methods.begin(); method_tag != methods.end(); method_tag++) {
                    Html::Tag * linker = (*method_tag) -> findFirst(">a");

                    QByteArray meth_name = linker -> attr(QByteArrayLiteral("name"));
                    QByteArray signature('#' % meth_name);

                    if (methods_formats.contains(signature))
                        signature = methods_formats[signature];
                    else {
                        Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant find signature for method: ") % signature % QLatin1Literal(" in file: ") % inpath);
                    }

                    DataMethod & meth = out.methods[meth_name];
                    meth.lex_type = methods_prefix;

                    procMethod(signature, *method_tag, meth, inpath);
                }
            }
        }

        Html::Tag * namespaces = metadata_block -> findFirst("#namespace-list-section");

        if (namespaces) {
            Html::Set entries = namespaces -> find("li a");

            for(Html::Set::Iterator entry = entries.begin(); entry != entries.end(); entry++) {
                Html::Tag * tag = *entry;

                QByteArray sname = tag -> text();
                QByteArray file_path = tag -> link();
                QByteArrayList namespace_name_parts = sname.split(':');

                if (QChar(namespace_name_parts.last()[0]).isLower()) {
                    parseFile(path, file_path, out, level, true);
                } else {
                    parseFile(path, file_path, out.namespaces[sname], level + 1);
                }
            }
        }

        datafile.close();
    } else {
        Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant open file: ") % inpath);
        return false;
    }

    return true;
}

bool RubydocParser::parseFolder(const QString & path) {
    bool ignore_folders = false;

    QDirIterator files_it(path, QDir::Files | QDir::Hidden);

    while(files_it.hasNext()) {
        QString filepath = files_it.next();
        QString filename = files_it.fileName();

        if (filename[0].isUpper()) {
            ignore_folders = true;

            qDebug() << "!!!!!" << filepath;

            QString name = filename.section('.', 0, 0);

            bool is_attach = parsed_objs.contains(name);

            parseFile(path, filename, parsed_objs[name], 0, is_attach);
        }
    }

    if (ignore_folders)
        return true;

    QDirIterator dir_it(path, QDir::AllDirs | QDir::NoDotAndDotDot);

    while(dir_it.hasNext()) {
        QString dir_path = dir_it.next();

        parseFolder(dir_path);
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

bool RubydocParser::parse(const QString & inpath) {
    return parseFolder(inpath);
}

bool RubydocParser::saveParsedDatum(const QString & outpath) {
    if (!Dir::createPath(outpath))
        return false;

    const QByteArray description_prefix         = QByteArray("# ");
    const QByteArray description_list_prefix    = QByteArray("#    - ");
    const QByteArray description_example_prefix = QByteArray("#       ");
    const QByteArray target_prefix              = QByteArray("    ");
    const QByteArray h2_border                  = QByteArray(80, '-').prepend('#');
    const QByteArray h3_border                  = h2_border.mid(0, 61);
    const QByteArray h4_border                  = h2_border.mid(0, 41);

    for(QHash<QString, DataObj>::Iterator obj = parsed_objs.begin(); obj != parsed_objs.end(); obj++) {
        {
            QString filename = obj.key();
            Info::camelcaseToUnderscore(filename);
            filename = outpath % '/' % filename % QLatin1Literal(".rb");

            DataObj & data_obj = obj.value();
            QFile outfile(filename);

            if (outfile.open(QFile::WriteOnly | QFile::Text)) {
                QTextStream out(&outfile);
                out.setCodec("UTF-8");

                QByteArray level_padding(level * target_prefix.length(), ' ');

                out << "# encoding: UTF-8" << Logger::nl;
                out << "# GENERATED BY @JB FU" << Logger::nl << Logger::nl;

                if (!data_obj.description.isEmpty()) {
                    for(QStringList::Iterator desc_line = data_obj.description.begin(); desc_line != data_obj.description.end(); desc_line++) {
                        QStringRef & str = (*desc_line).midRef(1);

                        switch((*desc_line)[0]) {
                            case h2_prefix:     {
                                out << h2_border << Logger::nl << description_prefix << str << Logger::nl << h2_border << Logger::nl << Logger::nl;
                            continue;}
                            case h3_prefix:     {
                                out << h3_border << Logger::nl << description_prefix << str << Logger::nl << h3_border << Logger::nl << Logger::nl;
                            continue;}
                            case h4_prefix:     {
                                out << h4_border << Logger::nl << description_prefix << str << Logger::nl << h4_border << Logger::nl << Logger::nl;
                            continue;}

                            case p_prefix:      {
                                out << description_prefix << str << Logger::nl;
                            break;}
                            case li_prefix:     {
                                out << description_list_prefix << str << Logger::nl;
                            break;}
                            case pre_prefix:    {
                                out << description_example_prefix << str << Logger::nl;
                            break;}
                            case dt_prefix:     {

                            break;}
                            case dd_prefix:     {

                            break;}
                            case newline_prefix:     {

                            break;}
                        }

                        out << (*desc_line).midRef(1) << Logger::nl;
                    }
                }

                out.flush();
                outfile.close();
            } else {
                Logger::obj().write(QLatin1Literal("RubydocParser"), QLatin1Literal("Cant open output file: ") % filename);
                return false;
            }
        }
    }

    return true;
}
