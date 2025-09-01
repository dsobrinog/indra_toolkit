#pragma once
#include "indra_toolkit/Widget.h"
#include <vector>
#include <imgui.h>

#include <algorithm>


namespace indra_toolkit
{
    class HorizontalContainer : public Widget
    {
        std::vector<Widget*> m_Children;
    
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

        virtual void Draw() override
        {
            ImGui::BeginChild(GetWidgetName().c_str(), GetPixelSize());
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
            ImGui::EndChild();
        }

    };
}
