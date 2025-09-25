#pragma once

#include "indra_toolkit/Widget.h"
#include "indra_toolkit/widgets/ButtonWidget.h"
#include <string>
#include <functional>
#include "imgui.h"

namespace indra_toolkit
{

class WriteableText : public Widget
{
public:
    WriteableText(std::function<void(const std::string&)> search_CB_, Layer* onwing_layer_, const std::string& button_header_ = "write: ") : search_CB(search_CB_)
    {
        SetOwningLayer(onwing_layer_);
        
        search_button = new ButtonWidget(button_header_, 
            [this]()
            {
                OnSearchClicked();
            }
        );

        search_button->SetOwningLayer(onwing_layer_);
    }

    virtual void Draw() override;

    bool IsOpen() const { return is_open; }
    void SetOpen(bool state_) { is_open = state_; }

    void SetPopupHeader(const std::string& header_) { popup_header = header_; }

    std::string GetSearchText() const { return search_text; }

    void OnSearchClicked();

protected:
    ButtonWidget* search_button = nullptr;
    std::function<void(const std::string&)> search_CB;
    std::string popup_header;
    std::string search_text;  // Static tooltip text
    bool is_open = false;
};

}
