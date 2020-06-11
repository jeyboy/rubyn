#ifndef IDOCUMENT_H
#define IDOCUMENT_H

#include "project/code_formats.h"

#include <qpoint.h>
#include <qvariant.h>

#define READ_LIMIT 512000LL // ~512 kb

class ILexer;

class IDocument {
    bool _fully_readed;
protected:
    ILexer * _lexer;

    QPoint scroll_pos;
    int to_char_pos;
    bool _word_wrap;

    static QLatin1String tab_space;
    static QHash<QChar, bool> word_boundary;

    inline void setFullyReaded(const bool & readed) { _fully_readed = readed; }
public:
    inline IDocument() : _fully_readed(false), _lexer(nullptr), scroll_pos(0, 0), to_char_pos(-1), _word_wrap(false) {}
    virtual ~IDocument();

    inline bool isFullyReaded() const { return _fully_readed; }
    inline bool isWordWrap() const { return _word_wrap; }
    virtual bool isChanged() const { return false; }

    virtual bool save() { return false; }
    virtual bool dump(QVariant & /*data*/) { return false; }
    virtual bool restore(const QVariant & /*data*/) { return false; }

    virtual bool registerStateChangedCallback(QObject * /*target*/, const char * /*slot*/) { return false; }
    virtual void setWordWrap(const bool & word_wrap) { _word_wrap = word_wrap; }

    virtual void highlight(QRegularExpression * reg_exp, const bool & scroll = true) = 0;

    inline bool scrollPredefined() { return scroll_pos.rx() > 0 || scroll_pos.ry() > 0; }
    inline void setHorizontalScrollPos(const int & pos) { scroll_pos.rx() = pos; }
    inline void setVerticalScrollPos(const int & pos) { scroll_pos.ry() = pos; }
    inline QPoint scrollPos(const bool & drop = true) {
        QPoint res = scroll_pos;
        if (drop)
            scroll_pos = QPoint(0, 0);
        return res;
    }

    inline void setMoveToCharPos(const int & pos) { to_char_pos = pos; }
    inline bool moveToChar() { return to_char_pos != -1; }
    inline int moveToCharPos() {
        int res = to_char_pos;
        to_char_pos = -1;
        return res;
    }
};

#endif // IDOCUMENT_H
