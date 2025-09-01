#include "indra_toolkit/widgets/MainMenuWidget.h"

void indra_toolkit::MainMenuBarWidget::OnProcessData()
{
}

void indra_toolkit::MainMenuBarWidget::OnRender()
{
    if(m_windowPadding.x != -1 || m_windowPadding.y != -1) ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, m_windowPadding); 

    if (ImGui::BeginMainMenuBar())
    {
        for (const auto& menu : menus)
            RenderMenuElement(menu);

        ImGui::EndMainMenuBar();
    }

    if(m_windowPadding.x != -1 || m_windowPadding.y != -1) ImGui::PopStyleVar();
}

void indra_toolkit::MainMenuBarWidget::AddMenu(const MenuElement &menu)
{
    menus.push_back(menu);
}

void indra_toolkit::MainMenuBarWidget::RenderMenuElement(const MenuElement &element)
{
    if(element.SpacingFromPrevious.x != 0 || element.SpacingFromPrevious.y != 0) ImGui::SameLine(element.SpacingFromPrevious.x, element.SpacingFromPrevious.y);

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

    if(element.SpacingToNext.x != 0 || element.SpacingToNext.y != 0) ImGui::SameLine(element.SpacingToNext.x, element.SpacingToNext.y);
}
