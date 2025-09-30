#include "indra_toolkit/widgets/MultiTableWidget.h"


using namespace indra_toolkit;

MultiTableWidget::MultiTableWidget(float spacing)
    : spacing(spacing), uniform_width(0.0f)
{
}

MultiTableWidget::~MultiTableWidget()
{
    for (auto* t : tables)
        delete t;
    tables.clear();
}

TableWidget* MultiTableWidget::AddTable(const std::string& name, int columns, int rows)
{
    TableWidget* table = new TableWidget(name, columns, rows);
    tables.push_back(table);
    return table;
}

TableWidget* MultiTableWidget::GetTable(size_t index)
{
    if (index >= tables.size())
        return nullptr;
    return tables[index];
}

void MultiTableWidget::OnProcessData()
{
    for (auto* t : tables)
        t->OnProcessData();
}

void MultiTableWidget::Draw()
{
    if (tables.empty())
        return;

    float total_width = ImGui::GetContentRegionAvail().x;
    float table_width = uniform_width > 0 ? uniform_width
                                          : (total_width - (tables.size() - 1) * spacing) / tables.size();

    for (size_t i = 0; i < tables.size(); i++)
    {
        ImGui::BeginGroup();

        // Force table width by setting a child window
        ImGui::BeginChild(("TableChild" + std::to_string(i)).c_str(), ImVec2(table_width, 0), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
        tables[i]->Draw();
        ImGui::EndChild();

        ImGui::EndGroup();

        if (i + 1 < tables.size())
            ImGui::SameLine(0.0f, spacing);
    }
}
