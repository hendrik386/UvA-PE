#pragma once

#include <thread>
#include <atomic>

#include "safeQueue.hpp"

class Body;

class Worker
{
    private:
        std::thread m_thisThread;
        Safequeue<Body> m_bodiesQueue;
        std::atomic<bool> m_working;
        std::atomic<bool> m_running;

        void run();
    public:
        Worker();

        void start();
        void stop();
        const bool running() const;

        void pushBody(const Body *bod);
        const bool working() const;
};