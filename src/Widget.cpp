#include "Widget.h"

void indra_toolkit::Widget::Enable()
{
    enable = true;
    OnEnable();
}

void indra_toolkit::Widget::Disable()
{
    enable = false;
    OnDisable();
}

void indra_toolkit::Widget::OnCreation()
{
    
}

// VINCULAR CON EL DESTRUCTOR
void indra_toolkit::Widget::Destroy()
{
    enable = false;
    OnDestroy();
}


