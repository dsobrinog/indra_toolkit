#include "indra_toolkit/widgets/MainMenuWidget.h"
#include "imgui_internal.h"


void indra_toolkit::MainMenuBarWidget::OnProcessData()
{
}

void indra_toolkit::MainMenuBarWidget::Draw()
{
    if(m_windowPadding.x != -1 || m_windowPadding.y != -1) ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, m_windowPadding); 

    if (ImGui::BeginMenuBar())
    {
        for (const auto& menu : menus)
            RenderMenuElement(menu);

        ImGui::EndMenuBar();
    }

    if(m_windowPadding.x != -1 || m_windowPadding.y != -1) ImGui::PopStyleVar();
}

void indra_toolkit::MainMenuBarWidget::AddMenu(const MenuElement &menu)
{
    menus.push_back(menu);
}

void indra_toolkit::MainMenuBarWidget::RenderMenuElement(const MenuElement &element)
{
    if(element.SpacingFromPrev.x != 0 || element.SpacingFromPrev.y != 0) ImGui::SameLine(element.SpacingFromPrev.x, element.SpacingFromPrev.y);

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
        if (!element.HasChild())
        {
            ImGui::PushID(element.name.c_str());

            if (element.icon)
            {
                ImGui::Image((void*)(intptr_t)element.icon, ImVec2(16,16));
                ImGui::SameLine();
            }

            if (ImGui::MenuItem(element.name.c_str(),
                                element.shortcut.empty() ? nullptr : element.shortcut.c_str()))
            {
                if (element.callback)
                    element.callback();
            }

            ImGui::PopID();
        }

    }

    if(element.SpacingToNext.x != 0 || element.SpacingToNext.y != 0) ImGui::SameLine(element.SpacingToNext.x, element.SpacingToNext.y);
}

