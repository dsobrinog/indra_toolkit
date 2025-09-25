#include "indra_toolkit/modules/file_explorer/FileExplorer.h"
#include "indra_toolkit/modules/file_explorer/widgets/FileExplorerMainMenu.h"

namespace indra_toolkit
{

bool FileExplorer::OnInit() 
{
    std::cout << "FileExplorer Start!" << std::endl;
    if(!main_menu && interactive_layer) main_menu = &interactive_layer->CreateWidget<indra_toolkit::FEMainMenu>(interactive_layer);
    else if(main_menu) main_menu->SetOpen(true);

    TestExplore();

    return true;
}

void FileExplorer::OnUpdate()
{
   
}

void FileExplorer::TestExplore()
{
    // fs::path cwd = fs::current_path();
    // std::cout << "Current working directory: " << cwd << std::endl;
    // // 2. Iterate over directory contents
    // for (const auto& entry : fs::directory_iterator(cwd)) 
    // {
    //     std::string name = entry.path().filename().string();
    //     if(!name.empty() && name[0] == '.') continue;

    //     if (entry.is_directory()) {
    //         std::cout << "[DIR]  " << entry.path().filename().string() << std::endl;
    //     } else if (entry.is_regular_file()) {
    //         std::cout << "[FILE] " << entry.path().filename().string() << std::endl;
    //     } else {
    //         std::cout << "[OTHER] " << entry.path().filename().string() << std::endl;
    //     }
    // }
}

void FileExplorer::OnShutdown()
{
    if(!interactive_layer) return;
    
    interactive_layer->RemoveWidget(main_menu);
}

} //indra_toolkit