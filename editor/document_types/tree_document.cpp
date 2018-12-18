#include "tree_document.h"

#include "project/file.h"

//#include "lexer/ilexer.h"
//#include "lexer/lexers_factory.h"

//#include "highlighter/highlighter.h"

//#include <qtextstream.h>

//#include <qelapsedtimer.h>

//#include <qjsonobject.h>
//#include <qjsonarray.h>


//bool TextDocument::identificateLexer() {
//    FormatType format = _file -> formatType();

//    _lexer = LexersFactory::obj().lexerFor(format);
//    if (_lexer)
//        highlighter = new Highlighter(this);

//    return _lexer != nullptr;
//}

bool TreeDocument::registerStateChangedCallback(QObject * target, const char * slot) {
    connect(this, SIGNAL(hasChanges(QString, bool)), target, slot);

    return true;
}

TreeDocument::TreeDocument(File * file) : IDocument()/*, highlighter(nullptr)*/, _file(file) {
//    qint64 content_length = _file -> source() -> size();
    setFullyReaded(true);

    QByteArray ar = _file -> source() -> readAll();
//    ar.replace('\t', TextDocument::tab_space);
//    setPlainText(ar);

//    if (!identificateLexer()) {
//        if (_file -> formatType() == ft_unknown) {
//            QString str = firstBlock().text();

//            if (file -> identifyTypeByShebang(str))
//                identificateLexer();
//        }
//    }

//    if (!highlighter)
//        connect(this, SIGNAL(contentsChange(int, int, int)), this, SLOT(changesInContent(int,int,int)));
//    else
//        connect(this, SIGNAL(highlightingComplete()), this, SLOT(highlighterFinished()));

//    connect(this, SIGNAL(contentsChanged()), this, SLOT(hasUnsavedChanges()));
}

TreeDocument::~TreeDocument() {

}

const QString & TreeDocument::documentUid() { return _file -> uid(); }

//void TextDocument::lexicate(const QString & text, IHighlighter * highlighter) {
//    if (_lexer)
//        _lexer -> handle(text, highlighter);
//}

//bool TextDocument::isCompleterInitiable(const LEXEM_TYPE & lex, const bool & at_end) {
//    switch(lex) {
//        case lex_inline_commentary_content:
//        case lex_commentary_content:
//        case lex_bin:
//        case lex_oct:
//        case lex_dec:
//        case lex_hex:
//        case lex_float:
//        case lex_double:
//            return false;

//        case lex_operator_add:
//        case lex_operator_minus:
//        case lex_operator_multiplication:
//        case lex_operator_division:
//        case lex_operator_modulus:
//        case lex_operator_exponentiation:

//        case lex_operator_add_assigment:
//        case lex_operator_minus_assigment:
//        case lex_operator_multiplication_assigment:
//        case lex_operator_division_assigment:
//        case lex_operator_modulus_assigment:
//        case lex_operator_exponentiation_assigment:

//        case lex_operator_assigment:
//        case lex_operator_comparison:
//        case lex_operator_not_equal:
//        case lex_operator_great:
//        case lex_operator_less:
//        case lex_operator_great_eql:
//        case lex_operator_less_eql:
//        case lex_operator_sort:
//        case lex_operator_equality:
//        case lex_dot_dot:
//        case lex_dot_dot_dot:

//        case lex_operator_bit_and:
//        case lex_operator_bit_or:
//        case lex_operator_bit_exclusive_or:
//        case lex_operator_bit_not:
//        case lex_operator_bit_left_shift:
//        case lex_operator_bit_right_shift:

//        case lex_operator_bit_and_assigment:
//        case lex_operator_bit_or_assigment:
//        case lex_operator_bit_exclusive_or_assigment:
//        case lex_operator_bit_left_shift_assigment:
//        case lex_operator_bit_right_shift_assigment:


//        case lex_rocket:
//        case lex_question_mark:
//        case lex_colon:

//        case lex_operator_not:
//        case lex_operator_and:
//        case lex_operator_or:


//        case lex_operator_and_assigment:
//        case lex_operator_or_assigment:

