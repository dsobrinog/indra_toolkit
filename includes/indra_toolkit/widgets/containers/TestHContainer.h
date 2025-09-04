#pragma once
#include "indra_toolkit/widgets/containers/ContainerWidget.h"
#include <vector>
#include <imgui.h>

#include <algorithm>


namespace indra_toolkit
{
    class TestHContainer : public ContainerWidget
    {
    public:

        virtual void OnProcessData() override {}

        virtual void Draw() override
        {
            // ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
            
            for (size_t i = 0; i < m_Children.size(); ++i)
            {
                if (m_Children[i])
                {
                    m_Children[i]->OnRender();
                    if (i + 1 < m_Children.size())
                        ImGui::SameLine();
                }
                else
                {
                    RemoveChild(m_Children[i]);
                }
            }

            // ImGui::PopStyleVar();
        }
    };
}
