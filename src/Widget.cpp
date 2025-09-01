#include "Widget.h"
#include "widgets/containers/ContainerWidget.h"

void indra_toolkit::Widget::OnRender()
{
    ApplyLayout();
    Draw();
}

void indra_toolkit::Widget::Enable()
{
    enable = true;
    OnEnable();
}

void indra_toolkit::Widget::Disable()
{
    enable = false;
    OnDisable();
}

void indra_toolkit::Widget::OnCreation()
{
    
}

// VINCULAR CON EL DESTRUCTOR
void indra_toolkit::Widget::Destroy()
{
    enable = false;
    OnDestroy();
}

void indra_toolkit::Widget::SetWidgetName(const std::string& inWidgetName)
{
    widget_name = inWidgetName;
}

ImVec2 indra_toolkit::Widget::GetPosition() const
{
    return m_posVars.Position;
}

void indra_toolkit::Widget::SetPosition(ImVec2 inPos)
{
    m_posVars.Position = inPos;
}

ImVec2 indra_toolkit::Widget::GetSize() const
{
    return m_posVars.Size;
}

ImVec2 indra_toolkit::Widget::GetPixelSize() const
{
    return m_posVars.PixelSize;
}

void indra_toolkit::Widget::SetSize(ImVec2 inSize)
{
    m_posVars.Size = inSize;
}

std::pair<indra_toolkit::UIBehaviourMode, indra_toolkit::UIBehaviourMode> indra_toolkit::Widget::GetBehaviourModes() const
{
    return std::pair<indra_toolkit::UIBehaviourMode, indra_toolkit::UIBehaviourMode>(m_posVars.PosMode, m_posVars.SizeMode);
}

indra_toolkit::UIBehaviourMode indra_toolkit::Widget::GetPositionMode() const
{
    return m_posVars.PosMode;
}

indra_toolkit::UIBehaviourMode indra_toolkit::Widget::GetSizeMode() const
{
    return m_posVars.SizeMode;
}

void indra_toolkit::Widget::SetBehaviourModes(UIBehaviourMode positionMode, UIBehaviourMode sizeMode)
{
    m_posVars.PosMode = positionMode;
    m_posVars.SizeMode = sizeMode;
}

void indra_toolkit::Widget::SetPositionMode(UIBehaviourMode positionMode)
{
    m_posVars.PosMode = positionMode;
}

void indra_toolkit::Widget::SetSizeMode(UIBehaviourMode sizeMode)
{
    m_posVars.SizeMode = sizeMode;
}

indra_toolkit::UIAnchor indra_toolkit::Widget::GetAnchorMode() const 
{
    return m_posVars.Anchor;
}

void indra_toolkit::Widget::SetAnchorMode(indra_toolkit::UIAnchor anchorMode) 
{
    m_posVars.Anchor = anchorMode;
}

void indra_toolkit::Widget::ApplyLayout()
{
    ImVec2 calcPos = {0, 0};
    switch (m_posVars.PosMode)
    {
        case UIBehaviourMode::Absolute: //hardcodes to setted position in the window
        {
            calcPos = m_posVars.Position;
            break;
        }

        case UIBehaviourMode::Relative: //takes into account where the mouse previously was before adding to it
        {
            calcPos = { ImGui::GetCursorPos().x + m_posVars.Position.x, ImGui::GetCursorPos().y + m_posVars.Position.y};
            break;
        }

        case UIBehaviourMode::SpacePercent:  //takes into account the current content region you are in, and gives a posotion in it based on the percentage in position
        {
            // ImVec2 displaySize = ImGui::GetIO().DisplaySize;
            ImVec2 displaySize = ImGui::GetContentRegionAvail();
            ImVec2 absPos = ImVec2(
                displaySize.x * m_posVars.Position.x,   // e.g. (0.1f, 0.2f) = 10% X, 20% Y
                displaySize.y * m_posVars.Position.y
            );

            ImGui::SetCursorPos(absPos);
            break;
        }
    }

    ImGui::SetCursorPos(calcPos);
    
    switch(m_posVars.SizeMode)
    {
        case UIBehaviourMode::Absolute:  //directly sets size 
        {
            m_posVars.PixelSize = m_posVars.Size; 
            break;
        }
        case UIBehaviourMode::Relative:  //directly sets size
        {
            m_posVars.PixelSize = m_posVars.Size;
        }
        case UIBehaviourMode::SpacePercent:  //takes into account the current content region, and gives a size in it based on the percentage size
        {
            ImVec2 displaySize = ImGui::GetContentRegionAvail();

            ImVec2 absSize = ImVec2(
                displaySize.x * m_posVars.Size.x,       // e.g. (0.3f, 0.1f) = 30% width, 10% height
                displaySize.y * m_posVars.Size.y
            );

            m_posVars.PixelSize = absSize;
        }
    }
}

ImVec2 indra_toolkit::Widget::CalculateAnchorPoint()
{
    if(GetAnchorMode() == indra_toolkit::UIAnchor::None) return ImVec2(0, 0);

    ImVec2 available = (m_Container != nullptr) ? m_Container->GetPixelSize() : ImGui::GetContentRegionAvail();
    ImVec2 widgetSize = GetPixelSize();
    ImVec2 pos = {0.0f, 0.0f};

    switch(m_posVars.Anchor)
    {
        case UIAnchor::TopLeft:      pos = {0.0f, 0.0f}; break;
        case UIAnchor::Top:          pos = {available.x/2 - widgetSize.x/2, 0.0f}; break;
        case UIAnchor::TopRight:     pos = {available.x - widgetSize.x, 0.0f}; break;

        case UIAnchor::CenterLeft:   pos = {0.0f, available.y/2 - widgetSize.y/2}; break;
        case UIAnchor::CenterMiddle: pos = {available.x/2 - widgetSize.x/2, available.y/2 - widgetSize.y/2}; break;
        case UIAnchor::CenterRight:  pos = {available.x - widgetSize.x, available.y/2 - widgetSize.y/2}; break;

        case UIAnchor::BottomLeft:   pos = {0.0f, available.y - widgetSize.y}; break;
        case UIAnchor::BottomMiddle: pos = {available.x/2 - widgetSize.x/2, available.y - widgetSize.y}; break;
        case UIAnchor::BottomRight:  pos = {available.x - widgetSize.x, available.y - widgetSize.y}; break;

        case UIAnchor::Left:         pos = {0.0f, available.y/2 - widgetSize.y/2}; break;
        case UIAnchor::Middle:       pos = {available.x/2 - widgetSize.x/2, available.y/2 - widgetSize.y/2}; break;
        case UIAnchor::Right:        pos = {available.x - widgetSize.x, available.y/2 - widgetSize.y/2}; break;

        case UIAnchor::TopMiddle:    pos = {available.x/2 - widgetSize.x/2, 0.0f}; break;
        case UIAnchor::Center:       pos = {available.x/2 - widgetSize.x/2, available.y/2 - widgetSize.y/2}; break;
        case UIAnchor::Bottom:       pos = {available.x/2 - widgetSize.x/2, available.y - widgetSize.y}; break;

        default: break;
    }

    return available;
}