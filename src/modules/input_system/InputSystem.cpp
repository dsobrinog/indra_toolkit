#include "indra_toolkit/modules/input_system/InputSystem.h"

using namespace indra_toolkit;

InputSystem::InputSystem(ToolApplication* app_, ToolModules moduleIdentity_)
    : Module(app_, moduleIdentity_)
{
    EnableTick(true);
};

// Called every tick
void InputSystem::OnUpdate()
{
    HandleKeyboardInputs();
    HandleMouseInputs();
    HandleCombinationInputs();
}

void InputSystem::OnShutdown()
{
    key_callbacks.clear();
    mouse_callbacks.clear();
    combination_callbacks.clear();
}

void InputSystem::HandleKeyboardInputs()
{
    for (auto& [event, callbacks] : key_callbacks)
    {
        bool trigger = false;
        switch (event.eventType)
        {
        case InputEventType::Pressed:
            trigger = ImGui::IsKeyPressed(event.key, false);
            break;

        case InputEventType::Released:
            trigger = ImGui::IsKeyReleased(event.key);
            break;

        case InputEventType::Held:
            trigger = ImGui::IsKeyDown(event.key);
            break;
        
        default:
            break;
        }

        if (trigger)
        {
            for (auto& cb : callbacks)
            {
                cb(); // Trigger callback
            }
        }
        
    }
}

void InputSystem::HandleMouseInputs()
{
    for (auto& [event, callbacks] : mouse_callbacks)
    {
        bool trigger = false;
        switch (event.eventType)
        {
            case InputEventType::Pressed:
                trigger = ImGui::IsMouseClicked(event.button, false);
                break;
            
            case InputEventType::Released:
                trigger = ImGui::IsMouseReleased(event.button);
                break;
            
            case InputEventType::Held:
                trigger = ImGui::IsMouseDown(event.button);
                break;

            default:
                break;
        }

        if(trigger)
        {
           for (auto& cb : callbacks)
           {
               cb(); //trigger mouse callbacks
           }
        }
    }

    
}
void InputSystem::HandleCombinationInputs()
{
    for (auto& [event, callbacks] : combination_callbacks)
    {
        bool trigger = false;
        
        // First check if all modifiers are pressed
        bool modifiersPressed = AreModifiersPressed(event.modifierKeys, event.modifierType);
        
        if (modifiersPressed)
        {
            switch (event.eventType)
            {
            case InputEventType::Pressed:
                trigger = ImGui::IsKeyPressed(event.mainKey, false);
                break;

            case InputEventType::Released:
                trigger = ImGui::IsKeyReleased(event.mainKey);
                break;

            case InputEventType::Held:
                trigger = ImGui::IsKeyDown(event.mainKey);
                break;
            
            default:
                break;
            }
        }

        if (trigger)
        {
            for (auto& cb : callbacks)
            {
                cb(); // Trigger callback
            }
        }
    }
}

bool InputSystem::AreModifiersPressed(const std::vector<ImGuiKey>& modifierKeys, ModifierType mt) const
{
    if (modifierKeys.empty()) 
        return true;

    if(mt == ModifierType::AnyPresh)
    {
        // At least one modifier must be down
        for (auto modifier : modifierKeys)
        {
            if (ImGui::IsKeyDown(modifier))
                return true;
        }

        return false;
    }
    else if(mt == ModifierType::AllPresh)
    {
        // All modifiers must be down
        for (auto modifier : modifierKeys)
        {
            if (!ImGui::IsKeyDown(modifier))
            {
                return false;
            }
        }

        return true;
    }
  
    return false;
}