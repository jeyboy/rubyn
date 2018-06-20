#include "html_page.h"

#include <qdebug.h>

using namespace Html;

//// remove me later
Page::Page(Tag * root_tag, const char * str_data, const Decoding::CharsetType & doc_charset, const ParseFlags & parse_flags)
    : root(0), pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
    parse(str_data, root_tag);
}
Page::Page(Tag * root_tag, const QByteArray & str, const Decoding::CharsetType & doc_charset, const ParseFlags & parse_flags)
   : root(0), pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
   parse(str.constData(), root_tag);
}
Page::Page(Tag * root_tag, const QString & str, const Decoding::CharsetType & doc_charset, const ParseFlags & parse_flags)
    : root(0), pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
    parse(QSTR_TO_CHAR(str), root_tag);
}
//////////////////////////
//////////////////////////

Page::Page(QIODevice * device, const Decoding::CharsetType & doc_charset, const ParseFlags & parse_flags)
    : pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
    QByteArray data = device -> readAll();
    parse(data.constData(), INIT_ROOT_TAG);
}
Page::Page(const QByteArray & str, const Decoding::CharsetType & doc_charset, const ParseFlags & parse_flags)
    : pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
    parse(str.constData(), INIT_ROOT_TAG);
}
Page::Page(const QString & str, const Decoding::CharsetType & doc_charset, const ParseFlags & parse_flags)
    : pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
    parse(QSTR_TO_CHAR(str), INIT_ROOT_TAG);
}
Page::Page(const char * str_data, const Decoding::CharsetType & doc_charset, const ParseFlags & parse_flags)
    : pflags(parse_flags), sflags(sf_none), charset(doc_charset)
{
    parse(str_data, INIT_ROOT_TAG);
}

Set Page::find(const Selector * selector, const bool & findFirst) const {
    return root -> children().find(selector, findFirst);
}
Set Page::find(const char * predicate) const {
    Selector selector(predicate);
    return find(&selector);
}
Tag * Page::findFirst(const char * predicate) const {
    Selector selector(predicate);
    Set set = find(&selector, true);
    return set.isEmpty() ? 0 : set.first();
}

