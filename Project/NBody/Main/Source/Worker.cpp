#include "Worker.hpp"
#include "Body.hpp"
#include "Bhtree.hpp"

Worker::Worker(Bhtree *tree) :
    m_tree(tree),
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

const bool Worker::running() const {
    return m_running;
}

const bool Worker::working() const {
    return m_working;
}

void Worker::pushBody(Body *bod) {
    m_working = true;
    m_bodiesQueue.push(std::move(bod));
}

void Worker::run() {
    m_working = false;
    while(m_running) {
        m_bodiesQueue.waitIfEmpty();
        while(!m_bodiesQueue.empty()){
            Body *bod = std::move(m_bodiesQueue.moveFrontNpop());
            insertBody(bod);
        }
        m_working = false;
    }
}

void Worker::insertBody(Body *bod) {
    m_tree->insert(*bod);
}