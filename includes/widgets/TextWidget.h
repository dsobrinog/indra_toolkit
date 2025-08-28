
#pragma once

#include "Widget.h"

namespace indra_toolkit
{
    class TextWidget : public Widget 
    {
        std::string m_text;
        const std::string* m_text_ptr = nullptr;
        ImVec2 m_Size;
    
    public:
        explicit TextWidget(const std::string& text)
            : m_text(text), m_text_ptr(nullptr)
        {}   

        explicit TextWidget(const std::string* text_ptr)
            : m_text(), m_text_ptr(text_ptr)
        {}


        void SetText(const std::string& text) 
        { 
            m_text = text; 
            m_text_ptr = nullptr; // now we own the text
        }

        void SetDynamicText(const std::string* _ptr)
        {
            m_text_ptr = _ptr;
        }

        const std::string& GetText() const
        {
            return m_text_ptr ? *m_text_ptr : m_text;
        }
        
        void SetSize(const ImVec2 size) {m_Size = size; }

        virtual void OnProcessData(){};
        virtual void OnRender() override {
            // ImGui::LabelText(m_Text.c_str(), "lorem ipsum");

            ImGui::TextUnformatted(GetText().c_str());
        }
    };

}
