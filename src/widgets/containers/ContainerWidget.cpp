#include "containers/ContainerWidget.h"

namespace indra_toolkit
{
    int ContainerWidget::GetIndexOfChild(std::string ChildName)
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

}