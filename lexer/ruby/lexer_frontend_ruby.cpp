#include "lexer_frontend_ruby.h"

void LexerFrontendRuby::lexicate(const QString & text, Highlighter * lighter) {
    for(QString::Iterator ch = text.begin(); ch != text.end(); ch++) {

    }
}

LexerFrontendRuby::LexerFrontendRuby() {

}

void LexerFrontendRuby::handle(const QString & text, Highlighter * lighter) {
        LexerState * state = 0;

        QTextBlock block = lighter -> currentBlock();
        QTextBlock prev_block = lighter -> prevBlock();

        BlockUserData * prev_udata = reinterpret_cast<BlockUserData *>(prev_block.userData());
        BlockUserData * udata = reinterpret_cast<BlockUserData *>(block.userData());

        if (!udata) {
            udata = new BlockUserData(
                tokens, paras,
                prev_udata ? prev_udata -> token_end : 0,
                prev_udata ? prev_udata -> para_end : 0
            );
            block.setUserData(udata);
        }
        else lighter -> clearExtraFormatForCurrBlock();

        state = new LexerState(scope, udata, prev_udata ? prev_udata -> stackState() : 0, lighter);

        QByteArray text_val = text.toUtf8();
        const char * window = text_val.constData();
        state -> setBuffer(window);

    //        quint64 date = QDateTime::currentMSecsSinceEpoch();
        handle(state);
    //        qDebug() << "SSOOS: " << (QDateTime::currentMSecsSinceEpoch() - date);

        block.setUserState(state -> status);
        udata -> syncLine(state -> token, state -> para, state -> control_para, state -> stack);
        delete state;
}
