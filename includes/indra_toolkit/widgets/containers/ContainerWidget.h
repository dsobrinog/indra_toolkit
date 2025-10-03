#pragma once

#include "indra_toolkit/Widget.h"
#include <indra_toolkit/Utils.h>

#include <vector>
#include <memory>
#include <algorithm>
#include <imgui.h>


namespace indra_toolkit
{
    class ContainerWidget : public Widget
    {
    public:

        using Widget::Widget;

        virtual ~ContainerWidget()
        {
            ResetChilds();
        }

        virtual void OnProcessData() override;

        void AddChild(const std::shared_ptr<Widget> child) 
        {
            m_Children.push_back(child);
            child->SetContainer(this);
            child->SetOwningLayer(GetOwningLayer());
        }

        void AddChild(Widget* child)
        {
            // Wrap raw pointer into shared_ptr → container owns it
            std::shared_ptr<Widget> owned(child);

            owned->SetContainer(this);
            owned->SetOwningLayer(GetOwningLayer());

            m_Children.emplace_back(std::move(owned));
        }

        void RemoveChild(const std::shared_ptr<Widget>& child)
        {
            auto it = std::find(m_Children.begin(), m_Children.end(), child);
            if (it != m_Children.end())
            {
                (*it)->SetContainer(nullptr);
                m_Children.erase(it);
            }
        }

        void ResetChilds()
        {
            m_Children.clear();
        }

        /// @brief Create a widget in the layer and returns a reference to edit.
        /// @param widget_name Name of the widget 
        /// @param ...args Constructor arguments
        /// @return reference to the widget
        template<typename T, typename... Args>
        T& CreateChildWidget(Args&&... args)
        {
            static_assert(std::is_base_of<Widget, T>::value, 
                "T must derive from Widget");

            static_assert(std::is_constructible<T, Args...>::value,
                "Layer::CreateWidget: Wrong constructor arguments for widget type T");
                
            auto widget = std::make_shared<T>(std::forward<Args>(args)...);
            T& ref = *widget;
            Widget* baseWidget = static_cast<Widget*>(widget.get());
            baseWidget->SetContainer(this);
            baseWidget->SetOwningLayer(GetOwningLayer());
            
            m_Children.emplace_back(widget);
            return ref;
        }

        int GetNumOfChilds() const { return m_Children.size(); }
        //returns index of the child with the name passed. If not found it returns -1
        int GetIndexOfChild(const std::string& ChildName);

        ImVec2 GetItemPadding() const;
        void SetItemPadding(ImVec2 InPadding) { m_ItemPadding = InPadding; } 
        ImVec2 GetAllPaddingBetweenItems();

        ImVec2 GetWindowPadding() const { return m_WindowPadding; }
        void SetWindowPadding(ImVec2 InWindowPadding) { m_WindowPadding = InWindowPadding; }

        void SetBackgroundColor(ImVec4 bgColor) { m_bgColor = bgColor; }
        ImVec4 GetBackgroundColor() const { return m_bgColor; }

        virtual ImVec2 GetSize() const override;
        virtual ImVec2 GetPixelSize() const override;

        virtual void BeginStyle() override;
        virtual void EndStyle() override;

    protected:
        std::vector<std::shared_ptr<Widget>> m_Children;

        ImVec2 m_ItemPadding = { -1, -1 };          //Padding between the elements of the container (if its (-1, -1), we use ImGuiStyle ItemSpacing) 
        ImVec2 m_WindowPadding = { -1, -1};   
        ImVec4 m_bgColor = { 0.f, 0.f, 0.f, 0.f };  
    };
}