void Page::parse(const char * data, Tag * root_tag) {
    Tag * elem = root_tag;
    PState state = content;
    const char *pdata = data, *sname = 0, *sval = 0, *ename = 0;
    bool has_cdata = false, is_xml = false; // cdata presents in text
    quint8 tag_flags = 0; // charset

    while(*pdata) {
        if (*pdata < 0) {
            tag_flags |= Decoding::decode_content;
            pdata++;
            continue;
        }

        if (*pdata == code_start && (state == in_val || state == code || state == raw_data || state == content)) {
            tag_flags |= Decoding::decode_mnemo;
        }

        if (*pdata < 32 && *pdata > 0) { // skip not printable trash
            if (sname && !NBUFF_VALID) sname++;

            pdata++;
            continue;
        }

        switch(state) {
            case content: {
                switch(*pdata) {
                    case space: {
                        if (sname && !NBUFF_VALID) sname++;
                    break;}

                    case open_tag: {
                        char chr = *(pdata + 2);

                        bool is_service = *(pdata + 1) == service_token;

                        if (is_service) {
                            if (chr == raw_data_token) {
                                state = raw_data;
                                goto next_step;
                            } else if (chr == comment_token) {
                                state = comment;
                                goto next_step;
                            } else
                                sflags = (StateFlags)(sflags | sf_html);
                        } else if (*(pdata + 1) == question_token) {
                            is_xml = true;
                            sflags = (StateFlags)(sflags | sf_xml);
                        }

                        if (NAME_BUFF_VALID) {
                            if (!(pflags & pf_skip_text))  {
                                QByteArray ar = NAME_BUFF;

                                if (has_cdata)
                                    ar.replace(tkn_scdata, 0).replace(tkn_ecdata,  0);

                                elem -> appendText(DECODE_NAME(ar));
                            }
                            has_cdata = false;
                        }

                        state = tag;
                        sname = pdata + 1;
                    break;}
                }
            break;}

            case val: {
                switch(*pdata) {
                    case close_tag:
                    case space: {
                        elem -> addAttr(NAME_BUFF, DECODE_NAME(VAL_BUFF));
                        sname = 0; sval = 0; ename = 0;
                        state = attr;
                        continue;
                    break;}
                }
            break;}

            case in_val: {
                switch(*pdata) {
                    case content_del1:
                    case content_del2: {
                        if (*sval == *pdata) {
                            sval++;
                            elem -> addAttr(NAME_BUFF, DECODE_NAME(VAL_BUFF));
                            sname = 0; sval = 0; ename = 0;
                            state = attr;
                        }
                    break;}
                }
            break;}

            case in_attr: {
                switch(*pdata) {
                    case content_del1:
                    case content_del2: {
                        if (*sname == *pdata) {
                            sname++;
                            ename = pdata;
                            state = attr;
                        }
                    break;}
                }
            break;}

            case tag_exit: {
                switch(*pdata) {
                    case close_tag: {
                        if (sflags < sf_use_doc_charset)
                            checkCharset(elem);

//                      use this check for strict verification (open tag is eql to close)
                        if (
                            (is_xml && *(pdata - 1) == close_tag_predicate) ||
                            elem -> isSolo() || (sname && checkTagClose(elem, NAME_BUFF.toLower()))
                        ) {
                            if (elem -> isFrame()) {
                                iframes << elem;
                                sflags = (StateFlags)(sflags | sf_has_iframes);
                            }

                            elem = elem -> parent();

                            if (!elem) {
                                elem = root;
                                sflags = (StateFlags)(sflags | sf_has_errors);
                            }
                        } else {
                            sflags = (StateFlags)(sflags | sf_has_errors);
                            qDebug() << "IGNORE CLOSING OF TAG: " << NAME_BUFF << " around " << QByteArray(pdata - 60, 60);

                            Tag * curr = elem -> parent();
                            QByteArray block_name = NAME_BUFF.toLower();
                            QByteArray buf;

                            // drop elem to nearest compatible tag
                            while(curr) {
                                buf.append(curr -> name()).append(" -> ");

                                if (curr -> name() == block_name) {
                                    elem = curr -> parent();
                                    qDebug() << "+++ TREE STATE CORRECTION: " << buf.append(elem -> name());
                                    break;
                                }

                                curr = curr -> parent();
                            }
                        }

                        state = content;
                        sname = pdata + 1;
                    break;}
                }
            break;}

            case code: { // TODO: cdata in javascript and styles is not catched by main stream // need to catch it here
                switch(*pdata) {
                    case space: {
                        if (sname && !NBUFF_VALID) sname++;
                    break;}

                    case open_tag: {
                        if (*(pdata + 1) == close_tag_predicate && elem -> isClosableBy(pdata + 2)) {
                            if (NAME_BUFF_VALID) {
                                if (!(pflags & pf_skip_text))
                                    elem -> appendText(NAME_BUFF);
                            }

                            pdata += 2;
                            sname = pdata;
                            state = tag_exit;
                        }
                    }
                }
            break;}

            case raw_data: {
                switch(*pdata) {
                    case close_tag: {
                        if (*(pdata - 1) == raw_data_end_token && *(pdata - 2) == raw_data_end_token) {
                            state = content;
                            has_cdata = true;
                        }
                    break;}

                    default:;
                }
            break;}

            case comment: {
                switch(*pdata) {
                    case close_tag: {
                        if (*(pdata - 1) == comment_token && *(pdata - 2) == comment_token) {
                            if (!(pflags & pf_skip_comment))
                                elem -> appendComment(NAME_BUFF);

                            sname = pdata + 1;
                            state = content;
                        }
                    }
                    default:;
                }
            break;}

            default: {
                switch(*pdata) {
                    case space: {
                        switch(state) {
                            case attr:
                            case val: {
                                if (NAME_BUFF_VALID)
                                    elem -> addAttr(NAME_BUFF, VAL_BUFF);

                                sval = 0; sname = 0; ename = 0;

                                if (*(pdata + 1) == content_del1 || *(pdata + 1) == content_del2) {
                                    state = in_attr;
                                    sname = ++pdata;
                                }
                                else {
                                    state = attr;
                                    sname = pdata + 1;
                                }
                            break; }

                            case tag: {
                                elem = elem -> appendTag(NAME_BUFF);
                                state = attr;
                                sname = pdata + 1;
                            break;}
                            default:;
                        }
                    break;}

                    case attr_rel: {
                        ename = pdata;
                        sval = pdata + 1;
                        if (*sval == content_del1 || *sval == content_del2) {
                            state = in_val;
                            pdata++;
                        }
                        else state = val;
                    break;}

                    case close_tag: {
                        switch(state) {
                            case attr:
                            case val: {
                                if (sname && *(pdata - 1) != question_token) // ignore ?>
                                    elem -> addAttr(NAME_BUFF, VAL_BUFF);

                                sname = 0; sval = 0; ename = 0;
                            break;}

                            case tag: {
                                elem = elem -> appendTag(NAME_BUFF);
                            break;}
                            default:;
                        }

                        state = content;

                        if (elem -> isSolo()) {
                            if (sflags < sf_use_doc_charset)
                                checkCharset(elem);

                            elem = elem -> parent();

                            if (!elem) {
                                elem = root;
                                sflags = (StateFlags)(sflags | sf_has_errors);
                            }

                        } else if (elem -> isCodeBlock()) {
                            state = code;
                        }

                        sname = pdata + 1;
                    break;}

                    case close_tag_predicate: {
                        switch (state) {
                            case attr_val: {
                                elem -> addAttr(NAME_BUFF, VAL_BUFF);
                                sname = 0; sval = 0; ename = 0;
                            }
                            case tag: {
                                if (*(pdata - 1) != open_tag) // <br/> ant etc
                                    elem = elem -> appendTag(NAME_BUFF);

                                state = tag_exit;
                                sname++;
                            break;}
                            case attr: state = tag_exit;
                            default: ;
                        }
                    break; }
                    default:;
                }
            }
        }

        next_step:
            pdata++;
    }
}

