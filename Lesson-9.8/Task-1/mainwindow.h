#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtConcurrent>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlError>
#include "database.h"
#include "dbdata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupTableModel();
    void setupQueryModel(const QString& category);

public slots:
    void ScreenDataFromDB(const QTableWidget *widget, int typeRequest);
    void ReceiveStatusConnectionToDB(bool status);

private slots:
    void on_act_addData_triggered();
    void on_act_connect_triggered();
    void on_pb_request_clicked();
    void on_pb_clear_clicked();
    void on_cb_category_currentIndexChanged(int index);

signals:
    void sig_RequestToDb(QString request);

private:
    QVector<QString> dataForConnect;
    Ui::MainWindow *ui;
    DbData *dataDb;
    DataBase* dataBase;
    QMessageBox* msg;
    
    QSqlTableModel *tableModel;
    QSqlQueryModel *queryModel;
};
#endif
