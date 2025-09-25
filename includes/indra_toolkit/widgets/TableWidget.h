#pragma once

#include "indra_toolkit/Widget.h"

#include <vector>


namespace indra_toolkit
{
    struct TableCell {
    std::string value;       
    std::string* external;   // optional pointer (non-owning)

    ImVec4* custom_color = nullptr;

    TableCell() : value(""), external(nullptr), custom_color(nullptr) {}

    const std::string& Get() const {
        return external ? *external : value;
    }

    void Set(const std::string& v) {
        value = v;
        external = nullptr; // switch back to owned
    }

    void Bind(std::string* ptr) {
        external = ptr;
    }

    // Set optional color
    void SetColor(const ImVec4& c) {
        memcpy(custom_color, &c, sizeof(ImVec4));
    }

    // Clear color (use default)
    void ClearColor() {
        custom_color = nullptr;
    }
};

    class TableWidget : public Widget
    {
        public:

            TableWidget(const std::string& table_name, int column_number, int row_number);
            virtual ~TableWidget(); 

            virtual void OnProcessData() override;
            virtual void Draw() override;

            void SetSize(int columns, int rows);
            void SetHeaders(const std::vector<std::string>& headers_in);

            void SetCell(int row, int col, const std::string& value);
            void SetCell(int row, int col, std::string* ptr);
            const std::string& GetCell(int row, int col) const;

            void SetFlags(ImGuiTableFlags flags);
            void ShowTitle(bool show);
            void ShowHeaders(bool show);

        protected:
            // table metadata
            std::string table_name;
            int col_num, row_num;

            // UI config
            ImGuiTableFlags table_flags;
            bool show_title;
            bool show_headers;
            
            // data
            std::vector<std::string> headers;
            std::vector<std::vector<TableCell>> cells;
    };
}