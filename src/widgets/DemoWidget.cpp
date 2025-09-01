#include "indra_toolkit/widgets/DemoWidget.h"


void indra_toolkit::DemoWidget::OnProcessData()
{

}

void indra_toolkit::DemoWidget::Draw()
{
    // ImGui::Begin("Test");
    // ImGui::Text("Hello world");
    // ImGui::End();

    ImGui::ShowDemoWindow();
}