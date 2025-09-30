#pragma once

#include "imgui.h"
#include <string>
#include <iostream>
#include "interfaces/IPositionable.h"

namespace indra_toolkit
{
    class Layer;
    class ContainerWidget;

    enum class UIStyleFlags : uint32_t
    {
        None            = 0,
        BackgroundColor = 1 << 0,
        Padding         = 1 << 1
    };

    inline UIStyleFlags operator|(UIStyleFlags a, UIStyleFlags b) 
    {
        return static_cast<UIStyleFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
    }

    inline UIStyleFlags operator&(UIStyleFlags a, UIStyleFlags b) 
    {
        return static_cast<UIStyleFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
    }
    
    inline bool HasFlag(UIStyleFlags value, UIStyleFlags flag)
    {
        return (static_cast<uint32_t>(value) & static_cast<uint32_t>(flag)) != 0;
    }

    class Widget : public IPositionable
    {
        friend class Layer;

        public:
            Widget() = default;
            Widget(const PositionVars& posSettings, const std::string& widgetName) : m_posVars(posSettings), widget_name(widgetName) {}
            virtual ~Widget()
            {
                std::cout << "Widget: " << widget_name << " is being destroyed" << std::endl;
            }
            
            virtual void OnProcessData() {};
            virtual void OnRender();
            virtual void Draw() = 0;
            //Here you should use the style enum flag to push the styles however you want
            virtual void BeginStyle() {};
            //Here you need to pop as many styles as you pushed in BeginStyle
            virtual void EndStyle() {};

            void Enable();
            void Disable();
            inline bool IsEnabled() const { return enable; }
            void Destroy();
            
            std::string GetWidgetName() const {return widget_name; }
            void SetWidgetName(const std::string& inWidgetName);

            UIStyleFlags GetWidgetStyle() const { return m_style; }
            void SetWidgetStyle(UIStyleFlags styleFlags) { m_style = styleFlags; }
        
            void SetOwningLayer(Layer* owning_layer_);
            Layer* GetOwningLayer() const { return owning_layer; }
            
            bool IsDebugEnabled() const;
            void DrawDebug(bool draw_state) { draw_debug = draw_state; }

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

            void SetPositionVars(const PositionVars& position_vars_) { m_posVars = position_vars_; }

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

            bool enable = true;
            bool draw_debug = false;
            std::string layer_name = {"Default Layer"};
            std::string widget_name = {"Default Name"}; //For debug purposes mostly, I wanna know which widget is which

            ContainerWidget* m_Container = nullptr;  //The widget that contains this widget. Null for root widgets
            Layer* owning_layer = nullptr;
    };
}