#ifndef HTML_TAG_H
#define HTML_TAG_H

#include "html_global.h"
#include "html_set.h"

#include <qhash.h>
#include <qdebug.h>

#define DEBUG_LIMIT_OUTPUT 10000

class QUrl;
class QDebug;

namespace Html {
    class Selector;

    class Tag {
        int _level;
        int _tag_id;
        int _tag_len;

        QHash<QByteArray, QByteArray> _attrs;
        QHash<QByteArray, bool> * _classes;
        Set _tags;
        Tag * _parent;
    protected:
        static QHash<QByteArray, int> list;

        const static QHash<int, bool> solo;
        const static QHash<int, bool> acceptable_by_parent;

        QByteArray selectValue() const;
        QByteArray radioValue() const;
        QByteArray textareaValue() const;
    public:
        enum FormSerializationFlags {
            fsf_none,
            fsf_append_vals_from_hash = 1,
            fsf_percent_encoding,
            fsf_ignore_empty
        };

        enum Tags {
            tg_none = 0,

            /// special
            tg_any,
            tg_text,
            tg_newline,
            ////////////

            tg_html,
            tg_head,
            tg_body,
            tg_colgroup,
            tg_caption,
            tg_i,
            tg_li,
            tg_dt,
            tg_dd,
            tg_p,
            tg_address,
            tg_article,
            tg_aside,
            tg_blockquote,
            tg_details,
            tg_div,
            tg_dl,
            tg_fieldset,
            tg_figcaption,
            tg_figure,
            tg_footer,
            tg_form,
            tg_h1,
            tg_h2,
            tg_h3,
            tg_h4,
            tg_h5,
            tg_h6,
            tg_header,
            tg_hr,
            tg_main,
            tg_menu,
            tg_nav,
            tg_ol,
            tg_pre,
            tg_section,
            tg_table,
            tg_ul,
            tg_a,
            tg_audio,
            tg_del,
            tg_ins,
            tg_map,
            tg_noscript,
            tg_video,
            tg_rt,
            tg_rp,
            tg_optgroup,
            tg_option,
            tg_thead,
            tg_tbody,
            tg_tfoot,
            tg_tr,
            tg_td,
            tg_th,

            tg_br,
            tg_meta,
            tg_link,
            tg_img,
            tg_doctype,
            tg_xml,
            tg_input,
            tg_base,
            tg_embed,
            tg_area,
            tg_col,
            tg_command,
            tg_keygen,
            tg_param,
            tg_source,
            tg_track,
            tg_wbr,
            tg_object,
            tg_span,
            tg_iframe,
            tg_style,
            tg_script,
            tg_select,
            tg_textarea,
            tg_ruby,

            //...
            tg_appendable
        };

        static Tag * stub() { return new Tag(HTML_ANY_TAG); }

        inline Tag(const QByteArray & tag, Tag * parent_tag = 0) :
            _level(parent_tag ? parent_tag -> _level + 1 : 0), _tag_id(tagId(tag)), _tag_len(tag.length()), _classes(0), _parent(parent_tag) {}
        inline Tag(const int & tag_id, const int & tag_length, Tag * parent_tag = 0) :
            _level(parent_tag ? parent_tag -> _level + 1 : 0), _tag_id(tag_id), _tag_len(tag_length), _classes(0), _parent(parent_tag) {}

        inline ~Tag() {
            qDeleteAll(_tags);
            delete _classes;
        }

        static int tagId(const QByteArray & tag, bool append = true) {
            if (append && !list.contains(tag))
                list.insert(tag, list.size() + tg_appendable);

            return list.value(tag, -1);
        }

        inline int tagID() { return _tag_id; }
        inline int level() const { return _level; }
        inline QByteArray name() const { return list.key(_tag_id); }
        inline QHash<QByteArray, QByteArray> attributes() const { return _attrs; }
        inline QByteArray data(const QByteArray & name) const { return value(QByteArrayLiteral("data-") + name); }

        inline QByteArray src() const { return _attrs.value(attr_src); }
        QByteArray src(QByteArray * base_url) const;
        inline QByteArray link() const { return _attrs.value(attr_href); }
        QByteArray link(QByteArray * base_url) const;
        inline QByteArray action() const { return _attrs.value(attr_action); }
        QByteArray action(QByteArray * base_url) const;

        inline Set children() const { return _tags; }

        //INFO: all data stored like UTF-8
        // alias
        inline QByteArray attr(const QByteArray & name = attr_default) const { return value(name); }
        QByteArray value(const QByteArray & name = attr_default) const;
        QByteArray text() const;
        QByteArray texts() const;

        void proceedIFrameData(const QByteArray & data);
        void proceedIFrameData(const QString & data);
        void proceedIFrameData(const char * data);

        void serializeForm(QUrl & url, QByteArray & payload, const QHash<QString, QString> & vals = QHash<QString, QString>(), const FormSerializationFlags & flags = fsf_none, const QString & default_url = QString());
        QUrl serializeFormToUrl(const QHash<QString, QString> & vals = QHash<QString, QString>(), const FormSerializationFlags & flags = fsf_none, const QString & default_url = QString());
        QByteArray toByteArray() const;

//        static QByteArray & decodeMnemonics(QByteArray & val);
//        static QByteArray & decodeLink(QByteArray & val);
//        static QByteArray & decodeContent(QByteArray & val);

//        inline bool hasRelativeSrc() {
//            QByteArray elem_src = src();

//            if (elem_src.isEmpty()) return false;
//        }

