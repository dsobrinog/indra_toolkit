#include "widgets/CheckboxWidget.h"


indra_toolkit::CheckboxWidget::CheckboxWidget(const std::string& label, bool initialValue)
    : label(label), value(initialValue)
{}

void indra_toolkit::CheckboxWidget::Draw()
{
    ImGui::Checkbox(label.c_str(), &value);
}

