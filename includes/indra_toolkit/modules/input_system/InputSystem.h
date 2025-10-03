#pragma once
#include "indra_toolkit/ToolApplication.h"
#include "indra_toolkit/Module.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <utility>



namespace indra_toolkit
{
    enum class InputEventType
    {
        Pressed,
        Released,
        Held
    };

    enum class ModifierType
    {
        AllPresh,
        AnyPresh
    };

    class InputSystem : public Module
    {
    
    public:
        using Callback = std::function<void()>;
    
        InputSystem(ToolApplication* app_, ToolModules moduleIdentity_);
        ~InputSystem() = default;

        
        virtual void OnUpdate() override;
        virtual void OnShutdown() override;

        /// @brief Register a keyboard callback
        /// @param key @enum ImGuiKey
        /// @param eventType 
        /// @param callback 
        void RegisterKeyCallback(ImGuiKey key, InputEventType eventType, Callback callback)
        {
            key_callbacks[{key, eventType}].push_back(std::move(callback));
        }

        /// @brief Register a mouse button callback
        /// @param mouseButton 0 (Left), 1(Right), 2(Middle)
        /// @param eventType Pressed, Released or Held
        /// @param callback associated callback
        void RegisterMouseCallback(int mouseButton, InputEventType eventType, Callback callback)
        {
            mouse_callbacks[{mouseButton, eventType}].push_back(std::move(callback));
        }

        /// @brief Register a key combination callback (e.g., Ctrl+R)
        /// @param mainKey The main key (e.g., ImGuiKey_R)
        /// @param modifierKeys Vector of modifier keys (e.g., {ImGuiKey_LeftCtrl, ImGuiKey_RightCtrl})
        /// @param eventType Pressed, Released or Held
        /// @param callback associated callback
        void RegisterKeyCombinationCallback(ImGuiKey mainKey, const std::vector<ImGuiKey>& modifierKeys, InputEventType eventType, Callback callback, ModifierType mtype = ModifierType::AnyPresh)
        {
            combination_callbacks[{mainKey, modifierKeys, eventType, mtype}].push_back(std::move(callback));
        }

    private:
        void HandleKeyboardInputs();
        void HandleMouseInputs();
        void HandleCombinationInputs();
        bool AreModifiersPressed(const std::vector<ImGuiKey>& modifierKeys, ModifierType mt) const;
        
        struct KeyEvent
        {
            ImGuiKey key;
            InputEventType eventType;

            bool operator==(const KeyEvent& other) const noexcept
            {
                return key == other.key && eventType == other.eventType;
            }
        };

        struct MouseEvent
        {
            int button; // 0=Left, 1=Right, 2=Center
            InputEventType eventType;

            bool operator==(const MouseEvent& other) const noexcept
            {
                return button == other.button && eventType == other.eventType;
            }
        };

        struct CombinationEvent
        {
            ImGuiKey mainKey;
            std::vector<ImGuiKey> modifierKeys;
            InputEventType eventType;
            ModifierType modifierType = ModifierType::AllPresh;

            bool operator==(const CombinationEvent& other) const noexcept
            {
                return mainKey == other.mainKey && 
                       modifierKeys == other.modifierKeys && 
                       eventType == other.eventType &&
                       modifierType == other.modifierType;
            }
        };

        struct KeyEventHash
        {
            std::size_t operator()(const KeyEvent& e) const noexcept
            {
                return std::hash<int>()(static_cast<int>(e.key)) ^ (std::hash<int>()(static_cast<int>(e.eventType)) << 1);
            }
        };

        struct MouseEventHash
        {
            std::size_t operator()(const MouseEvent& e) const noexcept
            {
                return std::hash<int>()(e.button) ^ (std::hash<int>()(static_cast<int>(e.eventType)) << 1);
            }
        };

        struct CombinationEventHash
        {
            std::size_t operator()(const CombinationEvent& e) const noexcept
            {
                std::size_t hash = std::hash<int>()(static_cast<int>(e.mainKey));
                hash ^= std::hash<int>()(static_cast<int>(e.eventType)) << 1;
                
                for (auto modifier : e.modifierKeys) {
                    hash ^= std::hash<int>()(static_cast<int>(modifier)) << 1;
                }
                return hash;
            }
        };

        std::unordered_map<KeyEvent, std::vector<Callback>, KeyEventHash> key_callbacks;
        std::unordered_map<MouseEvent, std::vector<Callback>, MouseEventHash> mouse_callbacks;
        std::unordered_map<CombinationEvent, std::vector<Callback>, CombinationEventHash> combination_callbacks;
    };
}
