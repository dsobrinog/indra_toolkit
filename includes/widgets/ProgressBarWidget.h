#pragma once
#include "Widget.h"

namespace indra_toolkit
{
    class ProgressBarWidget : public Widget
    {
    public:
        ProgressBarWidget(float fraction, const std::string& overlay = "");

        virtual void OnProcessData() override;
        virtual void OnRender() override;
        void SetFraction(float f) { fraction = f; }

    private:
        float fraction;
        std::string overlayText;
    };
}
