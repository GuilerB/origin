#ifndef INDEXER_H
#define INDEXER_H

#include <QString>
#include <QStringList>

class Indexer
{
public:
    Indexer() = default;

    void setIndexPaths(const QStringList &paths);
    void setFileExtensions(const QStringList &extensions);
    void addIndexPath(const QString &path);

    void run();

private:
    void processFile(const QString &filePath);
    void indexDirectory(const QString &dirPath);

    QStringList m_indexPaths;
    QStringList m_allowedExtensions;
};

#endif