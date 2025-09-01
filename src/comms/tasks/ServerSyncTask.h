#pragma once

#include "indra_toolkit/comms/IWorkerTask.h"
#include "indra_toolkit/comms/IClient.h"
#include <string>

namespace indra_toolkit
{
    class ServerSyncTask : public IWorkerTask
    {
    public:
         
        ServerSyncTask(IClient* client);
        
        void Tick() override;
    };
}