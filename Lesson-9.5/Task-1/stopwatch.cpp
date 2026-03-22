#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent)
    : QObject(parent)
    , m_pausedTime(0.0)
    , m_running(false)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(100);
    connect(m_timer, &QTimer::timeout, this, &Stopwatch::onTimeout);
}

Stopwatch::~Stopwatch()
{
    stop();
}

void Stopwatch::start()
{
    if (!m_running) {
        m_elapsedTimer.start();
        m_running = true;
        m_timer->start();
    }
}

void Stopwatch::stop()
{
    if (m_running) {
        m_timer->stop();
        m_pausedTime += m_elapsedTimer.elapsed() / 1000.0;
        m_running = false;
    }
}

void Stopwatch::reset()
{
    stop();
    m_pausedTime = 0.0;
    emit timeUpdated(0.0);
}

bool Stopwatch::isRunning() const
{
    return m_running;
}

double Stopwatch::getElapsedSeconds() const
{
    if (m_running) {
        return m_pausedTime + m_elapsedTimer.elapsed() / 1000.0;
    }
    return m_pausedTime;
}

void Stopwatch::onTimeout()
{
    emit timeUpdated(getElapsedSeconds());
}