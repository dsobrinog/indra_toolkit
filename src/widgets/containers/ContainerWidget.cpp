#include "indra_toolkit/widgets/containers/ContainerWidget.h"


namespace indra_toolkit
{
    void ContainerWidget::OnProcessData()
    {
        for (size_t i = 0; i < m_Children.size(); i++)
        {
            m_Children[i]->OnProcessData();
        }
    }

    int ContainerWidget::GetIndexOfChild(const std::string& ChildName)
    {
        for (size_t i = 0; i < m_Children.size(); i++)
        {
            if(m_Children[i]->GetWidgetName() == ChildName)
            {
                return i;
            }
        }
        
        return -1;
    }

    ImVec2 ContainerWidget::GetItemPadding() const
    {
        ImVec2 ItemPadding;
        ImGuiStyle& style = ImGui::GetStyle();
        if(HasFlag(m_style, indra_toolkit::UIStyleFlags::ItemSpacing))
        {
            ItemPadding = m_ItemPadding; //use custom
        }
        else 
        {
            ItemPadding = style.ItemSpacing; //use ImGui ItemSpacing
        }

        return ItemPadding;
    }

    ImVec2 ContainerWidget::GetAllPaddingBetweenItems()
    {
        ImVec2 ItemPadding = GetItemPadding();
        int numOfItems = GetNumOfChilds() -1;

        return { ItemPadding.x * numOfItems, ItemPadding.y};
    }

    ImVec2 ContainerWidget::GetSize() const
    {
        if(m_posVars.Size.x == 0 && m_posVars.Size.y == 0) return GetFullContentSizeOfCurrentWindow();
        else return m_posVars.Size;
    }

    ImVec2 ContainerWidget::GetPixelSize() const
    {
        if(m_posVars.PixelSize.x == 0 && m_posVars.PixelSize.y == 0) return GetFullContentSizeOfCurrentWindow();
        else return m_posVars.PixelSize;
    }

    void ContainerWidget::BeginStyle()
    {
        if(HasFlag(m_style, UIStyleFlags::BackgroundColor))
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, m_bgColor);
        }

        if(HasFlag(m_style, UIStyleFlags::Padding))
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, m_WindowPadding);
        }

        if(HasFlag(m_style, UIStyleFlags::ItemSpacing))
        {
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, m_ItemPadding);
        }
    }

    void ContainerWidget::EndStyle()
    {
        if(HasFlag(m_style, UIStyleFlags::BackgroundColor))
        {
            ImGui::PopStyleColor();
        }

        if(HasFlag(m_style, UIStyleFlags::Padding))
        {
            ImGui::PopStyleVar();
        }

        if(HasFlag(m_style, UIStyleFlags::ItemSpacing))
        {
            ImGui::PopStyleVar();
        }
    }

} // namespace indra_toolkit
