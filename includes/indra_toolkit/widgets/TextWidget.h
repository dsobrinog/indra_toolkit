
#pragma once

#include "indra_toolkit/Widget.h"
#include "indra_toolkit/Utils.h"

namespace indra_toolkit
{
    class TextWidget : public Widget 
    {
        std::string m_text;
        const std::string* m_text_ptr = nullptr;
    
    public:

        explicit TextWidget(const char* text)
            : m_text(std::string(text)), m_text_ptr(nullptr)
        {}   
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
        
        virtual void OnProcessData(){};
        virtual void Draw() override {
            ImGui::TextUnformatted(GetText().c_str());
        }
    };

}
