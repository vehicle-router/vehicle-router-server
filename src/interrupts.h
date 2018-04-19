#pragma once

#include <csignal>
#include <condition_variable>
#include <mutex>

static std::condition_variable condition;
static std::mutex mutex;

class InterruptHandler {
public:
    static void hookSIGINT() {
        signal(SIGINT, handleInterrupt);
    }

    static void handleInterrupt(int signal) {
        if (signal == SIGINT) {
            condition.notify_one();
        }
    }

    static void waitForUserInterrupt() {
        std::unique_lock<std::mutex> lock{mutex};
        condition.wait(lock);
        lock.unlock();
    }
};
