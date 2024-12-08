#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <vector>
#include <thread>

static constexpr int MAX_THREADS_COUNT = 12;

class ThreadPool {
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> taskQueue;

    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;

    void worker() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock lock(queueMutex);
                condition.wait(lock, [this] -> bool {
                    return stop || !taskQueue.empty();
                });

                if (stop && taskQueue.empty()) {
                    break;
                }

                task = std::move(taskQueue.front());
                taskQueue.pop();
            }

            if (task) {
                task();
            }
        }
    }

public:
    ThreadPool() : stop(false) {
        auto threadCount = std::thread::hardware_concurrency();
        if (threadCount == 0) {
            threadCount = MAX_THREADS_COUNT;
        }

        for (auto i = 0; i < threadCount; ++i) {
            threads.emplace_back(&ThreadPool::worker, this);
        }
    }

    ~ThreadPool() {
        {
            std::lock_guard lock(queueMutex);
            stop = true;
        }
        condition.notify_all();

        for (auto& thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

    template<typename Func>
    void addTask(Func task) {
        {
            std::lock_guard lock(queueMutex);
            if (stop) {
                throw std::runtime_error("Cannot add task => thread pool is stopping.");
            }
            taskQueue.emplace(std::function<void()>(task));
        }
        condition.notify_one();
    }

};

#endif //THREADPOOL_H
