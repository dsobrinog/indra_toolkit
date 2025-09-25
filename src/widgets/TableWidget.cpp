#include "indra_toolkit/widgets/TableWidget.h"

indra_toolkit::TableWidget::TableWidget(const std::string &table_name, int column_number, int row_number)
    : Widget(),
      table_name(table_name),
      col_num(column_number),
      row_num(row_number),
      table_flags(ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg), // default flags
      show_title(true) // show table name by default
{
    SetSize(column_number, row_number);
}

indra_toolkit::TableWidget::~TableWidget() {}


void indra_toolkit::TableWidget::SetSize(int columns, int rows)
{
    col_num = columns;
    row_num = rows;
    cells.assign(row_num, std::vector<TableCell>(col_num));
}

void indra_toolkit::TableWidget::SetHeaders(const std::vector<std::string>& headers_in)
{
    headers = headers_in;
    if ((int)headers.size() < col_num)
        headers.resize(col_num, ""); // fill missing headers with empty
}

void indra_toolkit::TableWidget::SetCell(int row, int col, const std::string& value) {
    if (row < 0 || row >= row_num || col < 0 || col >= col_num) return;
    cells[row][col].Set(value);
}

void indra_toolkit::TableWidget::SetCell(int row, int col, std::string* ptr) {
    if (row < 0 || row >= row_num || col < 0 || col >= col_num) return;
    cells[row][col].Bind(ptr);
}

const std::string& indra_toolkit::TableWidget::GetCell(int row, int col) const {
    static std::string empty;
    if (row < 0 || row >= row_num || col < 0 || col >= col_num) return empty;
    return cells[row][col].Get();
}

void indra_toolkit::TableWidget::SetFlags(ImGuiTableFlags flags)
{
    table_flags = flags;
}

void indra_toolkit::TableWidget::ShowTitle(bool show)
{
    show_title = show;
}

void indra_toolkit::TableWidget::ShowHeaders(bool show)
{
    show_headers = show;
}

void indra_toolkit::TableWidget::OnProcessData()
{
    
}

void indra_toolkit::TableWidget::Draw()
{
    if (show_title && !table_name.empty())
        ImGui::Text("%s", table_name.c_str());

    if (ImGui::BeginTable(table_name.c_str(), col_num, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        // Setup headers
        for (int c = 0; c < col_num; c++)
        {
            std::string header = (c < (int)headers.size() && !headers[c].empty()) 
                                 ? headers[c] 
                                 : "Col " + std::to_string(c);
            ImGui::TableSetupColumn(header.c_str());
        }
        
        // Draw header row only if enabled
        if (show_headers)
            ImGui::TableHeadersRow();

        // Fill rows
        for (int r = 0; r < row_num; r++) {
            ImGui::TableNextRow();
            for (int c = 0; c < col_num; c++) {
                ImGui::TableSetColumnIndex(c);
                const TableCell& cell = cells[r][c];

                if (cell.custom_color) {
                    ImGui::PushStyleColor(ImGuiCol_Text, *cell.custom_color);
                    ImGui::Text("%s", cell.Get().c_str());
                    ImGui::PopStyleColor();
                } else {
                    ImGui::Text("%s", cell.Get().c_str()); // default style
                }
            }
        }

        ImGui::EndTable();
    }
}
