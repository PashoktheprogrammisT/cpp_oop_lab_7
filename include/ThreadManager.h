#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <vector>
#include <thread>
#include <functional>

class ThreadManager {
private:
    std::vector<std::thread> threads;
    
public:
    ThreadManager() = default;
    ~ThreadManager();
    
    void addThread(std::function<void()> task);
    void joinAll();
    void detachAll();
};

#endif
