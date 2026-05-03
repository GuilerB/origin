#include "indexer.h"
#include "database.h"
#include "tokenizer.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

void Indexer::addIndexPath(const QString &path)
{
    m_indexPaths.append(path);
}

void Indexer::setFileExtensions(const QStringList &extensions)
{
    m_allowedExtensions = extensions;
}

void Indexer::setIndexPaths(const QStringList &paths)
{
    m_indexPaths = paths;
}

void Indexer::run()
{
    qDebug() << "Indexing started...";
    DB::instance().clearTables();

    for (const QString &path : m_indexPaths) {
        QFileInfo fi(path);
        if (!fi.exists()) {
            qWarning() << "Path does not exist:" << path;
            continue;
        }

        if (fi.isDir()) {
            indexDirectory(path);
        } else if (fi.isFile()) {
            if (m_allowedExtensions.contains(fi.suffix().toLower())) {
                processFile(path);
            }
        }
    }

    qDebug() << "Indexing finished.";
}

void Indexer::indexDirectory(const QString &dirPath)
{
    QDir dir(dirPath);
    QFileInfoList entries = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QFileInfo &info : entries) {
        if (info.isDir()) {
            indexDirectory(info.absoluteFilePath());
        } else if (info.isFile()) {
            if (m_allowedExtensions.contains(info.suffix().toLower())) {
                processFile(info.absoluteFilePath());
            }
        }
    }
}

void Indexer::processFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open file:" << filePath;
        return;
    }

    QByteArray rawBytes = file.readAll();
    file.close();

    QString content = QString::fromUtf8(rawBytes);

    int cyrillicCount = 0;
    for (const QChar &c : content) {
        if (c.unicode() >= 0x0400 && c.unicode() <= 0x04FF) cyrillicCount++;
    }

    if (rawBytes.length() > 500 && cyrillicCount < 10) {
        content = QString::fromLocal8Bit(rawBytes);
    }

    if (content.isEmpty()) return;

    QStringList tokens = Tokenizer::tokenize(content);
    if (tokens.isEmpty()) return;

    QMap<QString, int> wordFrequency;
    for (const QString &w : tokens) wordFrequency[w]++;

    DB &db = DB::instance();
    db.insertDocument(filePath);
    int docId = db.getDocumentId(filePath);
    if (docId < 0) return;

    for (auto it = wordFrequency.constBegin(); it != wordFrequency.constEnd(); ++it) {
        db.insertWord(it.key());
        int wordId = db.getWordId(it.key());
        if (wordId >= 0) {
            db.insertWordFrequency(docId, wordId, it.value());
        }
    }
}
