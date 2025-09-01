#pragma once
#include "indra_toolkit/Widget.h"
#include <vector>
#include <imgui.h>

#include <algorithm>


namespace indra_toolkit
{
    class ContainerWidget : public Widget
    {
    public:
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

        int GetNumOfChilds() const { return m_Children.size(); }

        //returns index of the child with the name passed. If not found it returns -1
        int GetIndexOfChild(std::string ChildName);

    private:
        std::vector<Widget*> m_Children;

    };
}
