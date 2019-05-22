#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>
#include <type_traits>

template<typename ttype>
class Safequeue
{
    private:
    	std::queue<ttype> m_msgQueue;
		std::mutex m_msgQueueLock;
        std::condition_variable m_queueConditionVariable;

    public:
        template <typename ttemp = ttype>
		void push(typename std::enable_if<std::is_copy_constructible<ttype>::value, const ttemp&>::type &msg)
		{
			std::unique_lock<std::mutex> lock(this->m_msgQueueLock);
			this->m_msgQueue.push(msg);
			notify();
		}


 		void push(ttype&& msg) override
		{
			std::unique_lock<std::mutex> lock(this->m_msgQueueLock);
			this->m_msgQueue.push(std::forward<ttype>(msg));
			notify();
		}

        ttype frontNpop(void)
		{
			std::lock_guard<std::mutex> lock(m_msgQueueLock);
			ttype temp = m_msgQueue.front();
			m_msgQueue.pop();
			return temp;
		}

		ttype moveFrontNpop(void)
		{
			std::lock_guard<std::mutex> lock(m_msgQueueLock);
			ttype temp(std::move(m_msgQueue.front()));
			m_msgQueue.pop();
			return temp;
		}

        ttype front(void)
		{
			std::lock_guard<std::mutex> lock(m_msgQueueLock);
			return m_msgQueue.front();
		}

        void pop(void)
		{
			std::lock_guard<std::mutex> lock(m_msgQueueLock);
			m_msgQueue.pop();
		}

		const unsigned int size(void)
		{
			std::lock_guard<std::mutex> lock(m_msgQueueLock);
			return m_msgQueue.size();
		}

        const bool empty(void)
		{
			std::lock_guard<std::mutex> lock(m_msgQueueLock);
			return m_msgQueue.empty();
		}

        void waitIfEmpty(void)
		{
			std::unique_lock<std::mutex> lock(this->m_msgQueueLock);
			if(this->m_msgQueue.empty())
			{
				m_queueConditionVariable.wait(lock);
			}
		}

        void notify()
		{
			m_queueConditionVariable.notify_one();
		}
};