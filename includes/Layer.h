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
    class Layer
    {
        public:
            Layer() {};
            Layer(std::string name, ImVec2& size, ImVec2& pos): layer_name(name), _size(size), _position(pos){};

            virtual void OnInit() {};
            virtual void OnEnd() {};

            virtual void OnProcess() = 0;
            virtual void OnRender() = 0;

            // --------------------------
            // API genérica (templatizada)
            // --------------------------

            template<typename T, typename... Args>
            T& AddWidget(const std::string& widget_name, Args&&... args)
            {
                static_assert(std::is_base_of<Widget, T>::value, 
                              "T must derive from Widget");

                auto widget = std::make_unique<T>(std::forward<Args>(args)...);
                T& ref = *widget;
                _widgets.emplace_back(widget_name, std::move(widget));
                return ref;
            }
            
            void AddWidget(const std::string& widget_name, std::unique_ptr<Widget> widget);
            void RemoveWidget(const std::string& name);
            Widget* GetWidget(const std::string& name);

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
                return AddWidget<ButtonWidget>(widget_name, text, callback);
            }


            

            void SetPosition(const ImVec2& pos) { _position = pos; }
            void SetSize(const ImVec2& size) { _size = size; }

            void SetName(std::string name) { layer_name = std::move(name); }
            inline const std::string& GetName() { return layer_name; }

        protected:
            // Ordered storage of widgets
            std::vector<std::pair<std::string, std::unique_ptr<Widget>>> _widgets;

            int next_id = 0;
            std::string layer_name = { "Default Layer" };

            ImVec2 _position = ImVec2(0, 0);
            ImVec2 _size;
    };
}
