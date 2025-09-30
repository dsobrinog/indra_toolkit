#pragma once

#include "indra_toolkit/widgets/TableWidget.h"
#include <vector>

namespace indra_toolkit
{
    class MultiTableWidget : public Widget
    {
    public:
        MultiTableWidget(float spacing = 20.0f);
        virtual ~MultiTableWidget();

        virtual void OnProcessData() override;
        virtual void Draw() override;

        // Add a new table to the multi-widget
        TableWidget* AddTable(const std::string& name, int columns, int rows);

        // Access a table by index
        TableWidget* GetTable(size_t index);

        // Layout config
        void SetSpacing(float s) { spacing = s; }
        void SetUniformWidth(float w) { uniform_width = w; }

        // Number of tables
        size_t TableCount() const { return tables.size(); }

    private:
        std::vector<TableWidget*> tables;
        float spacing;          // horizontal space between tables
        float uniform_width;    // optional fixed width per table (0 = auto)
    };
}
