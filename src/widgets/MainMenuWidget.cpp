#include "widgets/MainMenuWidget.h"

void indra_toolkit::MainMenuWidget::OnProcessData()
{
}
void indra_toolkit::MainMenuWidget::OnRender()
{
    if (ImGui::BeginMainMenuBar())
    {
        for (const auto& menu : menus)
            RenderMenuElement(menu);

        ImGui::EndMainMenuBar();
    }
}
void indra_toolkit::MainMenuWidget::AddMenu(const MenuElement &menu)
{
    menus.push_back(menu);
}

void indra_toolkit::MainMenuWidget::RenderMenuElement(const MenuElement &element)
{
     if (element.HasChild())
        {
            if (ImGui::BeginMenu(element.name.c_str()))
            {
                for (const auto& child : element.childs)
                    RenderMenuElement(child);

                ImGui::EndMenu();
            }
        }
        else
        {
            if (ImGui::MenuItem(element.name.c_str()))
            {
                if (element.callback)
                    element.callback();
            }
        }
}
