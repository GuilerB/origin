#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>

class Stopwatch : public QObject
{
    Q_OBJECT

public:
    explicit Stopwatch(QObject *parent = nullptr);
    ~Stopwatch();

    void start();
    void stop();
    void reset();
    bool isRunning() const;
    double getElapsedSeconds() const;

signals:
    void timeUpdated(double seconds);

private slots:
    void onTimeout();

private:
    QTimer *m_timer;
    QElapsedTimer m_elapsedTimer;
    double m_pausedTime;
    bool m_running;
};

#endif // STOPWATCH_H