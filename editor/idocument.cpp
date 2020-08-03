#include "idocument.h"
#include "project/file.h"

QLatin1String IDocument::tab_space = QLatin1String("  ");

QHash<QChar, bool> IDocument::word_boundary = {
    {'~', true}, {'#', true}, {'%', true},
    {'^', true}, {'&', true}, {'*', true},
    {'(', true}, {')', true}, {'+', true},
    {'{', true}, {'}', true}, {'|', true},
    {'"', true}, {'<', true}, {'>', true},
    {',', true}, {'.', true}, {'/', true},
    {';', true}, {'\'', true}, {'[', true},
    {']', true}, {'\\', true}, {'-', true},
    {'=', true}, {' ', true}, {'`', true}
};

IDocument::~IDocument() {

}

uint IDocument::projectUid() {
    if (_file) {
        return _file -> projectUid();
    }

    return 0;
}