void Page::checkCharset(Tag * tag) {
    if (tag -> isMeta() || tag -> isXmlHead())
        proceedCharset(tag);
    else if (tag -> isHead())
        sflags = (StateFlags)(sflags | sf_use_user_charset);
}

void Page::proceedCharset(Tag * tag) { // refactor me: use qbytearray except string
    if (tag -> isXmlHead()) {
        QByteArray xml_encoding = tag -> value(tkn_encoding);
        if (!xml_encoding.isEmpty()) {
            charset = Decoding::charsetType(xml_encoding);
            sflags = (StateFlags)(sflags | sf_use_doc_charset);
        }
    } else {
        QByteArray meta = tag -> value(tkn_charset);
        if (meta.isEmpty()) {
            if (tag -> value(tkn_http_equiv).toLower() == tkn_content_type) {
                meta = tag -> value(tkn_content);

                int start_index = meta.indexOf(tkn_charset_attr);

                if (start_index != -1) { // not tested
                    start_index += tkn_charset_attr.length();
                    int end_index = meta.indexOf(' ', start_index);
                    meta = meta.mid(start_index, end_index == -1 ? -1 : (end_index - start_index));
                } else meta.clear();
            }
        }

        if (!meta.isEmpty()) {
            charset = Decoding::charsetType(meta);
            sflags = (StateFlags)(sflags | sf_use_doc_charset);
        }
    }
}

void Page::output() { qDebug() << (*root); }
