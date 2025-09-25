#pragma once
#include "indra_toolkit/widgets/containers/ContainerWidget.h"
#include "indra_toolkit/Utils.h"
#include <vector>
#include <imgui.h>

#include <algorithm>


namespace indra_toolkit
{
    class HorizontalContainer : public ContainerWidget
    {
    public:
        using ContainerWidget::ContainerWidget;    

        virtual void OnProcessData() override {}

        virtual void Draw() override
        {
            ImGui::BeginChild(GetWidgetName().c_str(), GetPixelSize(), ImGuiChildFlags_Borders);
            // ImGui::BeginChild(GetWidgetName().c_str(), GetPixelSize());

            if(IsDebugEnabled()) DrawContentRegionBounds(255, 0, 0);

            for (size_t i = 0; i < m_Children.size(); ++i)
            {
                if (m_Children[i])
                {
                    if (m_Children[i]->IsEnabled())
                    {
                        m_Children[i]->OnRender();
                        if (i + 1 < m_Children.size())
                        ImGui::SameLine();
                    }
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
