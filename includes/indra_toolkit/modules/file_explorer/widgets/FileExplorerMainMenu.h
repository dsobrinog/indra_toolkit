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
        FEMainMenu();
        virtual ~FEMainMenu();

        virtual void Draw() override;

    private:
        HorizontalContainer* MainHorizontalContainer;
        
    };
    
}