//        case lex_resolution:
//            return at_end;
//    }

//    return true;
//}

//bool TextDocument::isCompleterContinuable(const LEXEM_TYPE & lex, const bool & /*at_end*/) {
//    switch(lex) {
//        case lex_undefined: //INFO: compatibility for not lexable documents

//        case lex_method:
//        case lex_word:
//        case lex_const:
//        case lex_var_local:
//        case lex_var_instance:
//        case lex_var_object:
//        case lex_var_global:
//        case lex_end_of_code:
//        case lex_commentary_start:
//        case lex_commentary_end:

//        case lex_global_pre_hook:
//        case lex_global_post_hook:

//        case lex_alias:
//        case lex_operator_and_word:

//        case lex_begin:
//        case lex_loop_break:
//        case lex_case:
//        case lex_class_def:
//        case lex_method_def:
//        case lex_do:
//        case lex_else:
//        case lex_elsif:
//        case lex_end:
//        case lex_block_ensure:

//        case lex_operator_comparison:
//        case lex_operator_equality:

//        case lex_extend:
//        case lex_for:
//        case lex_if:
//        case lex_in:
//        case lex_include:

//        case lex_lambda_def:
//        case lex_module_def:
//        case lex_loop_next:
//        case lex_operator_not:
//        case lex_operator_or_word:
//        case lex_visibility_scope:
//        case lex_proc_def:
//        case lex_raise:
//        case lex_loop_redo:
//        case lex_require:
//        case lex_block_rescue:
//        case lex_block_retry:
//        case lex_return:
//        case lex_self:
//        case lex_super:
//        case lex_then:
//        case lex_undef:
//        case lex_unless:
//        case lex_until:
//        case lex_when:
//        case lex_while:
//        case lex_yield:
//        case lex_loop:
//            return true;
//    }

//    return false;
//}

//bool TextDocument::isCompleterReplaceable(const LEXEM_TYPE & lex, const bool & at_start) {
//    switch(lex) {
//        case lex_undefined: //INFO: compatibility for not lexable documents

//        case lex_method:
//        case lex_word:
//        case lex_const:
//        case lex_var_local:
//        case lex_var_instance:
//        case lex_var_object:
//        case lex_var_global:
//            return !at_start;
//    }

//    return false;
//}

//void TextDocument::paraOpositionStr(const PARA_TYPE & para, QString & res) {
//    if (_lexer)
//        _lexer -> paraOpositionStr(para, res);
//    else
//        res.clear();
//}

//LEXEM_TYPE TextDocument::getWordBoundaries(EDITOR_POS_TYPE & start, EDITOR_POS_TYPE & length, const QTextBlock & block, const EDITOR_POS_TYPE & pos, const bool & global_offset) {
//    BlockUserData * udata = static_cast<BlockUserData *>(block.userData());

//    start = global_offset ? block.position() : 0;

//    if (udata) {
//        TokenCell * tkn = udata -> tokenForPos(pos);

//        if (tkn) {
//            switch(tkn -> lexem) {
//                case lex_blanks: {
//                    start += pos;
//                    length = 1;
//                    return lex_blank;
//                }
//                case lex_tabs: {
//                    start += pos;
//                    length = 1;
//                    return lex_tab;
//                }

//                default: {
//                    start += tkn -> start_pos;
//                    length = static_cast<int>(tkn -> length);
//                    return tkn -> lexem;
//                }
//            }
//        }
//    }

//    const QString block_text = block.text();

//    if (block_text.isEmpty()) {
//        length = 0;
//        return lex_none;
//    }

//    int offset = 0;
//    for(int iter = pos - 1; iter >= 0; --iter, ++offset) {
//        if (word_boundary.contains(block_text[iter]))
//            break;
//    }

//    start += pos - offset;

//    if (length != -1) {
//        const int end_pos = block.length() - 1;
//        length = offset;

//        for(int iter = pos; iter < end_pos; ++iter, ++length) {
//            if (word_boundary.contains(block_text[iter]))
//                break;
//        }
//    }

//    return lex_undefined;
//}

