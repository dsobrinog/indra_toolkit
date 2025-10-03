#pragma once 

#include "Widget.h"
#include <vector>
#include <string>
#include <imgui.h>
#include <algorithm>

namespace indra_toolkit
{
    class HorizontalTable : public Widget
    {
        std::vector<Widget*> m_Children;
        std::string m_TableName;
    public:
        
        HorizontalTable(std::string TableName, float Height) : m_TableName(TableName) { SetSize({0.f, Height}); }

        void AddChild(Widget* child) { m_Children.push_back(child); }
        void RemoveChild(Widget* child)
        {
            auto it = std::find(m_Children.begin(), m_Children.end(), child);
            if (it != m_Children.end())
            {
                m_Children.erase(it);
            }
        }

        virtual void Draw() override
        {
            int n = static_cast<int>(m_Children.size());
            if (n == 0) return;
            
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.5f, 0.5f, 0.5f, 1.0f)); // child background

            // ImGui::BeginChild("TableBg", ImVec2(0, m_Height), false); // 'false' = no border

            // Begin a table with one row, n columns
            if (ImGui::BeginTable(m_TableName.c_str(), n, ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_RowBg, GetPixelSize()))
            {
                ImGui::TableNextRow();

                for (int i = 0; i < n; i++)
                {
                    if (m_Children[i]->IsEnabled())
                    {
                        ImGui::TableSetColumnIndex(i);
                        m_Children[i]->OnRender();
                    }
                }

                ImGui::EndTable();
            }

            // ImGui::EndChild();
            ImGui::PopStyleColor();
            ImGui::PopStyleVar();
        }
    };
}