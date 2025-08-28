#pragma once

#include <comms/SharedData.h>

namespace indra_toolkit
{
    class DataChannel
    {
        SharedData data = {};

    public:

        void SetData(SharedData& new_data){ data = new_data; }
        SharedData GetData(){ return data; }
    };
}