#include "indra_toolkit/widgets/text/EditableMultilineTextWidget.h"
#include "misc/cpp/imgui_stdlib.h"



namespace indra_toolkit
{

void EditableMultilineTextWidget::Draw()
{
    static std::string buffer;

    // Join vector into a single string with newlines
    buffer.clear();
    buffer = current_text;

    if(ImGui::InputTextMultiline(("##" + GetWidgetName()).c_str(), &buffer, GetPixelSize(), input_text_flags))
    {
        std::vector<std::string> newLines = SplitLines(buffer);

        std::vector<LineModifiedData> modifiedLines;

        size_t maxLines = std::max(stored_lines.size(), newLines.size());
        for (size_t i = 0; i < maxLines; i++) 
        {
            std::string oldLine = (i < stored_lines.size()) ? stored_lines[i] : "";
            std::string newLine = (i < newLines.size()) ? newLines[i] : "";

            if (oldLine != newLine) 
            {
                // ImGui::Text("Line %zu was modified", i + 1);
                modifiedLines.push_back({(int)i, oldLine, newLine});
                // you can also trigger a callback here
            }
        }

        if(modifiedLines.size() != 0 && line_modified_cb) 
        {
            line_modified_cb(modifiedLines);
        }

        stored_lines = std::move(newLines);
    }
}

void EditableMultilineTextWidget::SetText(const std::vector<std::string>& lines)
{
    current_text = CombineIntoText(lines); 
    previous_text = current_text;

    stored_lines = lines;
}

}