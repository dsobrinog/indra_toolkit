#pragma once

#include "indra_toolkit/Module.h"
#include "indra_toolkit/modules/resource_management/image/ImageLoader.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <GL/gl.h>
#include "imgui.h"

namespace indra_toolkit
{
    class CursorManager : public Module
    {
    public:
        using CursorCallback = std::function<void(CursorManager&)>;

        CursorManager(ToolApplication* app_, ToolModules moduleIdentity_) 
            : Module(app_, ToolModules::M_CursorManager) 
        {
            EnableTick(true);
        }

        virtual ~CursorManager() = default;

        bool OnInit() override 
        {
            // Initialize with default cursor
            current_cursor = ImGuiMouseCursor_Arrow;
            return true;
        }

        void OnUpdate() override 
        {
            // Apply the current cursor setting
            if (cursor_override_enabled && current_cursor != ImGuiMouseCursor_None)
            {
                ImGui::SetMouseCursor(current_cursor);
            }
        }

        // ===== Cursor Management Functions =====

        /// @brief Set the current mouse cursor type
        /// @param cursor The ImGuiMouseCursor_ type to set
        void SetCursor(ImGuiMouseCursor cursor)
        {
            current_cursor = cursor;
            cursor_override_enabled = (cursor != ImGuiMouseCursor_None);
        }

        /// @brief Reset to default arrow cursor and disable override
        void ResetCursor()
        {
            current_cursor = ImGuiMouseCursor_Arrow;
            cursor_override_enabled = false;
        }

        /// @brief Enable or disable cursor override
        /// @param enable If true, module will override ImGui's automatic cursor handling
        void EnableCursorOverride(bool enable)
        {
            cursor_override_enabled = enable;
        }

        /// @brief Check if cursor override is currently enabled
        bool IsCursorOverrideEnabled() const { return cursor_override_enabled; }

        /// @brief Get the current cursor type
        ImGuiMouseCursor GetCurrentCursor() const { return current_cursor; }

        // ===== Convenience Functions for Common Cursors =====

        void SetArrow() { SetCursor(ImGuiMouseCursor_Arrow); }
        void SetTextInput() { SetCursor(ImGuiMouseCursor_TextInput); }
        void SetResizeAll() { SetCursor(ImGuiMouseCursor_ResizeAll); }
        void SetResizeNS() { SetCursor(ImGuiMouseCursor_ResizeNS); }
        void SetResizeEW() { SetCursor(ImGuiMouseCursor_ResizeEW); }
        void SetResizeNESW() { SetCursor(ImGuiMouseCursor_ResizeNESW); }
        void SetResizeNWSE() { SetCursor(ImGuiMouseCursor_ResizeNWSE); }
        void SetHand() { SetCursor(ImGuiMouseCursor_Hand); }
        void SetNotAllowed() { SetCursor(ImGuiMouseCursor_NotAllowed); }

    private:
        ImGuiMouseCursor current_cursor = ImGuiMouseCursor_Arrow;
        bool cursor_override_enabled = false;
};
}