        inline bool isSolo() { return solo.contains(_tag_id); }
        static inline bool isSolo(const QByteArray & tag_name) { return solo.contains(tagId(tag_name)); }

        inline bool isClosableBy(const char * data) {
            return '>' == *(data + _tag_len) && _tag_id == tagId(QByteArray(data, _tag_len).toLower(), false);
        }
        inline bool isClosableBy(const QByteArray & tag_name) {
            return tag_name.length() == _tag_len && _tag_id == tagId(tag_name, false);
        }
        inline bool isClosableBy(const int & tag_id, const int & tag_len) {
            return tag_len == _tag_len && _tag_id == tag_id;
        }

        bool isRequireUpParent(const int & tag_id);
        bool isRequireUpParentOnClose(const int & tag_id);

        inline bool isNewline() { return _tag_id == tg_newline; }
        inline bool isStub() { return _tag_id == tg_any; }
        inline bool isText() { return _tag_id == tg_text; }
        inline bool isLink() { return _tag_id == tg_a; }
        inline bool isBody() { return _tag_id == tg_body; }
        inline bool isMeta() { return _tag_id == tg_meta; }

        inline bool isHead() { return _tag_id == tg_head; }
        inline bool isXmlHead() { return _tag_id == tg_xml; }

        inline bool isFrame() { return _tag_id == tg_iframe; }
        inline bool isFrameRequireInit() { return isFrame() && _tags.isEmpty(); }

        inline bool isScript() { return _tag_id == tg_script; }
        inline bool isStyle() { return _tag_id == tg_style; }
        inline bool isCodeBlock() { return isScript() || isStyle(); }

        bool isFormProceable() const;

        inline Tag * parent() { return _parent; }
        inline Tag * child(const int & pos) const { return pos < _tags.size() ? _tags[pos] : 0; }
        inline Tag * lastChild() const { return _tags.isEmpty() ? 0 : _tags.last(); }
        Tag * child(const QByteArray & name_predicate, const int & pos = 0) const;
        inline int childrenCount() { return _tags.size(); }

        inline QByteArray rawClasses() { return _attrs.take(attr_class); }
        QHash<QByteArray, bool> * classes();
        inline bool hasId(const QByteArray & id_name) { return _attrs[attr_id] == id_name; }
        inline bool hasClass(const QByteArray & class_name) {
            QHash<QByteArray, bool> * klasses = classes();
            return klasses && klasses -> contains(class_name);
        }
        inline bool hasAttr(const QByteArray & attr_name = attr_checked) const { return _attrs.contains(attr_name); }
        inline bool hasAttr(const QByteArray & attr_name, const QByteArray & attr_val) const { return _attrs[attr_name] == attr_val; }
        inline bool hasChildren(const char * predicate = 0) const { return !(predicate ? find(predicate).isEmpty() : _tags.isEmpty()); }

        Set find(const char * predicate) const;
        Tag * findFirst(const char * predicate) const;
        inline Set find(const Selector * selector) const { return _tags.find(selector); }
        Tag * findFirst(const Selector * selector) const;

        bool validTo(const Selector * selector);

        //TODO: rewrite
//        QHash<QString, QString> & findLinks(const Selector * selector, QHash<QString, QString> & links);

        inline void addAttr(const QByteArray & name, const QByteArray & val) { _attrs.insert(name.toLower().trimmed(), val.trimmed()); }
        Tag * appendTag(const QByteArray & tname);
        void appendNewline();
        void appendText(const QByteArray & val);
        void appendComment(const QByteArray & val);

        friend QDebug operator<< (QDebug debug, const Tag & c) {
            QString attrStr;
            QHash<QByteArray, QByteArray> vals = c.attributes();

            for (QHash<QByteArray, QByteArray>::iterator it = vals.begin(); it != vals.end(); ++it)
                attrStr.append(
                    '(' % it.key() %
                        (it.value().size() > 0 ?
                            QString(LSTR(": ") % (it.value().size() > DEBUG_LIMIT_OUTPUT ? QString(it.value().mid(0, DEBUG_LIMIT_OUTPUT / 2) % LSTR("...") % it.value().mid(it.value().size() - DEBUG_LIMIT_OUTPUT / 2, DEBUG_LIMIT_OUTPUT / 2)) : QString::fromUtf8(it.value())))
                            : QString()
                        ) % ')'

                );

            if (attrStr.isEmpty())
                qDebug("%s%s", QString(c.level() * 3, ' ').toUtf8().constData(), c.name().data());
            else
                qDebug("%s%s%s%s%s", QString(c.level() * 3, ' ').toUtf8().constData(), c.name().data(), "[", attrStr.toUtf8().constData(), "]");

            foreach(Tag * it, c.children())
                qDebug() << (*it);

            return debug;
        }
    };
}

#endif // HTML_TAG_H
