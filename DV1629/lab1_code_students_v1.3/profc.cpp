#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <stdio>
const int kNumPhilosophers = 5;

std::mutex forks[kNumPhilosophers];

void philosopher(int id) {
    int left_fork = id;
    int right_fork = (id + 1) % kNumPhilosophers;

    while (true) {
        // think for a while
        std::cout << "Philosopher " << id << " is thinking" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // pick up forks
        std::unique_lock<std::mutex> left_lock(forks[left_fork]);
        std::cout << "Philosopher " << id << " picks up left fork " << left_fork << std::endl;
        std::unique_lock<std::mutex> right_lock(forks[right_fork]);
        std::cout << "Philosopher " << id << " picks up right fork " << right_fork << std::endl;

        // eat for a while
        std::cout << "Philosopher " << id << " is eating" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // put down forks
        right_lock.unlock();
        left_lock.unlock();
        std::cout << "Philosopher " << id << " puts down forks" << std::endl;
    }
}

int main() {
    std::thread philosophers[kNumPhilosophers];
    for (int i = 0; i < kNumPhilosophers; ++i) {
        philosophers[i] = std::thread(philosopher, i);
    }
    for (int i = 0; i < kNumPhilosophers; ++i) {
        philosophers[i].join();
    }
    return 0;
}
