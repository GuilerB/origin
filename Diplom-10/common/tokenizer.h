#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <QString>
#include <QStringList>

class Tokenizer
{
public:
    static QStringList tokenize(const QString &text);
};
#endif
