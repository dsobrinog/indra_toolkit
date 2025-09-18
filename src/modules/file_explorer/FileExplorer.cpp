#include "indra_toolkit/modules/file_explorer/FileExplorer.h"
#include "indra_toolkit/modules/file_explorer/widgets/FileExplorerMainMenu.h"

namespace indra_toolkit
{
    bool FileExplorer::OnInit() 
    {
        std::cout << "FileExplorer Start!" << std::endl;

        interactive_layer = tool_app->RegisterLayerPtr<indra_toolkit::InteractiveLayer>(tool_app);
        const ImVec4 interactive_bg(1.f, 0.3f, 0.3f, 1.f);
        interactive_layer->SetBackgroundColor(ImVec4 (0.f, 0.f, 0.f, 1.f));
        interactive_layer->SetSize(tool_app->GetMainWindowSize());
        interactive_layer->SetName("File Explorer");
        interactive_layer->SetWindowPadding({0.f, 0.f});
        interactive_layer->SetWindowFlags(ImGuiWindowFlags_None);

        indra_toolkit::FEMainMenu& mainMenu = interactive_layer->CreateWidget<indra_toolkit::FEMainMenu>();

        return true;
    }

    void FileExplorer::OnUpdate()
    {
        
    }

    void FileExplorer::OnShutdown()
    {
        if(!interactive_layer) return;
        
        tool_app->UnregisterLayer(interactive_layer);
    }
}