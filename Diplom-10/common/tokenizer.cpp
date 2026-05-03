#include "tokenizer.h"
#include <QRegularExpression>

QStringList Tokenizer::tokenize(const QString &text)
{
    QString cleaned = text.toLower();
    static QRegularExpression nonAlphaRegex("[^a-zа-яё\\s]");
    cleaned.replace(nonAlphaRegex, " ");

    QStringList words = cleaned.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    QStringList result;
    for (const QString &w : words) {
        if (w.length() >= 3 && w.length() <= 32) {
            result.append(w);
        }
    }
    return result;
}