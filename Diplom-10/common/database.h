#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QStringList>
#include <QSqlDatabase>
#include <QVector>
#include <QPair>

struct SearchResult {
    QString filePath;
    int relevance;
};

class DB
{
public:
    static DB& instance();

    bool openConnection(const QString &host, int port, const QString &dbName,
                        const QString &user, const QString &password);
    bool initializeFromConfig(const QString &configPath);

    QSqlDatabase& connection();

    QVector<QPair<QString, int>> getAllWordsWithFrequency();
    QVector<SearchResult> search(const QStringList &words, int limit = 10);

    bool createTables();
    void clearTables();

    bool insertDocument(const QString &filePath);
    int getDocumentId(const QString &filePath);
    bool insertWord(const QString &word);
    int getWordId(const QString &word);
    bool insertWordFrequency(int documentId, int wordId, int frequency);

    QString databaseHost;
    int databasePort;
    QString databaseName;
    QString databaseUser;
    QString databasePassword;

private:
    DB();
    ~DB();
    DB(const DB&) = delete;
    DB& operator=(const DB&) = delete;

    QSqlDatabase m_database;
};

#endif 