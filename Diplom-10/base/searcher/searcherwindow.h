#ifndef SEARCHERWINDOW_H
#define SEARCHERWINDOW_H

#include <QMainWindow>
#include "database.h"

namespace Ui { class SearcherWindow; }

class SearcherWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SearcherWindow(QWidget *parent = nullptr);
    ~SearcherWindow();

private:
    void loadWordList();
    void displaySearchResults(const QVector<SearchResult> &results);
    QStringList parseSearchQuery(const QString &query);

    Ui::SearcherWindow *ui;
    QVector<SearchResult> m_lastSearchResults;

private slots:
    void onSearchClicked();
    void onShowRelevanceClicked();
};

#endif
