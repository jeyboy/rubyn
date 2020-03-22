#ifndef RUBY_PREDEFINED_H
#define RUBY_PREDEFINED_H

#include <qhash.h>
#include <qbytearray.h>

#include "misc/singleton.h"
#include "ruby_state_lexems.h"

//http://www.rubymagic.org/posts/ruby-and-rails-reserved-words
//https://www.tutorialspoint.com/ruby/ruby_regular_expressions.htm

namespace Ruby {
    class Predefined : public Singleton<Predefined> {
        QHash<QString, Ruby::StateLexem> keys;

        Predefined();
        friend class Singleton<Predefined>;
    public:
        bool hasKey(const QString & key);
        Ruby::StateLexem lexem(const QString & key);
    };
}

#endif // RUBY_PREDEFINED_H
