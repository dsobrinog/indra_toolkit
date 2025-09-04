#include "WorkerThread.h"
#include "indra_toolkit/comms/IWorkerTask.h"
#include <thread>
#include <chrono>

namespace indra_toolkit
{
    WorkerThread::WorkerThread(std::unique_ptr<IWorkerTaskBase> task, int frequencyMs)
        : task_(std::move(task)),
          frequency(frequencyMs),
          running(false)
    {
    }

    WorkerThread::~WorkerThread()
    {
        if(running)
            Stop();
    }

    void WorkerThread::Start()
    {
        if (running) return;
        running = true;
        worker = std::thread([this] { Run(); });
    }

    void WorkerThread::Stop()
    {
        if(running)
        {
            running = false;
            if (worker.joinable())
                worker.join();
        }
    }

    void WorkerThread::Run()
    {
        using namespace std::chrono;
        const milliseconds interval(frequency);

        while (running)
        {
            auto start = steady_clock::now();

            if (task_)
            {
                task_->ProcessCommands();
                task_->Tick();
            }

            auto elapsed = steady_clock::now() - start;
            if (elapsed < interval)
                std::this_thread::sleep_for(interval - elapsed);
        }
    }
}