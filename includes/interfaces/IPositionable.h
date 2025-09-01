#pragma once

#include "imgui.h"
#include <utility>

namespace indra_toolkit
{

enum class UIBehaviourMode
{
    Absolute        = 0,    //determines position only taking into account the window (if in container, we ignore container auto pos logic)
                            //determines size directly, ignoring any container resizing
    Relative        = 1,    //determines position relative to parent container 
                            //determines size directly, ignoring any container resizing
    SpacePercent    = 2     //determines position AND size based on the avialable space, using percentage from 0 to 1 as unit
};

enum class UIAnchor
{
    Left            = 0,
    Middle          = 1,
    Right           = 2,
    Top             = 3,
    Center          = 4,
    Bottom          = 5,
    TopLeft         = 6,
    TopRight        = 7,
    TopMiddle       = 8,
    CenterLeft      = 9,
    CenterRight     = 10,
    CenterMiddle    = 11,
    BottomLeft      = 12,
    BottomRight     = 13,
    BottomMiddle    = 14,
    None            = 15
};


struct PositionVars
{
    PositionVars()
    :   Size(0, 0), PixelSize(0, 0), Position(0, 0),
        PosMode(UIBehaviourMode::Relative), SizeMode(UIBehaviourMode::Relative), Anchor(UIAnchor::None)
    {

    }

    ImVec2 Size;
    ImVec2 PixelSize;
    ImVec2 Position;
    UIBehaviourMode PosMode;
    UIBehaviourMode SizeMode;
    UIAnchor Anchor;
};

class IPositionable
{
public:
    virtual ~IPositionable() = default;

    virtual ImVec2 GetPosition() const = 0;
    virtual void SetPosition(ImVec2 inPos) = 0;

    virtual ImVec2 GetSize() const = 0;
    virtual ImVec2 GetPixelSize() const = 0;
    virtual void SetSize(ImVec2 inSize) = 0;

    //Return in the pair 0 the Pos behaviour, and in the 1 the Size behaviour
    virtual std::pair<UIBehaviourMode, UIBehaviourMode> GetBehaviourModes() const = 0;
    virtual UIBehaviourMode GetPositionMode() const = 0;
    virtual UIBehaviourMode GetSizeMode() const = 0;
    virtual void SetBehaviourModes(UIBehaviourMode positionMode, UIBehaviourMode sizeMode) = 0;
    virtual void SetPositionMode(UIBehaviourMode positionMode) = 0;
    virtual void SetSizeMode(UIBehaviourMode sizeMode) = 0;

    virtual UIAnchor GetAnchorMode() const = 0;
    virtual void SetAnchorMode(UIAnchor anchorMode) = 0;

    virtual void ApplyLayout() = 0;
};

}