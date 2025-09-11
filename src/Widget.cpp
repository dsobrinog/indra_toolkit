#include "indra_toolkit/Widget.h"
#include "indra_toolkit/widgets/containers/ContainerWidget.h"
#include <indra_toolkit/Utils.h>
#include <iostream>

void indra_toolkit::Widget::OnRender()
{
    ApplyLayout(); //Pick size and position

    BeginStyle();
    Draw();
    EndStyle();

    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();

        ImGui::Text("Size:      (%.1f, %.1f)",     m_posVars.Size.x,      m_posVars.Size.y);
        ImGui::Text("MinSize:   (%.1f, %.1f)",     m_posVars.MinSize.x,   m_posVars.MinSize.y);
        ImGui::Text("MaxSize:   (%.1f, %.1f)",     m_posVars.MaxSize.x,   m_posVars.MaxSize.y);
        ImGui::Text("PixelSize: (%.1f, %.1f)",     m_posVars.PixelSize.x, m_posVars.PixelSize.y);
        ImGui::Text("Position:  (%.1f, %.1f)",     m_posVars.Position.x,  m_posVars.Position.y);

        ImGui::EndTooltip();
    }
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

ImVec2 indra_toolkit::Widget::GetMinSize() const
{
    return m_posVars.MinSize;
}

ImVec2 indra_toolkit::Widget::GetMaxSize() const
{
    return m_posVars.MaxSize;
}

void indra_toolkit::Widget::SetSize(ImVec2 inSize)
{
    m_posVars.Size = inSize;
}

void indra_toolkit::Widget::SetMinSize(ImVec2 inMinSize)
{
    m_posVars.MinSize = inMinSize;
}

void indra_toolkit::Widget::SetMaxSize(ImVec2 inMaxSize)
{
    m_posVars.MaxSize = inMaxSize;
}

bool indra_toolkit::Widget::UseMinMaxSizes() const
{
    //Do we have a min or max size setted anywhere?
    return ((m_posVars.MinSize.x != 0 || m_posVars.MinSize.y != 0) || (m_posVars.MaxSize.x != 0 || m_posVars.MaxSize.y != 0));
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

indra_toolkit::UIVerticaAlignment indra_toolkit::Widget::GetVerticalAlignment() const
{
    return m_posVars.VerticalAlign;
}

void indra_toolkit::Widget::SetVerticalAlignment(UIVerticaAlignment verticalAlignment)
{
    m_posVars.VerticalAlign = verticalAlignment;
}

indra_toolkit::UIHorizontalAlignment indra_toolkit::Widget::GetHorizontalAlignment() const
{
    return m_posVars.HorizontalAlign;
}

void indra_toolkit::Widget::SetHorizontalAlignment(UIHorizontalAlignment horizontalAlignment)
{
    m_posVars.HorizontalAlign = horizontalAlignment;
}

void indra_toolkit::Widget::ApplyLayout()
{
    ApplySize();
    ApplyPosition();
}

void indra_toolkit::Widget::ApplySize()
{
    if(m_posVars.SizeMode != UIBehaviourMode::None)
    {
        switch(m_posVars.SizeMode)
        {
            case UIBehaviourMode::Absolute:  //directly sets size 
            {
                m_posVars.PixelSize = UseMinMaxSizes() ? clampVec2(m_posVars.Size, m_posVars.MinSize, m_posVars.MaxSize) : m_posVars.Size; 
                break;
            }
            case UIBehaviourMode::Relative:  //directly sets size
            {
                m_posVars.PixelSize = m_posVars.Size;
                break;
            }
            case UIBehaviourMode::SpacePercent:  //takes into account the current content region, and gives a size in it based on the percentage size
            {
                ImVec2 displaySize = (m_Container) ? m_Container->GetPixelSize() : GetFullContentSizeOfCurrentWindow();
                ImVec2 paddingSize = (m_Container) ? m_Container->GetAllPaddingBetweenItems() : ImVec2(0, 0);
                ImVec2 availSize = { displaySize.x - paddingSize.x, displaySize.y - paddingSize.y };
                ImVec2 absSize = ImVec2(
                    availSize.x * m_posVars.Size.x,       // e.g. (0.3f, 0.1f) = 30% width, 10% height
                    availSize.y * m_posVars.Size.y
                );

                m_posVars.PixelSize = UseMinMaxSizes() ? clampVec2(absSize, m_posVars.MinSize, m_posVars.MaxSize) : absSize; 
                break;
            }
        }
    }
    else m_posVars.PixelSize = UseMinMaxSizes() ? clampVec2(m_posVars.Size, m_posVars.MinSize, m_posVars.MaxSize) : m_posVars.Size;
}

void indra_toolkit::Widget::ApplyPosition()
{
    if(m_posVars.PosMode != UIBehaviourMode::None)
    {
        if(ShouldUseAnchor())
        {
            ApplyAnchor();
        }
        else if (ShouldUseAlignment())
        {
            ApplyVerticalAlignment();
            ApplyHorizontalAlignment();
        }

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
                ImVec2 displaySize = (m_Container != nullptr) ? m_Container->GetPixelSize() : GetFullContentSizeOfCurrentWindow();
                ImVec2 offset = ImVec2(
                    displaySize.x * m_posVars.Position.x,   // e.g. (0.1f, 0.2f) = 10% X, 20% Y
                    displaySize.y * m_posVars.Position.y
                );

                calcPos = { ImGui::GetCursorPos().x + offset.x, ImGui::GetCursorPos().y + offset.y};
                break;
            }
        }

        ImGui::SetCursorPos(calcPos);
    }  
}

