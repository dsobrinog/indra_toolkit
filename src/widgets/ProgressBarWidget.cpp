#include "indra_toolkit/widgets/ProgressBarWidget.h"

indra_toolkit::ProgressBarWidget::ProgressBarWidget(float f, const std::string& overlay)
    : fraction(f), overlayText(overlay)
{}

void indra_toolkit::ProgressBarWidget::OnProcessData()
{
}

void indra_toolkit::ProgressBarWidget::OnRender()
{
    ImGui::ProgressBar(fraction, ImVec2(-1.0f, 0.0f), overlayText.c_str());
}
