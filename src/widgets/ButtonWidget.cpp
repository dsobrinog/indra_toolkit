#include "widgets/ButtonWidget.h"

void indra_toolkit::ButtonWidget::Draw()
{
    ImGui::PushStyleColor(ImGuiCol_Button, m_BgColor);
    ImGui::PushStyleColor(ImGuiCol_Text, m_TextColor);

    if (ImGui::Button(m_Label.c_str(), GetPixelSize())) {
        if (m_Callback) m_Callback();
    }

    ImGui::PopStyleColor(2);
}