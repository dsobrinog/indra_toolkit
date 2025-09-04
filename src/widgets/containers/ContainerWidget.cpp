#include "indra_toolkit/widgets/containers/ContainerWidget.h"

namespace indra_toolkit
{
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

    ImVec2 ContainerWidget::GetItemPadding()
    {
        ImVec2 ItemPadding;
        ImGuiStyle& style = ImGui::GetStyle();
        if(m_ItemPadding.x == -1) ItemPadding.x = style.ItemSpacing.x;
        else ItemPadding.x = m_ItemPadding.x;
        if(m_ItemPadding.y == -1) ItemPadding.y = style.ItemSpacing.y;
        else ItemPadding.y = m_ItemPadding.y;

        return ItemPadding;
    }

    ImVec2 ContainerWidget::GetAllPaddingBetweenItems()
    {
        ImVec2 ItemPadding = GetItemPadding();
        int numOfItems = GetNumOfChilds();

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

} // namespace indra_toolkit


