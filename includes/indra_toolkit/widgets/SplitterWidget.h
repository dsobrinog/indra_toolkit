#pragma once

#include "indra_toolkit/widgets/containers/ContainerWidget.h"
#include "indra_toolkit/widgets/containers/HorizontalContainer.h"
#include <iostream>

namespace indra_toolkit
{
    class SplitterWidget : public ContainerWidget
    {
    public:
        SplitterWidget() { InitTopAndBottomContainers(); }

        SplitterWidget(float SplitterRatio, float SplitterThickness, float MinPanelRatio)
         : m_SplitterRatio(SplitterRatio), m_SplitterThickness(SplitterThickness), m_MinPanelRatio(MinPanelRatio)
        {
            InitTopAndBottomContainers();
        }

        void InitTopAndBottomContainers()
        {
            PositionVars posVars;
            posVars.PosMode = UIBehaviourMode::Relative;
            posVars.SizeMode = UIBehaviourMode::Absolute;
            HorizontalContainer* topContainer = new HorizontalContainer(posVars, "Splitter Top");
            HorizontalContainer* bottomContainer = new HorizontalContainer(posVars, "Splitter Bottom");
            AddChild(topContainer);
            AddChild(bottomContainer);
        }

        virtual void Draw() override 
        {  
            // DrawContentRegionBounds(255, 0, 0);

            ImVec2 avail = GetPixelSize(); // free space in parent container
            float totalHeight = avail.y;    
            float topHeight;
            float bottomHeight;

            if(GetTopWidget()->IsEnabled() && GetBottomWidget()->IsEnabled())
            {
                m_SplitterRatio = std::max(m_MinPanelRatio, std::min(1.0f - m_MinPanelRatio, m_SplitterRatio));
                topHeight = totalHeight * m_SplitterRatio;
                bottomHeight = totalHeight - topHeight - m_SplitterThickness;
            }
            else if(GetTopWidget()->IsEnabled() && !GetBottomWidget()->IsEnabled())
            {
                topHeight = totalHeight;
            }
            else if(!GetTopWidget()->IsEnabled() && GetBottomWidget()->IsEnabled())
            {
                bottomHeight = totalHeight;
            }

            GetTopWidget()->SetSize({avail.x, topHeight});
            GetBottomWidget()->SetSize({avail.x, bottomHeight});

            // Draw top child
            if(GetTopWidget()->IsEnabled()) GetTopWidget()->OnRender();

            if(BothPartsActive())
            {
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
                    m_SplitterRatio += delta / totalHeight; // adjust ratio by relative drag
                }
            }
            
            // Draw bottom child
            if(GetBottomWidget()->IsEnabled()) GetBottomWidget()->OnRender();
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

        void AddWidgetTop(Widget* widget)
        {
            ContainerWidget* containerWidget = static_cast<ContainerWidget*>(GetTopWidget());
            containerWidget->AddChild(widget);
        }

        void AddWidgetBottom(Widget* widget)
        {
            ContainerWidget* containerWidget = static_cast<ContainerWidget*>(GetBottomWidget());
            containerWidget->AddChild(widget);
        }     

        void EnableTop(bool state) 
        {
            state ? GetTopWidget()->Enable() : GetTopWidget()->Disable();
        }

        void EnableBottom(bool state) 
        { 
            state ? GetBottomWidget()->Enable() : GetBottomWidget()->Disable();
        } 

        bool IsTopEnabled() const    { return GetTopWidget()->IsEnabled(); } 
        bool IsBottomEnabled() const { return GetBottomWidget()->IsEnabled(); } 
        bool BothPartsActive() const { return IsTopEnabled() && IsBottomEnabled(); }
        
    private:
        float m_SplitterRatio = 0.5f;          // top panel takes 50% of available space
        float m_SplitterThickness = 4.0f;
        float m_MinPanelRatio = 0.2f;
    };

}
