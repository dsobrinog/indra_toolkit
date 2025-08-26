#pragma once 

#include "Widget.h"
#include <vector>
#include <imgui.h>
#include <algorithm>

namespace indra_toolkit
{
    class HorizontalTable : public Widget
    {
        std::vector<Widget*> m_Children;
        float m_Height = 0;
    public:

        void AddChild(Widget* child) { m_Children.push_back(child); }
        void RemoveChild(Widget* child)
        {
            auto it = std::find(m_Children.begin(), m_Children.end(), child);
            if (it != m_Children.end())
            {
                m_Children.erase(it);
            }
        }

        virtual void OnProcessData() override {}

        virtual void OnRender() override
        {
            int n = static_cast<int>(m_Children.size());
            if (n == 0) return;

            // Begin a table with one row, n columns
            if (ImGui::BeginTable("HorizontalContainerTable", n, ImGuiTableFlags_SizingStretchProp))
            {
                ImGui::TableNextRow();

                for (int i = 0; i < n; i++)
                {
                    ImGui::TableSetColumnIndex(i);
                    m_Children[i]->OnRender();
                }

                ImGui::EndTable();
            }
        }
    };
}