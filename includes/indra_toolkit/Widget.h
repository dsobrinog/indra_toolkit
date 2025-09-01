#pragma once

#include "imgui.h"
#include <string>
#include "interfaces/IPositionable.h"

namespace indra_toolkit
{
    class Layer;
    class ContainerWidget;

    class Widget : public IPositionable
    {
        friend class Layer;

        public:
            virtual ~Widget() {}
            virtual void OnProcessData() {};
            virtual void OnRender();
            virtual void Draw() = 0;

            void Enable();
            void Disable();
            inline bool IsEnabled() { return enable; }
            void Destroy();
            
            std::string GetWidgetName() const {return widget_name; }
            void SetWidgetName(const std::string& inWidgetName);

            //IPositionable Interface def implementation
            virtual ImVec2 GetPosition() const;
            virtual void SetPosition(ImVec2 inPos);

            virtual ImVec2 GetSize() const;
            virtual ImVec2 GetPixelSize() const;
            virtual void SetSize(ImVec2 inSize);

            virtual std::pair<UIBehaviourMode, UIBehaviourMode> GetBehaviourModes() const;
            virtual UIBehaviourMode GetPositionMode() const;
            virtual UIBehaviourMode GetSizeMode() const;

            virtual void SetBehaviourModes(UIBehaviourMode positionMode, UIBehaviourMode sizeMode);
            virtual void SetPositionMode(UIBehaviourMode positionMode);
            virtual void SetSizeMode(UIBehaviourMode sizeMode);

            virtual UIAnchor GetAnchorMode() const;
            virtual void SetAnchorMode(UIAnchor anchorMode);

            //sets cursor position based on stored position and updates size, so it can be used on Draw
            virtual void ApplyLayout();

            void SetContainer(ContainerWidget* ContainerWidget) { m_Container = ContainerWidget; }

        protected:
            virtual void OnCreation();
            virtual void OnDestroy(){};

            virtual void OnEnable(){};
            virtual void OnDisable(){};

        private:
            ImVec2 CalculateAnchorPoint();

            // Creador global de widgets ? Cada vez que creas un widget se asocia a un identifier global unico
            int unique_identifier = -1;
            bool enable = true;
            std::string layer_name = {"Default Layer"};
            std::string widget_name = {"Default Name"}; //For debug purposes mostly, I wanna know which widget is which

            PositionVars m_posVars;
            ContainerWidget* m_Container = nullptr;  //The widget that contains this widget. Null for root widgets
    };
}