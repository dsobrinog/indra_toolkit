#include "widgets/ImageWidget.h"

void indra_toolkit::ImageWidget::OnRender()
{
    if (!enable || texture == nullptr) return;
    ImGui::Image(texture, size);
}
