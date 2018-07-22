#ifndef PREDEFINED_RUBY_H
#define PREDEFINED_RUBY_H

#include <qhash.h>
#include <qbytearray.h>

#include "misc/singleton.h"
#include "lexer/state_lexems.h"

//http://www.rubymagic.org/posts/ruby-and-rails-reserved-words
//https://www.tutorialspoint.com/ruby/ruby_regular_expressions.htm

namespace Ruby {
    class Predefined : public SingletonPtr<Predefined> {
        QHash<QByteArray, StateLexem> keys;

        Predefined();
        friend class SingletonPtr<Predefined>;
    public:
        bool hasKey(const QByteArray & key);
        StateLexem lexem(const QByteArray & key);
    };
}

#endif // PREDEFINED_RUBY_H
