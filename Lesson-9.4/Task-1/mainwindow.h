#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGroupBox;
class QRadioButton;
class QComboBox;
class QPushButton;
class QProgressBar;
class QVBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onToggleButtonClicked();

private:
    QGroupBox *groupBox;
    QRadioButton *radioButton1;
    QRadioButton *radioButton2;
    QComboBox *comboBox;
    QPushButton *toggleButton;
    QProgressBar *progressBar;
    QVBoxLayout *mainLayout;
    QWidget *centralWidget;

    int progressValue;
};

#endif // MAINWINDOW_H