void indra_toolkit::Widget::ApplyAnchor()
{
    if(GetAnchorMode() == indra_toolkit::UIAnchor::None) return;

    ImVec2 available = (m_Container != nullptr) ? m_Container->GetPixelSize() : GetFullContentSizeOfCurrentWindow();
    ImVec2 widgetSize = GetPixelSize();
    ImVec2 pos;

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

    ImGui::SetCursorPos(pos);
}

void indra_toolkit::Widget::ApplyVerticalAlignment()
{
    if(GetVerticalAlignment() == indra_toolkit::UIVerticaAlignment::None) return;

    ImVec2 available = (m_Container != nullptr) ? m_Container->GetPixelSize() : GetFullContentSizeOfCurrentWindow();
    ImVec2 widgetSize = GetPixelSize();
    float posY = ImGui::GetCursorPosY();
    
    switch(m_posVars.VerticalAlign)
    {
        case UIVerticaAlignment::Top:           posY = {0.0f}; break;
        case UIVerticaAlignment::Center:        posY = ((available.y/2) - (widgetSize.y/2)); break;
        case UIVerticaAlignment::Bottom:        posY = available.y - widgetSize.y; break;
        default: break;
    }

    ImGui::SetCursorPosY(posY);
}

void indra_toolkit::Widget::ApplyHorizontalAlignment()
{
    if(GetHorizontalAlignment() == indra_toolkit::UIHorizontalAlignment::None) return;

    ImVec2 available = (m_Container != nullptr) ? m_Container->GetPixelSize() : GetFullContentSizeOfCurrentWindow();
    ImVec2 widgetSize = GetPixelSize();
    float posX = ImGui::GetCursorPosX();

    switch(m_posVars.HorizontalAlign)
    {
        case UIHorizontalAlignment::Left:       posX = {0.0f}; break;
        case UIHorizontalAlignment::Middle:     posX = (available.x/2 - widgetSize.x/2); break;
        case UIHorizontalAlignment::Right:      posX = available.x - widgetSize.x; break;
        default: break;
    }

    ImGui::SetCursorPosX(posX);
}

bool indra_toolkit::Widget::ShouldUseAnchor() const
{
    bool UseAnchor = false;

    if((GetAnchorMode() != UIAnchor::None) && ((GetVerticalAlignment() == UIVerticaAlignment::None) && (GetHorizontalAlignment() == UIHorizontalAlignment::None)))
    {
        UseAnchor = true;
    }
    else if(GetAnchorMode() != UIAnchor::None)
    {
        std::cout << "A widget called: " << GetWidgetName() << "has a valid anchor, but is also trying to use an alignment.\n "
            << "Anchors and alignments are not compatible, so please use either anchors or alignemnts." << std::endl;
    }

    return UseAnchor; 
}

bool indra_toolkit::Widget::ShouldUseAlignment() const
{
    bool UseAlignment = false;

    if(((GetVerticalAlignment() != UIVerticaAlignment::None) || (GetHorizontalAlignment() != UIHorizontalAlignment::None)) && (GetAnchorMode() == UIAnchor::None))
    {
        UseAlignment = true;
    }
    else if((GetVerticalAlignment() != UIVerticaAlignment::None) || (GetHorizontalAlignment() != UIHorizontalAlignment::None))
    {
        std::cout << "A widget called: " << GetWidgetName() << "is trying to use aligment, but also has an anchor set.\n "
            << "Alignments and anchors are not compatible, so please use either alignemnts or anchors." << std::endl;
    }

    return UseAlignment; 
}