#pragma once

#include "indra_toolkit/Widget.h"
#include <indra_toolkit/Utils.h>

#include <vector>
#include <algorithm>
#include <imgui.h>


namespace indra_toolkit
{
    class ContainerWidget : public Widget
    {
    public:
        virtual ~ContainerWidget()
        {
            for (Widget* child : m_Children)
            {
                delete child;
            }

            m_Children.clear();
        }

        void AddChild(Widget* child) 
        {
            m_Children.push_back(child);
            child->SetContainer(this);
        }

        void RemoveChild(Widget* child)
        {
            auto it = std::find(m_Children.begin(), m_Children.end(), child);
            if (it != m_Children.end())
            {
                m_Children.erase(it);
                child->SetContainer(nullptr);
            }
        }

        int GetNumOfChilds() const { return m_Children.size() - 1; }
        //returns index of the child with the name passed. If not found it returns -1
        int GetIndexOfChild(const std::string& ChildName);

        ImVec2 GetItemPadding();
        void SetItemPadding(ImVec2 InPadding) { m_ItemPadding = InPadding; } 
        ImVec2 GetAllPaddingBetweenItems();

        void SetBackgroundColor(ImVec4 bgColor) { m_bgColor = bgColor; }
        ImVec4 GetBackgroundColor() const { return m_bgColor; }

        virtual ImVec2 GetSize() const override;
        virtual ImVec2 GetPixelSize() const override;

    protected:
        std::vector<Widget*> m_Children;

        ImVec2 m_ItemPadding = { -1, -1 };          //Padding between the elements of the container (if its (-1, -1), we use ImGuiStyle ItemSpacing)     
        ImVec4 m_bgColor = { 0.f, 0.f, 0.f, 0.f };  
    };
}
