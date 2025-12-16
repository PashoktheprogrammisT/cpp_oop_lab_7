#include "ThreadManager.h"

ThreadManager::~ThreadManager() {
    joinAll();
}

void ThreadManager::addThread(std::function<void()> task) {
    threads.emplace_back(task);
}

void ThreadManager::joinAll() {
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    threads.clear();
}

void ThreadManager::detachAll() {
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.detach();
        }
    }
    threads.clear();
}
