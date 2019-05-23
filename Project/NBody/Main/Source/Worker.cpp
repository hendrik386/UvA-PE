#include "Worker.hpp"
#include "Body.hpp"
#include "Bhtree.hpp"

Worker::Worker(std::unique_ptr<Bhtree> &&tree) :
    m_tree(std::move(tree)),
    m_running(false),
    m_working(true),
    m_worked(false)
{
}

Worker::Worker() :
    m_running(false),
    m_working(true),
    m_worked(false)
{
}

void Worker::setTree(std::unique_ptr<Bhtree> &&tree) {
    m_tree = std::move(tree);
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
    m_bodiesQueue.notify();
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
            m_worked = true;
            Body *bod = std::move(m_bodiesQueue.moveFrontNpop());
            insertBody(bod);
        }
        m_working = false;
    }
}

void Worker::insertBody(Body *bod) {
    m_tree->insert(*bod);
}

std::unique_ptr<Bhtree> &&Worker::getTree(){
    return std::move(m_tree);
}

const bool Worker::hasWorked() const{
    return m_worked;
}