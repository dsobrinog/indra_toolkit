#include "widgets/DemoWidget.h"


void indra_toolkit::DemoWidget::OnProcessData()
{

}

void indra_toolkit::DemoWidget::OnRender()
{
    // ImGui::Begin("Test");
    // ImGui::Text("Hello world");
    // ImGui::End();

    ImGui::ShowDemoWindow();
}