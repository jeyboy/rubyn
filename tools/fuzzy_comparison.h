#ifndef FUZZY_COMPARISON
#define FUZZY_COMPARISON

#include <qstring.h>
#include <qstringbuilder.h>
#include <qlist.h>
#include <qregularexpression.h>

//TODO: rewrite wordLetterPairs for usage of splitRef and letterPairs for usage of QStringRef

class FuzzyComparison {
    static QStringList wordLetterPairs(const QString & str) {
        QStringList all_pairs;

        QStringList words = str.split(QRegularExpression(QLatin1String("\\s")), Qt::SkipEmptyParts);

        while(!words.isEmpty())
            all_pairs.append(letterPairs(words.takeFirst()));

        return all_pairs;
    }

    static QStringList letterPairs(const QString & str) {
        int num_pairs = str.size() - 1;

        QStringList pairs;
        pairs.reserve(num_pairs);

        for (int i = 0; i < num_pairs; i++)
            pairs.append(str.mid(i, 2));

        return pairs;
    }
public:
    static float compareStrings(const QString & str1, const QString & str2) {
        QStringList pairs1 = wordLetterPairs(str1.toUpper());
        QStringList pairs2 = wordLetterPairs(str2.toUpper());

        int intersection = 0;
        int pairs_amount = pairs1.size() + pairs2.size();

        for (int i = 0; i < pairs1.size(); i++) {
            for (int j = 0; j < pairs2.size(); j++) {
                if (pairs1[i] == pairs2[j]) {
                    intersection++;
                    pairs2.removeAt(j);
                    break;
                }
            }
        }

        return ((2.0 * intersection) / pairs_amount) * 100;
    }

    static float compareStrings2(const QString & str1, const QString & str2, int group_length = 2, Qt::CaseSensitivity caseSense = Qt::CaseInsensitive) {
        if (str1.isEmpty() || str2.isEmpty()) return 100;

        qreal hits = 0;
        int padd = group_length - 1;
//        QString buff = QLatin1String(" ").repeated(padd);
        QString buff(padd, ' ');
        QString source = buff % str1 % buff;
        QString target = buff % str2 % buff;

        for (int i = 0; i < source.count() - padd; i++)
            if (target.contains(source.mid(i, group_length), caseSense)) hits++;

        return (100 * hits / (qMin(target.length(), source.length()) - padd));
    }
};

#endif // FUZZY_COMPARISON
