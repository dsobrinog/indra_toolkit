#pragma once 

#include "indra_toolkit/Widget.h"

#include <functional>
#include <vector>
#include <sstream>

namespace indra_toolkit
{

struct LineModifiedData
{
    LineModifiedData(int line_index_, const std::string& prev_value_, const std::string& new_value_) 
    : line_index(line_index_), prev_value(prev_value_), new_value(new_value_) {}

    int line_index;
    std::string prev_value;
    std::string new_value;
};

class EditableMultilineTextWidget : public Widget
{
public:

    EditableMultilineTextWidget(const std::string& text) : current_text(text) {}

    virtual void Draw() override;

    ImGuiInputTextFlags_ GetInputTextFlags() const { return input_text_flags; }
    void SetInputTextFlags(ImGuiInputTextFlags_ input_text_flags_) { input_text_flags = input_text_flags_; }

    void SetText(const std::string& in_text_) { current_text = in_text_; }
    void SetText(const std::vector<std::string>& lines);
    std::string GetText() const { return current_text; }

    void SetLineModifiedCallback(std::function<void(std::vector<LineModifiedData>)> callback_) { line_modified_cb = callback_; }

    // Split text into lines
    static std::vector<std::string> SplitLines(const std::string& text) 
    {
        std::vector<std::string> lines;
        std::istringstream iss(text);
        std::string line;

        while (std::getline(iss, line))
            lines.push_back(line);

        return lines;
    }

    // Combine text into lines
    static std::string CombineIntoText(const std::vector<std::string>& lines) 
    {
        std::ostringstream oss;  
        for (size_t i = 0; i < lines.size(); ++i) 
        {
            if (i > 0) oss << '\n';
            oss << lines[i];
        }

        return oss.str();
    }

protected:
    ImGuiInputTextFlags_ input_text_flags = ImGuiInputTextFlags_ReadOnly; //By default, texts are read only
    std::string current_text;
    std::string previous_text;

    std::vector<std::string> stored_lines;
    std::function<void(std::vector<LineModifiedData>)> line_modified_cb;
};

}