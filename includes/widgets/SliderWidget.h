#pragma once
#include "Widget.h"

namespace indra_toolkit
{
    class SliderWidget : public Widget
    {
    public:
        SliderWidget(const std::string& label, float minValue, float maxValue, float initialValue);

        virtual void OnProcessData() override;
        virtual void Draw() override;

        float GetValue() const { return value; }

    private:
        std::string label;
        float minValue, maxValue;
        float value;
        float prev_value = value;
    };
}
