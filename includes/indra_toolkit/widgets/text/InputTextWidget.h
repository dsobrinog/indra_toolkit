#pragma once

#include "indra_toolkit/Widget.h"

#include <vector>

namespace indra_toolkit 
{

class InputTextWidget : public Widget
{
public:

    InputTextWidget(const std::string& text)
    : current_text(text)
    {
        
    }

    virtual void Draw() override;

    ImGuiInputTextFlags_ GetInputTextFlags() const { return input_text_flags; }
    void SetInputTextFlags(ImGuiInputTextFlags_ input_text_flags_) { input_text_flags = input_text_flags_; }

    void SetText(const std::string& in_text_) { current_text = in_text_; }
    void SetText(const std::vector<std::string>& lines);
    std::string GetText() const { return current_text; }

protected:
    ImGuiInputTextFlags_ input_text_flags = ImGuiInputTextFlags_ReadOnly; //By default, texts are read only
    std::string current_text;
};


} //indra_toolkit