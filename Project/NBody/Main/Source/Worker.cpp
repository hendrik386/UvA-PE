#include "Worker.hpp"

Worker::Worker() :
    m_running(false),
    m_working(true)
{
}

void Worker::start() {
    m_running = true;
    m_thisThread = std::thread([this]()
    {
        run();
        m_running = false;
    });
}

void Worker::stop() {
    if (m_running) {
        m_running = false;
    }
    if (m_thisThread.joinable()) {
		m_thisThread.join();
    }
}
