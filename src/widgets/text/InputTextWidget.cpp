#include "indra_toolkit/widgets/text/InputTextWidget.h"
#include "misc/cpp/imgui_stdlib.h"

#include <sstream>

namespace indra_toolkit 
{
    
void InputTextWidget::Draw()
{
    if(ImGui::InputTextMultiline(("##" + GetWidgetName()).c_str(), &current_text, GetPixelSize(), input_text_flags))
    // if(ImGui::InputText(("##" + GetWidgetName()).c_str(), &current_text, input_text_flags))
    {

    }
}

void InputTextWidget::SetText(const std::vector<std::string>& lines)
{
    std::ostringstream oss;  
    for (size_t i = 0; i < lines.size(); ++i) {
        if (i > 0) oss << '\n';
        oss << lines[i];
    }

    current_text = oss.str(); 
}

} // namespace indra_toolkit