//ParaCell * TextDocument::getPara(const QTextBlock & block, const EDITOR_POS_TYPE & pos) {
//    BlockUserData * udata = static_cast<BlockUserData *>(block.userData());

//    return udata ? udata -> paraForPos(pos) : nullptr;
//}

bool TreeDocument::save() {
    return false; // TODO: remove me

//    if (!isModified())
//        return true;

//    if (_file -> openDevice(QFile::WriteOnly)) {
//        QTextStream writer(_file -> _device);
////        writer.setGenerateByteOrderMark(true);
////        writer.setCodec();

//        writer << toPlainText();//toRawText();

//        writer.flush();

//        hasUnsavedChanges(false);
//    }

//    return false;
}

bool TreeDocument::dump(QVariant & data) {
//    if (_lexer) {
//        QTextBlock blk = begin();
//        int block_num = 0;

//        QByteArray res;
//        BlockUserData * udata;

//        while(blk.isValid()) {
//            int item_state = 0;
//            udata = TextDocumentLayout::getUserDataForBlock(blk);

//            if (udata && udata -> isFolded())
//                item_state |= 1;

//            if (!blk.isVisible())
//                item_state |= 2;

//            if (udata && udata -> hasBreakpoint())
//                item_state |= 4;

//            if (item_state > 0) {
//                res.append(QByteArray::number(block_num));
//                res.append('|');
//                res.append(QByteArray::number(item_state));
//                res.append('\n');
//            }

//            blk = blk.next();
//            ++block_num;
//        }

//        if (res.isEmpty())
//            return false;
//        else {
//            res.prepend('!' % QByteArray::number(_file -> size()) % '\n');
////            res = qCompress(res, 9);
//            data = QVariant::fromValue(res);
//            return true;
//        }
//    }

    return false;
}
bool TreeDocument::restore(const QVariant & data) {
//    QTextBlock blk = begin();

//    if (!blk.isValid())
//        return false;

//    if (data.isValid()) {
//        QByteArray res = data.toByteArray();
////        res = qUncompress(res);

//        QByteArray::Iterator it = res.begin();
//        QByteArray::Iterator it_end = res.end();

//        if (*it != '!')
//            return false;

//        ++it; // move '!'

//        int num = 0;

//        for(; it != it_end; ++it, ++num) {
//            if (*it == '\n')
//                break;
//        }

//        if (num == 0)
//            return false;
//        else {
//            QByteArray buff((it - num), num);

//            if (buff.toLongLong() != _file -> size())
//                return false;
//        }

//        ++it; // move '\n'

//        int item_data;
//        int block_pos = 0;
//        int block_num = 0;
//        int blocks_limit = blockCount();
//        BlockUserData * udata;

//        for(num = 0; it != it_end; ++it, ++num) {
//            switch(*it) {
//                case '|': {
//                    QByteArray buff((it - num), num);

//                    block_pos = buff.toInt();

//                    if (block_pos > blocks_limit)
//                        return false;

//                    num = -1;
//                break;}

//                case '\n': {
//                    if (num > 0) {
//                        QByteArray buff((it - num), num);
//                        item_data = buff.toInt();

//                        while(block_num < block_pos) {
//                            blk = blk.next();
//                            ++block_num;
//                        }

//                        if (item_data > 0) {
//                            if (item_data & 2) {
//                                blk.setVisible(false);
//                                blk.setLineCount(0);
//                            }

//                            if (item_data & 1 || item_data & 4) {
//                                udata = TextDocumentLayout::getUserDataForBlock(blk);

//                                if (!udata)
//                                    return false;

//                                if (item_data & 1) {
//                                    udata -> setFolded(true);
//                                }

//                                if (item_data & 4) {
//                                    udata -> setBreakpoint(true);
//                                }
//                            }
//                        }
//                    }

//                    num = -1;
//                break;}
//            }
//        }
//    }

    return false;
}

//void TextDocument::hasUnsavedChanges(const bool & has) {
//    emit hasChanges(_file -> uid(), has);
//}

//void TextDocument::changesInContent(int position, int removed_count, int added_count) {

//}

//void TextDocument::highlighterFinished() {

//}