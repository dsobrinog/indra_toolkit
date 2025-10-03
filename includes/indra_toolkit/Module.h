#pragma once
#include <string>
#include "CommonDefinitions.h"

namespace indra_toolkit
{
    class ToolApplication; // Forward declared!

    class Module
    {
    public:
        Module(ToolApplication* app_, ToolModules module_identity_) : tool_app(app_), module_identity(module_identity_) {}
        virtual ~Module() = default;

        virtual bool OnInit() { return true; }
        virtual void OnUpdate() {}
        virtual void OnShutdown() {}

        //If true, means that the Initialization of the module is up to the user, 
        //and its safe to Shutdown the module manually.
        //The toolApplication won´t manage it for you. After being initialized, the Update
        //will be called. When Shutdown is called for the Tool, the module shutdown will also be called
        virtual bool IsDeferred() const { return false;} ;

        // Non-virtual function to update the module. It checks the update flag and then calls the virtual OnUpdate.
        void Update() {
            if (update_tick) {
                OnUpdate();
            }
        }

        /// @brief Make the module process OnUpdate each frame
        inline void EnableTick(bool enable){ update_tick = enable; }

        ToolModules GetIdentity() const { return module_identity; }

    protected:
        ToolApplication* tool_app = nullptr;

        bool update_tick = false;

    private:
        ToolModules module_identity;    //can only set this in constructor. Shouldn´t be able to change it.
    };
}
