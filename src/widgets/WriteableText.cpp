#include "indra_toolkit/widgets/WriteableText.h"
#include "misc/cpp/imgui_stdlib.h"

namespace indra_toolkit
{

    void WriteableText::Draw()
    {
        if(is_open) ImGui::OpenPopup(popup_header.c_str());

        if (ImGui::BeginPopupModal(popup_header.c_str(), &is_open))
        {
            if(ImGui::InputText("Variable to search: ", &search_text))
            {

            }

            if(search_text != "")
            {
                search_button->OnRender();
            }

            ImGui::EndPopup();
        }
    }

    void WriteableText::OnSearchClicked()
    {
        search_CB(GetSearchText());
        is_open = false;
    }
}