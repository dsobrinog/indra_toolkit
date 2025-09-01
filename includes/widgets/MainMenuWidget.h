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
        
        //X is the 
        ImVec2 SpacingFromPrevious = {0, 0};
        ImVec2 SpacingToNext = {0, 0};

        bool HasChild() const { return !childs.empty(); }
    };

    //No tendria que ser MainMenuWidgetBar ? Esto es una MainMenuBar con Menus dentro
    class MainMenuBarWidget : public Widget
    {
        public:
            virtual void OnProcessData() override;
            virtual void Draw() override;

            // Añadir submenu
            void AddMenu(const MenuElement& menu);
            
            void SetMenuPadding(const ImVec2& windowPadding) { m_windowPadding = windowPadding; }

        protected:
            std::vector<MenuElement> menus;

            void RenderMenuElement(const MenuElement& element);

        private:
            ImVec2 m_windowPadding = {-1, -1};
    };
}