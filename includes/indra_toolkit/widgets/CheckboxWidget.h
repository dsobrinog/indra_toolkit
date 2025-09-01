#pragma once
#include "indra_toolkit/Widget.h"

namespace indra_toolkit
{
    class CheckboxWidget : public Widget
    {
    public:
        CheckboxWidget(const std::string& label, bool initialValue);

        virtual void OnRender() override;

        bool GetValue() const { return value; }

    private:
        std::string label;
        bool value;
    };
}
