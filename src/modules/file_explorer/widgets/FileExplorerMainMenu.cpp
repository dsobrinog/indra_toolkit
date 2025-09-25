#include "indra_toolkit/modules/file_explorer/widgets/FileExplorerMainMenu.h"
#include "indra_toolkit/widgets/containers/HorizontalContainer.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace indra_toolkit
{

FEMainMenu::FEMainMenu(Layer* owning_layer_)
{
    main_horizontal_container = new HorizontalContainer();
    main_horizontal_container->SetOwningLayer(owning_layer_);
}
FEMainMenu::~FEMainMenu()
{
}

void FEMainMenu::Draw()
{
    if(is_open) ImGui::OpenPopup("File Explorer Popup");
    if (ImGui::BeginPopupModal("File Explorer Popup", &is_open))
    {
        // main_horizontal_container->OnRender();
        static fs::path current_path = fs::current_path();
        ImGui::Text("Current path: %s", current_path.string().c_str());
        if (ImGui::Button(".. (Up)")) 
        {
            current_path = current_path.parent_path();
        }
        ImGui::Separator();
        for (auto& entry : fs::directory_iterator(current_path)) 
        {
            std::string name = entry.path().filename().string();
            if (entry.is_directory()) {
                if (ImGui::Selectable((name + "/").c_str(), false))
                {
                    current_path = entry.path(); // navigate into folder
                }
            } 
            else 
            {
                if (ImGui::Selectable(name.c_str(), false))
                {
                    std::cout << "Selected file: " << entry.path() << std::endl;
                }
            }
        }
        
        ImGui::EndPopup();
    }
}

} //indra_toolkit