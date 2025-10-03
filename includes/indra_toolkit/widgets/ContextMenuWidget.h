#pragma once
#include "indra_toolkit/Widget.h"
#include <functional>
#include <vector>
#include <string>

namespace indra_toolkit
{
    struct MenuItemData
    {
        const char* label;
        ImTextureID icon; // Texture ID
        std::function<void()> callback; // Action to execute
    };

    class ContextMenuWidget : public Widget
    {
    public:
        ContextMenuWidget(const PositionVars& posSettings, const std::string& widgetName, const char* popupName)
            : Widget(posSettings, widgetName), m_PopupName(popupName) {}

        void AddItem(const char* label, ImTextureID icon, std::function<void()> callback)
        {
            m_Items.push_back({ label, icon, callback });
        }

        bool IsOpen(){
            return is_active;
        }

        void Open()        {
            is_active = true;
        }

        void Close(){
            is_active = false;
        }

        void SetTextSize(float size){ txt_size = size;}

        void Draw() override
        {
            if(!is_active)
            {
                return;
            }

            ImGui::OpenPopup("ContextMenu");
            ImGui::SetClipboardText("debug");

            if (ImGui::BeginPopup("ContextMenu"))
            {
                 // Detect click izquierdo fuera del popup para cerrarlo
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows))
                {
                    ImGui::CloseCurrentPopup();
                    is_active = false;
                }
                
                if (txt_size > 0.0f)
                {
                    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]); // Default font, scale below
                    ImGui::SetWindowFontScale(txt_size);
                }

                for (auto& item : m_Items)
                {
                 
                    // if (item.icon)
                    // {
                    //     ImGui::Image(item.icon, ImVec2(15, 15));
                    //     ImGui::SameLine();
                    // }

                    if (ImGui::Selectable(item.label) || ImGui::IsItemClicked(ImGuiMouseButton_Right))
                    {
                        if (item.callback)
                        {
                            item.callback();
                            ImGui::CloseCurrentPopup();
                            is_active = false;
                            break;
                        }
                    }
                }

                if (txt_size > 0.0f)
                {
                    ImGui::SetWindowFontScale(1.0f);
                    ImGui::PopFont();
                }

                ImGui::EndPopup();
            }

            // Abrir el menú con clic derecho en cualquier lugar (fuera del menú)
            if (!is_active && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
            {
                Open();
            }

         
            

            // // Open popup when right-clicked over the widget
            // if (ImGui::BeginPopupContextItem(m_PopupName))
            // {
            //     for (auto& item : m_Items)
            //     {
            //         if (item.icon)
            //         {
            //             ImGui::Image(item.icon, ImVec2(20, 20));
            //             ImGui::SameLine();
            //         }

            //         if (ImGui::Selectable(item.label))
            //         {
            //             if (item.callback)
            //                 item.callback();
            //         }
            //     }
            //     ImGui::EndPopup();
            // }
        }

    protected:
        const char* m_PopupName;
        bool is_active = false;
        float txt_size = 0;
        std::vector<MenuItemData> m_Items;
    };
}
