#pragma once

#include "imgui.h"
#include <string>


namespace indra_toolkit
{
    class Layer;

    class Widget
    {
        friend class Layer;

        public:
            virtual ~Widget() {}
            virtual void OnProcessData() {};
            virtual void OnRender() = 0;

            void Enable();
            void Disable();
            inline bool IsEnabled() { return enable; }
            void Destroy();
            
        protected:
            virtual void OnCreation();
            virtual void OnDestroy(){};

            virtual void OnEnable(){};
            virtual void OnDisable(){};

            // Creador global de widgets ? Cada vez que creas un widget se asocia a un identifier global unico
            int unique_identifier = -1;
            bool enable = true;
            std::string layer_name = {"Default Layer"};
    };
}