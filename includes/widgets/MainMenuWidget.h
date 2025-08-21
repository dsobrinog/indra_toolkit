#pragma once

#include "Widget.h"

#include <vector>
#include <functional>

namespace indra_toolkit
{
    struct MenuElement
    {
        std::string name;                           // Nombre del menú o item
        std::function<void()> callback = nullptr;   // Callback al seleccionar
        std::vector<MenuElement> childs;            // Submenús

        bool HasChild() const { return !childs.empty(); }
    };

    class MainMenuWidget : public Widget
    {
        public:
            virtual void OnProcessData() override;
            virtual void OnRender() override;

            // Añadir submenu
            void AddMenu(const MenuElement& menu);
            
        protected:
            std::vector<MenuElement> menus;

            void RenderMenuElement(const MenuElement& element);
    };
}