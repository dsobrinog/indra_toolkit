#include "indra_toolkit/Widget.h"

namespace indra_toolkit
{
    class HorizontalContainer;
}

namespace indra_toolkit
{
    // Basic Image widget
    class FEMainMenu : public Widget
    {
    public:
        FEMainMenu(Layer* owning_layer_);
        virtual ~FEMainMenu();

        virtual void Draw() override;
        void SetOpen(bool is_open_) { is_open = is_open_; }

    private:
        HorizontalContainer* main_horizontal_container;
        bool is_open = true;
    };
    
}
