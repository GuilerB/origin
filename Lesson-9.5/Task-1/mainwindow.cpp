#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_lapCount(0)
    , m_lastLapTime(0.0)
{
    ui->setupUi(this);

    m_stopwatch = new Stopwatch(this);

    // Подключение сигналов
    connect(m_stopwatch, &Stopwatch::timeUpdated, this, &MainWindow::updateTimeDisplay);
    connect(ui->pb_startStop, &QPushButton::clicked, this, &MainWindow::onStartStopClicked);
    connect(ui->pb_clear, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(ui->pb_lap, &QPushButton::clicked, this, &MainWindow::onLapClicked);

    // Начальное состояние
    ui->lb_time->setText("0.0");
    ui->pb_lap->setEnabled(false);
    m_lastLapTime = 0.0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStartStopClicked()
{
    if (m_stopwatch->isRunning()) {
        m_stopwatch->stop();
        ui->pb_startStop->setText("Старт");
        ui->pb_lap->setEnabled(false);
    } else {
        m_stopwatch->start();
        ui->pb_startStop->setText("Стоп");
        ui->pb_lap->setEnabled(true);
    }
}

void MainWindow::onClearClicked()
{
    m_stopwatch->reset();
    ui->tb_laps->clear();
    m_lapCount = 0;
    m_lastLapTime = 0.0;
    ui->lb_time->setText("0.0");
    ui->pb_startStop->setText("Старт");
    ui->pb_lap->setEnabled(false);
}

void MainWindow::onLapClicked()
{
    if (!m_stopwatch->isRunning()) {
        return;
    }

    double currentTime = m_stopwatch->getElapsedSeconds();
    double lapTime;

    if (m_lapCount == 0) {
        lapTime = currentTime;
    } else {
        lapTime = currentTime - m_lastLapTime;
    }

    m_lapCount++;
    m_lastLapTime = currentTime;

    QString lapText = QString("Круг %1, время: %2 сек")
                          .arg(m_lapCount)
                          .arg(lapTime, 0, 'f', 1);

    ui->tb_laps->append(lapText);
}

void MainWindow::updateTimeDisplay(double seconds)
{
    ui->lb_time->setText(QString::number(seconds, 'f', 1));
}
