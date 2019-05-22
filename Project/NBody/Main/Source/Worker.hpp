#pragma once

#include <thread>
#include <atomic>
#include <memory>

#include "Bhtree.hpp"
#include "safeQueue.hpp"

class Body;

// class Bhtree;

class Worker
{
    private:
        std::thread m_thisThread;
        Safequeue<Body *> m_bodiesQueue;
        std::atomic<bool> m_working;
        std::atomic<bool> m_running;

        std::unique_ptr<Bhtree> m_tree = nullptr;

        void run();
        void insertBody(Body *bod);
    public:
        Worker(std::unique_ptr<Bhtree> &&tree);
        Worker();

        void setTree(std::unique_ptr<Bhtree> &&tree);
        void start();
        void stop();
        const bool running() const;

        void pushBody(Body *bod);
        const bool working() const;
};