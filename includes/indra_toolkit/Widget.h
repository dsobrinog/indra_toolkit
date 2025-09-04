#pragma once

#include "imgui.h"
#include <string>
#include "interfaces/IPositionable.h"

namespace indra_toolkit
{
    class Layer;
    class ContainerWidget;

    enum class UIStyleFlags : uint32_t
    {
        None            = 0,
        BackgroundColor = 1 << 0
    };

    inline UIStyleFlags operator|(UIStyleFlags a, UIStyleFlags b) 
    {
        return static_cast<UIStyleFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
    }

    inline UIStyleFlags operator&(UIStyleFlags a, UIStyleFlags b) 
    {
        return static_cast<UIStyleFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
    }

    class Widget : public IPositionable
    {
        friend class Layer;

        public:
            virtual ~Widget() {}
            virtual void OnProcessData() {};
            virtual void OnRender();
            virtual void Draw() = 0;
            virtual void BeginStyle();
            virtual void EndStyle();

            void Enable();
            void Disable();
            inline bool IsEnabled() { return enable; }
            void Destroy();
            
            std::string GetWidgetName() const {return widget_name; }
            void SetWidgetName(const std::string& inWidgetName);

            ////////// Begin of IPositionable ///////////
            
            virtual ImVec2 GetPosition() const;
            virtual void SetPosition(ImVec2 inPos);

            virtual ImVec2 GetSize() const;
            virtual ImVec2 GetPixelSize() const;
            virtual ImVec2 GetMinSize() const;
            virtual ImVec2 GetMaxSize() const;
            virtual void SetSize(ImVec2 inSize);
            virtual void SetMinSize(ImVec2 inMinSize);
            virtual void SetMaxSize(ImVec2 inMaxSize);
            bool UseMinMaxSizes() const;

            virtual std::pair<UIBehaviourMode, UIBehaviourMode> GetBehaviourModes() const;
            virtual UIBehaviourMode GetPositionMode() const;
            virtual UIBehaviourMode GetSizeMode() const;

            virtual void SetBehaviourModes(UIBehaviourMode positionMode, UIBehaviourMode sizeMode);
            virtual void SetPositionMode(UIBehaviourMode positionMode);
            virtual void SetSizeMode(UIBehaviourMode sizeMode);

            virtual UIAnchor GetAnchorMode() const;
            virtual void SetAnchorMode(UIAnchor anchorMode);

            virtual UIVerticaAlignment GetVerticalAlignment() const;
            virtual void SetVerticalAlignment(UIVerticaAlignment verticalAlignment);
            virtual UIHorizontalAlignment GetHorizontalAlignment() const;
            virtual void SetHorizontalAlignment(UIHorizontalAlignment horizontalAlignment);

            //-----------------------------------------//
        
            void SetContainer(ContainerWidget* ContainerWidget) { m_Container = ContainerWidget; }

        protected:
            virtual void OnCreation();
            virtual void OnDestroy(){};

            virtual void OnEnable(){};
            virtual void OnDisable(){};

            ////////// Begin of IPositionable ///////////

            //sets cursor position based on stored position and updates size, so it can be used on Draw
            virtual void ApplyLayout();
            virtual void ApplySize();
            virtual void ApplyPosition();
            virtual void ApplyAnchor();
            virtual void ApplyVerticalAlignment();
            virtual void ApplyHorizontalAlignment();

        protected:
            PositionVars m_posVars;
            UIStyleFlags m_style;

        private:
            bool ShouldUseAnchor() const;
            bool ShouldUseAlignment() const;

            //-----------------------------------------//

            // Creador global de widgets ? Cada vez que creas un widget se asocia a un identifier global unico
            int unique_identifier = -1;
            bool enable = true;
            std::string layer_name = {"Default Layer"};
            std::string widget_name = {"Default Name"}; //For debug purposes mostly, I wanna know which widget is which

            ContainerWidget* m_Container = nullptr;  //The widget that contains this widget. Null for root widgets
    };
}