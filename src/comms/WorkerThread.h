#pragma once

#include <thread>
#include <chrono>
#include <atomic>
#include <memory>

namespace indra_toolkit
{
    // Forward declaration
    class IWorkerTask;

    class WorkerThread
    {
    public:
        WorkerThread(std::unique_ptr<IWorkerTask> task, int frequencyMs = 10);
        ~WorkerThread();

        void Start();
        void Stop();

    private:
        void Run();

        std::thread worker;
        std::atomic<bool> running;
        int frequency;
        std::unique_ptr<IWorkerTask> task_;
    };
}