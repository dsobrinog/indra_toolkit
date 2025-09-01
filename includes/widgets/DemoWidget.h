#pragma once

#include "Widget.h"

namespace indra_toolkit
{
    class DemoWidget : public Widget
    {
            virtual void OnProcessData() override;
            virtual void Draw() override;
    };
}