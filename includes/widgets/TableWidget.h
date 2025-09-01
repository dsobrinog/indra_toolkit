#pragma once

#include "Widget.h"


namespace indra_toolkit
{
    class TableWidget : public Widget
    {
        public:
            TableWidget(const std::string& table_name, int column_number, int row_number);
            virtual ~TableWidget(); 

            virtual void OnProcessData() override;
            virtual void Draw() override;
        protected:
            std::string table_name;
            int col_num, row_num;

    };
}