#pragma once

#include "imgui.h"
#include <utility>

namespace indra_toolkit
{

//Determines how the size and position of the widget will behave.
enum class UIBehaviourMode
{
    Absolute        = 0,    //determines position only taking into account the window (if in container, we ignore container auto pos logic)
                            //determines size directly, ignoring any container resizing
    Relative        = 1,    //determines position relative to parent container 
                            //determines size directly, ignoring any container resizing
    SpacePercent    = 2,    //determines position based on the avialable space, using percentage from 0 to 1 (Ex: 0.2f -> 20%)
                            //determines size based on the available space, using percentage from 0 to 1 (Ex: 0.2f -> 20%)
    None            = 3     //allows ImGui default behaviour
};

//Determines where the start point of the widget will be when its time to position it on its container
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

enum class UIVerticaAlignment
{
    Top             = 0,
    Center          = 1,
    Bottom          = 2,
    None            = 3                      
};

enum class UIHorizontalAlignment
{
    Left             = 0,
    Middle          = 1,
    Right          = 2,
    None            = 3  
};

//Important notes
  //If you leave everything as is, it will be the same as regular ImGui programming.
  //Min/Max size only take effect if you set them to something.
  //PixelSize is calculated based on the Size, and the SizeMode you use.
  //Position is used in conjunction with PosisitionMode to decide the actual position of the widget.
  //Anchors and Alignments are always relative to the container you are in.
  //Anchors and Alignments arent compatible, so choose one or the other.
struct PositionVars
{
    PositionVars()
    :   Size(0, 0), MinSize(0, 0), MaxSize(0, 0), PixelSize(0, 0), SizeMode(UIBehaviourMode::None),
        Position(0, 0), PosMode(UIBehaviourMode::None),
        Anchor(UIAnchor::None), VerticalAlign(UIVerticaAlignment::None), HorizontalAlign(UIHorizontalAlignment::None)
    {

    }

    ImVec2 Size;
    ImVec2 MinSize;
    ImVec2 MaxSize;
    ImVec2 PixelSize;
    UIBehaviourMode SizeMode;
    

    ImVec2 Position;
    UIBehaviourMode PosMode;

    UIAnchor Anchor;
    UIVerticaAlignment VerticalAlign;
    UIHorizontalAlignment HorizontalAlign;  
};

class IPositionable
{
public:
    virtual ~IPositionable() = default;

    ////////// Size methods //////////////////////   

    virtual ImVec2 GetSize() const = 0;
    virtual ImVec2 GetPixelSize() const = 0;
    virtual ImVec2 GetMinSize() const = 0;
    virtual ImVec2 GetMaxSize() const = 0;
    virtual void SetSize(ImVec2 inSize) = 0;
    virtual void SetMinSize(ImVec2 inMinSize) = 0;
    virtual void SetMaxSize(ImVec2 inMaxSize) = 0;
    virtual bool UseMinMaxSizes() const = 0;
    virtual UIBehaviourMode GetSizeMode() const = 0;
    virtual void SetSizeMode(UIBehaviourMode sizeMode) = 0;

    //-----------------------------------------//

    ////////// Position methods /////////////////

    virtual ImVec2 GetPosition() const = 0;
    virtual void SetPosition(ImVec2 inPos) = 0;
    virtual UIBehaviourMode GetPositionMode() const = 0;
    virtual void SetPositionMode(UIBehaviourMode positionMode) = 0;

    //-----------------------------------------//

    ////////// Behaviour methods ////////////////

    //Return in the pair 0 the Pos behaviour, and in the 1 the Size behaviour
    virtual std::pair<UIBehaviourMode, UIBehaviourMode> GetBehaviourModes() const = 0;
    virtual void SetBehaviourModes(UIBehaviourMode positionMode, UIBehaviourMode sizeMode) = 0;

    //-----------------------------------------//

    ////////// Anchor & Alignment methods ///////

    virtual UIAnchor GetAnchorMode() const = 0;
    virtual void SetAnchorMode(UIAnchor anchorMode) = 0;

    virtual UIVerticaAlignment GetVerticalAlignment() const = 0;
    virtual void SetVerticalAlignment(UIVerticaAlignment verticalAlignment) = 0;
    virtual UIHorizontalAlignment GetHorizontalAlignment() const = 0;
    virtual void SetHorizontalAlignment(UIHorizontalAlignment horizontalAlignment) = 0;

    //-----------------------------------------//

protected:
    ////////// Apply methods ///////////////////

    virtual void ApplyLayout() = 0;
    virtual void ApplySize() = 0;
    virtual void ApplyPosition() = 0;
    virtual void ApplyAnchor() = 0;
    virtual void ApplyVerticalAlignment() = 0;
    virtual void ApplyHorizontalAlignment() = 0;

    //-----------------------------------------//
};

}