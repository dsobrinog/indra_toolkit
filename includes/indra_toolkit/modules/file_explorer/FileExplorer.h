#pragma once

#include "indra_toolkit/Module.h"
#include "indra_toolkit/layers/InteractiveLayer.h"


namespace indra_toolkit
{

    #define PATH_MAX 500

    class FEMainMenu;

    /// @brief Contains functionality for searching folders, choosing files, etc.
    class FileExplorer : public Module
    {
    public:
        FileExplorer(ToolApplication* app_, ToolModules moduleIdentity_) : Module(app_, moduleIdentity_){}

        virtual bool OnInit() override;
        virtual void OnUpdate() override;
        virtual void OnShutdown() override;

        virtual bool IsDeferred() const override { return true; }

        void SetFatherLayer(InteractiveLayer* in_interactive_layer_) {interactive_layer = in_interactive_layer_; }

private:

    void TestExplore();

    private:
        InteractiveLayer* interactive_layer = nullptr;
        FEMainMenu* main_menu = nullptr; 
    };
}