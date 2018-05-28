#pragma once

#include <csignal>
#include <condition_variable>
#include <mutex>

namespace utils {

    static std::condition_variable condition;
    static std::mutex mutex;

    class Interrupt_handler {
    public:
        static void hook_sigint() {
            signal(SIGINT, handle_sigint);
        }

        static void handle_sigint(const int signal) {
            if (signal == SIGINT) {
                condition.notify_one();
            }
        }

        static void wait_for_sigint() {
            std::unique_lock<std::mutex> lock{ mutex };

            condition.wait(lock);
        }
    };
}
