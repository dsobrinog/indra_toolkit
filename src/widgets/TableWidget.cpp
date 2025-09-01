#include "indra_toolkit/widgets/TableWidget.h"



indra_toolkit::TableWidget::TableWidget(const std::string &table_name, int column_number, int row_number): Widget()
{
    
}

indra_toolkit::TableWidget::~TableWidget() {}

void indra_toolkit::TableWidget::OnProcessData()
{
}

void indra_toolkit::TableWidget::OnRender() 
{
    if (ImGui::BeginTable("MiTabla", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        // Encabezado
        ImGui::TableSetupColumn("IFC");
        ImGui::TableSetupColumn("TIME");
        ImGui::TableSetupColumn("CYCLE");
        ImGui::TableHeadersRow(); // dibuja los encabezados

        // Fila 1
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0); ImGui::Text("1");
        ImGui::TableSetColumnIndex(1); ImGui::Text("2");
        ImGui::TableSetColumnIndex(2); ImGui::Text("3");

        // Fila 2
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0); ImGui::Text("4");
        ImGui::TableSetColumnIndex(1); ImGui::Text("5");
        ImGui::TableSetColumnIndex(2); ImGui::Text("6");

        ImGui::EndTable();
    }
}