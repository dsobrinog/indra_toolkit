#pragma once

#include <thread>
#include <chrono>

#include <comms/DataChannel.h>

namespace indra_toolkit
{
    class WorkerThread
    {
    protected:
    
        std::thread worker;
        DataChannel* channel;
        bool running;

        int frecuency = 10; // Miliseconds to fetch and send data

    public:
            WorkerThread(DataChannel* ch) : channel(ch) {}

        void Start()
        {
            running = true;
            worker = std::thread([this]()
            {
                this->Run();
            });
        }

        void Stop()
        {
            running = false;
            if (worker.joinable()) worker.join();
        }

        void Run()
        {
            using namespace std::chrono;

            const milliseconds interval(frecuency); // X milliseconds between iterations
            while (running)
            {
                auto startTime = steady_clock::now();

                // --- RECEIVE DATA FROM SERVER ---
                SharedData data;
                data.message = "Message received from Executive!";
                data.value = -1;
                channel->SetData(data);

                // --- SEND DATA TO SERVER ---
                SharedData current = channel->GetData();
                // std::cout << "[Worker] Sending value: " << current.value
                //         << " msg: " << current.message << std::endl;

                // --- Limit frequency ---
                auto endTime = steady_clock::now();
                auto elapsed = duration_cast<milliseconds>(endTime - startTime);
                if (elapsed < interval)
                {
                    std::this_thread::sleep_for(interval - elapsed);
                }
            }
        }
    };
};
