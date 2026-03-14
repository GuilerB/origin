#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , progressValue(0)
{
    ui->setupUi(this);

    // RadioButton s name
    ui->radioButton->setText("Painters");
    ui->radioButton_2->setText("Musicians");

    // List filling
    ui->comboBox->addItem("Camille Corot");
    ui->comboBox->addItem("Edu Manet");
    ui->comboBox->addItem("Johann Sebastian Bach");
    ui->comboBox->addItem("Bruce Dickinson");

    ui->toggleButton->setText("A step in study progress!");

    ui->toggleButton->setCheckable(true);

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toggleButton_clicked()
{
    progressValue += 10;

    if (progressValue > 100) {
        progressValue = 0;
    }

    ui->progressBar->setValue(progressValue);
}
