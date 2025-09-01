#include "indra_toolkit/widgets/SliderWidget.h"

indra_toolkit::SliderWidget::SliderWidget(const std::string & _label, float _minValue, float _maxValue, float _initialValue)
: label(_label), minValue(_minValue), maxValue(_maxValue), value(_initialValue)
{
    
}

void indra_toolkit::SliderWidget::OnProcessData()
{
    
}

void indra_toolkit::SliderWidget::Draw() 
{
    ImGui::SliderFloat(label.c_str(), &value, minValue, maxValue);
    
    // Now adjust FontGlobalScale using updated value
    // if (value != prev_value)
    // {
    //     ImGuiIO& io = ImGui::GetIO();
    //     float minScale = 0.5f;
    //     float maxScale = 2.0f;
    //     float normalized = (value - minValue) / (maxValue - minValue);
    //     io.FontGlobalScale = minScale + (maxScale - minScale) * normalized;

    //     std::cout << "on render value: " << value 
    //             << ", FontGlobalScale: " << io.FontGlobalScale << std::endl;
    // }
}
