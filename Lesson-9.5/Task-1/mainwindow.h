#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartStopClicked();
    void onClearClicked();
    void onLapClicked();
    void updateTimeDisplay(double seconds);

private:
    Ui::MainWindow *ui;
    Stopwatch *m_stopwatch;
    int m_lapCount;
    double m_lastLapTime;
};

#endif // MAINWINDOW_H