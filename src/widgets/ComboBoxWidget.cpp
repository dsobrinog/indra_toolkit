#include "indra_toolkit/widgets/ComboBoxWidget.h"


namespace indra_toolkit
{
    ComboBoxWidget::ComboBoxWidget()
        : current_index(0), Widget()
    {

    }

    void ComboBoxWidget::Draw()
    {
        ImGui::BeginChild(GetWidgetName().c_str(), GetPixelSize(), ImGuiChildFlags_Borders);
        ImGui::SetNextItemWidth(GetPixelSize().x);
        std::string ComboId = "##" + label;
        if (ImGui::BeginCombo(ComboId.c_str(), options[current_index].c_str(), /*ImGuiComboFlags_WidthFitPreview |*/ ImGuiComboFlags_PopupAlignLeft | ImGuiComboFlags_HeightSmall))
        {
            for (int i = 0; i < options.size(); i++)
            {
                bool is_selected = (current_index == i);
                if (ImGui::Selectable(options[i].c_str(), is_selected))
                    current_index = i;
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        ImGui::EndChild();
    }

    std::string ComboBoxWidget::GetSelectedItem() const
    {
        if(current_index >= 0 && current_index < options.size())
        {
            return options[current_index];
        }

        return "";
    }
}