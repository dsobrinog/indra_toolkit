#pragma once

#include "Widget.h"

namespace indra_toolkit
{
    class SplitterWidget : public Widget
    {
    public:
        SplitterWidget() {}

        SplitterWidget(float TopHeight, float BottomHeight, float SplitterThickness, float MinPanelHeight)
         : m_TopHeight(TopHeight), m_BottomHeight(BottomHeight), m_SplitterThickness(SplitterThickness), m_MinPanelHeight(MinPanelHeight)
        {}

        virtual ~SplitterWidget() override
         {
            delete m_TopItem;
            delete m_BottomItem;
        };

        virtual void Draw() override 
        {
            // Draw top child
            ImGui::BeginChild("TopRegion", ImVec2(0, m_TopHeight), true);
            ImGui::TextWrapped("Top content here");
            m_TopItem->OnRender();
            ImGui::EndChild();

            // Splitter
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f,0.5f,0.5f,0.5f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f,1.0f,1.0f,1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f,0.7f,0.7f,0.7f));
            ImGui::Button("##Splitter", ImVec2(-1, m_SplitterThickness));
            ImGui::PopStyleColor(3);

            // Drag resize
            if (ImGui::IsItemActive())
            {
                float delta = ImGui::GetIO().MouseDelta.y;
                m_TopHeight += delta;
                m_BottomHeight -= delta;
            
                // Enforce minimum sizes
                if (m_TopHeight < m_MinPanelHeight)
                {
                    m_BottomHeight += m_TopHeight - m_MinPanelHeight;
                    m_TopHeight = m_MinPanelHeight; 
                }
                if (m_BottomHeight < m_MinPanelHeight)
                {
                    m_TopHeight += m_BottomHeight - m_MinPanelHeight;
                    m_BottomHeight = m_MinPanelHeight; 
                }
            }

            // Draw bottom child
            ImGui::BeginChild("BottomRegion", ImVec2(0, m_BottomHeight), true);
            ImGui::TextWrapped("Bottom content here");
            m_BottomItem->OnRender();
            ImGui::EndChild();
        }

        void AddItems(indra_toolkit::Widget* TopItem, indra_toolkit::Widget* BottomItem)
        {
            m_TopItem = TopItem;
            m_BottomItem = BottomItem; 
        }

    private:
        float m_TopHeight = 200.0f;
        float m_BottomHeight = 200.0f;
        float m_SplitterThickness = 4.0f;
        float m_MinPanelHeight = 50.0f;

        indra_toolkit::Widget* m_TopItem = nullptr;
        indra_toolkit::Widget* m_BottomItem = nullptr;
    };

}
