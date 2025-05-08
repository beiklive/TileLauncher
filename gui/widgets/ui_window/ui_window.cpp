#include "ui_window.h"
#include "FramelessWindowHelper.h"
beiklive::Ui_Window::Ui_Window()
{
    resize(800, 600);

    #if BEIKLIVE_FRAMELESS
    setFrameless();
    #endif

}
#if BEIKLIVE_FRAMELESS
void beiklive::Ui_Window::setFrameless()
{
    FramelessWindowHelper helper(this);
    helper.setResizable(true);

}
#endif
