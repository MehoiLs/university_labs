#include <iostream>
#include <thread>
#include "ThreadPool.h"
#include "ThreadPoolUtil.h"

void sampleTask(const int id) {
    const auto threadId = std::to_string(ThreadPoolUtil::getCurrentThreadId());
    const auto msgRunning = "Task " + std::to_string(id) + " is running on thread #" + threadId + "...\n";
    std::cout << msgRunning;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    const auto msgCompleted = "Task " + std::to_string(id) + " completed." + '\n';
    std::cout << msgCompleted;
}

int main() {
    ThreadPool pool;

    for (int i = 0; i < 10; ++i) {
        pool.addTask([i] { sampleTask(i); } );
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}
