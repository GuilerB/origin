#ifndef SEARCHERWINDOW_H
#define SEARCHERWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QSqlDatabase>
#include "database.h"

namespace Ui { class SearcherWindow; }

class WordListLoader : public QObject
{
    Q_OBJECT
public:
    explicit WordListLoader(QObject *parent = nullptr);
    ~WordListLoader();

    QVector<QPair<QString, int>> loadWordList();

signals:
    void finished(const QVector<QPair<QString, int>> &wordList);
    void error(const QString &message);

private:
    QSqlDatabase m_threadDb;
    QString m_connectionName;  // уникальное имя соединения
};

class SearcherWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SearcherWindow(QWidget *parent = nullptr);
    ~SearcherWindow();

private:
    void loadWordList();
    void onWordListLoaded(const QVector<QPair<QString, int>> &wordList);
    void onWordListError(const QString &message);

    void displaySearchResults(const QVector<SearchResult> &results);
    QStringList parseSearchQuery(const QString &query);

    Ui::SearcherWindow *ui;
    QVector<SearchResult> m_lastSearchResults;

private slots:
    void onSearchClicked();
    void onShowRelevanceClicked();
};

#endif
