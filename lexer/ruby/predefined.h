#ifndef RUBY_PREDEFINED_H
#define RUBY_PREDEFINED_H

#include <qhash.h>
#include <qbytearray.h>

#include "misc/singleton.h"
#include "state_lexems.h"

//http://www.rubymagic.org/posts/ruby-and-rails-reserved-words
//https://www.tutorialspoint.com/ruby/ruby_regular_expressions.htm

namespace Ruby {
    class Predefined : public Singleton<Predefined> {
        QHash<QByteArray, LEXEM_TYPE> keys;

        Predefined();
        friend class Singleton<Predefined>;
    public:
        bool hasKey(const QByteArray & key);
        LEXEM_TYPE lexem(const QByteArray & key);
    };
}

#endif // RUBY_PREDEFINED_H
