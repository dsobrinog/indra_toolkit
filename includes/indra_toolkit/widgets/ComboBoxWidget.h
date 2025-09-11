#pragma once
#include "indra_toolkit/Widget.h"
#include <vector>

namespace indra_toolkit
{
    class ComboBoxWidget : public Widget
    {
    public:

        ComboBoxWidget();

        virtual void Draw() override;

        std::string GetSelectedItem() const;
        void SetOptions(const std::vector<std::string>& init_vals) { options = init_vals; }
        
        void SetLabel(const std::string& label_) { label = label_; }

    private:
        std::vector<std::string> options;
        std::string label;
        int current_index = 0;
    };
}