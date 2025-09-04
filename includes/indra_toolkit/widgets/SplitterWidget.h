#pragma once

#include "indra_toolkit/widgets/containers/ContainerWidget.h"
#include "indra_toolkit/widgets/containers/HorizontalContainer.h"

namespace indra_toolkit
{
    class SplitterWidget : public ContainerWidget
    {
    public:
        SplitterWidget() {}

        SplitterWidget(float TopHeight, float BottomHeight, float SplitterThickness, float MinPanelHeight)
         : m_TopHeight(TopHeight), m_BottomHeight(BottomHeight), m_SplitterThickness(SplitterThickness), m_MinPanelHeight(MinPanelHeight)
        {

        }

        virtual void Draw() override 
        {
            // ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            // Draw top child
            ImGui::BeginChild("TopRegion", ImVec2(0, m_TopHeight), ImGuiChildFlags_Borders);
            ImGui::TextWrapped("Top content here");
            GetTopWidget()->OnRender();
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
            ImGui::BeginChild("BottomRegion", ImVec2(0, m_BottomHeight), ImGuiChildFlags_Borders);
            ImGui::TextWrapped("Bottom content here");
            GetBottomWidget()->OnRender();
            ImGui::EndChild();

            // ImGui::PopStyleVar();
        }

        Widget* GetTopWidget() const 
        {
            if(m_Children.size() > 0)
                return m_Children[0];
            else return nullptr;
        }

        Widget* GetBottomWidget() const 
        {
            if(m_Children.size() > 1)
                return m_Children[1];
            else return nullptr;
        }

    private:
        float m_TopHeight = 200.0f;
        float m_BottomHeight = 200.0f;
        float m_SplitterThickness = 4.0f;
        float m_MinPanelHeight = 50.0f;
    };

}
