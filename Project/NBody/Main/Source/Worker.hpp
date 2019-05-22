#pragma once

#include <thread>
#include <atomic>

#include "safeQueue.hpp"

class Body;

class Bhtree;

class Worker
{
    private:
        std::thread m_thisThread;
        Safequeue<Body *> m_bodiesQueue;
        std::atomic<bool> m_working;
        std::atomic<bool> m_running;

        Bhtree *m_tree;

        void run();
        void insertBody(Body *bod);
    public:
        Worker(Bhtree *tree);

        void start();
        void stop();
        const bool running() const;

        void pushBody(Body *bod);
        const bool working() const;
};