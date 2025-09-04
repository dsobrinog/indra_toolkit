// IWorkerTaskBase.h
#pragma once

class IWorkerTaskBase
{
public:
    virtual ~IWorkerTaskBase() = default;

    virtual void Initialize() = 0;
    virtual void Tick() = 0;
    virtual void ProcessCommands() = 0;
};
