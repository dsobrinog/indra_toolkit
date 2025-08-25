#pragma once

#include <imgui.h>

#include "Widget.h"
#include "widgets/ButtonWidget.h"

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <functional>

namespace indra_toolkit
{
    class ToolApplication;

    class Layer
    {
        public:
            Layer(ToolApplication* app): tool_app(app) {};
            Layer(std::string name, ImVec2& size, ImVec2& pos): layer_name(name), _size(size), _position(pos){};

            virtual void OnInit() {};
            virtual void OnEnd() {};

            virtual void OnProcess() = 0;
            virtual void OnRender() = 0;

            // --------------------------
            // Widget API
            // --------------------------


            /// @brief Create a widget in the layer and returns a reference to edit.
            /// @param widget_name Name of the widget 
            /// @param ...args Constructor arguments
            /// @return reference to the widget
            template<typename T, typename... Args>
            T& CreateWidget(Args&&... args)
            {
                static_assert(std::is_base_of<Widget, T>::value, 
                    "T must derive from Widget");

                static_assert(std::is_constructible<T, Args...>::value,
                    "Layer::CreateWidget: Wrong constructor arguments for widget type T");

                auto widget = std::make_unique<T>(std::forward<Args>(args)...);
                T& ref = *widget;
                _widgets.emplace_back(std::move(widget));
                return ref;
            }

            /// @brief Add a widget by reference (for heap allocated unique_ptr)
            Widget& AddWidget(std::unique_ptr<Widget> widget)
            {
                Widget& ref = *widget;
                _widgets.emplace_back(std::move(widget));
                return ref;
            }

            void RemoveWidget(Widget* widget);

            // --------------------------
            // API específica 
            // --------------------------


            /// @brief Crea y añade un botón a la layer.
            /// @param widget_name 
            /// @param text text in the button
            /// @param callback eventos on click
            /// @return referencia al widget
            ButtonWidget& AddButton(const std::string& widget_name, 
                                    const std::string& text, 
                                    std::function<void()> callback)
            {
                return CreateWidget<ButtonWidget>(text, callback);
            }


            

            void SetPosition(const ImVec2& pos) { _position = pos; }
            void SetSize(const ImVec2& size) { _size = size; }

            void SetName(std::string name) { layer_name = std::move(name); }
            inline const std::string& GetName() { return layer_name; }

        protected:
            ToolApplication* tool_app = nullptr;

            // Ordered storage of widgets
            std::vector<std::unique_ptr<Widget>> _widgets;

            int next_id = 0;
            std::string layer_name = { "Default Layer" };

            ImVec2 _position = ImVec2(0, 0);
            ImVec2 _size;
    };
}
