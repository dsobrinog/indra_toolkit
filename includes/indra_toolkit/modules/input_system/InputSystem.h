#pragma once
#include "indra_toolkit/ToolApplication.h"
#include "indra_toolkit/Module.h"

#include <string>


namespace indra_toolkit
{
    class InputSystem : public Module
    {
    public:
        InputSystem(ToolApplication* app_, ToolModules moduleIdentity_) : Module(app_, moduleIdentity_){};

        virtual void OnShutdown() override;
        virtual bool IsDeferred() const { return false; }
        
    private:
      
    };
}
