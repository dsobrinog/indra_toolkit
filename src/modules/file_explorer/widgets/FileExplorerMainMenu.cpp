#include "indra_toolkit/modules/file_explorer/widgets/FileExplorerMainMenu.h"
#include "indra_toolkit/widgets/containers/HorizontalContainer.h"

namespace indra_toolkit
{
    FEMainMenu::FEMainMenu()
    {
        MainHorizontalContainer = new HorizontalContainer();
    }

    FEMainMenu::~FEMainMenu()
    {

    }
    
    void FEMainMenu::Draw()
    {
        MainHorizontalContainer->OnRender();
    }
}