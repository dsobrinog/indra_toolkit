#include "indra_toolkit/widgets/ButtonWidget.h"

void indra_toolkit::ButtonWidget::OnRender()
{
    ImGui::PushStyleColor(ImGuiCol_Button, m_BgColor);
    ImGui::PushStyleColor(ImGuiCol_Text, m_TextColor);

    if (ImGui::Button(m_Label.c_str(), m_Size)) {
        if (m_Callback) m_Callback();
    }

    ImGui::PopStyleColor(2);
}